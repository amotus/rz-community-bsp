require trusted-firmware-a-renesas.inc

COMPATIBLE_MACHINE = "(rzg2h-family|rzg2l-family)"

SRCREV_tfa = "ee439acb1fe784706165697b1d1ba5fdc8af0bff"
LIC_FILES_CHKSUM += "file://docs/license.rst;md5=b2c740efedc159745b9b31f88ff03dde"
SRC_URI = "git://github.com/amotus/arm-trusted-firmware;branch=v2.9/rz-sr;protocol=https;name=tfa"
