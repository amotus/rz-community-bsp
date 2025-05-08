DESCRIPTION = "Flash Writer tool to write binaries to flash on the target"
LICENSE = "BSD-3-Clause"

PACKAGE_ARCH = "${MACHINE_ARCH}"
COMPATIBLE_MACHINE = "(rzg2h-family|rzg2l-family)"

FLASH_WRITER_URL = "git://github.com/dimonoff/rzg2_flash_writer"

BRANCH = "solidrun"
SRCREV = "${AUTOREV}"
PV = "1.06+git${SRCPV}"
LIC_FILES_CHKSUM = "file://LICENSE.md;md5=1fb5dca04b27614d6d04abca6f103d8d"

BRANCH:rzg2h-family = "master"
SRCREV:rzg2h-family = "ceebddab90e5ae9b100536114553af818261c660"
PV:rzg2h-family = "1.05+git${SRCPV}"
LIC_FILES_CHKSUM:rzg2h-family = "file://LICENSE.md;md5=7f62d8fc087d1e90350a140c9f8c8e99"

SRC_URI = "${FLASH_WRITER_URL};branch=${BRANCH};protocol=https"

inherit deploy
inherit nopackages
deltask do_install

S = "${WORKDIR}/git"

do_compile() {
	cd ${S}

	oe_runmake BOARD=${FLASH_WRITER_BOARD}
}

do_deploy() {
	install -d ${DEPLOYDIR}
	install -m 644 ${S}/AArch64_output/*.mot ${DEPLOYDIR}

	# Create machine-specific symbolic link, to simplify scripts that need
	# to refer to the flash writer output file, since it has a name that is
	# encoded with the memory configuration of the board.
	FW_MOT="$(find ${DEPLOYDIR} -name Flash_Writer_SCIF_${FLASH_WRITER_BOARD}\*.mot -printf '%f\n')"
	ln -sf ${FW_MOT} ${DEPLOYDIR}/Flash_Writer_SCIF_${MACHINE}.mot
}
addtask deploy after do_compile before do_build
