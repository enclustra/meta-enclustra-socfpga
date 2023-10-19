SUMMARY = "U-boot boot environment for Intel SoCFPGA devices"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

FILESEXTRAPATHS:prepend := "${THISDIR}/env:"

DEPENDS = "u-boot-mkenvimage-native"

inherit deploy nopackages
PACKAGE_ARCH = "${MACHINE_ARCH}"

SRC_URI = "\
	file://mercury-aa1-sd_u-boot-env.txt \
	file://mercury-aa1-qspi_u-boot-env.txt \
	file://mercury-sa1_u-boot-env.txt \
	file://mercury-sa2_u-boot-env.txt \
	"

do_configure[noexec] = "1"
do_install[noexec] = "1"

do_compile() {
}

do_compile:append:mercury-aa1() {
	if [ ${UBOOT_CONFIG} = "mercury-aa1-sd" ]; then
		mkenvimage -s 0x80000 -o "${WORKDIR}/uboot.env" ${WORKDIR}/mercury-aa1-sd_u-boot-env.txt
	fi
	if [ ${UBOOT_CONFIG} = "mercury-aa1-qspi" ]; then
		mkenvimage -s 0x80000 -o "${WORKDIR}/uboot.env" ${WORKDIR}/mercury-aa1-qspi_u-boot-env.txt
	fi
}

do_compile:append:mercury-sa1() {
        mkenvimage -s 0x80000 -o "${WORKDIR}/uboot.env" ${WORKDIR}/mercury-sa1_u-boot-env.txt
}

do_compile:append:mercury-sa2() {
	mkenvimage -s 0x80000 -o "${WORKDIR}/uboot.env" ${WORKDIR}/mercury-sa2_u-boot-env.txt
}

do_deploy(){
	install -m 0644 ${WORKDIR}/uboot.env ${DEPLOYDIR}/u-boot-socfpga-${MACHINE}-${PV}-${PR}.env
	ln -sf u-boot-socfpga-${MACHINE}-${PV}-${PR}.env ${DEPLOYDIR}/uboot.env
}

addtask do_deploy after do_compile before do_build