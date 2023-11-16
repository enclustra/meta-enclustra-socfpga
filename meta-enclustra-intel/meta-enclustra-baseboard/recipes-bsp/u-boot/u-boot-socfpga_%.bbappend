FILESEXTRAPATHS:prepend := "${THISDIR}/files:"

FILESEXTRAPATHS:prepend:aa1sx270e3-module := "${THISDIR}/files/aa1sx270e3-module:"
FILESEXTRAPATHS:prepend:aa1sx270i2-module := "${THISDIR}/files/aa1sx270i2-module:"
FILESEXTRAPATHS:prepend:aa1sx480i2-module := "${THISDIR}/files/aa1sx480i2-module:"
FILESEXTRAPATHS:prepend:sa1-module := "${THISDIR}/files/sa1-module:"
FILESEXTRAPATHS:prepend:sa2-module := "${THISDIR}/files/sa2-module:"

# TODO rm        
#FILESEXTRAPATHS:prepend:refdes-aa1sx270e3-pe1 := "${THISDIR}/files/refdes-aa1sx270e3-pe1:"
#FILESEXTRAPATHS:prepend:refdes-aa1sx270e3-pe3 := "${THISDIR}/files/refdes-aa1sx270e3-pe3:"
#FILESEXTRAPATHS:prepend:refdes-aa1sx270e3-st1 := "${THISDIR}/files/refdes-aa1sx270e3-st1:"
#FILESEXTRAPATHS:prepend:refdes-aa1sx270i2-pe1 := "${THISDIR}/files/refdes-aa1sx270i2-pe1:"
#FILESEXTRAPATHS:prepend:refdes-aa1sx270i2-pe3 := "${THISDIR}/files/refdes-aa1sx270i2-pe3:"
#FILESEXTRAPATHS:prepend:refdes-aa1sx270i2-st1 := "${THISDIR}/files/refdes-aa1sx270i2-st1:"
#FILESEXTRAPATHS:prepend:refdes-aa1sx480i2-pe1 := "${THISDIR}/files/refdes-aa1sx480i2-pe1:"
#FILESEXTRAPATHS:prepend:refdes-aa1sx480i2-pe3 := "${THISDIR}/files/refdes-aa1sx480i2-pe3:"
#FILESEXTRAPATHS:prepend:refdes-aa1sx480i2-st1 := "${THISDIR}/files/refdes-aa1sx480i2-st1:"
#FILESEXTRAPATHS:prepend:refdes-sa1-pe1 := "${THISDIR}/files/refdes-sa1-pe1:"
#FILESEXTRAPATHS:prepend:refdes-sa1-pe3 := "${THISDIR}/files/refdes-sa1-pe3:"
#FILESEXTRAPATHS:prepend:refdes-sa1-st1 := "${THISDIR}/files/refdes-sa1-st1:"
#FILESEXTRAPATHS:prepend:refdes-sa2-pe1 := "${THISDIR}/files/refdes-sa2-pe1:"
#FILESEXTRAPATHS:prepend:refdes-sa2-pe3 := "${THISDIR}/files/refdes-sa2-pe3:"
#FILESEXTRAPATHS:prepend:refdes-sa2-st1 := "${THISDIR}/files/refdes-sa2-st1:"

inherit deploy

## probably not needed
#RDEPENDS_${PN} = "python"

## TODO refer in module?      
#DEPENDS:append = " hw-ref-design"

do_compile[deptask] = "do_deploy"

SRC_URI:append = " \
    file://enclustra_generated.dts \
"

##TODO rm     
#    file://socfpga_enclustra_mercury_pe1.dtsi \
#    file://socfpga_enclustra_mercury_pe3.dtsi \
#    file://socfpga_enclustra_mercury_st1.dtsi \
#"

### TODO aa1/sa1/sa2 sources - possible to overload?    
#SRC_URI:append:aa1-module = " \
#	file://mercury-aa1-sd.dts \
#	file://mercury-aa1-qspi.dts \
#	file://mercury-aa1-sd_defconfig \
#	file://mercury-aa1-qspi_defconfig \
#"
#
#SRC_URI:append:sa1-module = " \
#	file://mercury-sa1-sd_defconfig \
#	file://mercury-sa1-qspi_defconfig \
#"
#
#SRC_URI:append:sa2-module = " \
#	file://mercury-sa2-sd_defconfig \
#	file://mercury-sa2-qspi_defconfig \
#"

  
## TODO changed
#do_add_enclustra_files:append:aa1-module() {
#	## aa1
#	cp ${WORKDIR}/mercury-aa1-sd.dts ${S}/arch/arm/dts
#	cp ${WORKDIR}/mercury-aa1-qspi.dts ${S}/arch/arm/dts
#
#	cp ${WORKDIR}/mercury-aa1-sd_defconfig ${S}/configs/
#	cp ${WORKDIR}/mercury-aa1-qspi_defconfig ${S}/configs/
#}

## generic, split by FILESEXTRAPATH
# TODO discuss this approach in favor of overriding     
do_add_enclustra_files:append() {
    sed -i "s|UBOOT_CONFIG|${UBOOT_CONFIG}|g" ${WORKDIR}/enclustra_generated.dts || true
    cp ${WORKDIR}/enclustra_generated.dts ${S}/arch/arm/dts

## TODO not needed in u-boot, rm          
#    cp ${WORKDIR}/socfpga_enclustra_mercury_pe1.dtsi ${S}/arch/arm/dts
#    cp ${WORKDIR}/socfpga_enclustra_mercury_pe3.dtsi ${S}/arch/arm/dts
#    cp ${WORKDIR}/socfpga_enclustra_mercury_st1.dtsi ${S}/arch/arm/dts
}

#do_add_enclustra_files:append:sa1-module() {
#	## sa1
#	cp ${WORKDIR}/mercury-sa1-sd_defconfig ${S}/configs/
#	cp ${WORKDIR}/mercury-sa1-qspi_defconfig ${S}/configs/
#}

#do_add_enclustra_files:append:sa2-module() {
#	## sa2
#	cp ${WORKDIR}/mercury-sa2-sd_defconfig ${S}/configs/
#	cp ${WORKDIR}/mercury-sa2-qspi_defconfig ${S}/configs/
#}
#

           
### TODO adds aa1/sa1/sa2 files - possible to overload?
##do_add_enclustra_files() {    
#do_add_enclustra_files:append() {
#	## aa1
#	cp ${WORKDIR}/mercury-aa1-sd.dts ${S}/arch/arm/dts
#	cp ${WORKDIR}/mercury-aa1-qspi.dts ${S}/arch/arm/dts
#
#	cp ${WORKDIR}/mercury-aa1-sd_defconfig ${S}/configs/
#	cp ${WORKDIR}/mercury-aa1-qspi_defconfig ${S}/configs/
#
#	## sa1
##	cp ${WORKDIR}/mercury-sa1.dts ${S}/arch/arm/dts
#
#	cp ${WORKDIR}/mercury-sa1-sd_defconfig ${S}/configs/
#	cp ${WORKDIR}/mercury-sa1-qspi_defconfig ${S}/configs/
#
#	## sa2
##	cp ${WORKDIR}/mercury-sa2.dts ${S}/arch/arm/dts
#
#	cp ${WORKDIR}/mercury-sa2-sd_defconfig ${S}/configs/
#	cp ${WORKDIR}/mercury-sa2-qspi_defconfig ${S}/configs/
#}
#
##addtask do_add_enclustra_files after do_patch before do_configure    
