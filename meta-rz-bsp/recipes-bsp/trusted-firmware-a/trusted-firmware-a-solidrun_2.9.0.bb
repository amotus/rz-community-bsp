require trusted-firmware-a-renesas.inc

COMPATIBLE_MACHINE = "(rzg2h-family|rzg2l-family)"

# Do not include commits that activate the watchdog with an insane 5s delay:
SRCREV_tfa = "6d212fffd11a22aebe18a8fa924541b2513d6f68"
LIC_FILES_CHKSUM += "file://docs/license.rst;md5=b2c740efedc159745b9b31f88ff03dde"
SRC_URI = "git://github.com/SolidRun/arm-trusted-firmware;branch=v2.9/rz-sr;protocol=https;name=tfa"
