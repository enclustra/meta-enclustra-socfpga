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

# TODO rm        
#ENCLUSTRA_SELECT_ARCH := "zynq"
#ENCLUSTRA_SELECT_ARCH:zynqmp-generic := "zynqmp"
#SRC_URI:append = " file://system-user.dtsi"
#SRC_URI:append:eb1-generic = " file://${ENCLUSTRA_SELECT_ARCH}_enclustra_mars_eb1.dtsi"
#...

SRC_URI:append = " file://enclustra_generated.dts"

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
}

COMPATIBLE_MACHINE += "|pe1-generic|pe3-generic|st1-generic"


                      
## TODO rm
# SUMMARY = "Intel SoCFPGA Development Kit devicetrees"
# DESCRIPTION = "Devicetree addons for Intel SoCFPGA baseboard"
# SECTION = "bsp"
# 
# LICENSE = "MIT & GPL-2.0-only"
# 
# FILESEXTRAPATHS:prepend := "${THISDIR}/files:"
# 
# KERNEL_INCLUDE = " \
#         ${STAGING_KERNEL_DIR}/arch/${ARCH}/boot/dts \
#         ${STAGING_KERNEL_DIR}/arch/${ARCH}/boot/dts/* \
#         ${STAGING_KERNEL_DIR}/scripts/dtc/include-prefixes \
# 	${STAGING_KERNEL_DIR}/include \
# 	${STAGING_KERNEL_DIR}/include/dt-bindings/interrupt-controller \
# 	${STAGING_KERNEL_DIR}/include/dt-bindings/reset \
#         "
#
# inherit devicetree
# 
# PROVIDES = "virtual/dtb"
# 
# COMPATIBLE_MACHINE = "|aa1-module|sa1-module|sa2-module|"
# 
# SRC_URI = " \
# 	file://mercury-aa1.dts \
# 	file://mercury-sa1.dts \
# 	file://mercury-sa2.dts \
# 	"
# 
# do_configure[depends] += "virtual/kernel:do_configure"
# 
# do_deploy() {
# }
# 
# do_deploy:append:aa1-module() {
# 	install -Dm 0644 ${B}/mercury-aa1.dtb ${DEPLOYDIR}/devicetree.dtb
# }
# 
# do_deploy:append:sa1-module() {
# 	install -Dm 0644 ${B}/mercury-sa1.dtb ${DEPLOYDIR}/devicetree.dtb
# }
# 
# do_deploy:append:sa2-module() {
# 	install -Dm 0644 ${B}/mercury-sa2.dtb ${DEPLOYDIR}/devicetree.dtb
# }
