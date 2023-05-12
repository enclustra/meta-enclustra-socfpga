SUMMARY = "Intel SoCFPGA Development Kit devicetrees"
DESCRIPTION = "Devicetree addons for Intel SoCFPGA Development Kit examples"
SECTION = "bsp"

LICENSE = "MIT & GPL-2.0-only"

FILESEXTRAPATHS:prepend := "${THISDIR}/files:"

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

COMPATIBLE_MACHINE = "(mercury-aa1)"

SRC_URI:append:mercury-aa1 = "\
	file://mercury-aa1.dts \
	"

do_configure[depends] += "virtual/kernel:do_configure"

do_configure:append:mercury-aa1() {

}