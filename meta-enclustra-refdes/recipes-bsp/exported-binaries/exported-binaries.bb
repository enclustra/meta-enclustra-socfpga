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

SRC_URI[ME-AA1-270-2I2-D11E-NFX3_PE1.sha256sum] = "929973f598636e98fc19fdad081a98f0b181093667ed0df0d4726ecc2a1bbb21"
SRC_URI[ME-AA1-270-2I2-D11E-NFX3_PE3.sha256sum] = "4062fc60499c021a6a162bfa8676d93b7b6d7d9a9c728a8f00c78c22f2fc0569"
SRC_URI[ME-AA1-270-2I2-D11E-NFX3_ST1.sha256sum] = "f71ebb2088c7466ddf011e290a570521da11ebfc8cf80a5066a0bbf18d243b18"
SRC_URI[ME-AA1-270-3E4-D11E-NFX3_PE1.sha256sum] = "074c088639a66630f855a7cefd0b970fe8c0f04c0d4a300aa79242970bc06b08"
SRC_URI[ME-AA1-270-3E4-D11E-NFX3_PE3.sha256sum] = "1b64b167a31d6a5c03775331950d1629cce289cfe6affbdbbde2e90de79ca053"
SRC_URI[ME-AA1-270-3E4-D11E-NFX3_ST1.sha256sum] = "09e23f3d731d2203f3836baf3db3c5affada9b9be823d56ca90a648511170fe6"
SRC_URI[ME-AA1-480-2I3-D12E-NFX3_PE1.sha256sum] = "a6d451e6cb3dfabe97a8c0b1b98a7e6d47bb22841701b6dcd0808f4df41ecc9c"
SRC_URI[ME-AA1-480-2I3-D12E-NFX3_PE3.sha256sum] = "e454a90aff43d770896c5a5900267a029bb5e47350fbe3890c60d54c4931bf12"
SRC_URI[ME-AA1-480-2I3-D12E-NFX3_ST1.sha256sum] = "ae31b2fb2ac89680df984c9b1815f4c481279623a2adbaa7007f2e01f0351577"
SRC_URI[ME-SA1-C6-7I-D10_PE1.sha256sum] = "f7193193d843a3daf48e18553b8da498a7c7ccef263b973bbbc39428c0af7e25"
SRC_URI[ME-SA1-C6-7I-D10_PE3.sha256sum] = "82845c8ff0f3536c9fcc6e461e9ce7c3f60a3e29d1c62e2f76dd4b645afbf8b3"
SRC_URI[ME-SA1-C6-7I-D10_ST1.sha256sum] = "6e5e7de16da95523d23e384993cc3d7137c5a83aed4034ff6b2ee582244b14fe"
SRC_URI[ME-SA2-D6-7I-D11_PE1.sha256sum] = "5dd553eb114d725764db746d169abab9ebfcb3c8adc4d62ab515f31602ec6a3b"
SRC_URI[ME-SA2-D6-7I-D11_PE3.sha256sum] = "48d326d819c77e3751bcb6dd25dd2c53d3850c6fd60bdb0757b89df5fcd30cd8"
SRC_URI[ME-SA2-D6-7I-D11_ST1.sha256sum] = "30ba33304744261073fa538b7f54d7027b5861ce5ddcfaacd7993cfe2164467b"

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
