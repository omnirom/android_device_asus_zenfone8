/*
 * Copyright (C) 2019 The LineageOS Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#define LOG_TAG "FingerprintInscreenService"

#include <android-base/file.h>
#include "FingerprintInscreen.h"
#include <hidl/HidlTransportSupport.h>

#define GLOBAL_HBM_PATH "/proc/globalHbm"
#define GLOBAL_HBM_ON "1"
#define GLOBAL_HBM_OFF "0"

#define FP_CTRL_PATH "/proc/driver/fts_fp_ctrl_mode"
#define FP_CTRL_SEC "2"
#define FP_CTRL_OFF "0"

#define FOD_ENABLE_PATH "/proc/driver/fts_fp_mode"
#define FOD_ENABLE_ON "1"
#define FOD_ENABLE_OFF "0"

#define FOD_EVENT_PATH "/proc/driver/fod_event"
#define FOD_WAKEUP_EVENT "33"

namespace vendor {
namespace omni {
namespace biometrics {
namespace fingerprint {
namespace inscreen {
namespace V1_0 {
namespace implementation {

FingerprintInscreen::FingerprintInscreen() {
    this->mGoodixFingerprintDaemon = IGoodixFingerprintDaemon::getService();
}

Return<void> FingerprintInscreen::onStartEnroll() {
    return Void();
}

Return<void> FingerprintInscreen::onFinishEnroll() {
    return Void();
}

Return<void> FingerprintInscreen::onPress() {
    this->mGoodixFingerprintDaemon->sendCommand(200001, {},
                                                [](int, const hidl_vec<signed char>&) {});
    android::base::WriteStringToFile(FOD_WAKEUP_EVENT, FOD_EVENT_PATH);
    android::base::WriteStringToFile(FP_CTRL_SEC, FP_CTRL_PATH);
    android::base::WriteStringToFile(GLOBAL_HBM_ON, GLOBAL_HBM_PATH);
    this->mGoodixFingerprintDaemon->sendCommand(200002, {},
                                                [](int, const hidl_vec<signed char>&) {});
    return Void();
}

Return<void> FingerprintInscreen::onRelease() {
    android::base::WriteStringToFile(GLOBAL_HBM_OFF, GLOBAL_HBM_PATH);
    android::base::WriteStringToFile(FP_CTRL_OFF, FP_CTRL_PATH);
    this->mGoodixFingerprintDaemon->sendCommand(200003, {},
                                                [](int, const hidl_vec<signed char>&) {});
    return Void();
}

Return<void> FingerprintInscreen::onShowFODView() {
    android::base::WriteStringToFile(FOD_ENABLE_ON, FOD_ENABLE_PATH);
    return Void();
}

Return<void> FingerprintInscreen::onHideFODView() {
    android::base::WriteStringToFile(GLOBAL_HBM_OFF, GLOBAL_HBM_PATH);
    android::base::WriteStringToFile(FP_CTRL_OFF, FP_CTRL_PATH);
    android::base::WriteStringToFile(FOD_ENABLE_OFF, FOD_ENABLE_PATH);
    return Void();
}

Return<bool> FingerprintInscreen::handleAcquired(int32_t, int32_t) {
    return false;
}

Return<bool> FingerprintInscreen::handleError(int32_t, int32_t) {
    return false;
}

Return<void> FingerprintInscreen::setLongPressEnabled(bool) {
    return Void();
}

Return<int32_t> FingerprintInscreen::getDimAmount(int32_t) {
    return 0;
}

Return<bool> FingerprintInscreen::shouldBoostBrightness() {
    return false;
}

Return<void> FingerprintInscreen::setCallback(const sp<IFingerprintInscreenCallback>&) {
    return Void();
}

Return<int32_t> FingerprintInscreen::getPositionX() {
    return 435;
}

Return<int32_t> FingerprintInscreen::getPositionY() {
    return 1631;
}

Return<int32_t> FingerprintInscreen::getSize() {
    return 220;
}

}  // namespace implementation
}  // namespace V1_0
}  // namespace inscreen
}  // namespace fingerprint
}  // namespace biometrics
}  // namespace omni
}  // namespace vendor
