################################################################################
#
# MCYCLER
#
################################################################################

MCYCLER_VERSION = 1.0
MCYCLER_SITE = $(BR2_EXTERNAL_LITEX_VEXRISCV_PATH)/package/mcycler/src
MCYCLER_SITE_METHOD = local

MCYCLER_LICENSE = MIT
MCYCLER_LICENSE_FILES = LICENSE

define MCYCLER_BUILD_CMDS
	$(MAKE) -C $(@D)
endef

define MCYCLER_INSTALL_TARGET_CMDS
	$(MAKE) -C $(@D) DESTDIR=$(TARGET_DIR) install
endef

$(eval $(cmake-package))