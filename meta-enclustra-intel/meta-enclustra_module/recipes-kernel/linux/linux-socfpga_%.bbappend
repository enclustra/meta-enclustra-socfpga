FILESEXTRAPATHS:prepend := "${THISDIR}/files:"

# Kernel config is provided in recipe
unset KBUILD_DEFCONFIG

SRC_URI:append:aa1-module = " file://mercury-aa1_defconfig"
SRC_URI:append:sa1-module = " file://mercury-sa1_defconfig"
SRC_URI:append:sa2-module = " file://mercury-sa2_defconfig"

SRC_URI:append = " \
	file://0001-Add-atsha204a-driver-with-support-to-read-OTP-region.patch \
	"

PROVIDES += "uImage"

do_configure:prepend:aa1-module() {
	cp ${WORKDIR}/mercury-aa1_defconfig ${S}/arch/arm/configs
}

do_configure:prepend:sa1-module() {
	cp ${WORKDIR}/mercury-sa1_defconfig ${S}/arch/arm/configs
}

do_configure:prepend:sa2-module() {
	cp ${WORKDIR}/mercury-sa2_defconfig ${S}/arch/arm/configs
}
