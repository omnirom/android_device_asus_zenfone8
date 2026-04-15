#!/usr/bin/env -S PYTHONPATH=../../../tools/extract-utils python3
#
# SPDX-FileCopyrightText: 2024 The LineageOS Project
# SPDX-License-Identifier: Apache-2.0
#

from extract_utils.fixups_blob import (
    blob_fixup,
    blob_fixups_user_type,
)
from extract_utils.fixups_lib import (
    lib_fixup_remove,
    lib_fixups,
    lib_fixups_user_type,
)
from extract_utils.main import (
    ExtractUtils,
    ExtractUtilsModule,
)

namespace_imports = [
    'hardware/qcom-caf/sm8350',
    'hardware/qcom-caf/wlan',
    'vendor/qcom/opensource/commonsys-intf/display',
    'vendor/qcom/opensource/commonsys/display',
    'vendor/qcom/opensource/display',
]

def lib_fixup_vendor_suffix(lib: str, partition: str, *args, **kwargs):
    return f'{lib}_{partition}' if partition == 'vendor' else None

lib_fixups: lib_fixups_user_type = {
    **lib_fixups,
    (
        'com.qualcomm.qti.dpm.api@1.0',
        'vendor.qti.diaghal@1.0',
        'vendor.qti.imsrtpservice@3.0',
        'libxditk_DIT_Manager',
        'libxditk_ISP',
        'libxditk_arch',
        'libxditk_ditArchLIB',
        'libxditk_ditBSP',
        'libxditk_ditBSP_JNI',
    ): lib_fixup_vendor_suffix,
    (
    ): lib_fixup_remove,
}

blob_fixups: blob_fixups_user_type = {
    ('system/lib64/libxditk_ISP.so',
     'system/lib64/libxditk_LightArt.so',
     'system/lib64/libxditk_ditArchLIB.so'): blob_fixup()
        .replace_needed('libOpenCL.so', 'libOpenCL_system.so'),
    'system_ext/priv-app/com.qualcomm.location/com.qualcomm.location.apk': blob_fixup()
        .apktool_patch('blob-patches/com.qualcomm.location.patch', '-r'),
    'vendor/bin/hw/android.hardware.nfc@1.2-service.asus': blob_fixup()
        .replace_needed('ese_spi_nxp.so', 'ese_spi_nxp_prebuilt.so')
        .replace_needed('nfc_nci_nxp.so', 'nfc_nci_nxp_prebuilt.so'),
    'vendor/bin/hw/android.hardware.secure_element@1.2-service': blob_fixup()
        .replace_needed('ese_spi_nxp.so', 'ese_spi_nxp_prebuilt.so'),
    ('vendor/lib/nfc_nci_nxp_prebuilt.so',
     'vendor/lib64/nfc_nci_nxp_prebuilt.so'): blob_fixup()
        .replace_needed('ese_spi_nxp.so', 'ese_spi_nxp_prebuilt.so')
        .add_needed('libbase_shim.so'),
    ('vendor/lib/mediadrm/libwvdrmengine.so',
     'vendor/lib64/mediadrm/libwvdrmengine.so',
    'vendor/lib64/libwvhidl.so'): blob_fixup()
        .add_needed('libcrypto_shim.so'),
    ('vendor/lib/ese_spi_nxp_prebuilt.so',
     'vendor/lib64/ese_spi_nxp_prebuilt.so'): blob_fixup()
        .add_needed('libbase_shim.so'),
    ('vendor/bin/poweropt-service',
     'vendor/lib64/libdpps.so',
     'vendor/lib64/libsnapdragoncolor-manager.so'): blob_fixup()
        .replace_needed('libtinyxml2.so', 'libtinyxml2-v34.so'),
}  # fmt: skip

module = ExtractUtilsModule(
    'zenfone8',
    'asus',
    blob_fixups=blob_fixups,
    lib_fixups=lib_fixups,
    namespace_imports=namespace_imports,
)

module.add_proprietary_file('proprietary-files-vendor.txt')

if __name__ == '__main__':
    utils = ExtractUtils.device(module)
    utils.run()
