SUMMARY = "U-boot boot scripts for Intel SoCFPGA devices"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

FILESEXTRAPATHS:prepend := "${THISDIR}/files:"

DEPENDS = "u-boot-mkimage-native dtc-native"

inherit deploy nopackages
PACKAGE_ARCH = "${MACHINE_ARCH}"

SRC_URI = "\
	file://u-boot-qspi.txt \
	file://u-boot-sd.txt \
	"

do_configure[noexec] = "1"
do_install[noexec] = "1"

do_compile() {
	mkimage -A arm -O linux -T script -C none -a 0 -e 0 -n "QSPI Script" -d "${WORKDIR}/u-boot-qspi.txt" ${WORKDIR}/boot-qspi.scr
	mkimage -A arm -O linux -T script -C none -a 0 -e 0 -n "SD Card Script" -d "${WORKDIR}/u-boot-sd.txt" ${WORKDIR}/boot-sd.scr
}

do_deploy() {
	install -d ${DEPLOYDIR}
}

do_deploy:append:mercury-aa1() {
	install -m 0755 ${WORKDIR}/u-boot-qspi.txt ${DEPLOYDIR}/u-boot.txt
	install -m 0644 ${WORKDIR}/boot-qspi.scr ${DEPLOYDIR}/boot.scr
}

do_deploy:append:mercury-sa2() {
        install -m 0755 ${WORKDIR}/u-boot-sd.txt ${DEPLOYDIR}/u-boot.txt
        install -m 0644 ${WORKDIR}/boot-sd.scr ${DEPLOYDIR}/boot.scr
}

addtask do_deploy after do_compile before do_build