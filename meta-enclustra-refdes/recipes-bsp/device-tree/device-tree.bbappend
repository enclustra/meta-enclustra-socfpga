FILESEXTRAPATHS:prepend := "${THISDIR}/files/:"
FILESEXTRAPATHS:prepend:refdes-me-aa1-270-2i2-d11e-nfx3-pe1 := "${THISDIR}/refdes-me-aa1-270-2i2-d11e-nfx3-pe1:"
FILESEXTRAPATHS:prepend:refdes-me-aa1-270-2i2-d11e-nfx3-pe3 := "${THISDIR}/refdes-me-aa1-270-2i2-d11e-nfx3-pe3:"
FILESEXTRAPATHS:prepend:refdes-me-aa1-270-2i2-d11e-nfx3-st1 := "${THISDIR}/refdes-me-aa1-270-2i2-d11e-nfx3-st1:"
FILESEXTRAPATHS:prepend:refdes-me-aa1-270-3e4-d11e-nfx3-pe1 := "${THISDIR}/refdes-me-aa1-270-3e4-d11e-nfx3-pe1:"
FILESEXTRAPATHS:prepend:refdes-me-aa1-270-3e4-d11e-nfx3-pe3 := "${THISDIR}/refdes-me-aa1-270-3e4-d11e-nfx3-pe3:"
FILESEXTRAPATHS:prepend:refdes-me-aa1-270-3e4-d11e-nfx3-st1 := "${THISDIR}/refdes-me-aa1-270-3e4-d11e-nfx3-st1:"
FILESEXTRAPATHS:prepend:refdes-me-aa1-480-2i3-d12e-nfx3-pe1 := "${THISDIR}/refdes-me-aa1-480-2i3-d12e-nfx3-pe1:"
FILESEXTRAPATHS:prepend:refdes-me-aa1-480-2i3-d12e-nfx3-pe3 := "${THISDIR}/refdes-me-aa1-480-2i3-d12e-nfx3-pe3:"
FILESEXTRAPATHS:prepend:refdes-me-aa1-480-2i3-d12e-nfx3-st1 := "${THISDIR}/refdes-me-aa1-480-2i3-d12e-nfx3-st1:"
FILESEXTRAPATHS:prepend:refdes-me-sa1-c6-7i-d10-pe1 := "${THISDIR}/refdes-me-sa1-c6-7i-d10-pe1:"
FILESEXTRAPATHS:prepend:refdes-me-sa1-c6-7i-d10-pe3 := "${THISDIR}/refdes-me-sa1-c6-7i-d10-pe3:"
FILESEXTRAPATHS:prepend:refdes-me-sa1-c6-7i-d10-st1 := "${THISDIR}/refdes-me-sa1-c6-7i-d10-st1:"
FILESEXTRAPATHS:prepend:refdes-me-sa2-d6-7i-d11-pe1 := "${THISDIR}/refdes-me-sa2-d6-7i-d11-pe1:"
FILESEXTRAPATHS:prepend:refdes-me-sa2-d6-7i-d11-pe3 := "${THISDIR}/refdes-me-sa2-d6-7i-d11-pe3:"
FILESEXTRAPATHS:prepend:refdes-me-sa2-d6-7i-d11-st1 := "${THISDIR}/refdes-me-sa2-d6-7i-d11-st1:"

SRC_URI:append = " file://enclustra_generated.dts"
SRC_URI:append:me-pe1-generic = " file://socfpga_enclustra_mercury_pe1.dtsi"
SRC_URI:append:me-pe3-generic = " file://socfpga_enclustra_mercury_pe3.dtsi"
SRC_URI:append:me-st1-generic = " file://socfpga_enclustra_mercury_st1.dtsi"

COMPATIBLE_MACHINE += "|me-pe1-generic|me-pe3-generic|me-st1-generic"
