#
# Copyright (C) 2019 The LineageOS Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

set -e

# Load extract_utils and do some sanity checks
MY_DIR="${BASH_SOURCE%/*}"
if [[ ! -d "$MY_DIR" ]]; then MY_DIR="$PWD"; fi

CM_ROOT="$MY_DIR"/../../..

HELPER="$CM_ROOT"/vendor/omni/build/tools/extract_utils.sh

if [ ! -f "$HELPER" ]; then
    echo "Unable to find helper script at $HELPER"
    exit 1
fi
. "$HELPER"

if [ -z "$1" ]; then
    echo "No input image supplied"
    exit 1
fi

if [ -z "$2" ]; then
    echo "No output filename supplied"
    exit 1
fi

VENDOR_SKIP_FILES_COMMON=(
    # Biometrics
    "etc/init/android.hardware.biometrics.fingerprint@2.1-service.rc"
    "etc/init/android.hardware.biometrics.face@1.0-service.faceauth.rc"
    "bin/hw/android.hardware.biometrics.face@1.0-service.faceauth"
    "bin/hw/android.hardware.biometrics.fingerprint@2.1-service"

    # Bootctrl
    "lib/hw/bootctrl.lahaina.so"
    "lib/hw/android.hardware.boot@1.0-impl-1.1-qti.so"
    "lib/hw/android.hardware.boot@1.1-impl.so"
    "lib/libboot_control_qti.so"
    "lib64/hw/bootctrl.lahaina.so"
    "lib64/hw/android.hardware.boot@1.0-impl-1.1-qti.so"
    "lib64/hw/android.hardware.boot@1.1-impl.so"
    "lib64/libboot_control_qti.so"
    "bin/hw/android.hardware.boot@1.1-service"
    "etc/init/android.hardware.boot@1.1-service.rc"
    # keep boot@1.1.xml
    # "etc/vintf/manifest/android.hardware.boot@1.1.xml"

    # build.prop for Region specific
    "build_DC.prop"
    "build_EU.prop"
    "build_EU_2.prop"
    "build_FR.prop"
    "build_JP.prop"
    "build_RU.prop"

    # Logs
    "bin/init.asus.checkdatalog.sh"
    "bin/init.asus.checklogsize.sh"
    "bin/init.asus.kernelmessage.sh"
    "bin/init.asus.piq.sh"

    # Manifest
    "etc/vintf/manifest_lahaina.xml"
    "etc/vintf/manifest/manifest.xml"

    # Sepolicy
    "etc/selinux/vendor_file_contexts"
    "etc/selinux/vendor_service_contexts"
    "etc/selinux/plat_sepolicy_vers.txt"
    "etc/selinux/vndservice_contexts"
    "etc/selinux/plat_pub_versioned.cil"
    "etc/selinux/vendor_hwservice_contexts"
    "etc/selinux/vendor_mac_permissions.xml"
    "etc/selinux/vendor_property_contexts"
    "etc/selinux/vendor_seapp_contexts"
    "etc/selinux/vendor_sepolicy.cil"
    "etc/selinux/selinux_denial_metadata"

    # Vibrator
    "bin/hw/vendor.asus.vibrator.vibratorgovern@1.0-service"
    "etc/init/vendor.asus.vibrator.vibratorgovern@1.0-service.rc"
    "lib/vendor.asus.vibrator.vibratorgovern@1.0.so"
    "lib64/vendor.asus.vibrator.vibratorgovern@1.0.so"
    "lib/hw/vendor.asus.vibrator.vibratorgovern@1.0-impl.so"
    "lib64/hw/vendor.asus.vibrator.vibratorgovern@1.0-impl.so"

)
ALL_SKIP_FILES=("${VENDOR_SKIP_FILES_COMMON[@]}" "${VENDOR_SKIP_FILES_DEVICE[@]}")

generate_prop_list_from_image "$1" "$2" ALL_SKIP_FILES

# Fixups
_output_file=$2
function presign() {
    sed -i "s|vendor/$1$|vendor/$1;PRESIGNED|g" $_output_file
}
function as_module() {
    sed -i "s|vendor/$1$|-vendor/$1|g" $_output_file
}

as_module "etc/vintf/manifest/android.hardware.atrace@1.0-service.xml"
as_module "etc/vintf/manifest/android.hardware.boot@1.1.xml"
as_module "etc/vintf/manifest/android.hardware.cas@1.2-service.xml"
as_module "etc/vintf/manifest/android.hardware.gnss@2.1-service-qti.xml"
as_module "etc/vintf/manifest/android.hardware.graphics.mapper-impl-qti-display.xml"
as_module "etc/vintf/manifest/android.hardware.health@2.1.xml"
as_module "etc/vintf/manifest/android.hardware.lights-qti.xml"
as_module "etc/vintf/manifest/android.hardware.neuralnetworks@1.3-service-qti.xml"
as_module "etc/vintf/manifest/android.hardware.sensors@2.0-multihal.xml"
as_module "etc/vintf/manifest/android.hardware.thermal@2.0-service.qti.xml"
as_module "etc/vintf/manifest/android.hardware.usb@1.2-service.xml"
as_module "etc/vintf/manifest/android.hardware.wifi.hostapd.xml"
as_module "etc/vintf/manifest/android.hardware.wifi@1.0-service.xml"
as_module "etc/vintf/manifest/c2_manifest_vendor.xml"
as_module "etc/vintf/manifest/manifest_android.hardware.drm@1.3-service.clearkey.xml"
as_module "etc/vintf/manifest/manifest_android.hardware.drm@1.3-service.widevine.xml"
as_module "etc/vintf/manifest/power.xml"
as_module "etc/vintf/manifest/vendor.pixelworks.hardware.display.iris-service.xml"
as_module "etc/vintf/manifest/vendor.pixelworks.hardware.feature.irisfeature-service.xml"
as_module "etc/vintf/manifest/vendor.qti.diag.hal.service.xml"
as_module "etc/vintf/manifest/vendor.qti.gnss@4.0-service.xml"
as_module "etc/vintf/manifest/vendor.qti.hardware.display.allocator-service.xml"
as_module "etc/vintf/manifest/vendor.qti.hardware.display.composer-service.xml"
as_module "etc/vintf/manifest/vendor.qti.hardware.servicetracker@1.2-service.xml"
as_module "etc/vintf/manifest/vendor.qti.hardware.vibrator.service.xml"

