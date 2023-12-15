FILESEXTRAPATHS:prepend := "${THISDIR}/files:"
FILESEXTRAPATHS:prepend := "${THISDIR}/files/bitstream:"
FILESEXTRAPATHS:prepend := "${THISDIR}/files/configs:"
FILESEXTRAPATHS:prepend := "${THISDIR}/files/devicetree:"

DEPENDS:append = " hw-ref-design"

## TODO needed?    
DEPENDS:append = " xxd-native"

SRC_URI:append = " \
    file://fit_spl_fpga.its \
    file://0001-Add-Enclustra-board-files.patch \
    file://0002-Add-Enclustra-devicetree-to-Makefile.patch \
    file://0003-Make-intel-scripts-python-3-compatible.patch \
    file://0004-Enclustra-MAC-address-readout-from-EEPROM.patch \
    file://0005-Add-SI5338-configuration.patch \
    file://0006-mtd-spi-nor-Prevent-a-bricked-S25FL512S-flash.patch \
    file://0100-yocto-adjust-rootfs-partition-to-wic-image-layout.patch \
    file://Si5338-RevB-Registers.h \
"

## TODO to be extended by more UBOOT_CONFIG modes
SRC_URI:append:me-aa1-generic = " \
    file://socfpga_enclustra_mercury_aa1_mmc_defconfig \
    file://socfpga_enclustra_mercury_aa1_qspi_defconfig \
    file://socfpga_enclustra_mercury_aa1.dtsi \
    file://socfpga_enclustra_mercury_aa1_emmc_boot.dtsi \
    file://socfpga_enclustra_mercury_aa1_sdmmc_boot.dtsi \
    file://socfpga_enclustra_mercury_aa1_qspi_boot.dtsi \
"

SRC_URI:append:me-aa1-270-3e4-d11d-nfx3 = " \
    file://ME-AA1-270-3E4-D11E-NFX3.dtsi \
"

SRC_URI:append:me-aa1-270-2i2-d11d-nfx3 = " \
    file://ME-AA1-270-2I2-D11E-NFX3.dtsi \
"

SRC_URI:append:me-aa1-480-2i3-d12d-nfx3 = " \
    file://ME-AA1-480-2I3-D12E-NFX3.dtsi \
"

SRC_URI:append:me-sa1-c6-7i-d10 = " \
    file://socfpga_enclustra_mercury_sa1_mmc_defconfig \
    file://socfpga_enclustra_mercury_sa1_qspi_defconfig \
    file://ME-SA1-C6-7I-D10.dtsi \
    file://socfpga_enclustra_mercury_sa1.dtsi \
"

# TODO .dtsi files missing for sa2
SRC_URI:append:me-sa2-d6-7i-d11 = " \
    file://socfpga_enclustra_mercury_sa2_mmc_defconfig \
    file://socfpga_enclustra_mercury_sa2_qspi_defconfig \
    file://ME-SA2-D6-7I-D11.dtsi \
    file://socfpga_enclustra_mercury_sa2.dtsi \
"

## TODO adds aa1/sa1/sa2 files - possible to overload?
do_add_enclustra_files() {
}

## TODO integrate from "base" to "module"
do_add_enclustra_files:append:me-aa1-generic() {
    cp ${WORKDIR}/socfpga_enclustra_mercury_aa1.dtsi ${S}/arch/arm/dts
    cp ${WORKDIR}/socfpga_enclustra_mercury_aa1_${UBOOT_CONFIG}_boot.dtsi ${S}/arch/arm/dts
    if [ "qspi" == "$UBOOT_CONFIG" ]; then
        cp ${WORKDIR}/socfpga_enclustra_mercury_aa1_qspi_defconfig ${S}/configs
    else
        cp ${WORKDIR}/socfpga_enclustra_mercury_aa1_mmc_defconfig ${S}/configs
    fi
}

do_add_enclustra_files:append:me-aa1-270-3e4-d11d-nfx3() {
    cp ${WORKDIR}/ME-AA1-270-3E4-D11E-NFX3.dtsi ${S}/arch/arm/dts
}

do_add_enclustra_files:append:me-aa1-270-2i2-d11d-nfx3() {
    cp ${WORKDIR}/ME-AA1-270-2I2-D11E-NFX3.dtsi ${S}/arch/arm/dts
}

do_add_enclustra_files:append:me-aa1-480-2i3-d12d-nfx3() {
    cp ${WORKDIR}/ME-AA1-480-2I3-D12E-NFX3.dtsi ${S}/arch/arm/dts
}

do_add_enclustra_files:append:me-sa1-c6-7i-d10() {
    cp ${WORKDIR}/ME-SA1-C6-7I-D10.dtsi ${S}/arch/arm/dts
    cp ${WORKDIR}/socfpga_enclustra_mercury_sa1.dtsi ${S}/arch/arm/dts
    if [ "qspi" == "$UBOOT_CONFIG" ]; then
        cp ${WORKDIR}/socfpga_mercury_sa1_qspi_defconfig ${S}/configs
    else
        cp ${WORKDIR}/socfpga_mercury_sa1_mmc_defconfig ${S}/configs
    fi
}

do_add_enclustra_files:append:me-sa2-d6-7i-d11() {
    cp ${WORKDIR}/ME-SA2-D6-7I-D11.dtsi ${S}/arch/arm/dts
    cp ${WORKDIR}/socfpga_enclustra_mercury_sa2.dtsi ${S}/arch/arm/dts
    if [ "qspi" == "$UBOOT_CONFIG" ]; then
        cp ${WORKDIR}/socfpga_enclustra_mercury_sa2_qspi_defconfig ${S}/configs
    else
        cp ${WORKDIR}/socfpga_enclustra_mercury_sa2_mmc_defconfig ${S}/configs
    fi
}
addtask do_add_enclustra_files after do_patch before do_configure

