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

    # build.prop for Region specific
    "build_DC.prop"
    "build_EU.prop"
    "build_EU_2.prop"
    "build_FR.prop"
    "build_JP.prop"
    "build_RU.prop"

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
