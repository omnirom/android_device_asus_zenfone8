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

#define LOCAL_HBM_MODE "/proc/globalHbm"
#define LOCAL_HBM_MODE1 "/sys/devices/platform/soc/990000.i2c/i2c-1/1-0038/fts_fp_ctrl_mode"
#define LOCAL_HBM_ON1 "2"
#define LOCAL_HBM_ON "1"
#define LOCAL_HBM_OFF "0"

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
    //android::base::WriteStringToFile(LOCAL_HBM_ON, LOCAL_HBM_MODE1);
    return Void();
}

Return<void> FingerprintInscreen::onFinishEnroll() {
    return Void();
}

Return<void> FingerprintInscreen::onPress() {
    this->mGoodixFingerprintDaemon->sendCommand(200001, {},
                                                [](int, const hidl_vec<signed char>&) {});
    android::base::WriteStringToFile(LOCAL_HBM_ON, LOCAL_HBM_MODE);
    this->mGoodixFingerprintDaemon->sendCommand(200002, {},
                                                [](int, const hidl_vec<signed char>&) {});
    return Void();
}

Return<void> FingerprintInscreen::onRelease() {
    android::base::WriteStringToFile(LOCAL_HBM_OFF, LOCAL_HBM_MODE);
    android::base::WriteStringToFile(LOCAL_HBM_OFF, LOCAL_HBM_MODE1);
    this->mGoodixFingerprintDaemon->sendCommand(200003, {},
                                                [](int, const hidl_vec<signed char>&) {});
    return Void();
}

Return<void> FingerprintInscreen::onShowFODView() {
    android::base::WriteStringToFile(LOCAL_HBM_ON1, LOCAL_HBM_MODE1);
    return Void();
}

Return<void> FingerprintInscreen::onHideFODView() {
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
    return 410;
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
