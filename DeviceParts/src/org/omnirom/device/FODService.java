/*
 * Copyright (c) 2021 The OmniRom Project
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

package org.omnirom.device;

import android.app.Service;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.hardware.fingerprint.IFingerprintService;
import android.os.IBinder;
import android.os.Messenger;
import android.os.ServiceManager;
import android.os.SystemProperties;
import android.util.Log;

public class FODService extends Service {
    private Context mContext;
    private IFingerprintService mFingerprintService;
    private static final String TAG = "FODService";
    private static final boolean DEBUG = true;
    private BroadcastReceiver mIntentReceiver = new BroadcastReceiver() {
        @Override
        public void onReceive(Context context, Intent intent) {
            final String action = intent.getAction();
            if (Intent.ACTION_SCREEN_ON.equals(action)) {
                updateFingerprint();
            }
        }
    };

    @Override
    public void onCreate() {
        if (DEBUG) Log.d(TAG, "Creating service");
        mFingerprintService = IFingerprintService.Stub.asInterface(
                                ServiceManager.getService(Context.FINGERPRINT_SERVICE));
        registerReceiver();
    }

    @Override
    public int onStartCommand(Intent intent, int flags, int startId) {
        if (DEBUG) Log.d(TAG, "Starting service");
        return START_STICKY;
    }

    @Override
    public void onDestroy() {
        if (DEBUG) Log.d(TAG, "Destroying service");
        this.unregisterReceiver(mIntentReceiver);
        super.onDestroy();
    }

    @Override
    public IBinder onBind(Intent intent) {
        return null;
    }

    private void registerReceiver() {
        IntentFilter filter = new IntentFilter();
        filter.addAction(Intent.ACTION_SCREEN_ON);
        this.registerReceiver(mIntentReceiver, filter);
    }

    private void updateFingerprint() {
        boolean isFPClientActive = false;
        String value = SystemProperties.get("persist.vendor.asus.fp.wakeup");
        try {
            isFPClientActive = mFingerprintService.isClientActive();
        } catch (Exception e) {
            // do nothing.
        }
        if (isFPClientActive) {
            SystemProperties.set("persist.vendor.asus.fp.wakeup", "true");
        } else {
            SystemProperties.set("persist.vendor.asus.fp.wakeup", "false");
        }
        if (DEBUG) Log.i(TAG, "Finerprint wakepup = " + value);
    }
}
