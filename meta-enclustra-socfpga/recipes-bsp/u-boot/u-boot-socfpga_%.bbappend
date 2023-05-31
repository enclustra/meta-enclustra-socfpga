FILESEXTRAPATHS:prepend := "${THISDIR}/files:"

inherit deploy

RDEPENDS_${PN} = "python"

do_compile[deptask] = "do_deploy"

SRC_URI:append = " \
	file://mercury-aa1-qspi.dts \
	file://mercury-aa1-qspi_defconfig \
	file://mercury-sa2.dts \
	file://mercury-sa2-sd_defconfig \
	file://mercury-sa2-qspi_defconfig \
	file://fit_spl_fpga.its \
	file://0001-Add-Enclustra-devicetree-to-Makefile.patch \
	file://0002-Make-intel-scripts-python-3-compatible.patch \
	"

do_compile:prepend:mercury-aa1() {
	cp -r ${DEPLOY_DIR_IMAGE}/hps.xml ${S}/.
	${S}/arch/arm/mach-socfpga/qts-filter-a10.sh ${S}/hps.xml ${S}/arch/arm/dts/socfpga_arria10_socdk_qspi_handoff.h
}

do_compile:prepend:mercury-sa2() {
	mkdir -p ${WORKDIR}/sa2-handoff/system_hps_0
	cp -r ${DEPLOY_DIR_IMAGE}/sa2-handoff/system_hps_0/* ${WORKDIR}/sa2-handoff/system_hps_0/
	${PYTHON} ${S}/arch/arm/mach-socfpga/cv_bsp_generator/cv_bsp_generator.py -i ${WORKDIR}/sa2-handoff/system_hps_0 -o ${S}/board/altera/cyclone5-socdk/qts/
}

do_compile:append:mercury-aa1() {
	cp -r ${DEPLOY_DIR_IMAGE}/fpga.rbf ${S}/.
	cp ${B}/mercury-aa1-qspi_defconfig/u-boot-nodtb.bin ${S}/u-boot-nodtb.bin
	cp ${B}/mercury-aa1-qspi_defconfig/u-boot.dtb ${S}/u-boot.dtb
	cp ${WORKDIR}/fit_spl_fpga.its ${S}
	mkimage -E -f ${S}/board/altera/arria10-socdk/fit_uboot.its ${B}/fit_uboot.itb
	mkimage -E -f ${S}/fit_spl_fpga.its ${B}/fit_spl_fpga.itb
}

do_deploy:append:mercury-aa1() {
	install -d ${DEPLOYDIR}
	install -m 744 ${B}/fit_uboot.itb ${DEPLOYDIR}/fit_uboot.itb
	install -m 744 ${B}/fit_spl_fpga.itb ${DEPLOYDIR}/fit_spl_fpga.itb
}

do_add_enclustra_files() {
	cp ${WORKDIR}/mercury-aa1-qspi.dts ${S}/arch/arm/dts
	cp ${WORKDIR}/mercury-aa1-qspi_defconfig ${S}/configs/
	cp ${WORKDIR}/mercury-sa2.dts ${S}/arch/arm/dts
	cp ${WORKDIR}/mercury-sa2-sd_defconfig ${S}/configs/
	cp ${WORKDIR}/mercury-sa2-qspi_defconfig ${S}/configs/
}

addtask do_add_enclustra_files after do_patch before do_configure
