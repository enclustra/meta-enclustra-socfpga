# Enclustra Linux Reference Design for Intel FPGA SoC

## Maintainer

Enclustra GmbH  [support@enclustra.com]

## License

See [License](meta-enclustra-module/COPYING.MIT)

## Changelog

| Date       | Version | Comment                                                                         |
|------------|---------|---------------------------------------------------------------------------------|
| xxx        | xxx     | First version |

## Description

This repository contains Yocto layers to generate Linux reference designs for following Enclustra products:
- [Enclustra Mercury+ AA1 product series](https://www.enclustra.com/en/products/system-on-chip-modules/mercury-aa1/).
- [Enclustra Mercury SA1 product series](https://www.enclustra.com/en/products/system-on-chip-modules/mercury-sa1/).
- [Enclustra Mercury+ SA2 product series](https://www.enclustra.com/en/products/system-on-chip-modules/mercury-sa2/).

The [meta-enclustra-module](meta-enclustra-module) Yocto layer can be included into an own project or the [meta-enclustra-refdes](meta-enclustra-refdes) Yocto layer can be used to generate a reference design. The reference design can be built by manually setting up bitbake or the provided [build.yml](build.yml) can be used in combination with [kas](https://kas.readthedocs.io/en/latest/#) tool.
The reference design is based on [meta-intel-fpga](https://git.yoctoproject.org/meta-intel-fpga) that uses following versions.

- Yocto: mickledore
- U-Boot: 2023.01
- Linux:  kernel 6.1.0

## FPGA Reference Designs for Microchip Libero

The generated binaries are compatible with the binaries of following reference designs:

- [Mercury+ AA1 PE3 Reference Design](https://github.com/enclustra/Mercury_AA1_PE3_Reference_Design)
- [Mercury+ AA1 ST1 Reference Design](https://github.com/enclustra/Mercury_AA1_ST1_Reference_Design)
- [Mercury+ AA1 PE1 Reference Design](https://github.com/enclustra/Mercury_AA1_PE1_Reference_Design)

- [Mercury SA1 PE1 Reference Design](https://github.com/enclustra/Mercury_SA1_PE1_Reference_Design)
- [Mercury SA1 PE3 Reference Design](https://github.com/enclustra/Mercury_SA1_PE3_Reference_Design)
- [Mercury SA1 ST1 Reference Design](https://github.com/enclustra/Mercury_SA1_ST1_Reference_Design)

- [Mercury+ SA2 PE3 Reference Design](https://github.com/enclustra/Mercury_SA2_PE3_Reference_Design)
- [Mercury+ SA2 ST1 Reference Design](https://github.com/enclustra/Mercury_SA2_ST1_Reference_Design)
- [Mercury+ SA2 PE1 Reference Design](https://github.com/enclustra/Mercury_SA2_PE1_Reference_Design)


## Host Requirements

### Host Operating System

This reference design was tested on following operating systems:

- Ubuntu 22.04

### Required Packages

Following packages are required for building this reference design on Ubuntu:

    gawk wget git diffstat unzip texinfo gcc build-essential chrpath socat cpio python3 python3-pip python3-pexpect xz-utils debianutils iputils-ping python3-git python3-jinja2 libegl1-mesa libsdl1.2-dev pylint3 xterm python3-subunit mesa-common-dev zstd liblz4-tool libyaml-dev libelf-dev python3-distutils

The packages can be installed with **sudo apt install \<package\>** command.
See [Yocto System Requirements](https://docs.yoctoproject.org/3.4.2/ref-manual/system-requirements.html?highlight=host) for more details about requirements for Linux distributions other than Ubuntu.

## Build Reference Design

### Supported Machine Targets

The product model can be specified as target device (variable: **MACHINE**). Following product models are supported:

- refdes-me-aa1-270-2i2-d11e-nfx3-pe1
- refdes-me-aa1-270-2i2-d11e-nfx3-pe3
- refdes-me-aa1-270-2i2-d11e-nfx3-st1
- refdes-me-aa1-270-3e4-d11e-nfx3-pe1
- refdes-me-aa1-270-3e4-d11e-nfx3-pe3
- refdes-me-aa1-270-3e4-d11e-nfx3-st1
- refdes-me-aa1-480-2i3-d12e-nfx3-pe1
- refdes-me-aa1-480-2i3-d12e-nfx3-pe3
- refdes-me-aa1-480-2i3-d12e-nfx3-st1
- refdes-me-sa1-c6-7i-d10-pe1
- refdes-me-sa1-c6-7i-d10-pe3
- refdes-me-sa1-c6-7i-d10-st1
- refdes-me-sa2-d6-7i-d11-pe1
- refdes-me-sa2-d6-7i-d11-pe3
- refdes-me-sa2-d6-7i-d11-st1


### Supported Enclustra Base Boards

Following base boards are supported:

- pe1 ([Mercury+ PE1](https://www.enclustra.com/en/products/base-boards/mercury-pe1-200-300-400))
- pe3 ([Mercury+ PE3](https://www.enclustra.com/en/products/base-boards/mercury-pe3))
- st1 ([Mercury+ ST1](https://www.enclustra.com/en/products/base-boards/mercury-st1))

### Accelerate Build

To reuse the downloaded files and built packages for further builds, the **DL_DIR** and **SSTATE_DIR** variable can be set to a local directory. If this project is built for the first time, these directories must be created manually. If the variables are not set, the default directories in the build directory are used.

As example:

    export SSTATE_DIR="${HOME}/yocto-cache/mickledore-arm-ss"
    export DL_DIR="${HOME}/yocto-cache/mickledore-arm-dl"

### KAS

The recommended build flow is to use kas, which is a Python based tool that provides an easy mechanism to setup a bitbake project. The configuration file [build.yml](build.yml) provides all required settings. See [documentation](https://kas.readthedocs.io/en/latest/command-line.html) for more details.

#### Installation

    pip install kas
    export PATH=$PATH:${HOME}/.local/bin

#### Usage \#1

Use following command to build the target specified in the build.yml file.

    kas build build.yml

#### Usage \#2

Use following command to specify the bitbake command to be executed. **MACHINE** variable can be overridden according to section [Supported Machine Targets](#supported-machine-targets).

    kas shell build.yml -c 'MACHINE=refdes-me-sa1-c6-7i-d10-pe1 bitbake image-minimal-hwtest'

Note that the image [image-minimal-hwtest](meta-enclustra-refdes/recipes-core/images/image-minimal-hwtest.bb) can be replaced by any available image recipe. Following are a few examples provided by openembedded-core layer:
- core-image-base
- core-image-minimal
- core-image-minimal-dev
- core-image-x11

#### Usage \#3

The tool kas can be used to checkout the repositories and setup the build directory. The build process can be started independently with bitbake as shown in following example.

    kas checkout kas-project.yml
    source openembedded-core/oe-init-build-env
    MACHINE=refdes-me-sa1-c6-7i-d10-pe1 bitbake image-minimal-hwtest

## Deployment

The OpenEmbedded Image Creator (wic) creates a partitioned image file for SD card/eMMC. The partitions are configured in the OpenEmbedded kickstart file ([sdimage-enclustra-arria10.wks](meta-enclustra-refdes/wic/sdimage-enclustra-arria10.wks) / [sdimage-enclustra-cyclonev.wks](meta-enclustra-refdes/wic/sdimage-enclustra-cyclonev.wks)). The image file to be deployed on SD card/eMMC can be found in **build/tmp-glibc/deploy/images/\<MACHINE\>** directory, e.g. **image-minimal-hwtest-refdes-me-sa1-c6-7i-d10-pe1.wic**.


### Creating a Bootable SD Card

Copy the image file to a SD card e.g.

    dd if=image-minimal-hwtest-refdes-me-sa1-c6-7i-d10-pe1.wic of=<device> && sync

Note that the device of the SD card (\<device\>) needs to be replaced with the SD card device on your host (e.g. /dev/sdd).

### eMMC Memory

TODO


### QSPI flash ###

TODO


## Login on Target

Login with **root** as user name, no password is set.

## Devicetree

Following list show all devicetree include files added by meta-enclustra-module:

| File name                            | Description |
|--------------------------------------|-------------|
| [TODO.dtsi](TODO)                    | TODO |


## Patches

### U-Boot

Following U-Boot patches are added.

| Patch Name                                                | Description |
|-----------------------------------------------------------|-------------|
| [0001-TODO.patch](im-a-broken-link)                       | TODO |

### Linux Kernel

Following Linux kernel patches are added.

| Patch Name                                                | Description |
|-----------------------------------------------------------|-------------|
| [0001-TODO.patch](im-a-broken-link)                       | TODO |

## Additional Information

### Ethernet MAC address configuration

Each Enclustra module is delivered with two unique MAC addresses stored in the EEPROM. During the boot process, these MAC addresses are automatically read by U-Boot and configured to be used by U-Boot and Linux.

### Reading Serial Number of Module

The serial number of the module can be read by following command:

    cat /sys/bus/i2c/devices/1-0064/serial

The serial number is reported as follows:

    248173

### Read OTP region of EEPROM

The one time programmable region of the EEPROM contains the serial number, MAC address and information about the module. A detailed description can be found in the user manual of the module. The entire region can be read by following command:

    cat /sys/bus/i2c/devices/1-0064/otp

The 512 bits of the OTP region are reported as follows:

    00 03 C9 6D
    03 39 00 01
    00 88 51 23
    77 FF FF FF
    20 B0 F7 07
    92 DA FF FF
    FF FF FF FF
    FF FF FF FF
    FF FF FF FF
    FF FF FF FF
    FF FF FF FF
    FF FF FF FF
    FF FF FF FF
    FF FF FF FF
    FF FF FF FF
    FF FF FF FF

### Rootfs Partition Size

The size of the rootfs partition is set to 500 Mbyte by default. To change the partition size, the OpenEmbedded kickstart file ([sdimage-enclustra-arria10.wks](meta-enclustra-refdes/wic/sdimage-enclustra-arria10.wks) / [sdimage-enclustra-cyclonev.wks](meta-enclustra-refdes/wic/sdimage-enclustra-cyclonev.wks)) needs to be modified. The partition size is defined by **--fixed-size** parameter as shown below.

```
part / --source rootfs --ondisk mmcblk --fstype=ext4 --label root --align 1024 --fixed-size 500M
```

### Configure SI5338 clock generator on Mercury+ PE1 and Mercury+ ST1 base board

The U-Boot patch [0006-Add-SI5338-configuration.patch](meta-enclustra-module/recipes-bsp/u-boot/files/0006-Add-SI5338-configuration.patch) adds support to configure the clock generator device. To enable the configuration, follow the steps below:

1. Create a configuration with Skyworks [ClockBuilder Pro software](https://www.skyworksinc.com/Application-Pages/Clockbuilder-Pro-Software) and export the C code header file.
2. Copy the exported header file to **meta-enclustra-module/recipe_bsp/u-boot/files/** directory and overwrite the example file [Si5338-RevB-Registers.h](meta-enclustra-module/recipes-bsp/u-boot/files/Si5338-RevB-Registers.h)
3. Make following changes to file [meta-enclustra-module/recipes-bsp/u-boot/files/configs/socfpga_enclustra_mercury_*_defconfig](meta-enclustra-module/recipes-bsp/u-boot/files/configs/socfpga_enclustra_mercury_sa1_mmc_defconfig):

       CONFIG_SI5338_CONFIGURATION=y

## Known Issues:

TODO
