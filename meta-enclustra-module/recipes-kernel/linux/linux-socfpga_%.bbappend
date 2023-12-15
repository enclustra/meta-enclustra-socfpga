FILESEXTRAPATHS:prepend := "${THISDIR}/files:"

# Kernel config is provided in recipe
unset KBUILD_DEFCONFIG

SRC_URI:append = " \
        file://0001-Add-Enclustra-devicetree-to-Makefile.patch \
        file://0002-crypto-atmel-add-AT-SHA204-EEPROM-support.patch \
        file://0003-mtd-spi-nor-Prevent-a-bricked-S25FL512S-flash.patch \
"
SRC_URI:append:me-aa1-generic = " file://socfpga_enclustra_mercury_aa1_defconfig"
SRC_URI:append:me-sa1-c6-7i-d10 = " file://socfpga_enclustra_mercury_sa1_defconfig"
SRC_URI:append:me-sa2-d6-7i-d11 = " file://socfpga_enclustra_mercury_sa2_defconfig"

PROVIDES += "uImage"

do_configure:prepend:me-aa1-generic() {
	cp ${WORKDIR}/socfpga_enclustra_mercury_aa1_defconfig ${S}/arch/arm/configs
}

do_configure:prepend:me-sa1-c6-7i-d10() {
	cp ${WORKDIR}/socfpga_enclustra_mercury_sa1_defconfig ${S}/arch/arm/configs
}

do_configure:prepend:me-sa2-d6-7i-d11() {
	cp ${WORKDIR}/socfpga_enclustra_mercury_sa2_defconfig ${S}/arch/arm/configs
}
