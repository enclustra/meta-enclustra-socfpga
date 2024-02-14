SUMMARY = "Provides devicetree for Linux kernel"
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

SRC_URI:append:me-aa1-generic = " \
    file://socfpga_enclustra_mercury_aa1.dtsi \
"

SRC_URI:append:me-sa1-generic = " \
    file://socfpga_enclustra_mercury_sa1.dtsi \
"

SRC_URI:append:me-sa2-generic = " \
    file://socfpga_enclustra_mercury_sa2.dtsi \
"

SRC_URI:append:me-sa1-c6-7i-d10 = " \
    file://ME-SA1-C6-7I-D10.dtsi \
"

SRC_URI:append:me-sa2-d6-7i-d11 = " \
    file://ME-SA2-D6-7I-D11.dtsi \
"

SRC_URI:append:me-aa1-270-3e4-d11e-nfx3 = " \
    file://ME-AA1-270-3E4-D11E-NFX3.dtsi \
"

SRC_URI:append:me-aa1-270-2i2-d11e-nfx3 = " \
    file://ME-AA1-270-2I2-D11E-NFX3.dtsi \
"

SRC_URI:append:me-aa1-480-2i3-d12e-nfx3 = " \
    file://ME-AA1-480-2I3-D12E-NFX3.dtsi \
"

SRC_URI:append = " file://socfpga_enclustra_mercury_emmc_overlay.dtsi"
SRC_URI:append = " file://socfpga_enclustra_mercury_sdmmc_overlay.dtsi"
SRC_URI:append = " file://socfpga_enclustra_mercury_qspi_overlay.dtsi"

do_configure[depends] += "virtual/kernel:do_configure"

do_deploy:append() {
    install -Dm 0644 ${B}/enclustra-user.dtb ${DEPLOYDIR}/devicetree.dtb

    ## overlays
    install -Dm 0644 ${B}/socfpga_enclustra_mercury_emmc_overlay.dtbo ${DEPLOYDIR}/socfpga_enclustra_mercury_emmc_overlay.dtbo
    install -Dm 0644 ${B}/socfpga_enclustra_mercury_qspi_overlay.dtbo ${DEPLOYDIR}/socfpga_enclustra_mercury_qspi_overlay.dtbo
    install -Dm 0644 ${B}/socfpga_enclustra_mercury_sdmmc_overlay.dtbo ${DEPLOYDIR}/socfpga_enclustra_mercury_sdmmc_overlay.dtbo
}

COMPATIBLE_MACHINE = "|me-aa1-270-3e4-d11e-nfx3|me-aa1-270-2i2-d11e-nfx3|me-aa1-480-2i3-d12e-nfx3|me-sa1-c6-7i-d10|me-sa2-d6-7i-d11"
