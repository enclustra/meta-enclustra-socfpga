FILESEXTRAPATHS:prepend := "${THISDIR}/files/:"

SRC_URI:append:me-pe1-generic = " file://socfpga_enclustra_mercury_pe1.dtsi"
SRC_URI:append:me-pe3-generic = " file://socfpga_enclustra_mercury_pe3.dtsi"
SRC_URI:append:me-st1-generic = " file://socfpga_enclustra_mercury_st1.dtsi"

COMPATIBLE_MACHINE += "|me-pe1-generic|me-pe3-generic|me-st1-generic"
