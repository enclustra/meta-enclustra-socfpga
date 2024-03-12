# Enclustra Linux Reference Design for Intel FPGA SoC

## Maintainer

Enclustra GmbH  [support@enclustra.com]

## License

See [License](meta-enclustra-module/COPYING.MIT)

## Changelog

Date       | Version       | Comment
---------- | ------------- | -------------
29.02.2024 | 2023.1_v1.0.0 | First release

## Introduction

This repository contains Yocto layers to generate Linux reference designs for following Enclustra SoC module families:
- [Enclustra Mercury+ AA1 product series](https://www.enclustra.com/en/products/system-on-chip-modules/mercury-aa1/).
- [Enclustra Mercury SA1 product series](https://www.enclustra.com/en/products/system-on-chip-modules/mercury-sa1/).
- [Enclustra Mercury+ SA2 product series](https://www.enclustra.com/en/products/system-on-chip-modules/mercury-sa2/).

The reference designs are compatible with following base boards:

- [Enclustra Mercury+ PE1](https://www.enclustra.com/en/products/base-boards/mercury-pe1-200-300-400)
- [Enclustra Mercury+ PE3](https://www.enclustra.com/en/products/base-boards/mercury-pe3)
- [Enclustra Mercury+ ST1](https://www.enclustra.com/en/products/base-boards/mercury-st1)

This documentation explains how this rererence design can be used and does not go into details of the Yocto project. See [Yocto Project Manual](https://docs.yoctoproject.org) for more information about the Yocto project.

The [meta-enclustra-module](meta-enclustra-module) Yocto layer contains everything required to run Linux on Enclustra modules equipped with Intel SoCs. This layer can be included into an own project (see [Integrate meta-enclustra-module Layer into user Project](#integrate-meta-enclustra-module-layer-into-user-project)). The [meta-enclustra-refdes](meta-enclustra-refdes) Yocto layer builds up on this layer and can be used to generate a reference design using prebuilt binaries (see [Reference Designs for Intel Quartus II](#reference-designs-for-intel-quartus-ii)). These reference designs can be built by manually setting up bitbake or the provided [build.yml](build.yml) can be used in combination with [kas](https://kas.readthedocs.io/en/latest/#) tool.

The reference design is based on [meta-intel-fpga](https://git.yoctoproject.org/meta-intel-fpga) that uses following versions:

- Yocto: mickledore
- U-Boot: 2023.01
- Linux kernel: 6.1.0

## Supported Devices

Family          | Module , Revision | Base Boards
--------------- | ----------------- | --------------
Intel Cyclone V | Mercury  SA1 , R3 | Mercury+ PE1 / Mercury+ PE3 / Mercury+ ST1
Intel Cyclone V | Mercury+ SA2 , R1 | Mercury+ PE1 / Mercury+ PE3 / Mercury+ ST1
Intel Arria 10  | Mercury+ AA1 , R2 | Mercury+ PE1 / Mercury+ PE3 / Mercury+ ST1

## Reference Designs for Intel Quartus II

The `[meta-enclustra-refdes](meta-enclustra-refdes) Yocto layer in this reference design uses prebuilt binaries of following reference designs:

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

The packages can be installed with `sudo apt install <package>` command.
See [Yocto System Requirements](https://docs.yoctoproject.org/3.4.2/ref-manual/system-requirements.html?highlight=host) for more details about requirements for Linux distributions other than Ubuntu.

## Build Reference Design

### KAS

The recommended build flow is to use kas, which is a Python based tool that provides an easy mechanism to setup a bitbake project. The configuration file [build.yml](build.yml) provides all required settings. See [kas documentation](https://kas.readthedocs.io/en/latest/command-line.html) for more details.

#### Installation

    pip install kas
    export PATH=$PATH:${HOME}/.local/bin

#### Usage \#1

Use following command to build the target specified in the build.yml file.

    kas build build.yml

#### Usage \#2

Use following command to specify the bitbake command to be executed. `MACHINE` and `UBOOT_CONFIG` variable can be overridden according to section [Supported Machine Targets](#supported-machine-targets) and [Supported Boot Modes](#supported-boot-modes).

    kas shell build.yml -c 'MACHINE=refdes-me-sa1-c6-7i-d10-pe1 UBOOT_CONFIG=qspi bitbake image-minimal-refdes'

Note that the image [image-minimal-refdes](meta-enclustra-refdes/recipes-core/images/image-minimal-refdes.bb) can be replaced by any available image recipe. Following are a few examples provided by openembedded-core layer:
- core-image-base
- core-image-minimal
- core-image-minimal-dev

#### Usage \#3

The tool kas can be used to checkout the repositories and setup the build directory. The build process can be started independently with bitbake as shown in following example.

    kas checkout build.yml
    source openembedded-core/oe-init-build-env
    export BB_ENV_PASSTHROUGH_ADDITIONS="MACHINE UBOOT_CONFIG DL_DIR SSTATE_DIR"
    export MACHINE=refdes-me-sa1-c6-7i-d10-pe1
    export UBOOT_CONFIG=qspi
    bitbake image-minimal-refdes

### Supported Machine Targets

Following product models are supported:

Machine Name                        | Module                   | Base Board
----------------------------------- | ------------------------ | -----------
refdes-me-aa1-270-2i2-d11e-nfx3-pe1 | ME-AA1-270-2I2-D11E-NFX3 | ME-PE1-*
refdes-me-aa1-270-2i2-d11e-nfx3-pe3 | ME-AA1-270-2I2-D11E-NFX3 | ME-PE3-*
refdes-me-aa1-270-2i2-d11e-nfx3-st1 | ME-AA1-270-2I2-D11E-NFX3 | ME-ST1-W
refdes-me-aa1-270-3e4-d11e-nfx3-pe1 | ME-AA1-270-3E4-D11E-NFX3 | ME-PE1-*
refdes-me-aa1-270-3e4-d11e-nfx3-pe3 | ME-AA1-270-3E4-D11E-NFX3 | ME-PE3-*
refdes-me-aa1-270-3e4-d11e-nfx3-st1 | ME-AA1-270-3E4-D11E-NFX3 | ME-ST1-W
refdes-me-aa1-480-2i3-d12e-nfx3-pe1 | ME-AA1-480-2I3-D12E-NFX3 | ME-PE1-*
refdes-me-aa1-480-2i3-d12e-nfx3-pe3 | ME-AA1-480-2I3-D12E-NFX3 | ME-PE3-*
refdes-me-aa1-480-2i3-d12e-nfx3-st1 | ME-AA1-480-2I3-D12E-NFX3 | ME-ST1-W
refdes-me-sa1-c6-7i-d10-pe1         | ME-SA1-C6-7I-D10         | ME-PE1-*
refdes-me-sa1-c6-7i-d10-pe3         | ME-SA1-C6-7I-D10         | ME-PE3-*
refdes-me-sa1-c6-7i-d10-st1         | ME-SA1-C6-7I-D10         | ME-ST1-W
refdes-me-sa2-d6-7i-d11-pe1         | ME-SA2-D6-7I-D11         | ME-PE1-*
refdes-me-sa2-d6-7i-d11-pe3         | ME-SA2-D6-7I-D11         | ME-PE3-*
refdes-me-sa2-d6-7i-d11-st1         | ME-SA2-D6-7I-D11         | ME-ST1-W

The product model can be specified as target device via `MACHINE` variable. When [kas](#kas) is used as build tool, the target is set in the [build.yml](build.yml) file as shown below. All supported targets are included in the file as comment.

```
machine: refdes-me-aa1-270-2i2-d11e-nfx3-pe1
```

### Supported Boot Modes

The boot mode can be selected by `UBOOT_CONFIG` variable. When [kas](#kas) is used as build tool, the boot mode is set in the [build.yml](build.yml) file as shown below. All supported boot modes are included in the file as comment.

```
env:
    UBOOT_CONFIG: sdmmc
```

Following boot modes are supported:

Module   | Supported Boot Modes
-------- | -------------------
ME-AA1-* | sdmmc\(\*\), emmc, qspi
ME-SA1-* | sdmmc\(\*\), emmc, qspi
ME-SA2-* | sdmmc, qspi

\(\*\) see [Known Issues](#2-sd-card-access-is-not-reliable)

### Accelerate Build

To reuse the downloaded files and built packages for further builds, the `DL_DIR` and `SSTATE_DIR` variable can be set to a local directory. If this project is built for the first time, these directories must be created manually. If the variables are not set, the default directories in the build directory are used.

As example:

    export SSTATE_DIR="${HOME}/yocto-cache/mickledore-arm-ss"
    export DL_DIR="${HOME}/yocto-cache/mickledore-arm-dl"

## Deployment

This chapter describes how to prepare the hardware to boot from different boot media, using the binaries generated by this reference design.

### Generated Binary Files

After the reference design was built successfully, the generated files can be found in `build/tmp-glibc/deploy/images/<MACHINE>` directory. The \<MACHINE\> variable depends on your selected build target (see [Supported Machine Targets](#supported-machine-targets)).

### SD Card

The OpenEmbedded Image Creator (wic) creates a partitioned image file for SD card/eMMC. The partitions are configured in the OpenEmbedded kickstart file ([sdimage-enclustra-arria10.wks](meta-enclustra-refdes/wic/sdimage-enclustra-arria10.wks) / [sdimage-enclustra-cyclonev.wks](meta-enclustra-refdes/wic/sdimage-enclustra-cyclonev.wks)). The image file to be deployed on SD card/eMMC is named `*.wic` , e.g. `image-minimal-refdes-refdes-me-sa1-c6-7i-d10-pe1.wic`.

The partitions are configured in the kickstart file as follows:

Partition | Type       | Size      | Usage
--------- | ---------- | --------- | -----
1         | FAT        | 50 Mbyte  | Boot partition
2         | RAW (0xA2) | 2 Mbyte   | SPL bootloader
3         | ext4       | 400 Mbyte | Root file system

Create a bootable SD card following the instructions in the Yocto manual: https://docs.yoctoproject.org/dev-manual/bmaptool.html
```
$ cd <folder where the .bmap file resides>
$ bmaptool copy image-minimal-refdes-refdes-me-sa1-c6-7i-d10-pe1.wic /dev/sdX`
```

Note that the device of the SD card (\<device\>) needs to be replaced with the SD card device on your host (e.g. /dev/sdd). Figure out the available devices with `lsblk` in the linux shell.

### eMMC Memory

On the Mercury SA1-R3 and Mercury AA1+ modules the MMC bus lines are shared between eMMC flash and SD card. It is not possible to simultaneously access the SD card and eMMC memory. In the following approach an SD card is used to transfer the data including all the partitions to the eMMC memory.

1. Prepare 2 bootable SD cards (See section [SD Card](#sd-card) for the steps required to prepare an SD card):
    - One with a default SD card image, which is only used to boot until U-Boot console.
    - The second SD card contains the image to be written to the eMMC flash. Make sure that the image to be written to the eMMC is small enough to fit into the DDR memory. The recommended partition sizes are: fat 50Mbyte, raw 2Mbyte, ext4 400Mbyte. The rootfs partition size can be increased in a later step.

Two SD cards are required because on Mercury+ AA1 the U-Boot SPL configures the HPS system differently (e.g. 4 data lines for SD card and 8 data lines for eMMC memory). Programming the eMMC flash on Mercury SA1 might work with only one SD card, containing the image generated for eMMC boot.

2. Boot from the first SD card until U-Boot console

3. Replace the SD card with the one containing the eMMC image

4. Copy the SD card content into the DDR memory (assuming the total size is smaller than 512Mbyte)

```
mmc rescan
mmc dev 0
mmc read 0 0 0x100000   # copy 512Mbyte of data (block size = 512bytes)
```

5. Switch to the eMMC memory

```
altera_set_storage EMMC
```

6. Copy the data from the DDR memory to the eMMC memory

```
mmc rescan
mmc write 0 0 0x100000
```

7. When completed, remove the SD card and configure the hardware for eMMC boot.

8. Optional: If a bigger rootfs partition is required, it can be increased after booting from eMMC memory into Linux. The data on the disk will be preserved while the partition table is modified.

Run fdisk tool:

```
fdisk /dev/mmcblk0
```

Within fdisk run the following commands:

```
# delete rootfs partition
d
3
# show partition table
p

# as example, following is shown
Device       Boot StartCHS    EndCHS        StartLBA     EndLBA    Sectors  Size Id Type
/dev/mmcblk0p1    0,32,33     12,223,19         2048     206847     204800  100M  c Win95 FAT32 (LBA)
/dev/mmcblk0p2    12,223,20   13,33,20        206848     210943       4096 2048K a2 Unknow

# create a new partition
n
p
3
# set last sector of a2 partition plus one as first sector, as printed in the partition table in column 'EndLBA'
210944
# leave default end sector

# set the 3rd partition type to Linux
t
3
83
# write changes and exit
w
```

Reboot and run following command to resize the partition

```
resize2fs /dev/mmcblk0p3
```

### QSPI flash ###

The QSPI flash can be programmed via JTAG with the vendor tools. An alternative is described following. It requires booting from SD card to update the QSPI flash in U-Boot.

1. Prepare an SD card according to section [SD Card](#sd-card)

2. Create a directory on the SD card and copy the required files for QSPI boot to the SD card into this newly created directory. The directory name is assumed `qspi` in the following steps.

3. Configure the hardware to boot from SD card and boot from SD card until U-Boot console

4. Copy the files from the SD card to the DDR memory and write the data into the QSPI flash

For Mercury SA1 and Mercury+ SA2:

```
mmc dev 0

fatload mmc 0:1 0x10000000 qspi/u-boot-with-spl.sfp
fatload mmc 0:1 0x10200000 qspi/boot.scr
fatload mmc 0:1 0x10300000 qspi/devicetree.dtb
fatload mmc 0:1 0x11000000 qspi/fpga.rbf
fatload mmc 0:1 0x12000000 qspi/uImage
fatload mmc 0:1 0x13000000 qspi/<image>-<machine>.cpio.gz.u-boot

sf probe

sf update 0x10000000 ${qspi_offset_addr_spl} ${size_spl}
sf update 0x10200000 ${qspi_offset_addr_boot-script} ${size_boot-script}
sf update 0x10300000 ${qspi_offset_addr_devicetree} ${size_devicetree}
sf update 0x11000000 ${qspi_offset_addr_bitstream} ${size_tstream}
sf update 0x12000000 ${qspi_offset_addr_kernel} ${size_kernel}
sf update 0x13000000 ${qspi_offset_addr_rootfs} ${size_rootfs}
```

For Mercury+ AA1:

```
mmc dev 0

fatload mmc 0:1 0x10000000 qspi/u-boot-splx4.sfp
fatload mmc 0:1 0x10100000 qspi/u-boot.img
fatload mmc 0:1 0x10200000 qspi/boot.scr
fatload mmc 0:1 0x10300000 qspi/devicetree.dtb
fatload mmc 0:1 0x10400000 qspi/socfpga_enclustra_mercury_qspi_overlay.dtbo
fatload mmc 0:1 0x11000000 qspi/bitstream.itb
fatload mmc 0:1 0x12000000 qspi/uImage
fatload mmc 0:1 0x13000000 qspi/<image>-<machine>.cpio.gz.u-boot

altera_set_storage QSPI
sf probe

sf update 0x10000000 ${qspi_offset_addr_spl} ${size_spl}
sf update 0x10100000 ${qspi_offset_addr_u-boot} ${size_u-boot}
sf update 0x10200000 ${qspi_offset_addr_boot-script} ${size_boot-script}
sf update 0x10300000 ${qspi_offset_addr_devicetree} ${size_devicetree}
sf update 0x10400000 ${qspi_offset_addr_dtoverlay} ${size_dtoverlay}
sf update 0x11000000 ${qspi_offset_addr_bitstream} ${size_bitstream}
sf update 0x12000000 ${qspi_offset_addr_kernel} ${size_kernel}
sf update 0x13000000 ${qspi_offset_addr_rootfs} ${size_rootfs}
```

5. Remove the SD card and configure the hardware for QSPI boot.

#### QSPI Flash Layout for Mercury SA1 and Mercury+ SA2

Partition          | Filename                             | Offset    | Size
------------------ | ------------------------------------ | --------- | ----------
U-Boot with SPL    | u-boot-with-spl.sfp                  | 0x0       | 0x180000
U-Boot environment | -                                    | 0x180000  | 0x80000
U-Boot script      | boot.scr                             | 0x200000  | 0x80000
Linux devicetree   | devicetree.dtb                       | 0x280000  | 0x80000
FPGA bitstream     | fpga.rbf                             | 0x300000  | 0xd00000
Linux kernel       | uImage                               | 0x1000000 | 0x1000000
Rootfs             | \<image\>-\<machine\>.cpio.gz.u-boot | 0x2000000 | 0x2000000

#### QSPI Flash Layout for Mercury+ AA1

Partition                | Filename                                    | Offset    | Size
------------------------ | ------------------------------------------- | --------- | ---------
U-Boot SPL               | u-boot-splx4.sfp                            | 0x0       | 0x100000
U-Boot                   | u-boot.img                                  | 0x100000  | 0x80000
U-Boot environment       | -                                           | 0x180000  | 0x80000
U-Boot script            | boot.scr                                    | 0x200000  | 0x80000
Linux devicetree         | devicetree.dtb                              | 0x280000  | 0x40000
Linux devicetree overlay | socfpga_enclustra_mercury_qspi_overlay.dtbo | 0x2C0000  | 0x40000
FPGA bitstream           | bitstream.itb                               | 0x300000  | 0xd00000
Linux kernel             | uImage                                      | 0x1000000 | 0x1000000
Rootfs                   | \<image\>-\<machine\>.cpio.gz.u-boot        | 0x2000000 | 0x2000000

## Additional Information

### Login on Target

Login with `root` as user name, no password is set.

### Devicetree

The Linux devicetree is generated in a [device-tree.bb](meta-enclustra-module/recipes-bsp/device-tree/device-tree.bb) recipe included in the [meta-enclustra-module](meta-enclustra-module) Yocto layer.
This layer requires an additional file named `enclustra-user.dts` which is added in the [meta-enclustra-refdes](meta-enclustra-refdes) Yocto layer in the [device-tree.bbappend](meta-enclustra-refdes/recipes-bsp/device-tree/device-tree.bbappend) append file. This `enclustra-user.dts` file includes all the required devicetree include files, e.g:

```
/dts-v1/;

#include "socfpga_arria10.dtsi"
#include "socfpga_enclustra_mercury_aa1.dtsi"
#include "ME-AA1-270-3E4-D11E-NFX3.dtsi"
```

Following list show all devicetree include files added by [meta-enclustra-module](meta-enclustra-module):

File name                                                                                                                                        | Description
------------------------------------------------------------------------------------------------------------------------------------------------ | ------------
[ME-AA1-270-2I2-D11E-NFX3.dtsi](meta-enclustra-module/recipes-bsp/device-tree/files/ME-AA1-270-2I2-D11E-NFX3.dtsi)                               | Module specificconfigurations for ME-AA1-270-2I2-D11E-NFX3
[ME-AA1-270-3E4-D11E-NFX3.dtsi](meta-enclustra-module/recipes-bsp/device-tree/files/ME-AA1-270-3E4-D11E-NFX3.dtsi)                               | Module specificconfigurations for ME-AA1-270-3E4-D11E-NFX3
[ME-AA1-480-2I3-D12E-NFX3.dtsi](meta-enclustra-module/recipes-bsp/device-tree/files/ME-AA1-480-2I3-D12E-NFX3.dtsi)                               | Module specificconfigurations for ME-AA1-480-2I3-D12E-NFX3
[ME-SA1-C6-7I-D10.dtsi](meta-enclustra-module/recipes-bsp/device-tree/files/ME-SA1-C6-7I-D10.dtsi)                                               | Module specificconfigurations for ME-SA1-C6-7I-D10
[ME-SA2-D6-7I-D11.dtsi](meta-enclustra-module/recipes-bsp/device-tree/files/ME-SA2-D6-7I-D11.dtsi)                                               | Module specificconfigurations for ME-SA2-D6-7I-D11
[socfpga_enclustra_mercury_aa1.dtsi](meta-enclustra-module/recipes-bsp/device-tree/files/socfpga_enclustra_mercury_aa1.dtsi)                     | Contains a configuration common for all variants of the Mercury+ AA1 family
[socfpga_enclustra_mercury_sdmmc_overlay.dtsi](meta-enclustra-module/recipes-bsp/device-tree/files/socfpga_enclustra_mercury_sdmmc_overlay.dtsi) | Devicetree overlay for Mercury+ AA1 SD card boot
[socfpga_enclustra_mercury_emmc_overlay.dtsi](meta-enclustra-module/recipes-bsp/device-tree/files/socfpga_enclustra_mercury_emmc_overlay.dtsi)   | Devicetree overlay for Mercury+ AA1 eMMC boot
[socfpga_enclustra_mercury_qspi_overlay.dtsi](meta-enclustra-module/recipes-bsp/device-tree/files/socfpga_enclustra_mercury_qspi_overlay.dtsi)   | Devicetree overlay for Mercury+ AA1 QSPI boot
[socfpga_enclustra_mercury_sa1.dtsi](meta-enclustra-module/recipes-bsp/device-tree/files/socfpga_enclustra_mercury_sa1.dtsi)                     | Contains a configuration common for all variants of the Mercury SA1 family
[socfpga_enclustra_mercury_sa2.dtsi](meta-enclustra-module/recipes-bsp/device-tree/files/socfpga_enclustra_mercury_sa2.dtsi)                     | Contains a configuration common for all variants of the Mercury+ SA2 family

The U-Boot devicetree is created similar to the Linux devicetree in the [u-boot-socfpga](meta-enclustra-module/recipes-bsp/u-boot/u-boot-socfpga_%.bbappend) recipe. Because overlays can't be used, the boot mode specific include file must be included in the `enclustra-user.dts` file that is added in the [meta-enclustra-refdes](meta-enclustra-refdes) Yocto layer.  

Note: The setup i.e. u-boot and kernel, is generally prepared to handle also device-tree overlays (.dtbo files). The different bootmodes are applied by the u-boot as corresponding .dtbo files. The available .dtb files thus can be extended by further .dtbo files.  

### Patches

#### U-Boot

Following U-Boot patches are added.

Patch Name                                                                                                                                                                      | Description
------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |-------------
[0001-Add-Enclustra-board-files.patch](meta-enclustra-module/recipes-bsp/u-boot/files/0001-Add-Enclustra-board-files.patch)                                                     | Add support for Enclustra modules
[0002-Add-Enclustra-devicetree-to-Makefile.patch](meta-enclustra-module/recipes-bsp/u-boot/files/0002-Add-Enclustra-devicetree-to-Makefile.patch)                               | Add enclustra-user.dtb as build target to Makefile
[0003-Fix-cycloneV-handoff-scripts.patch](meta-enclustra-module/recipes-bsp/u-boot/files/0003-Fix-cycloneV-handoff-scripts.patch)                                               | Fix Python scripts to generate header files from Quartus handoff directory
[0004-Make-intel-scripts-python-3-compatible.patch](meta-enclustra-module/recipes-bsp/u-boot/files/0004-Make-intel-scripts-python-3-compatible.patch)                           | Modify Python scripts to be compatible with Python 3
[0005-Enclustra-MAC-address-readout-from-EEPROM.patch](meta-enclustra-module/recipes-bsp/u-boot/files/0005-Enclustra-MAC-address-readout-from-EEPROM.patch)                     | Support for configuring MAC address with address stored in module EEPROM
[0006-Add-SI5338-configuration.patch](meta-enclustra-module/recipes-bsp/u-boot/files/0006-Add-SI5338-configuration.patch)                                                       | Add code to configure SI5338 clock generator device on Enclustra base boards
[0007-mtd-spi-nor-Prevent-a-bricked-S25FL512S-flash.patch](meta-enclustra-module/recipes-bsp/u-boot/files/0007-mtd-spi-nor-Prevent-a-bricked-S25FL512S-flash.patch)             | Clear protection flags of QSPI flash if they were set accidentally (see [Known Issues](#1-protection-bits-are-set-in-qspi-flash))
[0008-Workaround-for-AA1-ST1-SD-card-boot.patch](meta-enclustra-module/recipes-bsp/u-boot/files/0008-Workaround-for-AA1-ST1-SD-card-boot.patch)                                 | Workaround for SD card access issues on AA1/ST1
[0009-Add-dtbo-for-AA1-boot.patch](meta-enclustra-module/recipes-bsp/u-boot/files/0009-Add-dtbo-for-AA1-boot.patch)                                                             | Load devicetree overlay in U-Boot boot script for Mercury+ AA1
[0010-Workaround-MMC-controller-initialization-issue.patch](meta-enclustra-module/recipes-bsp/u-boot/files/0010-Workaround-MMC-controller-initialization-issue.patch)           | Workaround to fix MMC controller initialization issues on Mercury+ AA1 modules.
[0011-Configure-MMC-clock-to-25MHz-because-of-Mercury-SA1.patch](meta-enclustra-module/recipes-bsp/u-boot/files/0011-Configure-MMC-clock-to-25MHz-because-of-Mercury-SA1.patch) | Configure MMC controller to operate with 25MHz due to a hardware limitation on Mercury SA1 modules. This patch is only applied to builds for Mercury SA1 modules.

#### Linux Kernel

Following Linux kernel patches are added.

Patch Name                                                                                                                                                            | Description
--------------------------------------------------------------------------------------------------------------------------------------------------------------------- | -------------
[0001-Add-Enclustra-devicetree-to-Makefile.patch](meta-enclustra-module/recipes-kernel/linux/files/0001-Add-Enclustra-devicetree-to-Makefile.patch)                   | Add enclustra-user.dtb as build target to Makefile
[0002-crypto-atmel-add-AT-SHA204-EEPROM-support.patch](meta-enclustra-module/recipes-kernel/linux/files/0002-crypto-atmel-add-AT-SHA204-EEPROM-support.patch)         | Add driver to read module serial number
[0003-mtd-spi-nor-Prevent-a-bricked-S25FL512S-flash.patch](meta-enclustra-module/recipes-kernel/linux/files/0003-mtd-spi-nor-Prevent-a-bricked-S25FL512S-flash.patch) | Clear protection flags of QSPI flash if they were set accidentally (see [Known Issues](#1-protection-bits-are-set-in-qspi-flash))

### Integrate meta-enclustra-module Layer into user Project

When the [meta-enclustra-module](meta-enclustra-module) layer is integrated into an own projet, the binaries exported from Quartus II tool and devicetree files need to be provided by an external layer. The directory structure of a minimal layer providing these files is shown below.

```
meta-test
├── conf
│   └─── layer.conf
└── recipes-bsp
    ├── device-tree
    │   ├── device-tree.bbappend
    │   └── files
    │       └── enclustra-user.dts
    ├── exported-binaries
    │   ├── files
    │   │   ├── handoff
    │   │   ├── fpga.periph.rbf
    │   │   └── fpga.core.rbf
    │   └── exported-binaries.bb
    └── u-boot
        ├── files
        │   └── enclustra-user.dts
        └── u-boot-socfpga_%.bbappend
```

The binaries exported from Quartus II tool can be added in an own yocto recipe named `exported-binaries`. Important is that all files from the HPS handoff directory are copied to `${DEPLOY_DIR_IMAGE}/handoff` directory and the bitstream to `${DEPLOY_DIR_IMAGE}/fpga.rbf` for Mercury SA1 and Mercury+ SA2 or `${DEPLOY_DIR_IMAGE}/bitstream.periph.rbf` and `${DEPLOY_DIR_IMAGE}/bitstream.core.rbf` for Mercury+ AA1.

The U-Boot and Linux devicetree files need to be named `enclustra-user.dts` and provided by the `device-tree.bbappend` and `u-boot-socfpga_%.bbappend` recipes. The files are copied to the correct location by the base recipes.

The user project should use one of the following machine configuations (named the same as the module). These machine configurations are provided by the [meta-enclustra-module](meta-enclustra-module) layer.

- me-aa1-270-2i2-d11e-nfx3
- me-aa1-270-3e4-d11e-nfx3
- me-aa1-480-2i3-d12e-nfx3
- me-sa1-c6-7i-d10
- me-sa2-d6-7i-d11


### Storage Multiplexing

Mercury+ AA1 provides QSPI flash, SD card and eMMC flash, but all these memories are connected to the same IO pins of the SoC device. Mercury SA1 shares SD card and eMMC flash with the same IO pins. The active memory is selected according to the configured boot mode. `altera_set_storage` U-Boot command provides a mechanism to switch the memory device in U-Boot temporarily. It takes one argument, either `MMC` (to select SD card), `EMMC` (to select eMMC memory) or `QSPI` (to select QSPI flash).

Examples:

```
# Switch to SD card
=> altera_set_storage MMC
=> mmc rescan
=> mmc info
Device: SOCFPGA DWMMC
Manufacturer ID: 3
OEM: 5344
Name: SL08G
Tran Speed: 50000000
Rd Block Len: 512
SD version 3.0
High Capacity: Yes
Capacity: 7.4 GiB
Bus Width: 4-bit

# Switch to eMMC
=> altera_set_storage EMMC
=> mmc rescan
=> mmc info
Device: SOCFPGA DWMMC
Manufacturer ID: 70
OEM: 100
Name: W5251
Tran Speed: 52000000
Rd Block Len: 512
MMC version 5.0
High Capacity: Yes
Capacity: 14.3 GiB
Bus Width: 8-bit

# Switch to QSPI
=> altera_set_storage QSPI
=> mmc rescan
dwmci_send_cmd: Timeout on data busy
dwmci_send_cmd: Timeout on data busy
dwmci_send_cmd: Timeout on data busy
dwmci_send_cmd: Timeout on data busy
Card did not respond to voltage select!
=> sf probe
SF: Detected S25FL512S_256K with page size 512 Bytes, erase size 256 KiB, total 64 MiB
```

### U-Boot Environment

U-Boot is using variables from the default environment. The boot scripts used by U-Boot rely on those variables. If the environment was changed and saved earlier, U-Boot will always use these saved environment variables on a fresh boot, even after changing the U-Boot environment. To restore the default environment, run the following command in the U-Boot command line:

```
env default -a
```

This will not overwrite the stored environment but will only restore the default one in the current run. To permanently restore the default environment, the `saveenv` command has to be invoked.

> **_Note:_**  A `*** Warning - bad CRC, using default environment` warning message that appears when booting into U-Boot indicates that the default environment will be loaded.

Boot storage | Offset            | Size
------------ | ----------------- | ---
MMC          | partition 1 (FAT) | 0x80000
eMMC         | partition 1 (FAT) | 0x80000
QSPI         | 0x180000          | 0x80000

### Ethernet MAC address configuration

Each Enclustra module is delivered with two unique MAC addresses stored in the EEPROM. During the boot process, these MAC addresses are automatically read by U-Boot and configured to be used by U-Boot and Linux.

### Reading Serial Number of Module

On modules equipped with a ATSHA204a EEPROM, the serial number can be read by following command:

    cat /sys/bus/i2c/devices/1-0064/serial

The serial number is reported as follows:

    248173

### Root File System

The rootfs is located on the ext4 partition on SD card or eMMC flash. This partition is persistent. For QSPI boot, an initramfs is used, which is copied to RAM while booting. The initramfs is not persistent and changes are lost after a reboot.

The size of the ext4 rootfs partition is set to 400 Mbyte by default. To change the partition size, the OpenEmbedded kickstart file ([sdimage-enclustra-arria10.wks](meta-enclustra-refdes/wic/sdimage-enclustra-arria10.wks) / [sdimage-enclustra-cyclonev.wks](meta-enclustra-refdes/wic/sdimage-enclustra-cyclonev.wks)) needs to be modified. The partition size is defined by `--fixed-size` parameter as shown below.

```
part / --source rootfs --ondisk mmcblk --fstype=ext4 --label root --align 1024 --fixed-size 400M
```

### Configure SI5338 clock generator on Mercury+ PE1 and Mercury+ ST1 base board

The U-Boot patch [0006-Add-SI5338-configuration.patch](meta-enclustra-module/recipes-bsp/u-boot/files/0006-Add-SI5338-configuration.patch) adds support to configure the clock generator device. To enable the configuration, follow the steps below:

1. Create a configuration with Skyworks [ClockBuilder Pro software](https://www.skyworksinc.com/Application-Pages/Clockbuilder-Pro-Software) and export the C code header file.
2. Copy the exported header file to `meta-enclustra-module/recipe_bsp/u-boot/files/` directory and overwrite the example file [Si5338-RevB-Registers.h](meta-enclustra-module/recipes-bsp/u-boot/files/Si5338-RevB-Registers.h)
3. Make following changes to file [meta-enclustra-module/recipes-bsp/u-boot/files/configs/socfpga_enclustra_mercury_*_defconfig](meta-enclustra-module/recipes-bsp/u-boot/files/configs/socfpga_enclustra_mercury_sa1_mmc_defconfig):

       CONFIG_SI5338_CONFIGURATION=y

### Program the flash memory from Linux

The following script can be used to flash the QSPI flash memory from Linux. All required files need to be present in the current folder. They can be loaded via TFTP or from USB drive / SD card.

```
#!/bin/sh

getsize ()
{
    local  size=`ls -al $1 | awk '{ print $5 }'`
    echo "$size"
}

SPL_FILE="u-boot-splx4.sfp"
UBOOT_FILE="u-boot.img"
SCRIPT_FILE="boot.scr"
DEVICETREE_FILE="devicetree.dtb"
OVERLAY_FILE="socfpga_enclustra_mercury_QSPI_overlay.dtbo"
BITSTREAM_FILE="bitstream.itb"
KERNEL_FILE="uImage"
ROOTFS_FILE="<image>-<machine>.cpio.gz.u-boot"

SPL_OFFSET=0x0
UBOOT_OFFSET=0x100000
SCRIPT_OFFSET=0x200000
DEVICETREE_OFFSET=0x280000
OVERLAY_OFFSET=0x2C0000
BITSTREAM_OFFSET=0x300000
KERNEL_OFFSET=0x1000000
ROOTFS_OFFSET=0x2000000

# erase flash device
flash_erase /dev/mtd0 0 0x4000000

# write SPL
FILESIZE=`getsize ${SPL_FILE}`
echo writing SPL file ${SPL_FILE} size ${FILESIZE}
mtd_debug write /dev/mtd0 ${SPL_OFFSET} ${FILESIZE} ${SPL_FILE}

# write U-Boot
FILESIZE=`getsize ${UBOOT_FILE}`
echo writing U-Boot file ${UBOOT_FILE} size ${FILESIZE}
mtd_debug write /dev/mtd0 ${UBOOT_OFFSET} ${FILESIZE} ${UBOOT_FILE}

# write U-Boot script
FILESIZE=`getsize ${SCRIPT_FILE}`
echo writing U-Boot script file ${SCRIPT_FILE} size ${FILESIZE}
mtd_debug write /dev/mtd0 ${SCRIPT_OFFSET} ${FILESIZE} ${SCRIPT_FILE}

# write devicetree
FILESIZE=`getsize ${DEVICETREE_FILE}`
echo writing devicetree ${DEVICETREE_FILE} size ${FILESIZE}
mtd_debug write /dev/mtd0 ${DEVICETREE_OFFSET} ${FILESIZE} ${DEVICETREE_FILE}

# write overlay
FILESIZE=`getsize ${OVERLAY_FILE}`
echo writing devicetree ${OVERLAY_FILE} size ${FILESIZE}
mtd_debug write /dev/mtd0 ${OVERLAY_OFFSET} ${FILESIZE} ${OVERLAY_FILE}

# write bitstream
FILESIZE=`getsize ${BITSTREAM_FILE}`
echo writing bitstream file ${BITSTREAM_FILE} size ${FILESIZE}
mtd_debug write /dev/mtd0 ${BITSTREAM_OFFSET} ${FILESIZE} ${BITSTREAM_FILE}

# write Linux kernel
FILESIZE=`getsize ${KERNEL_FILE}`
echo writing Linux kernel file ${KERNEL_FILE} size ${FILESIZE}
mtd_debug write /dev/mtd0 ${KERNEL_OFFSET} ${FILESIZE} ${KERNEL_FILE}

# write rootfs
FILESIZE=`getsize ${ROOTFS_FILE}`
echo writing rootfs file ${ROOTFS_FILE} size ${FILESIZE}
mtd_debug write /dev/mtd0 ${ROOTFS_OFFSET} ${FILESIZE} ${ROOTFS_FILE}
```

Just make the script executable and execute it like this:

```
chmod +x flash.sh
./flash.sh
```

## Known Issues:

### 1. Protection bits are set in QSPI flash

#### Affected hardware:

All Enclustra modules equipped with a S25FL512S device (all product models of Mercury+ AA1, Mercury SA1 and Mercury+ SA2).

#### Description

It can happen that all bits of the configuration register 1 of the QSPI flash device are set. One potential cause is when the power supply is turned off during a write command to this register. This register contains a one time programmable bit that defines the reset status of the block protection flags. When this bit is set by accident, the flash device is write protected after power up. As workaround a patch was added to U-Boot and Linux to clear these protection flags ([0007-mtd-spi-nor-Prevent-a-bricked-S25FL512S-flash.patch](meta-enclustra-module/recipes-bsp/u-boot/files/0007-mtd-spi-nor-Prevent-a-bricked-S25FL512S-flash.patch)).

:warning: If the block protection feature of the QSPI flash device is enabled on purpose, this feature needs to be disabled.

### 2. SD Card access is not reliable

#### Affected hardware:

This issue was observed on Mercury SA1 and Mercury+ AA1 modules equipped on Mercury ST1 base board.

#### Description

Linux does not boot or gets stuck while booting. Sometimes the SD Card stops working after Linux is up and running.
A patch is included which contains a workaround to fix the SD card access issues for Mercury+ AA1 ([0008-Workaround-for-AA1-ST1-SD-card-boot.patch](meta-enclustra-module/recipes-bsp/u-boot/files/0008-Workaround-for-AA1-ST1-SD-card-boot.patch)).
However, this fix only partially solves the problem, SD card access might still fail when the SPL is loaded by the boot ROM code.

### 3. AA1 Linux is limited to 2 Gbyte DDR memory size

#### Affected hardware

All Arria 10 modules equipped with more than 2 Gbyte DDR of memory connected to the HPS:

- ME-AA1-480-2I3-D12E-NFX3

#### Description

The memory size is limited in U-Boot to max. 2 Gbyte. Therefore, only 2 Gbyte is available for U-Boot and Linux. However, the upper 2 Gbyte can still be accessed by the FPGA fabric.

### 4. I2C frequency is wrong in U-Boot

#### Affected hardware

All Intel modules.

#### Description

In U-Boot, the I2C frequency is configured to be 100kHz. The frequency changes to 400kHz after "i2c probe" is executed. I2C gets reinitialized when probing fails (when "I2C probe" probes a non existent address), which changes the bus frequency.

### 5. USB host mode does not work in U-Boot

#### Affected hardware

All Mercury+ AA1 product models on PE1, ST1 and PE3 baseboards.

#### Description

USB host mode does not work in U-Boot because the U-Boot USB driver does not support overriding the mode dictated by the USB ID signal.

