SUMMARY = "Intel SoCFPGA Development Kit devicetrees"
DESCRIPTION = "Devicetree addons for Intel SoCFPGA Development module"
SECTION = "bsp"
LICENSE = "MIT & GPL-2.0-only"

inherit devicetree

PROVIDES = "virtual/dtb"

KERNEL_INCLUDE = " \
        ${STAGING_KERNEL_DIR}/arch/${ARCH}/boot/dts \
        ${STAGING_KERNEL_DIR}/arch/${ARCH}/boot/dts/* \
        ${STAGING_KERNEL_DIR}/scripts/dtc/include-prefixes \
        ${STAGING_KERNEL_DIR}/include \
        ${STAGING_KERNEL_DIR}/include/dt-bindings/interrupt-controller \
        ${STAGING_KERNEL_DIR}/include/dt-bindings/reset \
        "

## TODO decide where to place the (sd)mmc overlay and naming         
## TODO either use "_sdmmc_boot.dtsi" - or _sdmmc_overlay.dtsi in baseboard layer                    
SRC_URI:append:aa1-module = " file://socfpga_enclustra_mercury_aa1.dtsi \
                          file://socfpga_enclustra_mercury_aa1_emmc_boot.dtsi \
                          file://socfpga_enclustra_mercury_aa1_sdmmc_boot.dtsi \
                          file://socfpga_enclustra_mercury_aa1_qspi_boot.dtsi \
"
SRC_URI:append:sa1-module = " file://socfpga_enclustra_mercury_sa1.dtsi file://ME-SA1-C6-7I-D10.dtsi"
SRC_URI:append:sa2-module = " file://socfpga_enclustra_mercury_sa2.dtsi file://ME-SA2-D6-7I-D11.dtsi"

SRC_URI:append:aa1sx270e3-module = " file://ME-AA1-270-3E4-D11E-NFX3.dtsi"
SRC_URI:append:aa1sx270i2-module = " file://ME-AA1-270-2I2-D11E-NFX3.dtsi"
SRC_URI:append:aa1sx480i2-module = " file://ME-AA1-480-2I3-D12E-NFX3.dtsi"

## TODO use the sdmmc / qspi overlays where needed depending on the ${UBOOT_CONFIG} - implement!!!                    
## NB: don't replace emmc/sdmmc/qspi here by UBOOT_CONFIG - would fail, if file is not there...
#SRC_URI:append = " file://socfpga_enclustra_mercury_emmc_overlay.dtsi"
#SRC_URI:append = " file://socfpga_enclustra_mercury_sdmmc_overlay.dtsi"
#SRC_URI:append = " file://socfpga_enclustra_mercury_qspi_overlay.dtsi"

COMPATIBLE_MACHINE = "|aa1-module|aa1sx270e3-module|aa1sx270i2-module|aa1sx480i2-module|sa1-module|sa2-module"

do_configure[depends] += "virtual/kernel:do_configure"

do_deploy:append() {
    install -Dm 0644 ${B}/enclustra_generated.dtb ${DEPLOYDIR}/devicetree.dtb
}
