FILESEXTRAPATHS:prepend := "${THISDIR}/files:"

inherit deploy

do_compile[deptask] = "do_deploy"

SRC_URI:append = " \
	file://mercury-aa1-qspi_defconfig \
	file://0001-aa1-qspi-test-modifications.patch \
	"

do_compile:prepend:mercury-aa1() {
	cp -r ${DEPLOY_DIR_IMAGE}/refdes_hps.xml ${S}/.
	${S}/arch/arm/mach-socfpga/qts-filter-a10.sh ${S}/refdes_hps.xml ${S}/arch/arm/dts/socfpga_arria10_socdk_qspi_handoff.h
}

do_compile:append:mercury-aa1() {
	cp -r ${DEPLOY_DIR_IMAGE}/fpga.rbf ${S}/.
	cp ${B}/mercury-aa1-qspi_defconfig/u-boot-nodtb.bin ${S}/u-boot-nodtb.bin
	cp ${B}/mercury-aa1-qspi_defconfig/u-boot.dtb ${S}/u-boot.dtb
	mkimage -E -f ${S}/board/altera/arria10-socdk/fit_uboot.its ${B}/fit_uboot.itb
	mkimage -E -f ${S}/board/altera/arria10-socdk/fit_spl_fpga.its ${B}/fit_spl_fpga.itb
}

do_deploy:append:mercury-aa1() {
	install -d ${DEPLOYDIR}
	install -m 744 ${B}/fit_uboot.itb ${DEPLOYDIR}/fit_uboot.itb
	install -m 744 ${B}/fit_spl_fpga.itb ${DEPLOYDIR}/fit_spl_fpga.itb
}

do_add_enclustra_config() {
	cp ${WORKDIR}/mercury-aa1-qspi_defconfig ${S}/configs/
}

addtask do_add_enclustra_config after do_patch before do_configure