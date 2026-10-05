SUMMARY = "Exported reference design binaries"

inherit deploy

LICENSE = "Proprietary"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/Proprietary;md5=0557f9d92cf58f2ccdd50f62f8ac0b28"

PROVIDES = "virtual/bitstream"


SRC_URI:refdes-me-aa1-480-2i3-d12e-nfx3-pe1 = "\
    https://github.com/enclustra/Mercury_AA1_PE1_Reference_Design/releases/download/2023.1_v1.1.0/binaries_ME-AA1-480-2I3-D12E-NFX3_PE1.zip;name=ME-AA1-480-2I3-D12E-NFX3_PE1 \
"

SRC_URI:refdes-me-aa1-480-2i3-d12e-nfx3-pe3 = "\
    https://github.com/enclustra/Mercury_AA1_PE3_Reference_Design/releases/download/2023.1_v1.1.0/binaries_ME-AA1-480-2I3-D12E-NFX3_PE3.zip;name=ME-AA1-480-2I3-D12E-NFX3_PE3 \
"

SRC_URI:refdes-me-aa1-480-2i3-d12e-nfx3-st1 = "\
    https://github.com/enclustra/Mercury_AA1_ST1_Reference_Design/releases/download/2023.1_v1.1.0/binaries_ME-AA1-480-2I3-D12E-NFX3_ST1.zip;name=ME-AA1-480-2I3-D12E-NFX3_ST1 \
"

SRC_URI:refdes-me-aa1-270-2i2-d11e-nfx3-pe1 = "\
    https://github.com/enclustra/Mercury_AA1_PE1_Reference_Design/releases/download/2023.1_v1.1.0/binaries_ME-AA1-270-2I2-D11E-NFX3_PE1.zip;name=ME-AA1-270-2I2-D11E-NFX3_PE1 \
"

SRC_URI:refdes-me-aa1-270-2i2-d11e-nfx3-pe3 = "\
    https://github.com/enclustra/Mercury_AA1_PE3_Reference_Design/releases/download/2023.1_v1.1.0/binaries_ME-AA1-270-2I2-D11E-NFX3_PE3.zip;name=ME-AA1-270-2I2-D11E-NFX3_PE3 \
"
SRC_URI:refdes-me-aa1-270-2i2-d11e-nfx3-st1 = "\
    https://github.com/enclustra/Mercury_AA1_ST1_Reference_Design/releases/download/2023.1_v1.1.0/binaries_ME-AA1-270-2I2-D11E-NFX3_ST1.zip;name=ME-AA1-270-2I2-D11E-NFX3_ST1 \
"

SRC_URI:refdes-me-aa1-270-3e4-d11e-nfx3-pe1 = "\
    https://github.com/enclustra/Mercury_AA1_PE1_Reference_Design/releases/download/2023.1_v1.1.0/binaries_ME-AA1-270-3E4-D11E-NFX3_PE1.zip;name=ME-AA1-270-3E4-D11E-NFX3_PE1 \
"

SRC_URI:refdes-me-aa1-270-3e4-d11e-nfx3-pe3 = "\
    https://github.com/enclustra/Mercury_AA1_PE3_Reference_Design/releases/download/2023.1_v1.1.0/binaries_ME-AA1-270-3E4-D11E-NFX3_PE3.zip;name=ME-AA1-270-3E4-D11E-NFX3_PE3 \
"

SRC_URI:refdes-me-aa1-270-3e4-d11e-nfx3-st1 = "\
    https://github.com/enclustra/Mercury_AA1_ST1_Reference_Design/releases/download/2023.1_v1.1.0/binaries_ME-AA1-270-3E4-D11E-NFX3_ST1.zip;name=ME-AA1-270-3E4-D11E-NFX3_ST1 \
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

SRC_URI[ME-AA1-270-2I2-D11E-NFX3_PE1.sha256sum] = "46255028e4e234dc590769881ca36b592b22b0cee3cd1cf30a3c2dff76386933"
SRC_URI[ME-AA1-270-2I2-D11E-NFX3_PE3.sha256sum] = "cc410976b7eead48ddb32b108fb09b728548d05e6c8867d2484dac0bcaad62e4"
SRC_URI[ME-AA1-270-2I2-D11E-NFX3_ST1.sha256sum] = "6da1c5097d1329f0a45b97a18c50ce12edd2240ca2d71ca3879ad58f89d9af74"
SRC_URI[ME-AA1-270-3E4-D11E-NFX3_PE1.sha256sum] = "a4a57b64fd4122cf9d66bbfcdd6a8cd7ef29958d2f66ed49e6bbede8d8964d4d"
SRC_URI[ME-AA1-270-3E4-D11E-NFX3_PE3.sha256sum] = "e0858544a5a15b7591e5f0d07b02d8550e3b6b96ca61441f40afae40f5788de2"
SRC_URI[ME-AA1-270-3E4-D11E-NFX3_ST1.sha256sum] = "bab2a7d02568ee5eadb62ba8a13c222b003692e19082e1682ffe54abae300b17"
SRC_URI[ME-AA1-480-2I3-D12E-NFX3_PE1.sha256sum] = "218429608f1d64e572356eb77af1b86b222653e1da735d9fabccc36c8334e0ad"
SRC_URI[ME-AA1-480-2I3-D12E-NFX3_PE3.sha256sum] = "85a3bf5dd92796af638473661ab80567f57ab786fc56240dc1887062b80c01ef"
SRC_URI[ME-AA1-480-2I3-D12E-NFX3_ST1.sha256sum] = "e506e393bc94588eeaf66027f7fefda446eadce8c14214aeed37d8d802a48544"
SRC_URI[ME-SA1-C6-7I-D10_PE1.sha256sum] = "486bd2a7a500d855b70dfb9563967ed635c94b401c0c6ade614b2171ee50dafd"
SRC_URI[ME-SA1-C6-7I-D10_PE3.sha256sum] = "82845c8ff0f3536c9fcc6e461e9ce7c3f60a3e29d1c62e2f76dd4b645afbf8b3"
SRC_URI[ME-SA1-C6-7I-D10_ST1.sha256sum] = "6e5e7de16da95523d23e384993cc3d7137c5a83aed4034ff6b2ee582244b14fe"
SRC_URI[ME-SA2-D6-7I-D11_PE1.sha256sum] = "f91900bef6df603c4fc0a649634ac7195505e43c3fedab1d0b63c5a1eec8c03b"
SRC_URI[ME-SA2-D6-7I-D11_PE3.sha256sum] = "44818301919498037c6812c8564e432001997c1f072b74d5e6749e29e8822121"
SRC_URI[ME-SA2-D6-7I-D11_ST1.sha256sum] = "e23b520c2515f5cbc1faf36e33f1e54a3f83160f63c9e31f713f63964a1f5abb"

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
