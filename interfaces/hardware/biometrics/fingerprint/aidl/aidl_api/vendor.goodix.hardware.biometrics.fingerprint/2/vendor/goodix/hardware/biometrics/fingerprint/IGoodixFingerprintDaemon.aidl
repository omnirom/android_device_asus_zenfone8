package vendor.goodix.hardware.biometrics.fingerprint;

import vendor.goodix.hardware.biometrics.fingerprint.IGoodixFingerprintDaemonCallback;

@VintfStability
interface IGoodixFingerprintDaemon {
    void setNotify(IGoodixFingerprintDaemonCallback Callback);
    void sendCommand(int cmd, in byte[] data);
}

