SUMMARY = "U-boot boot scripts for Intel SoCFPGA devices"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

FILESEXTRAPATHS:prepend := "${THISDIR}/scr:"

DEPENDS = "u-boot-mkimage-native dtc-native"

inherit deploy nopackages
PACKAGE_ARCH = "${MACHINE_ARCH}"

SRC_URI = "\
	file://u-boot-qspi.txt \
	file://u-boot-sd.txt \
	file://u-boot-sd-aa1.txt \
	"

do_configure[noexec] = "1"
do_install[noexec] = "1"

do_compile() {
}

do_compile:append:mercury-sa1() {
	mkimage -A arm -O linux -T script -C none -a 0 -e 0 -n "QSPI Script" -d "${WORKDIR}/u-boot-qspi.txt" ${WORKDIR}/boot-qspi.scr
	mkimage -A arm -O linux -T script -C none -a 0 -e 0 -n "SD Card Script" -d "${WORKDIR}/u-boot-sd.txt" ${WORKDIR}/boot-sd.scr
}

do_compile:append:mercury-sa2() {
	mkimage -A arm -O linux -T script -C none -a 0 -e 0 -n "QSPI Script" -d "${WORKDIR}/u-boot-qspi.txt" ${WORKDIR}/boot-qspi.scr
	mkimage -A arm -O linux -T script -C none -a 0 -e 0 -n "SD Card Script" -d "${WORKDIR}/u-boot-sd.txt" ${WORKDIR}/boot-sd.scr
}

do_compile:append:mercury-aa1() {
	mkimage -A arm -O linux -T script -C none -a 0 -e 0 -n "QSPI Script" -d "${WORKDIR}/u-boot-qspi.txt" ${WORKDIR}/boot-qspi.scr
	mkimage -A arm -O linux -T script -C none -a 0 -e 0 -n "SD Card Script" -d "${WORKDIR}/u-boot-sd-aa1.txt" ${WORKDIR}/boot-sd.scr
}

do_deploy() {
	install -d ${DEPLOYDIR}
	install -m 0644 ${WORKDIR}/boot-qspi.scr ${DEPLOYDIR}/boot-qspi.scr
	install -m 0644 ${WORKDIR}/boot-sd.scr ${DEPLOYDIR}/boot-sd.scr
}

addtask do_deploy after do_compile before do_build