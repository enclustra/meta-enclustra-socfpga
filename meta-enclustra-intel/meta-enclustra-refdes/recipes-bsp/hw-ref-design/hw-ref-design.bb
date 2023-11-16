SUMMARY = "Exported reference design binaries"

inherit deploy

LICENSE = "Proprietary"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/Proprietary;md5=0557f9d92cf58f2ccdd50f62f8ac0b28"

SRC_URI:aa1-module = "\
    http://www.enclustra.com/binaries/enclustra-bsp/update/refdes/ME-AA1-480-2I3-D12E-NFX3_PE1.zip;name=aa14802i3pe1 \
    http://www.enclustra.com/binaries/enclustra-bsp/update/refdes/ME-AA1-270-2I2-D11E-NFX3_PE1.zip;name=aa12702i2pe1 \
    http://www.enclustra.com/binaries/enclustra-bsp/update/refdes/ME-AA1-270-3E4-D11E-NFX3_PE1.zip;name=aa12703e4pe1 \
    "

SRC_URI:sa1-module = "\
    http://www.enclustra.com/binaries/enclustra-bsp/update/refdes/ME-SA1-C6-7I-D10_PE1.zip;name=sa1c67ipe1 \
    "

SRC_URI:sa2-module = "\
    http://www.enclustra.com/binaries/enclustra-bsp/update/refdes/ME-SA2-D6-7I-D11_PE1.zip;name=sa2d67ipe1 \
    "

SRC_URI[aa14802i3pe1.sha256sum] = "8596579fd774028be8bcc88d6aca391c2e3e6ddca3ec094bda3512cc0defebd7"
SRC_URI[aa12702i2pe1.sha256sum] = "c87b5889fd16b14f66b8d3e5183e97efc7ef36b0fe3d23c8c81ac5c5bbd357b2"
SRC_URI[aa12703e4pe1.sha256sum] = "fdc8dbd287563b8989f296656262ca559ec668163e76c853d80d9e005a3f9236"
SRC_URI[sa1c67ipe1.sha256sum]   = "0b7dcd822f73baa8bc75468cd98a814df2b9df1ee0be3d02987b74585a14cad8"
SRC_URI[sa2d67ipe1.sha256sum]   = "095b85d2f574bd46efbbc2179e6949d3c69587b3edda2f0d462ed9305b92af51"

S ?= "${WORKDIR}/${MACHINE}"

PROVIDES = "virtual/bitstream"

ENCLUSTRA_BASE_NAME = "foo"
ENCLUSTRA_BASE_NAME:refdes-aa1sx270e3-pe1 = "Mercury_AA1_PE1"
ENCLUSTRA_BASE_NAME:refdes-aa1sx270e3-pe3 = "Mercury_AA1_PE3"
ENCLUSTRA_BASE_NAME:refdes-aa1sx270e3-st1 = "Mercury_AA1_ST1"
ENCLUSTRA_BASE_NAME:refdes-aa1sx270i2-pe1 = "Mercury_AA1_PE1"
ENCLUSTRA_BASE_NAME:refdes-aa1sx270i2-pe3 = "Mercury_AA1_PE3"
ENCLUSTRA_BASE_NAME:refdes-aa1sx270i2-st1 = "Mercury_AA1_ST1"
ENCLUSTRA_BASE_NAME:refdes-aa1sx480i2-pe1 = "Mercury_AA1_PE1"
ENCLUSTRA_BASE_NAME:refdes-aa1sx480i2-pe3 = "Mercury_AA1_PE3"
ENCLUSTRA_BASE_NAME:refdes-aa1sx480i2-st1 = "Mercury_AA1_ST1"
ENCLUSTRA_BASE_NAME:refdes-sa1-pe1 = "Mercury_SA1_PE1"
ENCLUSTRA_BASE_NAME:refdes-sa1-pe3 = "Mercury_SA1_PE3"
ENCLUSTRA_BASE_NAME:refdes-sa1-st1 = "Mercury_SA1_ST1"
ENCLUSTRA_BASE_NAME:refdes-sa2-pe1 = "Mercury_SA2_PE1"
ENCLUSTRA_BASE_NAME:refdes-sa2-pe3 = "Mercury_SA2_PE3"
ENCLUSTRA_BASE_NAME:refdes-sa2-st1 = "Mercury_SA2_ST1"

do_fetch[depends] += "unzip-native:do_populate_sysroot"

do_unpack() {
}

do_unpack:append:aa1sx270e3-module() {
     ${bindir}/env unzip -q -o "${DL_DIR}/ME-AA1-270-3E4-D11E-NFX3_PE1.zip" -d ${S}
}

do_unpack:append:aa1sx270i2-module() {
     ${bindir}/env unzip -q -o "${DL_DIR}/ME-AA1-270-2I2-D11E-NFX3_PE1.zip" -d ${S}
}

