package vendor.goodix.hardware.biometrics.fingerprint;

@VintfStability
interface IGoodixFingerprintDaemonCallback {
    float onDaemonMessage(int devId, int msgId, int cmdId, int[] msgData);
};

