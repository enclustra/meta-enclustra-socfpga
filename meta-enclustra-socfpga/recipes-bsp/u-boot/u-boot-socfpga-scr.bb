SUMMARY = "U-boot boot scripts for Intel SoCFPGA devices"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

FILESEXTRAPATHS:prepend := "${THISDIR}/files:"

DEPENDS = "u-boot-mkimage-native dtc-native"

inherit deploy nopackages
PACKAGE_ARCH = "${MACHINE_ARCH}"

SRC_URI = "file://u-boot.txt"

do_configure[noexec] = "1"
do_install[noexec] = "1"

do_compile:mercury-aa1() {
	mkimage -A arm -O linux -T script -C none -a 0 -e 0 -n "Arria10 Script" -d "${WORKDIR}/u-boot.txt" ${WORKDIR}/boot.scr
}

do_deploy() {
	install -d ${DEPLOYDIR}
	install -m 0755 ${WORKDIR}/u-boot.txt ${DEPLOYDIR}/u-boot.txt
	install -m 0644 ${WORKDIR}/boot.scr ${DEPLOYDIR}/boot.scr
}

addtask do_deploy after do_compile before do_build