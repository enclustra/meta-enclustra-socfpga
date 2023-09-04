FILESEXTRAPATHS:prepend := "${THISDIR}/files:"

inherit deploy

RDEPENDS_${PN} = "python"

do_compile[deptask] = "do_deploy"

## TODO aa1/sa1/sa2 sources - possible to overload?
SRC_URI:append = " \
	file://mercury-aa1-sd.dts \
	file://mercury-aa1-qspi.dts \
	file://mercury-aa1-sd_defconfig \
	file://mercury-aa1-qspi_defconfig \
	file://mercury-sa1.dts \
	file://mercury-sa1-sd_defconfig \
	file://mercury-sa1-qspi_defconfig \
	file://mercury-sa2.dts \
	file://mercury-sa2-sd_defconfig \
	file://mercury-sa2-qspi_defconfig \
	file://fit_spl_fpga.its \
	file://0001-Add-Enclustra-devicetree-to-Makefile.patch \
	file://0002-Make-intel-scripts-python-3-compatible.patch \
	file://0003-AA1-board-files-added.patch \
	file://0004-Enclustra-MAC-address-readout-from-EEPROM.patch \
	file://0005-SI5338-configuration.patch \
	file://Si5338-RevB-Registers.h \
	"

do_compile:prepend:mercury-aa1() {
	cp -r ${DEPLOY_DIR_IMAGE}/hps.xml ${S}/.
	cp -r ${WORKDIR}/Si5338-RevB-Registers.h ${S}/drivers/misc/
	${S}/arch/arm/mach-socfpga/qts-filter-a10.sh ${S}/hps.xml ${S}/arch/arm/dts/socfpga_arria10_handoff.h
}

do_compile:prepend:mercury-sa1() {
        mkdir -p ${WORKDIR}/sa1-handoff/system_hps_0
        cp -r ${DEPLOY_DIR_IMAGE}/sa1-handoff/system_hps_0/* ${WORKDIR}/sa1-handoff/system_hps_0/
        ${PYTHON} ${S}/arch/arm/mach-socfpga/cv_bsp_generator/cv_bsp_generator.py -i ${WORKDIR}/sa1-handoff/system_hps_0 -o ${S}/board/altera/cyclone5-socdk/qts/
}

do_compile:prepend:mercury-sa2() {
	mkdir -p ${WORKDIR}/sa2-handoff/system_hps_0
	cp -r ${DEPLOY_DIR_IMAGE}/sa2-handoff/system_hps_0/* ${WORKDIR}/sa2-handoff/system_hps_0/
	${PYTHON} ${S}/arch/arm/mach-socfpga/cv_bsp_generator/cv_bsp_generator.py -i ${WORKDIR}/sa2-handoff/system_hps_0 -o ${S}/board/altera/cyclone5-socdk/qts/
}

do_compile:append:mercury-aa1() {
	cp -r ${DEPLOY_DIR_IMAGE}/fpga.rbf ${S}/.

	for config in ${UBOOT_MACHINE}; do
		cp ${B}/${config}/u-boot-nodtb.bin ${S}/u-boot-nodtb.bin
		cp ${B}/${config}/u-boot.dtb ${S}/u-boot.dtb
	done

	cp ${WORKDIR}/fit_spl_fpga.its ${S}
	mkimage -E -f ${S}/board/altera/arria10-socdk/fit_uboot.its ${B}/fit_uboot.itb
	mkimage -E -f ${S}/fit_spl_fpga.its ${B}/fit_spl_fpga.itb
}

do_deploy:append:mercury-aa1() {
	install -d ${DEPLOYDIR}
	install -m 744 ${B}/fit_uboot.itb ${DEPLOYDIR}/fit_uboot.itb
	install -m 744 ${B}/fit_spl_fpga.itb ${DEPLOYDIR}/fit_spl_fpga.itb
}

## TODO adds aa1/sa1/sa2 files - possible to overload?
do_add_enclustra_files() {
	cp ${WORKDIR}/mercury-aa1-sd.dts ${S}/arch/arm/dts
	cp ${WORKDIR}/mercury-aa1-qspi.dts ${S}/arch/arm/dts
	cp ${WORKDIR}/mercury-aa1-sd_defconfig ${S}/configs/
	cp ${WORKDIR}/mercury-aa1-qspi_defconfig ${S}/configs/
	cp ${WORKDIR}/mercury-sa1.dts ${S}/arch/arm/dts
	cp ${WORKDIR}/mercury-sa1-sd_defconfig ${S}/configs/
	cp ${WORKDIR}/mercury-sa1-qspi_defconfig ${S}/configs/
	cp ${WORKDIR}/mercury-sa2.dts ${S}/arch/arm/dts
	cp ${WORKDIR}/mercury-sa2-sd_defconfig ${S}/configs/
	cp ${WORKDIR}/mercury-sa2-qspi_defconfig ${S}/configs/
}

addtask do_add_enclustra_files after do_patch before do_configure
