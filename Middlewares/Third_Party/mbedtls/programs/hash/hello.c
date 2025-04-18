/*
 *  Classic "Hello, world" demonstration program
 *
 *  Copyright The Mbed TLS Contributors
 *  SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-or-later
 */

#if !defined(MBEDTLS_CONFIG_FILE)
#include "mbedtls/config.h"
#else
#include MBEDTLS_CONFIG_FILE
#endif

#include "mbedtls/platform.h"

#if defined(MBEDTLS_MD5_C)
#include "mbedtls/md5.h"
#endif

#if !defined(MBEDTLS_MD5_C)
int main(void)
{
    mbedtls_printf("MBEDTLS_MD5_C not defined.\n");
    mbedtls_exit(0);
}
#else


int main(void)
{
    int i, ret;
    unsigned char digest[16];
    char str[] = "Hello, world!";

    mbedtls_printf("\n  MD5('%s') = ", str);

    if ((ret = mbedtls_md5_ret((unsigned char *) str, 13, digest)) != 0) {
        mbedtls_exit(MBEDTLS_EXIT_FAILURE);
    }

    for (i = 0; i < 16; i++) {
        mbedtls_printf("%02x", digest[i]);
    }

    mbedtls_printf("\n\n");

#if defined(_WIN32)
    mbedtls_printf("  Press Enter to exit this program.\n");
    fflush(stdout); getchar();
#endif

    mbedtls_exit(MBEDTLS_EXIT_SUCCESS);
}
#endif /* MBEDTLS_MD5_C */
