SUMMARY = "Intel SoCFPGA Development Kit devicetrees"
DESCRIPTION = "Devicetree addons for Intel SoCFPGA Development module"
SECTION = "bsp"

LICENSE = "MIT & GPL-2.0-only"
FILESEXTRAPATHS:prepend := "${THISDIR}/files:"

SRC_URI:append:aa1-module := " file://socfpga_enclustra_mercury_aa1.dtsi:"
SRC_URI:append:sa1-module := " file://socfpga_enclustra_mercury_sa1.dtsi:"
SRC_URI:append:sa2-module := " file://socfpga_enclustra_mercury_sa2.dtsi:"

COMPATIBLE_MACHINE = "|aa1-module|sa1-module|sa2-module|refdes-aa1sx270e3-pe1|refdes-aa1sx270e3-pe3|refdes-aa1sx270e3-st1|refdes-aa1sx270i2-pe1|refdes-aa1sx270i2-pe3|refdes-aa1sx270i2-st1|refdes-aa1sx480i2-pe1|refdes-aa1sx480i2-pe3|refdes-aa1sx480i2-st1|refdes-sa1-pe1|refdes-sa1-pe3|refdes-sa1-st1|refdes-sa2-pe1|refdes-sa2-pe3|refdes-sa2-st1"

                       
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
