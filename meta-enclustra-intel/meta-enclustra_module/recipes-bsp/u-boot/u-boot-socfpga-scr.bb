SUMMARY = "U-boot boot scripts for Intel SoCFPGA devices"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

FILESEXTRAPATHS:prepend:aa1-module := "${THISDIR}/scr/aa1-module:"
FILESEXTRAPATHS:prepend:sa1-module := "${THISDIR}/scr/sa1-module:"
FILESEXTRAPATHS:prepend:sa2-module := "${THISDIR}/scr/sa2-module:"

DEPENDS = "u-boot-mkimage-native dtc-native"

inherit deploy nopackages

# TODO rm   
PACKAGE_ARCH = "${MACHINE_ARCH}"

# TODO extend       
SRC_URI = " \
        file://u-boot-qspi.txt \
        file://u-boot-sd.txt \
"

## skip
do_configure[noexec] = "1"
do_install[noexec] = "1"

do_compile() {
}

do_compile:append() {
#	mkimage -A arm -O linux -T script -C none -a 0 -e 0 -n "Boot Script" -d "${WORKDIR}/u-boot-${UBOOT_CONFIG}.txt" ${WORKDIR}/boot-${UBOOT_CONFIG}.scr
	mkimage -A arm -O linux -T script -C none -a 0 -e 0 -n "QSPI Script" -d "${WORKDIR}/u-boot-qspi.txt" ${WORKDIR}/boot-qspi.scr
	mkimage -A arm -O linux -T script -C none -a 0 -e 0 -n "SD Card Script" -d "${WORKDIR}/u-boot-sd.txt" ${WORKDIR}/boot-sd.scr
}

do_deploy() {
    install -d ${DEPLOYDIR}
    install -m 0644 ${WORKDIR}/*.scr ${DEPLOYDIR}/
## TODO rm          
#    if [ ${UBOOT_CONFIG} = "sdmmc" ]; then
#       install -m 0644 ${WORKDIR}/boot-sd.scr ${DEPLOYDIR}/boot.scr
#    elif [${UBOOT_CONFIG} = "emmc" ]; then
#       install -m 0644 ${WORKDIR}/boot-sd.scr ${DEPLOYDIR}/boot.scr
#    elif [${UBOOT_CONFIG} = "qspi" ]; then
#       install -m 0644 ${WORKDIR}/boot-qspi.scr ${DEPLOYDIR}/boot.scr
#    fi
}

addtask do_deploy after do_compile before do_build