do_unpack:append:aa1sx480i2-module() {
    ${bindir}/env unzip -q -o "${DL_DIR}/ME-AA1-480-2I3-D12E-NFX3_PE1.zip" -d ${S}
}

do_unpack:append:sa1-module() {
    ${bindir}/env unzip -q -o "${DL_DIR}/ME-SA1-C6-7I-D10_PE1.zip" -d ${S}
}

do_unpack:append:sa2-module() {
    ${bindir}/env unzip -q -o "${DL_DIR}/ME-SA2-D6-7I-D11_PE1.zip" -d ${S}
}

do_deploy[nostamp] = "1"

do_deploy() {
}

do_deploy:append:aa1-module() {
     install -D -m 0644 ${B}/${UBOOT_CONFIG}/hps_isw_handoff/hps.xml ${DEPLOY_DIR_IMAGE}/hps.xml
     install -D -m 0644 ${B}/${UBOOT_CONFIG}/${ENCLUSTRA_BASE_NAME}.core.rbf ${DEPLOY_DIR_IMAGE}/core.rbf
     install -D -m 0644 ${B}/${UBOOT_CONFIG}/${ENCLUSTRA_BASE_NAME}.periph.rbf ${DEPLOY_DIR_IMAGE}/periph.rbf
}

#do_deploy:append:aa1-module() {
## TODO rm              
# TODO use, or replace by UBOOT_CONFIG                                 
#    ENCLUSTRA_BOOTMODE="sdmmc"
#    if ${@bb.utils.contains('UBOOT_CONFIG','sdmmc','true','false',d)}; then
#        ENCLUSTRA_BOOTMODE="sdmmc"
#    elif ${@bb.utils.contains('UBOOT_CONFIG','qspi','true','false',d)}; then
#        ENCLUSTRA_BOOTMODE="qspi"
#    fi

#     install -D -m 0644 ${B}/sdmmc/hps_isw_handoff/hps.xml ${DEPLOY_DIR_IMAGE}/hps.xml
#     install -D -m 0644 ${B}/sdmmc/${ENCLUSTRA_BASE_NAME}.core.rbf ${DEPLOY_DIR_IMAGE}/core.rbf
#     install -D -m 0644 ${B}/sdmmc/${ENCLUSTRA_BASE_NAME}.periph.rbf ${DEPLOY_DIR_IMAGE}/periph.rbf

## TODO uncomment                   
#     install -D -m 0644 ${B}/${UBOOT_CONFIG}/hps_isw_handoff/hps.xml ${DEPLOY_DIR_IMAGE}/hps.xml
#     install -D -m 0644 ${B}/${UBOOT_CONFIG}/${ENCLUSTRA_BASE_NAME}.core.rbf ${DEPLOY_DIR_IMAGE}/core.rbf
#     install -D -m 0644 ${B}/${UBOOT_CONFIG}/${ENCLUSTRA_BASE_NAME}.periph.rbf ${DEPLOY_DIR_IMAGE}/periph.rbf


    
#    if ${@bb.utils.contains('UBOOT_CONFIG','mercury-aa1-sd','true','false',d)}; then
#        # TODO further types     
#        install -D -m 0644 ${B}/sdmmc/hps_isw_handoff/hps.xml ${DEPLOY_DIR_IMAGE}/hps.xml
#        install -D -m 0644 ${B}/sdmmc/Mercury_AA1_PE1.core.rbf ${DEPLOY_DIR_IMAGE}/core.rbf
#        install -D -m 0644 ${B}/sdmmc/Mercury_AA1_PE1.periph.rbf ${DEPLOY_DIR_IMAGE}/periph.rbf
#    fi
#
#    if ${@bb.utils.contains('UBOOT_CONFIG','mercury-aa1-qspi','true','false',d)}; then
#        install -D -m 0644 ${B}/qspi/hps_isw_handoff/hps.xml ${DEPLOY_DIR_IMAGE}/hps.xml
#        install -D -m 0644 ${B}/qspi/Mercury_AA1_PE1.core.rbf ${DEPLOY_DIR_IMAGE}/core.rbf
#        install -D -m 0644 ${B}/qspi/Mercury_AA1_PE1.periph.rbf ${DEPLOY_DIR_IMAGE}/periph.rbf
#    fi

## TODO rm
#        unzip binaries_ME-AA1-270-3E4-D11E-NFX3_PE1.zip
#}

