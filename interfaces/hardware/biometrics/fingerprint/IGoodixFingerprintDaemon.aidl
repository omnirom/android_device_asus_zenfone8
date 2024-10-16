package vendor.goodix.hardware.biometrics.fingerprint;

import vendor.goodix.hardware.biometrics.fingerprint.IGoodixFingerprintDaemonCallback;

@VintfStability
interface IGoodixFingerprintDaemon {
    setNotify(IGoodixFingerprintDaemonCallback Callback);
    sendCommand(int cmd, int[] data);
};
