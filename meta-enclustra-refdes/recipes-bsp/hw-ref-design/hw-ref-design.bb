SUMMARY = "Exported reference design binaries"

inherit deploy

LICENSE = "Proprietary"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/Proprietary;md5=0557f9d92cf58f2ccdd50f62f8ac0b28"

PROVIDES = "virtual/bitstream"


SRC_URI:refdes-me-aa1-480-2i3-d12e-nfx3-pe1 = "\
    https://github.com/enclustra/Mercury_AA1_PE1_Reference_Design/releases/download/2022.1_v1.0.0/binaries_ME-AA1-480-2I3-D12E-NFX3_PE1.zip;name=ME-AA1-480-2I3-D12E-NFX3_PE1 \
"

SRC_URI:refdes-me-aa1-480-2i3-d12e-nfx3-pe3 = "\
    https://github.com/enclustra/Mercury_AA1_PE3_Reference_Design/releases/download/2022.1_v1.0.0/binaries_ME-AA1-480-2I3-D12E-NFX3_PE3.zip;name=ME-AA1-480-2I3-D12E-NFX3_PE3 \
"

SRC_URI:refdes-me-aa1-480-2i3-d12e-nfx3-st1 = "\
    https://github.com/enclustra/Mercury_AA1_ST1_Reference_Design/releases/download/2022.1_v1.0.0/binaries_ME-AA1-480-2I3-D12E-NFX3_ST1.zip;name=ME-AA1-480-2I3-D12E-NFX3_ST1 \
"

SRC_URI:refdes-me-aa1-270-2i2-d11e-nfx3-pe1 = "\
    https://github.com/enclustra/Mercury_AA1_PE1_Reference_Design/releases/download/2022.1_v1.0.0/binaries_ME-AA1-270-2I2-D11E-NFX3_PE1.zip;name=ME-AA1-270-2I2-D11E-NFX3_PE1 \
"

SRC_URI:refdes-me-aa1-270-2i2-d11e-nfx3-pe3 = "\
    https://github.com/enclustra/Mercury_AA1_PE3_Reference_Design/releases/download/2022.1_v1.0.0/binaries_ME-AA1-270-2I2-D11E-NFX3_PE3.zip;name=ME-AA1-270-2I2-D11E-NFX3_PE3 \
"
SRC_URI:refdes-me-aa1-270-2i2-d11e-nfx3-st1 = "\
    https://github.com/enclustra/Mercury_AA1_ST1_Reference_Design/releases/download/2022.1_v1.0.0/binaries_ME-AA1-270-2I2-D11E-NFX3_ST1.zip;name=ME-AA1-270-2I2-D11E-NFX3_ST1 \
"

SRC_URI:refdes-me-aa1-270-3e4-d11e-nfx3-pe1 = "\
    https://github.com/enclustra/Mercury_AA1_PE1_Reference_Design/releases/download/2022.1_v1.0.0/binaries_ME-AA1-270-3E4-D11E-NFX3_PE1.zip;name=ME-AA1-270-3E4-D11E-NFX3_PE1 \
"

SRC_URI:refdes-me-aa1-270-3e4-d11e-nfx3-pe3 = "\
    https://github.com/enclustra/Mercury_AA1_PE3_Reference_Design/releases/download/2022.1_v1.0.0/binaries_ME-AA1-270-3E4-D11E-NFX3_PE3.zip;name=ME-AA1-270-3E4-D11E-NFX3_PE3 \
"

SRC_URI:refdes-me-aa1-270-3e4-d11e-nfx3-st1 = "\
    https://github.com/enclustra/Mercury_AA1_ST1_Reference_Design/releases/download/2022.1_v1.0.0/binaries_ME-AA1-270-3E4-D11E-NFX3_ST1.zip;name=ME-AA1-270-3E4-D11E-NFX3_ST1 \
"

SRC_URI:refdes-me-sa1-c6-7i-d10-pe1 = "\
    https://github.com/enclustra/Mercury_SA1_PE1_Reference_Design/releases/download/2022.1_v1.0.0/binaries_ME-SA1-C6-7I-D10_PE1.zip;name=ME-SA1-C6-7I-D10_PE1 \
"

SRC_URI:refdes-me-sa1-c6-7i-d10-pe3 = "\
    https://github.com/enclustra/Mercury_SA1_PE3_Reference_Design/releases/download/2022.1_v1.0.0/binaries_ME-SA1-C6-7I-D10_PE3.zip;name=ME-SA1-C6-7I-D10_PE3 \
"

SRC_URI:refdes-me-sa1-c6-7i-d10-st1 = "\
    https://github.com/enclustra/Mercury_SA1_ST1_Reference_Design/releases/download/2022.1_v1.0.0/binaries_ME-SA1-C6-7I-D10_ST1.zip;name=ME-SA1-C6-7I-D10_ST1 \
"

SRC_URI:refdes-me-sa2-d6-7i-d11-pe1 = "\
    https://github.com/enclustra/Mercury_SA2_PE1_Reference_Design/releases/download/2022.1_v1.0.0/binaries_ME-SA2-D6-7I-D11_PE1.zip;name=ME-SA2-D6-7I-D11_PE1 \
"

