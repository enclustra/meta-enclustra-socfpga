SUMMARY = "Exported reference design binaries"

FILESEXTRAPATHS:prepend := "${THISDIR}/files:"

inherit deploy

LICENSE = "Proprietary"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/Proprietary;md5=0557f9d92cf58f2ccdd50f62f8ac0b28"

SRC_URI:mercury-aa1 = "\
	file://hps-aa1-qspi.xml \
	file://fpga-aa1-qspi.rbf \
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

addtask deploy after do_configure