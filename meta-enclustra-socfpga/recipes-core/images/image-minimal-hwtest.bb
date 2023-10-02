IMAGE_LINGUAS = " "

LICENSE = "MIT"

inherit core-image

IMAGE_INSTALL = "packagegroup-core-boot"
IMAGE_INSTALL:append = " i2c-tools"
IMAGE_INSTALL:append = " mtd-utils"
IMAGE_INSTALL:append = " devmem2"
IMAGE_INSTALL:append = " iperf3"
IMAGE_INSTALL:append = " usbutils"
IMAGE_INSTALL:append = " ${CORE_IMAGE_EXTRA_INSTALL}"
