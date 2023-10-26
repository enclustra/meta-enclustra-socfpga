SUMMARY = "U-boot boot environment for Intel SoCFPGA devices"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

#FILESEXTRAPATHS:prepend := "${THISDIR}/env:"

FILESEXTRAPATHS:prepend:aa1-module := "${THISDIR}/env/aa1-module:"
FILESEXTRAPATHS:prepend:sa1-module := "${THISDIR}/env/sa1-module:"
FILESEXTRAPATHS:prepend:sa2-module := "${THISDIR}/env/sa2-module:"

DEPENDS = "u-boot-mkenvimage-native"

inherit deploy nopackages

#PACKAGE_ARCH = "${MACHINE_ARCH}"
#
#SRC_URI = "\
#	file://mercury-aa1-sd_u-boot-env.txt \
#	file://mercury-aa1-qspi_u-boot-env.txt \
#	file://mercury-sa1_u-boot-env.txt \
#	file://mercury-sa2_u-boot-env.txt \
#	"
SRC_URI:append:aa1-module = " file://sd_u-boot-env.txt file://qspi_u-boot-env.txt"
SRC_URI:append:sa1-module = " file://u-boot-env.txt"
SRC_URI:append:sa2-module = " file://u-boot-env.txt"

do_configure[noexec] = "1"
do_install[noexec] = "1"

do_compile() {
}

# TODO verify if 2xif can be replaced by "elif"
#do_compile:append:aa1-module() {  
do_compile:append() {
	if [ ${UBOOT_CONFIG} = "sdmmc" ]; then
		mkenvimage -s 0x80000 -o "${WORKDIR}/uboot.env" ${WORKDIR}/sd_u-boot-env.txt
	elif [ ${UBOOT_CONFIG} = "emmc" ]; then
		mkenvimage -s 0x80000 -o "${WORKDIR}/uboot.env" ${WORKDIR}/sd_u-boot-env.txt
	elif [ ${UBOOT_CONFIG} = "qspi" ]; then
		mkenvimage -s 0x80000 -o "${WORKDIR}/uboot.env" ${WORKDIR}/qspi_u-boot-env.txt
	else
                mkenvimage -s 0x80000 -o "${WORKDIR}/uboot.env" ${WORKDIR}/u-boot-env.txt
        fi
}

## TODO rm    
#do_compile:append:sa1-module() {
#        mkenvimage -s 0x80000 -o "${WORKDIR}/uboot.env" ${WORKDIR}/u-boot-env.txt
#}
#
#do_compile:append:sa2-module() {
#	mkenvimage -s 0x80000 -o "${WORKDIR}/uboot.env" ${WORKDIR}/u-boot-env.txt
#}

do_deploy(){
	install -m 0644 ${WORKDIR}/uboot.env ${DEPLOYDIR}/u-boot-socfpga-${MACHINE}-${PV}-${PR}.env
	ln -sf u-boot-socfpga-${MACHINE}-${PV}-${PR}.env ${DEPLOYDIR}/uboot.env
}

addtask do_deploy after do_compile before do_build
