#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>
#include "MopekaAdvertisement.h"

int scanTime = 10;
BLEScan* pBLEScan;

class MyAdvertisedDeviceCallbacks : public BLEAdvertisedDeviceCallbacks {
  void onResult(BLEAdvertisedDevice advertisedDevice) {
    if (!advertisedDevice.haveManufacturerData()) return;

    String mfgStr = advertisedDevice.getManufacturerData();
    const uint8_t* raw = (const uint8_t*)mfgStr.c_str();
    size_t len = mfgStr.length();



    MopekaAdvertisement mopeka;
    if (mopeka.parse(mfgStr, len)) {
      mopeka.rssi = advertisedDevice.getRSSI();
      mopeka.mac = advertisedDevice.getAddress().toString().c_str();
      if (advertisedDevice.haveName()) {
        mopeka.name = advertisedDevice.getName().c_str();
      }

      Serial.println("✅ Mopeka-Sensor erkannt!");
      Serial.println(mopeka.toString());
      Serial.println(mopeka.mac);
      //mopeka.Dump();
      Serial.println();
    }
  }
};

void setup() {
  Serial.begin(115200);
  Serial.println("Starte BLE-Scan...");

  BLEDevice::init("");
  pBLEScan = BLEDevice::getScan();
  pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
  pBLEScan->setActiveScan(true);
  pBLEScan->setInterval(100);
  pBLEScan->setWindow(99);
}

void loop() {
  BLEScanResults* foundDevices = pBLEScan->start(scanTime, false);
  Serial.printf("Scan abgeschlossen. %d Geräte gefunden.\n\n", foundDevices->getCount());
  pBLEScan->clearResults();
  delay(3000);
}

