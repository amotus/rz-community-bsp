FILESEXTRAPATHS:prepend := "${THISDIR}/files:"

SRC_URI:append = " \
    file://0001-add-solidrun-rzg2lc-support.patch \
    file://0002-add-sr-rzg2l-1g-board-support.patch \
    file://0003-add-sr-rzv2l-2GB-board-support.patch \
    file://0004-renesas-solidrun-Use-updated-memory-timing-configura.patch \
    file://0005-renesas-solidrun-add-sr-rzg2l-2g-board-support.patch \
    file://0006-renesas-solidrun-add-sr-rzg2ul-1g-board-support.patch \
    file://0007-renesas-solidrun-add-sr-rzg2ul-512MB-board-support.patch \
    file://0008-HACK-drivers-renesas-micro-delay-count-from-10-milli.patch \
    file://0009-import-rz-g3s-i2c-driver-from-v2.7-rzg3s.patch \
    file://0010-drivers-renesas-adapt-g3s-i2c-driver-for-rz-g2l-rz-v.patch \
    file://0011-drivers-renesas-i2c-change-api-to-support-multi-byte.patch \
    file://0012-drivers-renesas-i2c-add-tlv-library.patch \
    file://0013-plat-renesas-rz-ddr-call-new-function-ddr_param_setu.patch \
    file://0014-add-generic-sr_rzg2l-board-for-all-memory-sizes.patch \
    file://0015-plat-renesas-rz-return-optional-dtb-blob-with-dram-i.patch \
    file://0016-plat-renesas-rz-call-optional-board-specific-functio.patch \
    file://0017-board-sr_rzg2l-add-support-for-passing-dram-info-to-.patch \
    file://0018-plat-renesas-rz-ddr-fix-build-error-when-DDR_PARAM_S.patch \
    file://0019-board-sr_rzg2l-optimise-ddr-parameter-selection-for-.patch \
"
