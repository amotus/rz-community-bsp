require recipes-bsp/trusted-firmware-a/trusted-firmware-a.inc

DEPENDS += "bootparameter-native"
PROVIDES = "virtual/trusted-firmware-a"

EXTRA_OEMAKE:append = "${TFA_EXTRA_OEMAKE}"

# For the RZ/G2L family of SoCs we need a version of bl2 with a special header
# We also need to use SREC files
do_compile:append:rzg2l-family() {
	echo "Create bp.bin"
	bootparameter ${BUILD_DIR}/bl2.bin ${BUILD_DIR}/bp.bin

	echo "Create bl2_bp.bin"
	cat ${BUILD_DIR}/bp.bin ${BUILD_DIR}/bl2.bin > ${BUILD_DIR}/bl2_bp.bin

	echo "Convert bl2_bp.bin to bl2_bp.srec"
	objcopy -O srec --adjust-vma=0x00011E00 --srec-forceS3 -I binary ${BUILD_DIR}/bl2_bp.bin ${BUILD_DIR}/bl2_bp.srec

	echo "Convert fip.bin to fip.srec"
	objcopy -I binary -O srec --adjust-vma=0x0000 --srec-forceS3 ${BUILD_DIR}/fip.bin ${BUILD_DIR}/fip.srec
}

# For the RZ/G2H family of SoCs we need a number of files not installed by the
# meta-arm recipe
do_install:append:rzg2h-family() {
	echo "Install bl2.srec"
	install -m 0644 ${BUILD_DIR}/bl2.srec ${D}/firmware/bl2-${MACHINE}.srec

	echo "Install bl31.srec"
	install -m 0644 ${BUILD_DIR}/bl31.srec ${D}/firmware/bl31-${MACHINE}.srec

	echo "Install bootparam_sa0.srec"
	install -m 0644 ${S}/tools/renesas/rzg_layout_create/bootparam_sa0.srec \
		${D}/firmware/bootparam_sa0.srec

	echo "Install cert_header_sa6.srec"
	install -m 0644 ${S}/tools/renesas/rzg_layout_create/cert_header_sa6.srec \
		${D}/firmware/cert_header_sa6.srec
}

# Install files we need for the RZ/G2L family of SoCs that are not installed by
# the meta-arm recipe
do_install:append:rzg2l-family() {
	echo "Install bp.bin"
	install -m 0644 ${BUILD_DIR}/bp.bin ${D}/firmware/bp-${MACHINE}.bin

	echo "Install bl2.bin"
	install -m 0644 ${BUILD_DIR}/bl2.bin ${D}/firmware/bl2-${MACHINE}.bin

	echo "Install bl2_bp.srec"
	install -m 0644 ${BUILD_DIR}/bl2_bp.srec ${D}/firmware/bl2_bp-${MACHINE}.srec

	echo "Install bl2_bp.bin"
	install -m 0644 ${BUILD_DIR}/bl2_bp.bin ${D}/firmware/bl2_bp-${MACHINE}.bin

	echo "Install fip.srec"
	install -m 0644 ${BUILD_DIR}/fip.srec ${D}/firmware/fip-${MACHINE}.srec

	echo "Install fip.bin"
	install -m 0644 ${BUILD_DIR}/fip.bin ${D}/firmware/fip-${MACHINE}.bin
}
