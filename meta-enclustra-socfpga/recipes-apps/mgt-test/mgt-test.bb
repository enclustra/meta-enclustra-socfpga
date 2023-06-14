LICENSE = "CLOSED"

FILESEXTRAPATHS:append = "files"

FILES:${PN} += "/home/root"

S = "${WORKDIR}"

SRC_URI = " \
    file://Makefile \
    file://mgt-test.c \
    "

do_compile:append() {
    bbwarn "mgt test is recompiled"
}

do_install() {
    install -d ${D}/home/root
    install -m 0755 mgt-test ${D}/home/root
}
