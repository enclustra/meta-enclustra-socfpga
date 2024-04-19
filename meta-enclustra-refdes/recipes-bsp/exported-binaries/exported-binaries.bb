SUMMARY = "Exported reference design binaries"

inherit deploy

LICENSE = "Proprietary"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/Proprietary;md5=0557f9d92cf58f2ccdd50f62f8ac0b28"

PROVIDES = "virtual/bitstream"


SRC_URI:refdes-me-aa1-480-2i3-d12e-nfx3-pe1 = "\
    https://github.com/enclustra/Mercury_AA1_PE1_Reference_Design/releases/download/2023.1_v1.0.0/binaries_ME-AA1-480-2I3-D12E-NFX3_PE1.zip;name=ME-AA1-480-2I3-D12E-NFX3_PE1 \
"

SRC_URI:refdes-me-aa1-480-2i3-d12e-nfx3-pe3 = "\
    https://github.com/enclustra/Mercury_AA1_PE3_Reference_Design/releases/download/2023.1_v1.0.0/binaries_ME-AA1-480-2I3-D12E-NFX3_PE3.zip;name=ME-AA1-480-2I3-D12E-NFX3_PE3 \
"

SRC_URI:refdes-me-aa1-480-2i3-d12e-nfx3-st1 = "\
    https://github.com/enclustra/Mercury_AA1_ST1_Reference_Design/releases/download/2023.1_v1.0.0/binaries_ME-AA1-480-2I3-D12E-NFX3_ST1.zip;name=ME-AA1-480-2I3-D12E-NFX3_ST1 \
"

SRC_URI:refdes-me-aa1-270-2i2-d11e-nfx3-pe1 = "\
    https://github.com/enclustra/Mercury_AA1_PE1_Reference_Design/releases/download/2023.1_v1.0.0/binaries_ME-AA1-270-2I2-D11E-NFX3_PE1.zip;name=ME-AA1-270-2I2-D11E-NFX3_PE1 \
"

SRC_URI:refdes-me-aa1-270-2i2-d11e-nfx3-pe3 = "\
    https://github.com/enclustra/Mercury_AA1_PE3_Reference_Design/releases/download/2023.1_v1.0.0/binaries_ME-AA1-270-2I2-D11E-NFX3_PE3.zip;name=ME-AA1-270-2I2-D11E-NFX3_PE3 \
"
SRC_URI:refdes-me-aa1-270-2i2-d11e-nfx3-st1 = "\
    https://github.com/enclustra/Mercury_AA1_ST1_Reference_Design/releases/download/2023.1_v1.0.0/binaries_ME-AA1-270-2I2-D11E-NFX3_ST1.zip;name=ME-AA1-270-2I2-D11E-NFX3_ST1 \
"

SRC_URI:refdes-me-aa1-270-3e4-d11e-nfx3-pe1 = "\
    https://github.com/enclustra/Mercury_AA1_PE1_Reference_Design/releases/download/2023.1_v1.0.0/binaries_ME-AA1-270-3E4-D11E-NFX3_PE1.zip;name=ME-AA1-270-3E4-D11E-NFX3_PE1 \
"

SRC_URI:refdes-me-aa1-270-3e4-d11e-nfx3-pe3 = "\
    https://github.com/enclustra/Mercury_AA1_PE3_Reference_Design/releases/download/2023.1_v1.0.0/binaries_ME-AA1-270-3E4-D11E-NFX3_PE3.zip;name=ME-AA1-270-3E4-D11E-NFX3_PE3 \
"

SRC_URI:refdes-me-aa1-270-3e4-d11e-nfx3-st1 = "\
    https://github.com/enclustra/Mercury_AA1_ST1_Reference_Design/releases/download/2023.1_v1.0.0/binaries_ME-AA1-270-3E4-D11E-NFX3_ST1.zip;name=ME-AA1-270-3E4-D11E-NFX3_ST1 \
"

SRC_URI:refdes-me-sa1-c6-7i-d10-pe1 = "\
    https://github.com/enclustra/Mercury_SA1_PE1_Reference_Design/releases/download/2023.1_v1.0.0/binaries_ME-SA1-C6-7I-D10_PE1.zip;name=ME-SA1-C6-7I-D10_PE1 \
"

