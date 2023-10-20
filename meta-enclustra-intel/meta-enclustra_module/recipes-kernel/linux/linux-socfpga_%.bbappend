FILESEXTRAPATHS:prepend := "${THISDIR}/files:"

# Kernel config is provided in recipe
unset KBUILD_DEFCONFIG

SRC_URI:append = " \
	file://mercury-aa1_defconfig \
	file://mercury-sa1_defconfig \
	file://mercury-sa2_defconfig \
	"

SRC_URI:append = " \
	file://0001-Add-atsha204a-driver-with-support-to-read-OTP-region.patch \
	"

do_configure:prepend:aa1-module() {
	cp ${WORKDIR}/mercury-aa1_defconfig ${S}/arch/arm/configs
}

do_configure:prepend:sa1-module() {
	cp ${WORKDIR}/mercury-sa1_defconfig ${S}/arch/arm/configs
}

do_configure:prepend:sa2-module() {
	cp ${WORKDIR}/mercury-sa2_defconfig ${S}/arch/arm/configs
}
