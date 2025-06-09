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

FILES:${PN}-bcm43439 += " \
    ${nonarch_base_libdir}/firmware/brcm/*43439* \
"
