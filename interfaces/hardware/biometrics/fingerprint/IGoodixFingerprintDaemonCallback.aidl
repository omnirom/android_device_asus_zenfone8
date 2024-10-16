package vendor.goodix.hardware.biometrics.fingerprint;

@VintfStability
interface IGoodixFingerprintDaemonCallback {
    oneway onDaemonMessage(int devId, int msgId, int cmdId, int[] msgData);
};

