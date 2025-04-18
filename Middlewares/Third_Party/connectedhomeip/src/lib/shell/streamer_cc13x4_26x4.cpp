/*
 *
 *    Copyright (c) 2022 Project CHIP Authors
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */

/**
 *    @file
 *      Source implementation of an input / output stream for cc13xx_26xx targets
 */

#include "streamer.h"
#include <lib/shell/Engine.h>
#include <lib/shell/streamer.h>
#include <lib/support/CHIPMem.h>
#include <platform/CHIPDeviceLayer.h>

#include "ti_drivers_config.h"

#include <ti/drivers/UART2.h>

namespace chip {
namespace Shell {

#ifndef SHELL_STREAMER_APP_SPECIFIC

UART2_Handle sStreamUartHandle = NULL;

#if !MATTER_CC13XX_26XX_PLATFORM_LOG_ENABLED
extern "C" int cc13xx_26xxLogInit(void)
{
    return 0;
}

extern "C" void cc13xx_26xxVLog(const char * msg, va_list v)
{
    if (NULL != sStreamUartHandle)
    {
        static char sDebugUartBuffer[CHIP_CONFIG_LOG_MESSAGE_MAX_SIZE];
        size_t ret;

        ret = vsnprintf(sDebugUartBuffer, sizeof(sDebugUartBuffer), msg, v);
        if (0 < ret)
        {
            // PuTTY likes \r\n
            size_t len                = (ret + 2U) < sizeof(sDebugUartBuffer) ? (ret + 2) : sizeof(sDebugUartBuffer);
            sDebugUartBuffer[len - 2] = '\r';
            sDebugUartBuffer[len - 1] = '\n';

            UART2_write(sStreamUartHandle, sDebugUartBuffer, len, NULL);
        }
    }
}
#endif // !MATTER_CC13XX_26XX_PLATFORM_LOG_ENABLED

int streamer_cc13xx_26xx_init(streamer_t * streamer)
{
    UART2_Params uartParams;

    UART2_Params_init(&uartParams);
    // Most params can be default because we only send data, we don't receive
    uartParams.baudRate = 115200;

    sStreamUartHandle = UART2_open(CONFIG_UART_STREAMER, &uartParams);
    return 0;
}

ssize_t streamer_cc13xx_26xx_read(streamer_t * streamer, char * buf, size_t len)
{
    (void) streamer;
    size_t ret;

    UART2_read(sStreamUartHandle, buf, len, &ret);

    return ret;
}

ssize_t streamer_cc13xx_26xx_write(streamer_t * streamer, const char * buf, size_t len)
{
    (void) streamer;
    return UART2_write(sStreamUartHandle, buf, len, NULL);
}

static streamer_t streamer_cc13xx_26xx = {
    .init_cb  = streamer_cc13xx_26xx_init,
    .read_cb  = streamer_cc13xx_26xx_read,
    .write_cb = streamer_cc13xx_26xx_write,
};

streamer_t * streamer_get()
{
    return &streamer_cc13xx_26xx;
}

#endif // #ifndef SHELL_STREAMER_APP_SPECIFIC

} // namespace Shell
} // namespace chip
