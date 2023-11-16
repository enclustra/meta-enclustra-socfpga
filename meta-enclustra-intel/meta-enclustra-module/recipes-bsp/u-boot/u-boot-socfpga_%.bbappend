FILESEXTRAPATHS:prepend := "${THISDIR}/files:"
FILESEXTRAPATHS:prepend := "${THISDIR}/files/bitstream:"
FILESEXTRAPATHS:prepend := "${THISDIR}/files/configs:"
FILESEXTRAPATHS:prepend := "${THISDIR}/files/devicetree:"

## TODO check needed?
#inherit deploy

## TODO currently probably not needed   
DEPENDS:append = " hw-ref-design"


## NB: use .h files instead of u-boot-socfpga-env approach
## the flatfile approach is not working out here

## TODO needed?    
DEPENDS:append = " xxd-native"

SRC_URI:append = " \
    file://fit_spl_fpga.its \
    file://0001-Add-Enclustra-devicetree-to-Makefile.patch \
    file://0002-Make-intel-scripts-python3-compatible.patch \
    file://0003-Add-Enclustra-board-files.patch \
    file://0004-Enclustra-MAC-address-readout-from-EEPROM.patch \
    file://0005-SI5338-configuration.patch \
    file://Si5338-RevB-Registers.h \
"

## TODO to be extended by more UBOOT_CONFIG modes
SRC_URI:append:aa1-module = " \
    file://socfpga_mercury_aa1_sdmmc_defconfig \
    file://socfpga_enclustra_mercury_aa1.dtsi \
    file://socfpga_enclustra_mercury_aa1_${UBOOT_CONFIG}_boot.dtsi \
"

SRC_URI:append:aa1sx270e3-module = " \
    file://ME-AA1-270-3E4-D11E-NFX3.dtsi \
"

SRC_URI:append:aa1sx270i2-module = " \
    file://ME-AA1-270-2I2-D11E-NFX3.dtsi \
"

SRC_URI:append:aa1sx480i2-module = " \
    file://ME-AA1-480-2I3-D12E-NFX3.dtsi \
"

SRC_URI:append:sa1-module = " \
    file://socfpga_mercury_sa1_${UBOOT_CONFIG}_defconfig \
    file://ME-SA1-C6-7I-D10.dtsi \
    file://socfpga_enclustra_mercury_sa1.dtsi \
"

# TODO .dtsi files missing for sa2
SRC_URI:append:sa2-module = " \
    file://socfpga_mercury_sa2_${UBOOT_CONFIG}_defconfig \
"

## TODO adds aa1/sa1/sa2 files - possible to overload?
do_add_enclustra_files() {
}
    
## TODO integrate from "base" to "module"
do_add_enclustra_files:append:aa1-module() {
    cp ${WORKDIR}/socfpga_enclustra_mercury_aa1.dtsi ${S}/arch/arm/dts
    cp ${WORKDIR}/socfpga_enclustra_mercury_aa1_${UBOOT_CONFIG}_boot.dtsi ${S}/arch/arm/dts
    cp ${WORKDIR}/socfpga_mercury_aa1_${UBOOT_CONFIG}_defconfig ${S}/configs

## TODO rm    
#    cp ${WORKDIR}/socfpga_enclustra_mercury_aa1_mmc_boot.dtsi ${S}/arch/arm/dts
#    cp ${WORKDIR}/socfpga_enclustra_mercury_aa1_qspi_boot.dtsi ${S}/arch/arm/dts

## TODO check out to use $UBOOT_CONFIG in the naming to generalize boodmode, TODO rm    
#    cp ${WORKDIR}/socfpga_mercury_aa1_emmc_defconfig ${S}/configs
#    cp ${WORKDIR}/socfpga_mercury_aa1_qspi_defconfig ${S}/configs
#    cp ${WORKDIR}/socfpga_mercury_aa1_sdmmc_defconfig ${S}/configs
}

