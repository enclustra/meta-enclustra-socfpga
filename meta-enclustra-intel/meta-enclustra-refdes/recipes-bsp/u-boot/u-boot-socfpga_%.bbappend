FILESEXTRAPATHS:prepend := "${THISDIR}/files:"

FILESEXTRAPATHS:prepend:aa1sx270e3-module := "${THISDIR}/files/aa1sx270e3-module:"
FILESEXTRAPATHS:prepend:aa1sx270i2-module := "${THISDIR}/files/aa1sx270i2-module:"
FILESEXTRAPATHS:prepend:aa1sx480i2-module := "${THISDIR}/files/aa1sx480i2-module:"
FILESEXTRAPATHS:prepend:sa1-module := "${THISDIR}/files/sa1-module:"
FILESEXTRAPATHS:prepend:sa2-module := "${THISDIR}/files/sa2-module:"


inherit deploy

## probably not needed
#RDEPENDS_${PN} = "python"

## TODO refer in module?      
#DEPENDS:append = " hw-ref-design"

do_compile[deptask] = "do_deploy"

SRC_URI:append = " \
    file://enclustra_generated.dts \
"


# TODO needed? rm?      
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

# TODO needed?   
##addtask do_add_enclustra_files after do_patch before do_configure    
