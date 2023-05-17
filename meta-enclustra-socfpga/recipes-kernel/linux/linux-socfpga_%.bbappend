FILESEXTRAPATHS:prepend := "${THISDIR}/files:"

# Kernel config is provided in recipe
unset KBUILD_DEFCONFIG

SRC_URI:append:mercury-aa1 = " \
	file://mercury-aa1-qspi_defconfig \
	"

do_configure:prepend:mercury-aa1() {
	cp ${WORKDIR}/mercury-aa1-qspi_defconfig ${S}/arch/arm/configs
}