DESCRIPTION = "Linux kernel from SolidRun"

require linux.inc

KERNEL_URL = "git://github.com/SolidRun/linux-stable.git"
KBRANCH = "rz-5.10-cip36-sr"
SRCREV = "8772d496cb1c6cc15d762fb942fc510dbc4db3d4"

LINUX_VERSION = "5.10.184-cip36"

COMPATIBLE_MACHINE = "(rzg2h-family|rzg2l-family)"
