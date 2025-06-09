FILESEXTRAPATHS:prepend := "${THISDIR}/files:"

BRCM_SRC = "brcmfmac43439-sdio"

SRC_URI += " \
    file://LICENSE \
    file://brcm-firmware.tar.gz \
"

do_install:append() {
    install -d ${D}${nonarch_base_libdir}/firmware
    cp -r ${WORKDIR}/firmware/* ${D}${nonarch_base_libdir}/firmware
    cp -r ${WORKDIR}/LICENSE ${D}${nonarch_base_libdir}/firmware/brcm

    if [ "${KERNEL_DEVICETREE_MODEL}" != "" ]; then
        # Add per-board SDIO bins symbolic link to avoid having this warning:
        #   ... firmware load for brcm/brcmfmac43439-sdio.renesas,rzg2lc-sr-som.txt failed with error -2
        for ext in txt bin clm_blob; do
            if [ -f ${D}${nonarch_base_libdir}/firmware/brcm/${BRCM_SRC}.${ext} ]; then
                ln -s ${BRCM_SRC}.${ext} \
		    ${D}${nonarch_base_libdir}/firmware/brcm/${BRCM_SRC}.${KERNEL_DEVICETREE_MODEL}.${ext}
            fi
        done
    fi
}

PACKAGES =+ "${PN}-bcm43439"
LICENSE:${PN}-bcm43439 = "Firmware-broadcom_bcm43xx"
RDEPENDS:${PN}-bcm43439 += "${PN}-broadcom-license"

FILES:${PN}-bcm43439 += " \
    ${nonarch_base_libdir}/firmware/brcm/*43439* \
"