SRC_URI:refdes-me-sa1-c6-7i-d10-pe3 = "\
    https://github.com/enclustra/Mercury_SA1_PE3_Reference_Design/releases/download/2023.1_v1.0.0/binaries_ME-SA1-C6-7I-D10_PE3.zip;name=ME-SA1-C6-7I-D10_PE3 \
"

SRC_URI:refdes-me-sa1-c6-7i-d10-st1 = "\
    https://github.com/enclustra/Mercury_SA1_ST1_Reference_Design/releases/download/2023.1_v1.0.0/binaries_ME-SA1-C6-7I-D10_ST1.zip;name=ME-SA1-C6-7I-D10_ST1 \
"

SRC_URI:refdes-me-sa2-d6-7i-d11-pe1 = "\
    https://github.com/enclustra/Mercury_SA2_PE1_Reference_Design/releases/download/2023.1_v1.0.0/binaries_ME-SA2-D6-7I-D11_PE1.zip;name=ME-SA2-D6-7I-D11_PE1 \
"

SRC_URI:refdes-me-sa2-d6-7i-d11-pe3 = "\
    https://github.com/enclustra/Mercury_SA2_PE3_Reference_Design/releases/download/2023.1_v1.0.0/binaries_ME-SA2-D6-7I-D11_PE3.zip;name=ME-SA2-D6-7I-D11_PE3 \
"

SRC_URI:refdes-me-sa2-d6-7i-d11-st1 = "\
    https://github.com/enclustra/Mercury_SA2_ST1_Reference_Design/releases/download/2023.1_v1.0.0/binaries_ME-SA2-D6-7I-D11_ST1.zip;name=ME-SA2-D6-7I-D11_ST1 \
"

SRC_URI[ME-AA1-270-2I2-D11E-NFX3_PE1.sha256sum] = "301f50e3371c5dcf5809ed3f1ccadae7293f8a621e164b7c97310f42be2b3cab"
SRC_URI[ME-AA1-270-2I2-D11E-NFX3_PE3.sha256sum] = "d8947848801bdfa0c38e2d69bb6f2fde7067f60140ebbb0867f6bb964dd91259"
SRC_URI[ME-AA1-270-2I2-D11E-NFX3_ST1.sha256sum] = "e45f2a76046df285df92b0d25b251910f12b740e725bddee01f63012a26a2374"
SRC_URI[ME-AA1-270-3E4-D11E-NFX3_PE1.sha256sum] = "242be7f62cd131b80c3f2a3d77619ac6d275f35654df7e6fe0863123dba515c7"
SRC_URI[ME-AA1-270-3E4-D11E-NFX3_PE3.sha256sum] = "f2e6a7af60cdfc74364f02ca92777cc48015792883c381a420c535b393f387b0"
SRC_URI[ME-AA1-270-3E4-D11E-NFX3_ST1.sha256sum] = "c0d5b820dd668fd2ed3d9a1ffc2f81a3c3c6f9f55afa533337b441f100cedf8d"
SRC_URI[ME-AA1-480-2I3-D12E-NFX3_PE1.sha256sum] = "a6d451e6cb3dfabe97a8c0b1b98a7e6d47bb22841701b6dcd0808f4df41ecc9c"
SRC_URI[ME-AA1-480-2I3-D12E-NFX3_PE3.sha256sum] = "e454a90aff43d770896c5a5900267a029bb5e47350fbe3890c60d54c4931bf12"
SRC_URI[ME-AA1-480-2I3-D12E-NFX3_ST1.sha256sum] = "ae31b2fb2ac89680df984c9b1815f4c481279623a2adbaa7007f2e01f0351577"
SRC_URI[ME-SA1-C6-7I-D10_PE1.sha256sum] = "ea98a9c91d179208ea1a8ccd06857f977a116c37f9ffeefa25bba53f09ad9594"
SRC_URI[ME-SA1-C6-7I-D10_PE3.sha256sum] = "3a6a788d4266ffc6ab289843868955320ade6061d44e608b082740519efedaa4"
SRC_URI[ME-SA1-C6-7I-D10_ST1.sha256sum] = "9729c1b0fdabdcf65ca22276ec552587adec8d34667f31b6cd7b2f2d0ba067b3"
SRC_URI[ME-SA2-D6-7I-D11_PE1.sha256sum] = "5dd553eb114d725764db746d169abab9ebfcb3c8adc4d62ab515f31602ec6a3b"
SRC_URI[ME-SA2-D6-7I-D11_PE3.sha256sum] = "d2f517820cb46b2785fff98a369f0bf2196a0ee9bcf9fec15995f6bf71f52607"
SRC_URI[ME-SA2-D6-7I-D11_ST1.sha256sum] = "2d7a7dd62d3ecadcffaa61a56532c148807b94febe276f2cbb011cca979f6a95"