#do_compile:prepend() {
## TODO rm, use .h approach    
#	cp -L ${DEPLOY_DIR_IMAGE}/uboot.env ${S}/
#}

do_compile:prepend:me-aa1-generic() {
    mkdir -p ${WORKDIR}/handoff
    cp -r ${DEPLOY_DIR_IMAGE}/handoff/* ${WORKDIR}/handoff
    cp -r ${WORKDIR}/Si5338-RevB-Registers.h ${S}/drivers/misc/
    ${S}/arch/arm/mach-socfpga/qts-filter-a10.sh ${WORKDIR}/handoff/hps.xml ${S}/arch/arm/dts/socfpga_arria10_handoff.h
}

do_compile:prepend:me-sa1-c6-7i-d10() {
    mkdir -p ${WORKDIR}/handoff
    cp -r ${DEPLOY_DIR_IMAGE}/handoff/* ${WORKDIR}/handoff
    ${PYTHON} ${S}/arch/arm/mach-socfpga/cv_bsp_generator/cv_bsp_generator.py -i ${WORKDIR}/handoff -o ${S}/board/enclustra/mercury_sa1/qts/
}

do_compile:prepend:me-sa2-d6-7i-d11() {
    mkdir -p ${WORKDIR}/handoff
    cp -r ${DEPLOY_DIR_IMAGE}/handoff/* ${WORKDIR}/handoff
    ${PYTHON} ${S}/arch/arm/mach-socfpga/cv_bsp_generator/cv_bsp_generator.py -i ${WORKDIR}/handoff -o ${S}/board/enclustra/mercury_sa2/qts
}

do_compile:append:me-aa1-generic() {
    cp -r ${DEPLOY_DIR_IMAGE}/bitstream.core.rbf ${S}/.
    cp -r ${DEPLOY_DIR_IMAGE}/bitstream.periph.rbf ${S}/.

    for config in ${UBOOT_MACHINE}; do
	cp ${B}/${config}/u-boot-nodtb.bin ${S}/u-boot-nodtb.bin
	cp ${B}/${config}/u-boot.dtb ${S}/u-boot.dtb
    done

    cp ${WORKDIR}/fit_spl_fpga.its ${S}
    mkimage -E -f ${S}/board/altera/arria10-socdk/fit_uboot.its ${B}/fit_uboot.itb
    mkimage -E -f ${S}/fit_spl_fpga.its ${B}/fit_spl_fpga.itb

    if [ "${UBOOT_CONFIG}" == "qspi" ]; then
        CMD_FILE="qspi-aa1.cmd"
    else
        CMD_FILE="sd-aa1.cmd"
    fi
    mkimage -A arm -O linux -T script -C none -a 0 -e 0 -n "Uboot start script" -d ${S}/board/enclustra/bootscripts/${CMD_FILE} boot.scr
}

do_compile:append:me-sa1-c6-7i-d10() {
# TODO verify      
    cp -r ${DEPLOY_DIR_IMAGE}/fpga.rbf ${S}/.

    for config in ${UBOOT_MACHINE}; do
	cp ${B}/${config}/u-boot-nodtb.bin ${S}/u-boot-nodtb.bin
	cp ${B}/${config}/u-boot.dtb ${S}/u-boot.dtb
    done

    cp ${WORKDIR}/fit_spl_fpga.its ${S}
#    mkimage -E -f ${S}/board/altera/arria10-socdk/fit_uboot.its ${B}/fit_uboot.itb
    mkimage -E -f ${S}/fit_spl_fpga.its ${B}/fit_spl_fpga.itb

    if [ "${UBOOT_CONFIG}" == "qspi" ]; then
        CMD_FILE="qspi.cmd"
    else
        CMD_FILE="sd.cmd"
    fi
    mkimage -A arm -O linux -T script -C none -a 0 -e 0 -n "Uboot start script" -d ${S}/board/enclustra/bootscripts/${CMD_FILE} boot.scr
}

do_compile:append:me-sa2-d6-7i-d11() {
# TODO verify         
    cp -r ${DEPLOY_DIR_IMAGE}/fpga.rbf ${S}/.

    for config in ${UBOOT_MACHINE}; do
	cp ${B}/${config}/u-boot-nodtb.bin ${S}/u-boot-nodtb.bin
	cp ${B}/${config}/u-boot.dtb ${S}/u-boot.dtb
    done

    cp ${WORKDIR}/fit_spl_fpga.its ${S}
#    mkimage -E -f ${S}/board/altera/arria10-socdk/fit_uboot.its ${B}/fit_uboot.itb
    mkimage -E -f ${S}/fit_spl_fpga.its ${B}/fit_spl_fpga.itb

    if [ "${UBOOT_CONFIG}" == "qspi" ]; then
        CMD_FILE="qspi.cmd"
    else
        CMD_FILE="sd.cmd"
    fi
    mkimage -A arm -O linux -T script -C none -a 0 -e 0 -n "Uboot start script" -d ${S}/board/enclustra/bootscripts/${CMD_FILE} boot.scr
}

# TODO itb generation for sa1 and sa2   

## generally append
do_deploy:append() {
	install -d ${DEPLOYDIR}
## TODO needed?    
#	install -m 744 ${B}/fit_uboot.itb ${DEPLOYDIR}/fit_uboot.itb

# TODO move to module
	install -m 744 ${B}/fit_spl_fpga.itb ${DEPLOYDIR}/fit_spl_fpga.itb
        ln -sf fit_spl_fpga.itb ${DEPLOYDIR}/bitstream.itb

        ## boot.scr           
        install -m 0644 ${B}/*.scr ${DEPLOYDIR}/
}
