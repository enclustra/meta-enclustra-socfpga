FILESEXTRAPATHS:prepend := "${THISDIR}/files:"

# Kernel config is provided in recipe
unset KBUILD_DEFCONFIG

SRC_URI:append:aa1-module = " file://socfpga_enclustra_mercury_aa1_defconfig"
SRC_URI:append:sa1-module = " file://socfpga_enclustra_mercury_sa1_defconfig"
SRC_URI:append:sa2-module = " file://socfpga_enclustra_mercury_sa2_defconfig"

SRC_URI:append = " \
        file://0001-Add-Enclustra-devicetree-to-Makefile.patch \
        file://0002-crypto-atmel-add-AT-SHA204-EEPROM-support.patch \
        file://0003-mtd-spi-nor-Prevent-a-bricked-S25FL512S-flash.patch \
"

## TODO needed??    
#         file://0005-rest-indifferent.patch

## TODO check is this patch really needed?        
#SRC_URI:append:aa1-module = " file://0050-Update-socfpga_arria10.patch"

PROVIDES += "uImage"

do_configure:prepend:aa1-module() {
	cp ${WORKDIR}/socfpga_enclustra_mercury_aa1_defconfig ${S}/arch/arm/configs
}

do_configure:prepend:sa1-module() {
	cp ${WORKDIR}/socfpga_enclustra_mercury_sa1_defconfig ${S}/arch/arm/configs
}

do_configure:prepend:sa2-module() {
	cp ${WORKDIR}/socfpga_enclustra_mercury_sa2_defconfig ${S}/arch/arm/configs
}