SRC_URI:refdes-me-sa2-d6-7i-d11-pe3 = "\
    https://github.com/enclustra/Mercury_SA2_PE3_Reference_Design/releases/download/2022.1_v1.0.0/binaries_ME-SA2-D6-7I-D11_PE3.zip;name=ME-SA2-D6-7I-D11_PE3 \
"

SRC_URI:refdes-me-sa2-d6-7i-d11-st1 = "\
    https://github.com/enclustra/Mercury_SA2_ST1_Reference_Design/releases/download/2022.1_v1.0.0/binaries_ME-SA2-D6-7I-D11_ST1.zip;name=ME-SA2-D6-7I-D11_ST1 \
"

SRC_URI[ME-AA1-270-2I2-D11E-NFX3_PE1.sha256sum] = "6e0133670aac0d44d0d724bf44ac5671cf564b60f9b27e563a0a7a8f2541b2a2"
SRC_URI[ME-AA1-270-2I2-D11E-NFX3_PE3.sha256sum] = "f54d4edfa31b123fc62f83fc1a9580ad4c7a091fba08199c2529d55b43ac3e5b"
SRC_URI[ME-AA1-270-2I2-D11E-NFX3_ST1.sha256sum] = "0e62129a0badb004e1f9e6c505ecda4502f57377ec2f0e33f188483d947503e3"
SRC_URI[ME-AA1-270-3E4-D11E-NFX3_PE1.sha256sum] = "df3e4d93b77a7f1c948f3d05cead8733bcea78cd8c9e260d7975d114e3c9cf8b"
SRC_URI[ME-AA1-270-3E4-D11E-NFX3_PE3.sha256sum] = "3823e2c3dcf2a14d4066b4adf005bd085e4efe605433ea4a3ea6f15c0a5a4d9e"
SRC_URI[ME-AA1-270-3E4-D11E-NFX3_ST1.sha256sum] = "734f44d76a3bd7a3cb46e2e74dc5d3cd84450d288e4bb12c07438e61227aad02"
SRC_URI[ME-AA1-480-2I3-D12E-NFX3_PE1.sha256sum] = "09d1789e327f7c6b8f3bfdaa37a558b2072d4012aec108e2e865932a73e430d2"
SRC_URI[ME-AA1-480-2I3-D12E-NFX3_PE3.sha256sum] = "0c0780b9817ed87361e0b21dddaa4edee47c364dbcab6e969d37bd96354c82d5"
SRC_URI[ME-AA1-480-2I3-D12E-NFX3_ST1.sha256sum] = "6def21b9539c71201fe9593a9f609a9e05e272262d5bd15beb111e4ef63aa03f"
SRC_URI[ME-SA1-C6-7I-D10_PE1.sha256sum] = "4a9fe6b4ab4b9dd7fa1a1177be8fc6e9ab3dcd7ba3aacd091a99874a2e96ac29"
SRC_URI[ME-SA1-C6-7I-D10_PE3.sha256sum] = "6242b61c52e74250d6b569ff5c5a557b06c6df5e1a94c07ef23fca31666c7bf1"
SRC_URI[ME-SA1-C6-7I-D10_ST1.sha256sum] = "e004766c3f3cd221ada325c1be1e2ddab70df806f964bb58f2b791087b73ed6d"
SRC_URI[ME-SA2-D6-7I-D11_PE1.sha256sum] = "b765e223a4a6e70eda75b884eb4d982dfe3fcb7e1145d05e850750fe77ac79be"
SRC_URI[ME-SA2-D6-7I-D11_PE3.sha256sum] = "7c3bcf26aaabebe76ba339b79747aaf34e358fbd09dc1993d2edf89eedeb7436"
SRC_URI[ME-SA2-D6-7I-D11_ST1.sha256sum] = "1773efece2ad2b50417e170a3158e93307589ca4cee4143ee32f7d7ed7e31ee5"

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

do_deploy:append:me-sa1-c6-7i-d10() {
    mkdir -p ${DEPLOY_DIR_IMAGE}/handoff
    cp -r ${WORKDIR}/${UBOOT_CONFIG}/hps_isw_handoff/Mercury_SA1_pd_hps_0/* ${DEPLOY_DIR_IMAGE}/handoff
    install -D -m 0644 ${WORKDIR}/${UBOOT_CONFIG}/${ENCLUSTRA_BASE_NAME}.rbf ${DEPLOY_DIR_IMAGE}/fpga.rbf
}

do_deploy:append:me-sa2-d6-7i-d11() {
    mkdir -p ${DEPLOY_DIR_IMAGE}/handoff
    cp -r ${WORKDIR}/${UBOOT_CONFIG}/hps_isw_handoff/Mercury_SA2_pd_hps_0/* ${DEPLOY_DIR_IMAGE}/handoff
    install -D -m 0644 ${WORKDIR}/${UBOOT_CONFIG}/${ENCLUSTRA_BASE_NAME}.rbf ${DEPLOY_DIR_IMAGE}/fpga.rbf
}

addtask deploy after do_configure