do_add_enclustra_files:append:aa1sx270e3-module() {
    cp ${WORKDIR}/ME-AA1-270-3E4-D11E-NFX3.dtsi ${S}/arch/arm/dts
}

do_add_enclustra_files:append:aa1sx270i2-module() {
    cp ${WORKDIR}/ME-AA1-270-2I2-D11E-NFX3.dtsi ${S}/arch/arm/dts
}

do_add_enclustra_files:append:aa1sx480i2-module() {
    cp ${WORKDIR}/ME-AA1-480-2I3-D12E-NFX3.dtsi ${S}/arch/arm/dts
}

do_add_enclustra_files:append:sa1-module() {
    cp ${WORKDIR}/ME-SA1-C6-7I-D10.dtsi ${S}/arch/arm/dts
    cp ${WORKDIR}/socfpga_enclustra_mercury_sa1.dtsi ${S}/arch/arm/dts
    cp ${WORKDIR}/socfpga_mercury_sa1_${UBOOT_CONFIG}_defconfig ${S}/configs

#    cp ${WORKDIR}/socfpga_mercury_sa1_emmc_defconfig ${S}/configs
#    cp ${WORKDIR}/socfpga_mercury_sa1_qspi_defconfig ${S}/configs
#    cp ${WORKDIR}/socfpga_mercury_sa1_sdmmc_defconfig ${S}/configs
}

do_add_enclustra_files:append:sa2-module() {
# TODO dts                                           
    cp ${WORKDIR}/socfpga_mercury_sa2_${UBOOT_CONFIG}_defconfig ${S}/configs

#    cp ${WORKDIR}/socfpga_mercury_sa2_qspi_defconfig ${S}/configs
#    cp ${WORKDIR}/socfpga_mercury_sa2_sdmmc_defconfig ${S}/configs
}
addtask do_add_enclustra_files after do_patch before do_configure

#do_compile:prepend() {
## TODO rm, use .h approach    
#	cp -L ${DEPLOY_DIR_IMAGE}/uboot.env ${S}/
#}

do_compile:prepend:aa1-module() {
	cp -r ${DEPLOY_DIR_IMAGE}/hps.xml ${S}/.
	cp -r ${WORKDIR}/Si5338-RevB-Registers.h ${S}/drivers/misc/
	${S}/arch/arm/mach-socfpga/qts-filter-a10.sh ${S}/hps.xml ${S}/arch/arm/dts/socfpga_arria10_handoff.h
}

