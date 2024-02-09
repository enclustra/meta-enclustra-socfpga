FILESEXTRAPATHS:prepend:me-aa1-270-2i2-d11e-nfx3 := "${THISDIR}/me-aa1-270-2i2-d11e-nfx3:"
FILESEXTRAPATHS:prepend:me-aa1-270-3e4-d11e-nfx3 := "${THISDIR}/me-aa1-270-3e4-d11e-nfx3:"
FILESEXTRAPATHS:prepend:me-aa1-480-2i3-d12e-nfx3 := "${THISDIR}/me-aa1-480-2i3-d12e-nfx3:"
FILESEXTRAPATHS:prepend:me-sa1-c6-7i-d10 := "${THISDIR}/me-sa1-c6-7i-d10:"
FILESEXTRAPATHS:prepend:me-sa2-d6-7i-d11 := "${THISDIR}/me-sa2-d6-7i-d11:"

inherit deploy

do_compile[deptask] = "do_deploy"

SRC_URI:append = " \
    file://enclustra-user.dts \
"
