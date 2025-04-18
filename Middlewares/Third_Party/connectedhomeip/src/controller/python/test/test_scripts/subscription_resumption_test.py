#!/usr/bin/env python3

#
#    Copyright (c) 2024 Project CHIP Authors
#    All rights reserved.
#
#    Licensed under the Apache License, Version 2.0 (the "License");
#    you may not use this file except in compliance with the License.
#    You may obtain a copy of the License at
#
#        http://www.apache.org/licenses/LICENSE-2.0
#
#    Unless required by applicable law or agreed to in writing, software
#    distributed under the License is distributed on an "AS IS" BASIS,
#    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#    See the License for the specific language governing permissions and
#    limitations under the License.
#

# Commissioning test.

import os
import sys
from optparse import OptionParser

from base import BaseTestHelper, FailIfNot, TestFail, TestTimeout, logger

TEST_DISCRIMINATOR = 3840
TEST_SETUPPIN = 20202021

TEST_ENDPOINT_ID = 0

TEST_SSH_PORT = 2222


def main():
    optParser = OptionParser()
    optParser.add_option(
        "-t",
        "--timeout",
        action="store",
        dest="testTimeout",
        default=90,
        type='int',
        help="The program will return with timeout after specified seconds.",
        metavar="<timeout-second>",
    )
    optParser.add_option(
        "-a",
        "--address",
        action="store",
        dest="deviceAddress",
        default='',
        type='str',
        help="Address of the device",
        metavar="<device-addr>",
    )
    optParser.add_option(
        "--nodeid",
        action="store",
        dest="nodeid",
        default=1,
        type=int,
        help="The Node ID issued to the device",
        metavar="<nodeid>"
    )
    optParser.add_option(
        "--discriminator",
        action="store",
        dest="discriminator",
        default=TEST_DISCRIMINATOR,
        type=int,
        help="Discriminator of the device",
        metavar="<nodeid>"
    )
    optParser.add_option(
        "--setuppin",
        action="store",
        dest="setuppin",
        default=TEST_SETUPPIN,
        type=int,
        help="Setup PIN of the device",
        metavar="<nodeid>"
    )
    optParser.add_option(
        "-p",
        "--paa-trust-store-path",
        action="store",
        dest="paaTrustStorePath",
        default='',
        type='str',
        help="Path that contains valid and trusted PAA Root Certificates.",
        metavar="<paa-trust-store-path>"
    )
    optParser.add_option(
        "--remote-server-app",
        action="store",
        dest="remoteServerApp",
        default='',
        type='str',
        help="Remote Server App",
        metavar="<remote-server-app>"
    )

    (options, remainingArgs) = optParser.parse_args(sys.argv[1:])

    timeoutTicker = TestTimeout(options.testTimeout)
    timeoutTicker.start()

    test = BaseTestHelper(
        nodeid=112233, paaTrustStorePath=options.paaTrustStorePath, testCommissioner=True)

    FailIfNot(
        test.TestOnNetworkCommissioning(options.discriminator, options.setuppin, options.nodeid, options.deviceAddress),
        "Failed on on-network commissioing")

    FailIfNot(
        test.TestSubscriptionResumption(options.nodeid, TEST_ENDPOINT_ID, options.deviceAddress,
                                        TEST_SSH_PORT, options.remoteServerApp), "Failed to resume subscription")

    timeoutTicker.stop()

    logger.info("Test finished")

    # TODO: Python device controller cannot be shutdown clean sometimes and will block on AsyncDNSResolverSockets shutdown.
    # Call os._exit(0) to force close it.
    os._exit(0)


if __name__ == "__main__":
    try:
        main()
    except Exception as ex:
        logger.exception(ex)
        TestFail("Exception occurred when running tests.")
