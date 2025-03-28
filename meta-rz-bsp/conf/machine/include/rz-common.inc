require conf/machine/include/soc-family.inc

MACHINE_FEATURES = "serial screen usbhost"
IMAGE_FSTYPES:append = " tar.gz"
SERIAL_CONSOLES = "115200;ttySC0"

# Linux kernel configuration
PREFERRED_PROVIDER_virtual/kernel ?= "linux-cip"
PREFERRED_VERSION_linux-cip ?= "6.1%"
KERNEL_IMAGETYPE ?= "Image"
KERNEL_DEVICETREE ?= "renesas/${KERNEL_DEVICETREE_BASENAME}.dtb"

# Yocto Scarthgap has increased OLDEST_KERNEL to 5.15 but we have the option to
# build 5.10 with this meta-layer. Override OLDEST_KERNEL to allow this
OLDEST_KERNEL = "5.10"

# Packages always required in the rootfs
MACHINE_EXTRA_RDEPENDS += " \
	kernel-devicetree \
	kernel-image \
"

# Other dependencies that aren't included in the rootfs
EXTRA_IMAGEDEPENDS += " \
	flash-writer \
	virtual/bootloader \
	virtual/trusted-firmware-a \
"

# SD/MMC configuration:
ROOT_PARENT_DEV = "/dev/mmcblk0"
ROOT_PART_PREFIX = "p"

# U-Boot environment partition:
# For SD, set to:   /dev/mmcblk0
# For eMMC, set to: /dev/mmcblk0boot0
CONFIG_ENV_PART = "/dev/mmcblk0boot0"

# EXTLINUX configuration (needed by distroboot):
UBOOT_EXTLINUX = "1"
UBOOT_EXTLINUX_CONSOLE = ""
UBOOT_EXTLINUX_ROOT = "root=${ROOT_PARENT_DEV}${ROOT_PART_PREFIX}${distro_bootpart}"
UBOOT_EXTLINUX_FDT = "/boot/${KERNEL_DEVICETREE_BASENAME}.dtb"
UBOOT_EXTLINUX_KERNEL_ARGS = "rootwait rw"
