require trusted-firmware-a-renesas.inc

COMPATIBLE_MACHINE = "(rzg2h-family|rzg2l-family)"

SRCREV_tfa = "${AUTOREV}"
LIC_FILES_CHKSUM += "file://docs/license.rst;md5=b2c740efedc159745b9b31f88ff03dde"
SRC_URI = "git://github.com/amotus/arm-trusted-firmware;branch=v2.9/rz-sr;protocol=https;name=tfa"
