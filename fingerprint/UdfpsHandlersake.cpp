/*
 * Copyright (C) 2023 The LineageOS Project
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#define LOG_TAG "UdfpsHander"

#include "UdfpsHandler.h"

#include <android-base/logging.h>
#include <fcntl.h>
#include <poll.h>
#include <thread>
#include <unistd.h>
#include <vendor/goodix/hardware/biometrics/fingerprint/2.1/IGoodixFingerprintDaemon.h>

using ::android::sp;
using ::android::hardware::hidl_vec;
using ::vendor::goodix::hardware::biometrics::fingerprint::V2_1::IGoodixFingerprintDaemon;

static bool readBool(int fd) {
    char c;
    int rc;

    rc = lseek(fd, 0, SEEK_SET);
    if (rc) {
        LOG(ERROR) << "failed to seek fd, err: " << rc;
        return false;
    }

    rc = read(fd, &c, sizeof(char));
    if (rc != 1) {
        LOG(ERROR) << "failed to read bool from fd, err: " << rc;
        return false;
    }

    return c != '0';
}

class UdfpsHandlerSake : public UdfpsHandler {
  public:
    void init(fingerprint_device_t *device) {
        mDevice = device;

        mGoodixFingerprintDaemon = IGoodixFingerprintDaemon::getService();

        std::thread([this]() {
            int fd = open(FOD_UI_PATH, O_RDONLY);
            if (fd < 0) {
                LOG(ERROR) << "failed to open fd, err: " << fd;
                return;
            }

            struct pollfd fodUiPoll = {
                    .fd = fd,
                    .events = POLLERR | POLLPRI,
                    .revents = 0,
            };

            while (true) {
                int rc = poll(&fodUiPoll, 1, -1);
                if (rc < 0) {
                    LOG(ERROR) << "failed to poll fd, err: " << rc;
                    continue;
                }

                mGoodixFingerprintDaemon->sendCommand(readBool(fd) ? CMD_LIGHT_AREA_STABLE
                    : CMD_LIGHT_AREA_CLOSE, {}, [](int, const hidl_vec<signed char>&) {});
            }
        }).detach();
    }

    void onFingerDown(uint32_t /*x*/, uint32_t /*y*/, float /*minor*/, float /*major*/) {
        mGoodixFingerprintDaemon->sendCommand(CMD_FINGER_DOWN, {},
                                                [](int, const hidl_vec<signed char>&) {});
    }

    void onFingerUp() {
        mGoodixFingerprintDaemon->sendCommand(CMD_FINGER_UP, {},
                                                [](int, const hidl_vec<signed char>&) {});
    }

    void onAcquired(int32_t /*result*/, int32_t /*vendorCode*/) {
        // nothing
    }

    void cancel() {
        // nothing
    }

    void preEnroll() {
        // nothing
    }

    void enroll() {
        // nothing
    }

    void postEnroll() {
        // nothing
    }

  private:
    fingerprint_device_t *mDevice;
    sp<IGoodixFingerprintDaemon> mGoodixFingerprintDaemon;
};

static UdfpsHandler* create() {
    return new UdfpsHandlerSake();
}

static void destroy(UdfpsHandler* handler) {
    delete handler;
}

extern "C" UdfpsHandlerFactory UDFPS_HANDLER_FACTORY = {
        .create = create,
        .destroy = destroy,
};
