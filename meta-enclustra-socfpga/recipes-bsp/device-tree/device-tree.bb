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

COMPATIBLE_MACHINE = "|mercury-aa1|mercury-sa2|"

SRC_URI = " \
	file://mercury-aa1.dts \
	file://mercury-sa2.dts \
	"

do_configure[depends] += "virtual/kernel:do_configure"

do_deploy() {
	install -Dm 0644 ${B}/mercury-aa1.dtb ${DEPLOYDIR}
	install -Dm 0644 ${B}/mercury-sa2.dtb ${DEPLOYDIR}
}