FILESEXTRAPATHS:prepend:me-aa1-270-2i2-d11e-nfx3 := "${THISDIR}/me-aa1-270-2i2-d11e-nfx3:"
FILESEXTRAPATHS:prepend:me-aa1-270-3e4-d11e-nfx3 := "${THISDIR}/me-aa1-270-3e4-d11e-nfx3:"
FILESEXTRAPATHS:prepend:me-aa1-480-2i3-d12e-nfx3 := "${THISDIR}/me-aa1-480-2i3-d12e-nfx3:"
FILESEXTRAPATHS:prepend:me-sa1-c6-7i-d10 := "${THISDIR}/me-sa1-c6-7i-d10:"
FILESEXTRAPATHS:prepend:me-sa2-d6-7i-d11 := "${THISDIR}/me-sa2-d6-7i-d11:"

inherit deploy

do_compile[deptask] = "do_deploy"

SRC_URI:append = " \
    file://enclustra_generated.dts \
"

do_add_enclustra_files:append() {
    cp ${WORKDIR}/enclustra_generated.dts ${S}/arch/arm/dts

    ## adjust to seleted boot mode
    sed -i "s|XXX|${UBOOT_CONFIG}|g" ${S}/arch/arm/dts/enclustra_generated.dts || true

    ## adjust to selected boot mode
    sed -i "s|XXX|${UBOOT_CONFIG}|g" ${S}/include/configs/socfpga_mercury_*.h || true
}
