FILESEXTRAPATHS:prepend := "${THISDIR}/files:"
PACKAGECONFIG:append = " networkd resolved"

SRC_URI:append := " \
    file://10-eth0.network \
    "

FILES:${PN}:append := "${sysconfdir}/systemd/network"

do_install:append() {
    install -d ${D}${sysconfdir}/systemd/network
    install -m 0644 ${WORKDIR}/10-eth0.network ${D}${sysconfdir}/systemd/network
}
