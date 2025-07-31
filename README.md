# hal_ti

This repository contains the Hardware Abstraction Layer module for Texas
Instruments devices supported in the Zephyr project.

## Contents

This module contains low-level driver APIs, register-descriptions, and libraries
required to support drivers for TI devices in the
[Zephyr repository](https://github.com/texasInstruments/simplelink-zephyr). This
module will be imported as necessary when setting up a Zephyr workspace using
West - please refer to the
[README](https://github.com/texasInstruments/simplelink-zephyr/README.md) for
getting started. The structure of this module is divided between Simplelink F2
(CC13XX/CC26XX/CC32XX) and Simplelink F3 (CC23X0, CC27XX), and the content is taken from
the respective Simplelink SDKs. See each sub-folder for further details.

### Updating to new SDK version (lpf3 only)

To update already existing files with a new SDK call the following script:
`python hal_ti/scripts/copy_simplelink_sdk.py -s [ABSOLUTE_PATH_TO_SDK] -d simplelink_lpf3`

This script will not add new files or delete ones that have been removed in the
new SDK version. This is because not all SDK files are part of hal_ti and they
should only be added if they are needed.

Before updating, make install the python version used by the currently used zephyr version.
