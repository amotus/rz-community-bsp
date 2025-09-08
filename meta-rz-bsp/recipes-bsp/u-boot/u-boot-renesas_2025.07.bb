require u-boot-renesas.inc

COMPATIBLE_MACHINE = "(rzg2h-family|rzg2l-family)"

DEPENDS += "gnutls-native"

SRCREV = "${AUTOREV}"
BRANCH = "v2025.07_common"
UBOOT_URL = "git://github.com/amotus/u-boot.git"

LIC_FILES_CHKSUM = "file://Licenses/README;md5=2ca5f2c35c8cc335f0a19756634782f1"
