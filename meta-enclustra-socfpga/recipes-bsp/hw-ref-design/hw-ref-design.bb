SUMMARY = "Exported reference design binaries"

FILESEXTRAPATHS:prepend := "${THISDIR}/${MACHINE}/:"
FILESEXTRAPATHS:prepend := "${THISDIR}/${MACHINE}/handoff/:"

inherit deploy

LICENSE = "Proprietary"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/Proprietary;md5=0557f9d92cf58f2ccdd50f62f8ac0b28"

SRC_URI:mercury-aa1 = "\
	file://hps-aa1-qspi.xml \
	file://fpga-aa1-qspi.rbf \
	"

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

do_deploy[nostamp] = "1"

do_deploy() {
}

do_deploy:append:mercury-aa1() {
	install -D -m 0644 ${WORKDIR}/hps-aa1-qspi.xml ${DEPLOY_DIR_IMAGE}/hps.xml
	install -D -m 0644 ${WORKDIR}/fpga-aa1-qspi.rbf ${DEPLOY_DIR_IMAGE}/fpga.rbf
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
