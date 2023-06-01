SUMMARY = "U-boot boot environment for Intel SoCFPGA devices"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

FILESEXTRAPATHS:prepend := "${THISDIR}/env:"

DEPENDS = "u-boot-mkenvimage-native"

inherit deploy nopackages
PACKAGE_ARCH = "${MACHINE_ARCH}"

SRC_URI = "\
	file://mercury-aa1-qspi_u-boot-env.txt \
	file://mercury-sa1_u-boot-env.txt \
	file://mercury-sa2_u-boot-env.txt \
	"

do_configure[noexec] = "1"
do_install[noexec] = "1"

do_compile:mercury-aa1() {
	mkenvimage -s 0x80000 -o "${WORKDIR}/uboot.env" ${WORKDIR}/mercury-aa1-qspi_u-boot-env.txt
}

do_compile:mercury-sa1() {
        mkenvimage -s 0x80000 -o "${WORKDIR}/uboot.env" ${WORKDIR}/mercury-sa1_u-boot-env.txt
}

do_compile:mercury-sa2() {
	mkenvimage -s 0x80000 -o "${WORKDIR}/uboot.env" ${WORKDIR}/mercury-sa2_u-boot-env.txt
}

do_deploy(){
	install -m 0644 ${WORKDIR}/uboot.env ${DEPLOYDIR}/u-boot-socfpga-${MACHINE}-${PV}-${PR}.env
	ln -sf u-boot-socfpga-${MACHINE}-${PV}-${PR}.env ${DEPLOYDIR}/uboot.env
}

do_deploy:prepend:mercury-aa1() {
	install -d ${DEPLOYDIR}
	install -m 0755 ${WORKDIR}/mercury-aa1-qspi_u-boot-env.txt ${DEPLOYDIR}/u-boot-env.txt
}

do_deploy:prepend:mercury-sa1() {
        install -d ${DEPLOYDIR}
        install -m 0755 ${WORKDIR}/mercury-sa1_u-boot-env.txt ${DEPLOYDIR}/u-boot-env.txt
}

do_deploy:prepend:mercury-sa2() {
	install -d ${DEPLOYDIR}
	install -m 0755 ${WORKDIR}/mercury-sa2_u-boot-env.txt ${DEPLOYDIR}/u-boot-env.txt
}

addtask do_deploy after do_compile before do_build