ENCLUSTRA_BASE_NAME:refdes-me-aa1-270-2i2-d11e-nfx3-pe1 = "Mercury_AA1_PE1"
ENCLUSTRA_BASE_NAME:refdes-me-aa1-270-2i2-d11e-nfx3-pe3 = "Mercury_AA1_PE3"
ENCLUSTRA_BASE_NAME:refdes-me-aa1-270-2i2-d11e-nfx3-st1 = "Mercury_AA1_ST1"
ENCLUSTRA_BASE_NAME:refdes-me-aa1-270-3e4-d11e-nfx3-pe1 = "Mercury_AA1_PE1"
ENCLUSTRA_BASE_NAME:refdes-me-aa1-270-3e4-d11e-nfx3-pe3 = "Mercury_AA1_PE3"
ENCLUSTRA_BASE_NAME:refdes-me-aa1-270-3e4-d11e-nfx3-st1 = "Mercury_AA1_ST1"
ENCLUSTRA_BASE_NAME:refdes-me-aa1-480-2i3-d12e-nfx3-pe1 = "Mercury_AA1_PE1"
ENCLUSTRA_BASE_NAME:refdes-me-aa1-480-2i3-d12e-nfx3-pe3 = "Mercury_AA1_PE3"
ENCLUSTRA_BASE_NAME:refdes-me-aa1-480-2i3-d12e-nfx3-st1 = "Mercury_AA1_ST1"
ENCLUSTRA_BASE_NAME:refdes-me-sa1-c6-7i-d10-pe1 = "Mercury_SA1_PE1"
ENCLUSTRA_BASE_NAME:refdes-me-sa1-c6-7i-d10-pe3 = "Mercury_SA1_PE3"
ENCLUSTRA_BASE_NAME:refdes-me-sa1-c6-7i-d10-st1 = "Mercury_SA1_ST1"
ENCLUSTRA_BASE_NAME:refdes-me-sa2-d6-7i-d11-pe1 = "Mercury_SA2_PE1"
ENCLUSTRA_BASE_NAME:refdes-me-sa2-d6-7i-d11-pe3 = "Mercury_SA2_PE3"
ENCLUSTRA_BASE_NAME:refdes-me-sa2-d6-7i-d11-st1 = "Mercury_SA2_ST1"

do_deploy[nostamp] = "1"

do_deploy() {
}

do_deploy:append:me-aa1-generic() {
    mkdir -p ${DEPLOY_DIR_IMAGE}/handoff
    cp -r ${WORKDIR}/${UBOOT_CONFIG}/hps_isw_handoff/* ${DEPLOY_DIR_IMAGE}/handoff
    install -D -m 0644 ${WORKDIR}/${UBOOT_CONFIG}/bitstream.core.rbf ${DEPLOY_DIR_IMAGE}/bitstream.core.rbf
    install -D -m 0644 ${WORKDIR}/${UBOOT_CONFIG}/bitstream.periph.rbf ${DEPLOY_DIR_IMAGE}/bitstream.periph.rbf
}

do_deploy:append:me-sa1-generic() {
    mkdir -p ${DEPLOY_DIR_IMAGE}/handoff
    cp -r ${WORKDIR}/${UBOOT_CONFIG}/hps_isw_handoff/Mercury_SA1_pd_hps_0/* ${DEPLOY_DIR_IMAGE}/handoff
    install -D -m 0644 ${WORKDIR}/${UBOOT_CONFIG}/${ENCLUSTRA_BASE_NAME}.rbf ${DEPLOY_DIR_IMAGE}/fpga.rbf
}

do_deploy:append:me-sa2-generic() {
    mkdir -p ${DEPLOY_DIR_IMAGE}/handoff
    cp -r ${WORKDIR}/${UBOOT_CONFIG}/hps_isw_handoff/Mercury_SA2_pd_hps_0/* ${DEPLOY_DIR_IMAGE}/handoff
    install -D -m 0644 ${WORKDIR}/${UBOOT_CONFIG}/${ENCLUSTRA_BASE_NAME}.rbf ${DEPLOY_DIR_IMAGE}/fpga.rbf
}

addtask deploy after do_configure
