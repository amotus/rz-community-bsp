# Autogenerate /etc/fw_env.config.
#
# Also add symbolic link in /etc:
#     u-boot-initial-env -> ${PN}-initial-env
# Needed because of this definition in uboot-config.bbclass:
#     UBOOT_INITIAL_ENV ?= "${PN}-initial-env"

# Obtain environment size/offset by reading U-Boot configuration file:
uboot_read_config() {
    CONFIG_ENV_SIZE=$(cat ${B}/.config   | grep CONFIG_ENV_SIZE   | sed "s@.*=@@")
    CONFIG_ENV_OFFSET=$(cat ${B}/.config | grep CONFIG_ENV_OFFSET | sed "s@.*=@@")
    CONFIG_ENV_OFFSET_D=$(printf "%d\n" ${CONFIG_ENV_OFFSET})
    CONFIG_ENV_OFFSET_K=$(echo ${CONFIG_ENV_OFFSET_D} | awk '{ print $1 / 1024 }')
}

do_install:prepend() {
    uboot_read_config

    # Create fw_printenv/setenv configuration file:
    echo "# PARTITION    CONFIG_ENV_OFFSET   CONFIG_ENV_SIZE" > ${WORKDIR}/fw_env.config
    echo "${CONFIG_ENV_PART}   ${CONFIG_ENV_OFFSET}            ${CONFIG_ENV_SIZE}" >> ${WORKDIR}/fw_env.config
}

do_install:append() {
    if [ -n "${UBOOT_INITIAL_ENV}" ]; then
        if [ "${PN}-initial-env" != "u-boot-initial-env" ]; then
            # Install the u-boot-initial-env symbolic link:
            ln -sf ${UBOOT_INITIAL_ENV}-${MACHINE}-${PV}-${PR} ${D}/${sysconfdir}/u-boot-initial-env
        fi
    fi
}

do_deploy:append() {
    if [ -n "${UBOOT_INITIAL_ENV}" ]; then
        uboot_read_config

        # Create environment image that can be incorporated into the wic image.
        ${B}/tools/mkenvimage -s ${CONFIG_ENV_SIZE} -o ${DEPLOYDIR}/${UBOOT_INITIAL_ENV}.bin \
            ${UBOOT_INITIAL_ENV}

        if [ "${PN}-initial-env" != "u-boot-initial-env" ]; then
            # Deploy the u-boot-initial-env symbolic links:
            ln -sf ${UBOOT_INITIAL_ENV}-${MACHINE}-${PV}-${PR} ${DEPLOYDIR}/u-boot-initial-env
            ln -sf ${UBOOT_INITIAL_ENV}.bin ${DEPLOYDIR}/u-boot-initial-env.bin
        fi
    fi
}

FILES:${PN}-env += " \
    ${@ '${sysconfdir}/u-boot-initial-env' if d.getVar('UBOOT_INITIAL_ENV') else ''} \
"