do_deploy:append:sa1-module() {
## TODO test if possible
#do_deploy:append:sa1-module:sa2-module() {

    install -D -m 0644 ${B}/${UBOOT_CONFIG}/hps_isw_handoff/hps.xml ${DEPLOY_DIR_IMAGE}/hps.xml
    install -D -m 0644 ${B}/${UBOOT_CONFIG}/${ENCLUSTRA_BASE_NAME}.core.rbf ${DEPLOY_DIR_IMAGE}/core.rbf
    install -D -m 0644 ${B}/${UBOOT_CONFIG}/${ENCLUSTRA_BASE_NAME}.periph.rbf ${DEPLOY_DIR_IMAGE}/periph.rbf


## TODO                                                   
#    if ${@bb.utils.contains('UBOOT_CONFIG','mercury-sa1-sd','true','false',d)}; then
#        cp -r ${B}/sdmmc/hps_isw_handoff/Mercury_SA1_pd_hpd_0/* ${DEPLOY_DIR_IMAGE}/sa1-handoff/system_hps_0
#	install -D -m 0644 ${B}/sdmmc/Mercury_SA1_PE1.rbf ${DEPLOY_DIR_IMAGE}/fpga.rbf
#    fi
#
#    if ${@bb.utils.contains('UBOOT_CONFIG','mercury-sa1-qspi','true','false',d)}; then
#        cp -r ${B}/qspi/hps_isw_handoff/Mercury_SA1_pd_hpd_0/* ${DEPLOY_DIR_IMAGE}/sa1-handoff/system_hps_0
#	install -D -m 0644 ${B}/qspi/Mercury_SA1_PE1.rbf ${DEPLOY_DIR_IMAGE}/fpga.rbf
#    fi
#
#    if ${@bb.utils.contains('UBOOT_CONFIG','mercury-sa1-emmc','true','false',d)}; then
#        cp -r ${B}/emmc/hps_isw_handoff/Mercury_SA1_pd_hpd_0/* ${DEPLOY_DIR_IMAGE}/sa1-handoff/system_hps_0
#	install -D -m 0644 ${B}/emmc/Mercury_SA1_PE1.rbf ${DEPLOY_DIR_IMAGE}/fpga.rbf
#    fi
}

#do_deploy:append:mercury-sa2() {
# TODO    
#}

#do_deploy:append:mercury-sa1() {
#    install -d ${DEPLOY_DIR_IMAGE}/sa1-handoff
#    install -d ${DEPLOY_DIR_IMAGE}/sa1-handoff/system_hps_0
#
#    if ${@bb.utils.contains('UBOOT_CONFIG','mercury-sa1-sd','true','false',d)}; then
#        cp -r ${B}/sdmmc/hps_isw_handoff/Mercury_SA1_pd_hpd_0/* ${DEPLOY_DIR_IMAGE}/sa1-handoff/system_hps_0
#	install -D -m 0644 ${B}/sdmmc/Mercury_SA1_PE1.rbf ${DEPLOY_DIR_IMAGE}/fpga.rbf
#    fi
#
#    if ${@bb.utils.contains('UBOOT_CONFIG','mercury-sa1-qspi','true','false',d)}; then
#        cp -r ${B}/qspi/hps_isw_handoff/Mercury_SA1_pd_hpd_0/* ${DEPLOY_DIR_IMAGE}/sa1-handoff/system_hps_0
#	install -D -m 0644 ${B}/qspi/Mercury_SA1_PE1.rbf ${DEPLOY_DIR_IMAGE}/fpga.rbf
#    fi
#
#    if ${@bb.utils.contains('UBOOT_CONFIG','mercury-sa1-emmc','true','false',d)}; then
#        cp -r ${B}/emmc/hps_isw_handoff/Mercury_SA1_pd_hpd_0/* ${DEPLOY_DIR_IMAGE}/sa1-handoff/system_hps_0
#	install -D -m 0644 ${B}/emmc/Mercury_SA1_PE1.rbf ${DEPLOY_DIR_IMAGE}/fpga.rbf
#    fi
#}
#
#do_deploy:append:mercury-sa2() {
#    install -d ${DEPLOY_DIR_IMAGE}/sa2-handoff
#    install -d ${DEPLOY_DIR_IMAGE}/sa2-handoff/system_hps_0
#
#    if ${@bb.utils.contains('UBOOT_CONFIG','mercury-sa2-sd','true','false',d)}; then
#        cp -r ${B}/sdmmc/hps_isw_handoff/Mercury_SA2_pd_hpd_0/* ${DEPLOY_DIR_IMAGE}/sa1-handoff/system_hps_0
#	install -D -m 0644 ${B}/sdmmc/Mercury_SA2_PE1.rbf ${DEPLOY_DIR_IMAGE}/fpga.rbf
#    fi
#
#    if ${@bb.utils.contains('UBOOT_CONFIG','mercury-sa2-sd','true','false',d)}; then
#        cp -r ${B}/qspi/hps_isw_handoff/Mercury_SA2_pd_hpd_0/* ${DEPLOY_DIR_IMAGE}/sa1-handoff/system_hps_0
#	install -D -m 0644 ${B}/qspi/Mercury_SA2_PE1.rbf ${DEPLOY_DIR_IMAGE}/fpga.rbf
#    fi
#}
#
addtask deploy after do_configure
