FILESEXTRAPATHS:prepend := "${THISDIR}/files:"

# Kernel config is provided in recipe
unset KBUILD_DEFCONFIG

SRC_URI:append = " \
	file://mercury-aa1-qspi_defconfig \
	file://mercury-sa1_defconfig \
	file://mercury-sa2_defconfig \
	"

do_configure:prepend:mercury-aa1() {
	cp ${WORKDIR}/mercury-aa1-qspi_defconfig ${S}/arch/arm/configs
}

do_configure:prepend:mercury-sa1() {
	cp ${WORKDIR}/mercury-sa1_defconfig ${S}/arch/arm/configs
}

do_configure:prepend:mercury-sa2() {
	cp ${WORKDIR}/mercury-sa2_defconfig ${S}/arch/arm/configs
}