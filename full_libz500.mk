$(call inherit-product, $(SRC_TARGET_DIR)/product/languages_full.mk)
$(call inherit-product, $(SRC_TARGET_DIR)/product/full_base.mk)

DEVICE_PACKAGE_OVERLAYS :=

# Copy files from our partitions folder to the appropriate outputs
COPY_FILES   := $(foreach I,$(shell find $(LOCAL_PATH)/copyfiles/ -type f | sed 's/.*\/copyfiles\///'), $(LOCAL_PATH)/copyfiles/$(I):$(I))
PRODUCT_COPY_FILES  += $(COPY_FILES)

PRODUCT_PACKAGES +=
PRODUCT_COPY_FILES +=
PRODUCT_NAME := full_libz500
PRODUCT_DEVICE := libz500
PRODUCT_MODEL := Sciaps LIBZ 500

