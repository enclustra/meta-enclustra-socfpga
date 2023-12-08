FILESEXTRAPATHS:prepend := "${THISDIR}/files/:"

SRC_URI:append:pe1-generic = " file://socfpga_enclustra_mercury_pe1.dtsi"
SRC_URI:append:pe3-generic = " file://socfpga_enclustra_mercury_pe3.dtsi"
SRC_URI:append:st1-generic = " file://socfpga_enclustra_mercury_st1.dtsi"

COMPATIBLE_MACHINE += "|pe1-generic|pe3-generic|st1-generic"
