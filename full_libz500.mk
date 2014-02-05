PRODUCT_PACKAGES := \
    DeskClock \
    Bluetooth \
    Calculator \
    Calendar \
    CertInstaller \
    DrmProvider \
    Email2 \
    Exchange2 \
    FusedLocation \
    Gallery2 \
    InputDevices \
    LatinIME \
    Launcher2 \
    Music \
    MusicFX \
    Provision \
    QuickSearchBox \
    Settings \
    SystemUI \
    CalendarProvider \
    bluetooth-health \
    hostapd \
    wpa_supplicant.conf

PRODUCT_PACKAGES += \
    audio \
    dhcpcd.conf \
    network \
    pand \
    pppd \
    sdptool \
    wpa_supplicant

PRODUCT_PACKAGES += \
    icu.dat

PRODUCT_PACKAGES += \
    librs_jni \
    libvideoeditor_jni \
    libvideoeditor_core \
    libvideoeditor_osal \
    libvideoeditor_videofilters \
    libvideoeditorplayer \

PRODUCT_PACKAGES += \
    audio.primary.default \
    audio_policy.default \
    local_time.default \
    power.default

PRODUCT_PACKAGES += \
    local_time.default

PRODUCT_COPY_FILES := \
        frameworks/av/media/libeffects/data/audio_effects.conf:system/etc/audio_effects.conf

$(call inherit-product-if-exists, frameworks/base/data/fonts/fonts.mk)
$(call inherit-product-if-exists, external/cibu-fonts/fonts.mk)
$(call inherit-product-if-exists, external/lohit-fonts/fonts.mk)
$(call inherit-product-if-exists, external/naver-fonts/fonts.mk)
$(call inherit-product-if-exists, frameworks/base/data/keyboards/keyboards.mk)
$(call inherit-product, $(SRC_TARGET_DIR)/product/core.mk)

$(call inherit-product, hardware/ti/omap4xxx/omap4.mk)
$(call inherit-product, frameworks/native/build/tablet-dalvik-heap.mk)

$(call inherit-product-if-exists, device/ti/proprietary-open/omap4/ti-omap4-vendor.mk)

DEVICE_PACKAGE_OVERLAYS :=

# Copy files from our partitions folder to the appropriate outputs
COPY_FILES   := $(foreach I,$(shell find $(LOCAL_PATH)/copyfiles/ -type f | sed 's/.*\/copyfiles\///'), $(LOCAL_PATH)/copyfiles/$(I):$(I))
PRODUCT_COPY_FILES  += $(COPY_FILES)

PRODUCT_PACKAGES +=
PRODUCT_COPY_FILES +=
PRODUCT_NAME := full_libz500
PRODUCT_DEVICE := libz500
PRODUCT_MODEL := Sciaps LIBZ 500