do_compile:prepend:sa1-module() {
# TODO fix name, why using "sa1-handoff" in the sa1 DEPLOY_DIR?
        mkdir -p ${WORKDIR}/sa1-handoff/system_hps_0 
        cp -r ${DEPLOY_DIR_IMAGE}/sa1-handoff/system_hps_0/* ${WORKDIR}/sa1-handoff/system_hps_0/ 
        ${PYTHON} ${S}/arch/arm/mach-socfpga/cv_bsp_generator/cv_bsp_generator.py -i ${WORKDIR}/sa1-handoff/system_hps_0 -o ${S}/board/altera/cyclone5-socdk/qts/ 
#        mkdir -p ${WORKDIR}/handoff/system_hps_0
#        cp -r ${DEPLOY_DIR_IMAGE}/sa1-handoff/system_hps_0/* ${WORKDIR}/handoff/system_hps_0/
#        ${PYTHON} ${S}/arch/arm/mach-socfpga/cv_bsp_generator/cv_bsp_generator.py -i ${WORKDIR}/handoff/system_hps_0 -o ${S}/board/altera/cyclone5-socdk/qts/
}

# TODO fix name, why using "sa1-handoff" in the sa1 DEPLOY_DIR?
do_compile:prepend:sa2-module() {
# TODO fix name, why using "sa1-handoff" in the sa1 DEPLOY_DIR?
	mkdir -p ${WORKDIR}/sa2-handoff/system_hps_0 
	cp -r ${DEPLOY_DIR_IMAGE}/sa2-handoff/system_hps_0/* ${WORKDIR}/sa2-handoff/system_hps_0/ 
	${PYTHON} ${S}/arch/arm/mach-socfpga/cv_bsp_generator/cv_bsp_generator.py -i ${WORKDIR}/sa2-handoff/system_hps_0 -o ${S}/board/altera/cyclone5-socdk/qts/ 
#	mkdir -p ${WORKDIR}/handoff/system_hps_0
#	cp -r ${DEPLOY_DIR_IMAGE}/handoff/system_hps_0/* ${WORKDIR}/sa2-handoff/system_hps_0/
#	${PYTHON} ${S}/arch/arm/mach-socfpga/cv_bsp_generator/cv_bsp_generator.py -i ${WORKDIR}/handoff/system_hps_0 -o ${S}/board/altera/cyclone5-socdk/qts/
}

do_compile:append:aa1-module() {
	cp -r ${DEPLOY_DIR_IMAGE}/core.rbf ${S}/.
	cp -r ${DEPLOY_DIR_IMAGE}/periph.rbf ${S}/.

	for config in ${UBOOT_MACHINE}; do
		cp ${B}/${config}/u-boot-nodtb.bin ${S}/u-boot-nodtb.bin
		cp ${B}/${config}/u-boot.dtb ${S}/u-boot.dtb
	done

	cp ${WORKDIR}/fit_spl_fpga.its ${S}
	mkimage -E -f ${S}/board/altera/arria10-socdk/fit_uboot.its ${B}/fit_uboot.itb
	mkimage -E -f ${S}/fit_spl_fpga.its ${B}/fit_spl_fpga.itb
}

# TODO itb generation for sa1 and sa2   

do_deploy:append:aa1-module() {
	install -d ${DEPLOYDIR}
## TODO needed?    
#	install -m 744 ${B}/fit_uboot.itb ${DEPLOYDIR}/fit_uboot.itb

# TODO move to module
	install -m 744 ${B}/fit_spl_fpga.itb ${DEPLOYDIR}/fit_spl_fpga.itb
        ln -sf fit_spl_fpga.itb ${DEPLOYDIR}/bitstream.itb
}


                    
# FILESEXTRAPATHS:prepend := "${THISDIR}/files:"
# 
# inherit deploy
# 
# ## probably not needed
# #RDEPENDS_${PN} = "python"
# 
# DEPENDS:append = "hw-ref-design"
# 
# do_compile[deptask] = "do_deploy"
# 
# ## TODO aa1/sa1/sa2 sources - possible to overload?
# SRC_URI:append = " \
# 	file://mercury-aa1-sd.dts \
# 	file://mercury-aa1-qspi.dts \
# 	file://mercury-aa1-sd_defconfig \
# 	file://mercury-aa1-qspi_defconfig \
# 	file://mercury-sa1.dts \
# 	file://mercury-sa1-sd_defconfig \
# 	file://mercury-sa1-qspi_defconfig \
# 	file://mercury-sa2.dts \
# 	file://mercury-sa2-sd_defconfig \
# 	file://mercury-sa2-qspi_defconfig \
# 	file://fit_spl_fpga.its \
# 	file://0001-Add-Enclustra-devicetree-to-Makefile.patch \
# 	file://0002-Make-intel-scripts-python-3-compatible.patch \
# 	file://0003-AA1-board-files-added.patch \
# 	file://0004-Enclustra-MAC-address-readout-from-EEPROM.patch \
# 	file://0005-SI5338-configuration.patch \
# 	file://Si5338-RevB-Registers.h \
# 	"
# 
# do_compile:prepend:aa1-module() {
# 	cp -r ${DEPLOY_DIR_IMAGE}/hps.xml ${S}/.
# 	cp -r ${WORKDIR}/Si5338-RevB-Registers.h ${S}/drivers/misc/
# 	${S}/arch/arm/mach-socfpga/qts-filter-a10.sh ${S}/hps.xml ${S}/arch/arm/dts/socfpga_arria10_handoff.h
# }
# 
# do_compile:prepend:sa1-module() {
#         mkdir -p ${WORKDIR}/sa1-handoff/system_hps_0
#         cp -r ${DEPLOY_DIR_IMAGE}/sa1-handoff/system_hps_0/* ${WORKDIR}/sa1-handoff/system_hps_0/
#         ${PYTHON} ${S}/arch/arm/mach-socfpga/cv_bsp_generator/cv_bsp_generator.py -i ${WORKDIR}/sa1-handoff/system_hps_0 -o ${S}/board/altera/cyclone5-socdk/qts/
# }
# 
# do_compile:prepend:sa2-module() {
# 	mkdir -p ${WORKDIR}/sa2-handoff/system_hps_0
# 	cp -r ${DEPLOY_DIR_IMAGE}/sa2-handoff/system_hps_0/* ${WORKDIR}/sa2-handoff/system_hps_0/
# 	${PYTHON} ${S}/arch/arm/mach-socfpga/cv_bsp_generator/cv_bsp_generator.py -i ${WORKDIR}/sa2-handoff/system_hps_0 -o ${S}/board/altera/cyclone5-socdk/qts/
# }
# 
# do_compile:append:aa1-module() {
# 	cp -r ${DEPLOY_DIR_IMAGE}/core.rbf ${S}/.
# 	cp -r ${DEPLOY_DIR_IMAGE}/periph.rbf ${S}/.
# 
# 	for config in ${UBOOT_MACHINE}; do
# 		cp ${B}/${config}/u-boot-nodtb.bin ${S}/u-boot-nodtb.bin
# 		cp ${B}/${config}/u-boot.dtb ${S}/u-boot.dtb
# 	done
# 
# 	cp ${WORKDIR}/fit_spl_fpga.its ${S}
# 	mkimage -E -f ${S}/board/altera/arria10-socdk/fit_uboot.its ${B}/fit_uboot.itb
# 	mkimage -E -f ${S}/fit_spl_fpga.its ${B}/fit_spl_fpga.itb
# }
# 
# do_deploy:append:aa1-module() {
# 	install -d ${DEPLOYDIR}
# 
#         ## TODO needed?
# 	install -m 744 ${B}/fit_uboot.itb ${DEPLOYDIR}/fit_uboot.itb
# 
# #	install -m 744 ${B}/fit_spl_fpga.itb ${DEPLOYDIR}/fit_spl_fpga.itb
# 	install -m 744 ${B}/fit_spl_fpga.itb ${DEPLOYDIR}/bitstream.itb
# }
# 
## TODO adds aa1/sa1/sa2 files - possible to overload?
# do_add_enclustra_files() {
# 	## aa1
# 	cp ${WORKDIR}/mercury-aa1-sd.dts ${S}/arch/arm/dts
# 	cp ${WORKDIR}/mercury-aa1-qspi.dts ${S}/arch/arm/dts
# 
# 	cp ${WORKDIR}/mercury-aa1-sd_defconfig ${S}/configs/
# 	cp ${WORKDIR}/mercury-aa1-qspi_defconfig ${S}/configs/
# 
# 	## sa1
# 	cp ${WORKDIR}/mercury-sa1.dts ${S}/arch/arm/dts
# 
# 	cp ${WORKDIR}/mercury-sa1-sd_defconfig ${S}/configs/
# 	cp ${WORKDIR}/mercury-sa1-qspi_defconfig ${S}/configs/
# 
# 	## sa2
# 	cp ${WORKDIR}/mercury-sa2.dts ${S}/arch/arm/dts
# 
# 	cp ${WORKDIR}/mercury-sa2-sd_defconfig ${S}/configs/
# 	cp ${WORKDIR}/mercury-sa2-qspi_defconfig ${S}/configs/
# }
# 
# addtask do_add_enclustra_files after do_patch before do_configure
