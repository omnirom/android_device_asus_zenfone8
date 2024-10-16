package vendor.goodix.hardware.biometrics.fingerprint;

import vendor.goodix.hardware.biometrics.fingerprint.IGoodixFingerprintDaemonCallback;

@VintfStability
interface IGoodixFingerprintDaemon {
    void setNotify(IGoodixFingerprintDaemonCallback Callback);
    byte[] sendCommand(int cmd, in byte[] data);
}
