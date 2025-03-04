require u-boot-renesas.inc

COMPATIBLE_MACHINE = "(rzg2h-family|rzg2l-family)"

# Based on Renesas BSP v3.0.6-update4
SRCREV = "455cf5a3ac6e34523136cc6a5ab55cffdfd8f57e"
BRANCH = "v2021.10/rz"
UBOOT_URL = "git://github.com/renesas-rz/renesas-u-boot-cip.git"

LIC_FILES_CHKSUM = "file://Licenses/README;md5=5a7450c57ffe5ae63fd732446b988025"
