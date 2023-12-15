FILESEXTRAPATHS:prepend := "${THISDIR}/files/common:"

FILESEXTRAPATHS:prepend:refdes-aa1sx270e3-pe1 := "${THISDIR}/files/refdes-aa1sx270e3-pe1:"
FILESEXTRAPATHS:prepend:refdes-aa1sx270e3-pe3 := "${THISDIR}/files/refdes-aa1sx270e3-pe3:"
FILESEXTRAPATHS:prepend:refdes-aa1sx270e3-st1 := "${THISDIR}/files/refdes-aa1sx270e3-st1:"
FILESEXTRAPATHS:prepend:refdes-aa1sx270i2-pe1 := "${THISDIR}/files/refdes-aa1sx270i2-pe1:"
FILESEXTRAPATHS:prepend:refdes-aa1sx270i2-pe3 := "${THISDIR}/files/refdes-aa1sx270i2-pe3:"
FILESEXTRAPATHS:prepend:refdes-aa1sx270i2-st1 := "${THISDIR}/files/refdes-aa1sx270i2-st1:"
FILESEXTRAPATHS:prepend:refdes-aa1sx480i2-pe1 := "${THISDIR}/files/refdes-aa1sx480i2-pe1:"
FILESEXTRAPATHS:prepend:refdes-aa1sx480i2-pe3 := "${THISDIR}/files/refdes-aa1sx480i2-pe3:"
FILESEXTRAPATHS:prepend:refdes-aa1sx480i2-st1 := "${THISDIR}/files/refdes-aa1sx480i2-st1:"
FILESEXTRAPATHS:prepend:refdes-sa1-pe1 := "${THISDIR}/files/refdes-sa1-pe1:"
FILESEXTRAPATHS:prepend:refdes-sa1-pe3 := "${THISDIR}/files/refdes-sa1-pe3:"
FILESEXTRAPATHS:prepend:refdes-sa1-st1 := "${THISDIR}/files/refdes-sa1-st1:"
FILESEXTRAPATHS:prepend:refdes-sa2-pe1 := "${THISDIR}/files/refdes-sa2-pe1:"
FILESEXTRAPATHS:prepend:refdes-sa2-pe3 := "${THISDIR}/files/refdes-sa2-pe3:"
FILESEXTRAPATHS:prepend:refdes-sa2-st1 := "${THISDIR}/files/refdes-sa2-st1:"

SRC_URI:append = " file://enclustra_generated.dts"

## TODO use the sdmmc / qspi overlays where needed depending on the ${UBOOT_CONFIG} - implement!!!                    
## NB: don't replace emmc/sdmmc/qspi here by UBOOT_CONFIG - would fail, if file is not there...
SRC_URI:append = " file://socfpga_enclustra_mercury_emmc_overlay.dtsi"
SRC_URI:append = " file://socfpga_enclustra_mercury_sdmmc_overlay.dtsi"
SRC_URI:append = " file://socfpga_enclustra_mercury_qspi_overlay.dtsi"

SRC_URI:append:pe1-generic = " file://socfpga_enclustra_mercury_pe1.dtsi"
SRC_URI:append:pe3-generic = " file://socfpga_enclustra_mercury_pe3.dtsi"
SRC_URI:append:st1-generic = " file://socfpga_enclustra_mercury_st1.dtsi"

KERNEL_INCLUDE = " \
        ${STAGING_KERNEL_DIR}/arch/${ARCH}/boot/dts \
        ${STAGING_KERNEL_DIR}/arch/${ARCH}/boot/dts/* \
        ${STAGING_KERNEL_DIR}/scripts/dtc/include-prefixes \
        ${STAGING_KERNEL_DIR}/include \
        ${STAGING_KERNEL_DIR}/include/dt-bindings/interrupt-controller \
        ${STAGING_KERNEL_DIR}/include/dt-bindings/reset \
        "

inherit devicetree

PROVIDES = "virtual/dtb"

do_configure[depends] += "virtual/kernel:do_configure"

do_deploy() {
        install -Dm 0644 ${B}/enclustra_generated.dtb ${DEPLOYDIR}/devicetree.dtb

        install -Dm 0644 ${B}/socfpga_enclustra_mercury_emmc_overlay.dtbo ${DEPLOYDIR}/socfpga_enclustra_mercury_emmc_overlay.dtbo
        install -Dm 0644 ${B}/socfpga_enclustra_mercury_qspi_overlay.dtbo ${DEPLOYDIR}/socfpga_enclustra_mercury_qspi_overlay.dtbo
        install -Dm 0644 ${B}/socfpga_enclustra_mercury_sdmmc_overlay.dtbo ${DEPLOYDIR}/socfpga_enclustra_mercury_sdmmc_overlay.dtbo

## TODO implement baseboard DT for kernel also as .dtbo
#        install -Dm 0644 ${B}/socfpga_enclustra_mercury_pe1.dtbo ${DEPLOYDIR}/socfpga_enclustra_mercury_pe1.dtbo
#        install -Dm 0644 ${B}/socfpga_enclustra_mercury_pe3.dtbo ${DEPLOYDIR}/socfpga_enclustra_mercury_pe3.dtbo
#        install -Dm 0644 ${B}/socfpga_enclustra_mercury_st1.dtbo ${DEPLOYDIR}/socfpga_enclustra_mercury_st1.dtbo
}

COMPATIBLE_MACHINE += "|pe1-generic|pe3-generic|st1-generic"
