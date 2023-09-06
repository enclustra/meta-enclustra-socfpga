SUMMARY = "Exported reference design binaries"

FILESEXTRAPATHS:prepend := "${THISDIR}/${MACHINE}/:"
FILESEXTRAPATHS:prepend := "${THISDIR}/${MACHINE}/handoff/:"

inherit deploy

LICENSE = "Proprietary"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/Proprietary;md5=0557f9d92cf58f2ccdd50f62f8ac0b28"

EBE_RELEASE := "update"
SRC_URI:mercury-aa1 = "\
	http://www.enclustra.com/binaries/enclustra-bsp/${EBE_RELEASE}/refdes/ME-AA1-480-2I3-D12E-NFX3_PE1.zip;name=aa14802i3 \
        http://www.enclustra.com/binaries/enclustra-bsp/${EBE_RELEASE}/refdes/ME-AA1-270-2I2-D11E-NFX3_PE1.zip;name=aa12702i2 \
        http://www.enclustra.com/binaries/enclustra-bsp/${EBE_RELEASE}/refdes/ME-AA1-270-3E4-D11E-NFX3_PE1.zip;name=aa12703e4 \
	"

SRC_URI[aa14802i3.sha256sum] = "8596579fd774028be8bcc88d6aca391c2e3e6ddca3ec094bda3512cc0defebd7"
SRC_URI[aa12702i2.sha256sum] = "c87b5889fd16b14f66b8d3e5183e97efc7ef36b0fe3d23c8c81ac5c5bbd357b2"
SRC_URI[aa12703e4.sha256sum] = "fdc8dbd287563b8989f296656262ca559ec668163e76c853d80d9e005a3f9236"

SRC_URI:mercury-sa1 = "\
	file://fpga-sa1.rbf \
	file://alt_types.h \
	file://emif.xml \
	file://hps.xml \
	file://id \
	file://sdram_io.h \
	file://sequencer_auto_ac_init.c \
	file://sequencer_auto.h \
	file://sequencer_auto_inst_init.c \
	file://sequencer.c \
	file://sequencer_defines.h \
	file://sequencer.h \
	file://system.h \
	file://system_hps_0.hiof \
	file://tclrpt.c \
	file://tclrpt.h \
	"

SRC_URI:mercury-sa2 = "\
	file://fpga-sa2.rbf \
	file://alt_types.h \
	file://emif.xml \
	file://hps.xml \
	file://id \
	file://sdram_io.h \
	file://sequencer_auto_ac_init.c \
	file://sequencer_auto.h \
	file://sequencer_auto_inst_init.c \
	file://sequencer.c \
	file://sequencer_defines.h \
	file://sequencer.h \
	file://system.h \
	file://system_hps_0.hiof \
	file://tclrpt.c \
	file://tclrpt.h \
	"

S ?= "${WORKDIR}/${MACHINE}"

PROVIDES = "virtual/bitstream"

do_fetch[depends] += "unzip-native:do_populate_sysroot"

do_unpack() {
}

do_unpack:append:mercury-aa1() {
#        ${bindir}/env unzip -q -o "${DL_DIR}/ME-AA1-480-2I3-D12E-NFX3_PE1.zip" -d ${S}
#        ${bindir}/env unzip -q -o "${DL_DIR}/ME-AA1-270-2I2-D11E-NFX3_PE1.zip" -d ${S}
        ${bindir}/env unzip -q -o "${DL_DIR}/ME-AA1-270-3E4-D11E-NFX3_PE1.zip" -d ${S}
}

do_deploy[nostamp] = "1"

do_deploy() {
}

# TODO improve this...      
do_deploy:append:mercury-aa1() {
	if ${@bb.utils.contains('UBOOT_CONFIG','mercury-aa1-sd','true','false',d)}; then
                # TODO further types     
		install -D -m 0644 ${B}/sdmmc/hps_isw_handoff/hps.xml ${DEPLOY_DIR_IMAGE}/hps.xml
                install -D -m 0644 ${B}/sdmmc/Mercury_AA1_PE1.core.rbf ${DEPLOY_DIR_IMAGE}/core.rbf
                install -D -m 0644 ${B}/sdmmc/Mercury_AA1_PE1.periph.rbf ${DEPLOY_DIR_IMAGE}/periph.rbf
	fi

	if ${@bb.utils.contains('UBOOT_CONFIG','mercury-aa1-qspi','true','false',d)}; then
		install -D -m 0644 ${B}/qspi/hps_isw_handoff/hps.xml ${DEPLOY_DIR_IMAGE}/hps.xml
                install -D -m 0644 ${B}/qspi/Mercury_AA1_PE1.core.rbf ${DEPLOY_DIR_IMAGE}/core.rbf
                install -D -m 0644 ${B}/qspi/Mercury_AA1_PE1.periph.rbf ${DEPLOY_DIR_IMAGE}/periph.rbf
	fi

        ## TODO rm
#        unzip binaries_ME-AA1-270-3E4-D11E-NFX3_PE1.zip
}

