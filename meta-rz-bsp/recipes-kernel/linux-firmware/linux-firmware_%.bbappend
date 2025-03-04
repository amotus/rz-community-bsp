FILESEXTRAPATHS:prepend := "${THISDIR}/files:"

SRC_URI += " \
    file://LICENSE \
    file://brcm-firmware.tar.gz \
"

do_install:append() {
    install -d ${D}${nonarch_base_libdir}/firmware
    cp -r ${WORKDIR}/firmware/* ${D}${nonarch_base_libdir}/firmware
    cp -r ${WORKDIR}/LICENSE ${D}${nonarch_base_libdir}/firmware/brcm
}

PACKAGES =+ "${PN}-bcm43439"
LICENSE:${PN}-bcm43439 = "Firmware-broadcom_bcm43xx"
RDEPENDS:${PN}-bcm43439 += "${PN}-broadcom-license"

FILES:${PN}-bcm43455 += "${nonarch_base_libdir}/firmware/brcm/*43455*"
FILES:${PN}-bcm43439 += " \
    ${nonarch_base_libdir}/firmware/brcm/*43439* \
    ${nonarch_base_libdir}/firmware/cypress/*43439* \
"
FILES:${PN}-bcm-0bb4-0306 += "${nonarch_base_libdir}/firmware/brcm/BCM.hcd"
