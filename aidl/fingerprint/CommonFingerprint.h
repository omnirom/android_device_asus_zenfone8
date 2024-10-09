/*
 * Copyright (C) 2024 The Omnirom Project
 *
 * SPDX-License-Identifier: Apache-2.0
 */
 
#include "concurrent_queue.h"
#include "fingerprint.h"

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
