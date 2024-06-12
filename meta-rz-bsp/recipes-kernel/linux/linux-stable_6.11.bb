DESCRIPTION = "Linux stable kernel"

require linux.inc

KBRANCH = "linux-6.11.y-renesas"
SRCREV = "b51a1e80e7ac3923dcbd14194b9fc4f4ebb7e58b"
SRC_URI = "https://github.com/amotus/linux-renesas;protocol=https;branch=${KBRANCH}"

LINUX_VERSION = "6.11.0"

COMPATIBLE_MACHINE = "(rzg2h-family|rzg2l-family)"
