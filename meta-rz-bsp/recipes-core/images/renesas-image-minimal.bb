# Copyright (c) 2023, Renesas Electronics Corp.
#
# SPDX-License-Identifier: MIT

SUMMARY = "Renesas minimal BSP image based on core-image"
LICENSE = "MIT"

inherit core-image

IMAGE_FEATURES += " \
	package-management \
	splash \
	ssh-server-openssh \
"

# Additional packages we want to include
IMAGE_INSTALL:append = " \
	${PREFERRED_PROVIDER_virtual/bootloader}-extlinux \
"

IMAGE_LINGUAS = " "
IMAGE_ROOTFS_SIZE ?= "1048576"
IMAGE_NAME_SUFFIX = ""
