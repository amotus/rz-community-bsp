# rz-community-bsp

This repository provides a basic BSP that will build a simple, usable images
for Renesas RZ reference platforms.

It is designed to allow users to use the latest upstream open source projects
and is provided as-is with no support from Renesas.

For supported and fully functional software from Renesas please use the
official BSPs provided on [renesas.com](https://renesas.com).

## Dependencies

| Name | Layers | Repository | Branch | Revision |
| --- | --- | --- | --- | --- |
| poky | meta<br>meta-poky | https://git.yoctoproject.org/poky | kirkstone<br>scarthgap | kirkstone-4.0.22<br>scarthgap-5.0.5 |
| meta-arm | meta-arm-toolchain<br>meta-arm | https://git.yoctoproject.org/meta-arm | kirkstone<br>master | yocto-4.0.5<br>yocto-5.0.1 |
| meta-openembedded | meta-oe | https://git.openembedded.org/meta-openembedded | kirkstone<br>scarthgap | 4ad41baed623<br>2e3126c9c16b |

### Optional Dependencies

The following layers are only required when certain options are selected:

| Condition |Name | Layers | Repository | Branch | Revision |
| --- | --- | --- | --- | --- | --- |
| Mainline kernel is selected<br>via `kas/kernel/mainline.yml`<br>or `KERNEL_MAINLINE=y` in `kas menu` | meta-linux-mainline | meta-linux-mainline | https://github.com/betafive/meta-linux-mainline | main | HEAD |
| renesas-image-demo is selected<br>via `kas/image/renesas-image-demo.yml`<br>or `IMAGE_RENESAS_IMAGE_DEMO=y` in `kas menu` | meta-rz-panfrost | meta-rz-panfrost | https://github.com/renesas-rz/meta-rz-panfrost.git | scarthgap | 7ec5305383a3 |

## Supported Machines

| SoC | Reference Platform | Machine Name |
| --- | --- | --- |
| Renesas RZ/G2H | RZ/G2H HopeRun Evaluation Kit | hihope-rzg2h |
| Renesas RZ/G2M | RZ/G2M HopeRun Evaluation Kit | hihope-rzg2m |
| Renesas RZ/G2N | RZ/G2N HopeRun Evaluation Kit | hihope-rzg2n |
| Renesas RZ/G2E | RZ/G2E SiLinux Evaluation Kit | ek874 |
| Renesas RZ/G2L | RZ/G2L SMARC Evaluation Kit | smarc-rzg2l |
| Renesas RZ/G2LC | RZ/G2LC SMARC Evaluation Kit | smarc-rzg2lc |
| Renesas RZ/G2UL | RZ/G2UL SMARC Evaluation Kit | smarc-rzg2ul |
| Renesas RZ/V2L | RZ/V2L SMARC Evaluation Kit | smarc-rzv2l |

## Provided Images

| Image Name | Description | Key Features |
| --- | --- | --- |
| renesas-image-minimal | Provides a basic BSP image based on Poky's core-image. | Linux kernel<br>U-Boot<br>Trusted-Firmware-A |
| renesas-image-demo | Provides a more featured image that includes Weston/Wayland with Panfrost support. | Linux kernel<br>U-Boot<br>Trusted-Firmware-A<br>Weston<br>Wayland<br>Panfrost<br>Various debug tools |

### renesas-image-demo Notes

This image is currently only supported for smarc-rzg2l and smarc-rzg2lc using
Yocto Scarthgap.

If not building using Kas, the following needs to be added to \*local.conf\*:

```bitbake
DISTRO_FEATURES += " opengl wayland"
```

## Linux Kernel Support

The RZ Community BSP makes it possible to build a number of different versions
of the Linux kernel.

Each RZ device/platform is **not** supported to the same level on all kernel
versions!

The Renesas BSP kernels will have the most functionality supported. \
The Mainline kernel is next, followed by the CIP SLTS kernels. \
LTS kernels are likely to have the least functionality, so use with caution.

## What's Tested?

For full details on what is and isn't tested please see
[docs/TESTING.md](docs/TESTING.md).

## Building

This project is set up to be built with [Kas](https://github.com/siemens/kas).
The Kas tool provides an easy mechanism to setup bitbake based projects.
Documentation for Kas is available on [readthedocs.io](
https://kas.readthedocs.io/en/latest/userguide.html).

### kas-container

The easiest way to use Kas is to use `kas-container`. This script will run the
Bitbake built in a pre-configured Docker container.

For ease of use a copy of the script has been included in this repository.

#### Using kas-container on Ubuntu 20.04

There is a known issue when building Yocto BSPs with `kas-container` on an
Ubuntu 20.04 host due to mismatched glibc versions.

A workaround is to add the below argument when calling `kas-container`:

```bash
./kas-container --runtime-args "--security-opt seccomp=unconfined" build
```

### Kas Menu

Kas supports a Kconfig based menu system which can be accessed with the
`kas menu` (or `kas-container menu`) command. This allows users to easily select
between options without having to manually select the kas yaml files required
for their build.

Follow the instuctions in the menu to select the build configuration and then
either "Build" to save the configuration to a .config.yaml file and kick off a
build straight way, or "Save & Exit" to only store the configuration to a
.config.yaml file for future use.

Example kas menu usage:

```bash
# Make sure we're inside rz-community-bsp (this repository)
cd rz-community-bsp

./kas-container menu
```

If you exit the kas menu screen without selecting "Build" you can subsequently
start a build using the saved configuration:

```bash
./kas-container build
```

Alternatively you can start a shell within the kas build environment that has
already been configured for use with bitbake, with all dependencies checked out:

```bash
./kas-container shell
```

### Kas with Configuraiton Fragments

The build can also be configured using a number of options provided in different
kas yaml files. They can be daisy chained onto each other so that multiple
options can be selected.

**kas/base.yml**\
This file adds in the base configuration used by this project. It is
automatically included by the yocto version yaml files (see below).

**kas/yocto/*.yml**\
This includes the dependency configuration for building the rz-community-bsp
based on specific versions of Yocto.

**kas/machine/*.yml**\
A selection of files to use to specify which machine to build for.

**kas/image/*.yml**\
A selection of files to use to specify which image to build.

**kas/kernel/*.yml**\
A selection of files to use to specify which Linux kernel version to build.

**kas/u-boot/*.yml**\
A selection of files to use to specify which U-Boot version to build.

**kas/trusted-firmware-a/*.yml**\
A selection of files to use to specify which Trusted-Firmware-A version to build.

**kas/opt/debug.yml**\
Add various features to the image to help with development and debugging.\
Specifically, it enables the *debug-tweaks* image feature that allows users to\
be able to login without a password. More information can be found\
[here](https://docs.yoctoproject.org/dev/ref-manual/features.html#:~:text=debug%2Dtweaks%3A%20Makes%20an%20image,enables%20post%2Dinstallation%20logging).

Various hardware debugging tools are also included.

Example usage:

```bash
# Make sure we're inside rz-community-bsp (this repository)
cd rz-community-bsp

# Yocto: kirkstone
# Image: renesas-image-minimal
# Machine: hihope-rzg2h
# Linux: linux-renesas v5.10
./kas-container build kas/yocto/kirkstone.yml:kas/opt/debug.yml:kas/image/renesas-image-minimal.yml:kas/machine/hihope-rzg2h.yml:kas/kernel/renesas-5.10.yml

# Yocto: kirkstone
# Image: renesas-image-minimal
# Machine: smarc-rzg2l
# Linux: linux-cip v6.1
./kas-container build kas/yocto/kirkstone.yml:kas/opt/debug.yml:kas/image/renesas-image-minimal.yml:kas/machine/smarc-rzg2l.yml:kas/kernel/cip-6.1.yml

# If you are re-building in the same directory as a previous build it may be
# prudent to use --update and --force-checkout to ensure that the dependency
# repositories are correct
./kas-container build --update --force-checkout kas/yocto/kirkstone.yml:kas/opt/debug.yml:kas/image/renesas-image-minimal.yml:kas/machine/hihope-rzg2h.yml:kas/kernel/cip-6.1.yml

# Yocto: scarthgap
# Image: renesas-image-demo
# Machine: smarc-rzg2l
# Linux: linux-cip v6.1
./kas-container build --update --force-checkout kas/yocto/scarthgap.yml:kas/opt/debug.yml:kas/image/renesas-image-demo.yml:kas/machine/smarc-rzg2l.yml:kas/kernel/cip-6.1.yml
```

### Building the SDK

In order to (cross) compile applications to run on the flashed image an SDK is
needed. Yocto provides a way to build this SDK and create a suitable installer
for your build machine.

The architecture (e.g. x86_64, aarch64) of the machine where the SDK is to be
used can be set in local.conf with the `SDKMACHINE` variable. It can also be
configured in the kas menu.

To build the SDK installer package run the following, replacing
`renesas-image-minimal` with the target image of your choice:

```bash
bitbake renesas-image-minimal -c populate_sdk
```

The SDK installer (the \*.sh file) will be output to the standard deploy
directory. Here is an example:

```bash
ls tmp/deploy/sdk
poky-glibc-x86_64-renesas-image-minimal-cortexa55-smarc-rzg2l-toolchain-4.0.16.host.manifest
poky-glibc-x86_64-renesas-image-minimal-cortexa55-smarc-rzg2l-toolchain-4.0.16.sh
poky-glibc-x86_64-renesas-image-minimal-cortexa55-smarc-rzg2l-toolchain-4.0.16.target.manifest
poky-glibc-x86_64-renesas-image-minimal-cortexa55-smarc-rzg2l-toolchain-4.0.16.testdata.json
```

## Contributions

Contributions are *very* welcome! Please submit a pull request for review.

## License

This repository and its contents is licensed under MIT. See
[COPYING.MIT](COPYING.MIT) for details.

## Maintenance

This repository provided on a best-effort basis. There are no promises that
everything will work!

Maintainer: **Chris Paterson**

* Email: [chris.paterson2@renesas.com](mailto:chris.paterson2@renesas.com)
* GitHub/GitLab username: patersonc
* IRC (Libera.Chat): patersonc