do_deploy:append:mercury-sa1() {
	install -d ${DEPLOY_DIR_IMAGE}/sa1-handoff
	install -d ${DEPLOY_DIR_IMAGE}/sa1-handoff/system_hps_0
	install -D -m 0644 ${WORKDIR}/fpga-sa1.rbf ${DEPLOY_DIR_IMAGE}/fpga.rbf
	install -D -m 0644 ${WORKDIR}/alt_types.h ${DEPLOY_DIR_IMAGE}/sa1-handoff/system_hps_0/
	install -D -m 0644 ${WORKDIR}/emif.xml ${DEPLOY_DIR_IMAGE}/sa1-handoff/system_hps_0/
	install -D -m 0644 ${WORKDIR}/hps.xml ${DEPLOY_DIR_IMAGE}/sa1-handoff/system_hps_0/
	install -D -m 0644 ${WORKDIR}/id ${DEPLOY_DIR_IMAGE}/sa1-handoff/system_hps_0/
	install -D -m 0644 ${WORKDIR}/sdram_io.h ${DEPLOY_DIR_IMAGE}/sa1-handoff/system_hps_0/
	install -D -m 0644 ${WORKDIR}/sequencer_auto_ac_init.c ${DEPLOY_DIR_IMAGE}/sa1-handoff/system_hps_0/
	install -D -m 0644 ${WORKDIR}/sequencer_auto.h ${DEPLOY_DIR_IMAGE}/sa1-handoff/system_hps_0/
	install -D -m 0644 ${WORKDIR}/sequencer_auto_inst_init.c ${DEPLOY_DIR_IMAGE}/sa1-handoff/system_hps_0/
	install -D -m 0644 ${WORKDIR}/sequencer.c ${DEPLOY_DIR_IMAGE}/sa1-handoff/system_hps_0/
	install -D -m 0644 ${WORKDIR}/sequencer_defines.h ${DEPLOY_DIR_IMAGE}/sa1-handoff/system_hps_0/
	install -D -m 0644 ${WORKDIR}/sequencer.h ${DEPLOY_DIR_IMAGE}/sa1-handoff/system_hps_0/
	install -D -m 0644 ${WORKDIR}/system.h ${DEPLOY_DIR_IMAGE}/sa1-handoff/system_hps_0/
	install -D -m 0644 ${WORKDIR}/system_hps_0.hiof ${DEPLOY_DIR_IMAGE}/sa1-handoff/system_hps_0/
	install -D -m 0644 ${WORKDIR}/tclrpt.c ${DEPLOY_DIR_IMAGE}/sa1-handoff/system_hps_0/
	install -D -m 0644 ${WORKDIR}/tclrpt.h ${DEPLOY_DIR_IMAGE}/sa1-handoff/system_hps_0/
}

do_deploy:append:mercury-sa2() {
	install -d ${DEPLOY_DIR_IMAGE}/sa2-handoff
	install -d ${DEPLOY_DIR_IMAGE}/sa2-handoff/system_hps_0
	install -D -m 0644 ${WORKDIR}/fpga-sa2.rbf ${DEPLOY_DIR_IMAGE}/fpga.rbf
	install -D -m 0644 ${WORKDIR}/alt_types.h ${DEPLOY_DIR_IMAGE}/sa2-handoff/system_hps_0/
	install -D -m 0644 ${WORKDIR}/emif.xml ${DEPLOY_DIR_IMAGE}/sa2-handoff/system_hps_0/
	install -D -m 0644 ${WORKDIR}/hps.xml ${DEPLOY_DIR_IMAGE}/sa2-handoff/system_hps_0/
	install -D -m 0644 ${WORKDIR}/id ${DEPLOY_DIR_IMAGE}/sa2-handoff/system_hps_0/
	install -D -m 0644 ${WORKDIR}/sdram_io.h ${DEPLOY_DIR_IMAGE}/sa2-handoff/system_hps_0/
	install -D -m 0644 ${WORKDIR}/sequencer_auto_ac_init.c ${DEPLOY_DIR_IMAGE}/sa2-handoff/system_hps_0/
	install -D -m 0644 ${WORKDIR}/sequencer_auto.h ${DEPLOY_DIR_IMAGE}/sa2-handoff/system_hps_0/
	install -D -m 0644 ${WORKDIR}/sequencer_auto_inst_init.c ${DEPLOY_DIR_IMAGE}/sa2-handoff/system_hps_0/
	install -D -m 0644 ${WORKDIR}/sequencer.c ${DEPLOY_DIR_IMAGE}/sa2-handoff/system_hps_0/
	install -D -m 0644 ${WORKDIR}/sequencer_defines.h ${DEPLOY_DIR_IMAGE}/sa2-handoff/system_hps_0/
	install -D -m 0644 ${WORKDIR}/sequencer.h ${DEPLOY_DIR_IMAGE}/sa2-handoff/system_hps_0/
	install -D -m 0644 ${WORKDIR}/system.h ${DEPLOY_DIR_IMAGE}/sa2-handoff/system_hps_0/
	install -D -m 0644 ${WORKDIR}/system_hps_0.hiof ${DEPLOY_DIR_IMAGE}/sa2-handoff/system_hps_0/
	install -D -m 0644 ${WORKDIR}/tclrpt.c ${DEPLOY_DIR_IMAGE}/sa2-handoff/system_hps_0/
	install -D -m 0644 ${WORKDIR}/tclrpt.h ${DEPLOY_DIR_IMAGE}/sa2-handoff/system_hps_0/
}

addtask deploy after do_configure
