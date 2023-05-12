SUMMARY = "Intel SoCFPGA Golden Hardware Reference Design (GHRD)"
DESCRIPTION = "Prebuilt FPGA bitstream for SOC Development Kit"
SECTION = "bsp"

FILESEXTRAPATHS:prepend := "${THISDIR}/files:"

inherit deploy

LICENSE = "Proprietary"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/Proprietary;md5=0557f9d92cf58f2ccdd50f62f8ac0b28"

SRC_URI:mercury-aa1 = "\
		file://refdes_hps.xml \
		file://fpga.rbf \
		"

S ?= "${WORKDIR}/${MACHINE}"

PROVIDES = "virtual/bitstream"

FILES:${PN} += " \
		/boot \
		/lib/firmware \
		"

PACKAGES = "${PN}"

PACKAGE_ARCH = "${MACHINE_ARCH}"

do_deploy[nostamp] = "1"

do_install () {
}

do_deploy () {
	install -D -m 0644 ${WORKDIR}/refdes_hps.xml ${DEPLOY_DIR_IMAGE}/refdes_hps.xml
	install -D -m 0644 ${WORKDIR}/fpga.rbf ${DEPLOY_DIR_IMAGE}/fpga.rbf
}

addtask install after do_configure before do_deploy
addtask deploy after do_install