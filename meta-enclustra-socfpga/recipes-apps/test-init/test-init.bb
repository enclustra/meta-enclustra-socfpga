LICENSE = "CLOSED"

inherit systemd

SYSTEMD_AUTO_ENABLE = "enable"
SYSTEMD_SERVICE:${PN} = "test.service"

SRC_URI = " \
    file://test.service \
    file://pt-autostart.sh \
    "

FILES:${PN} += "\${systemd_system_unitdir}/system/test.service"

do_install:append() {
    install -d ${D}${systemd_system_unitdir}
    install -m 0644 ${WORKDIR}/test.service ${D}/${systemd_system_unitdir}

    install -d ${D}${bindir}
    install -m 0744 ${WORKDIR}/pt-autostart.sh ${D}/${bindir}
}
