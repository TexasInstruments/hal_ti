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
(CC13XX/CC26XX/CC32XX) and Simplelink F3 (CC23X0), and the content is taken from
the respective Simplelink SDKs. See each sub-folder for further details.
