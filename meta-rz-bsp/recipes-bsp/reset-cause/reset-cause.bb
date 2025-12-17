DESCRIPTION = "Reset cause determination script"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

PV = "0.1.0"

SRC_URI += "file://reset-cause.sh"

S = "${WORKDIR}"

do_install() {
    install -d ${D}${sbindir}
    install -m 0755 ${S}/reset-cause.sh ${D}${sbindir}/reset-cause
}

FILES:${PN} += "${sbindir}/*"

RDEPENDS:${PN} += "bash dimonoff-scripts devmem2"
