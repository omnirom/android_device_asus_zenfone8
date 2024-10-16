/*
 * Copyright (C) 2022 The LineageOS Project
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include <hardware/fingerprint.h>
#include <stdint.h>

#define AOD_ENABLED "doze_always_on"
#define AOD_PROPERTY "vendor.asus.touch_control_aod"
#define AOD_PROPERTY_FALSE "0"
#define AOD_PROPERTY_TRUE "1"

#define CMD_FINGER_DOWN 200001
#define CMD_FINGER_UP 200003
#define CMD_LIGHT_AREA_CLOSE 200000
#define CMD_LIGHT_AREA_STABLE 200002
#define CMD_PARTIAL_FINGER_DETECTED 200004

#define FOD_UI_PATH "/sys/devices/platform/soc/soc:qcom,dsi-display-primary/fod_ui"

#define UDFPS_PROPERTY "persist.vendor.asus.fp.wakeup"
#define UDFPS_PROPERTY_FALSE "false"
#define UDFPS_PROPERTY_TRUE "true"

class UdfpsHandler {
  public:
    virtual ~UdfpsHandler() = default;

    virtual void init(fingerprint_device_t* device) = 0;
    virtual void onFingerDown(uint32_t x, uint32_t y, float minor, float major) = 0;
    virtual void onFingerUp() = 0;

    virtual void onAcquired(int32_t result, int32_t vendorCode) = 0;
    virtual void cancel() = 0;

    virtual void preEnroll() = 0;
    virtual void enroll() = 0;
    virtual void postEnroll() = 0;
};

struct UdfpsHandlerFactory {
    UdfpsHandler* (*create)();
    void (*destroy)(UdfpsHandler* handler);
};

UdfpsHandlerFactory* getUdfpsHandlerFactory();
