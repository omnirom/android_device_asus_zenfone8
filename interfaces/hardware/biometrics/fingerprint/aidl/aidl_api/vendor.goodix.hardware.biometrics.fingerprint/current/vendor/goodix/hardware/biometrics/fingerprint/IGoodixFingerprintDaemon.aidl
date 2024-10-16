package vendor.goodix.hardware.biometrics.fingerprint;

@VintfStability
interface IGoodixFingerprintDaemon {
    void setNotify(vendor.goodix.hardware.biometrics.fingerprint.IGoodixFingerprintDaemonCallback Callback);
   void sendCommand(int cmd, int data);
}
