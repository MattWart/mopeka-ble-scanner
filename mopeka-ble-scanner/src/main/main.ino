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

/*
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>

int scanTime = 15;  // In Sekunden
BLEScan* pBLEScan;

class MyAdvertisedDeviceCallbacks : public BLEAdvertisedDeviceCallbacks {
  void onResult(BLEAdvertisedDevice advertisedDevice) {
    Serial.println("=== Neues Gerät gefunden ===");
    Serial.printf("Adresse: %s\n", advertisedDevice.getAddress().toString().c_str());

    // Name ausgeben, wenn vorhanden
    if (advertisedDevice.haveName()) {
      Serial.printf("Name: %s\n", advertisedDevice.getName().c_str());
    } else {
      Serial.println("Name: <kein Name>");
    }

    // Signalstärke (optional)
    Serial.printf("RSSI: %d dBm\n", advertisedDevice.getRSSI());

    // Manufacturer Data prüfen
    if (advertisedDevice.haveManufacturerData()) {
      String mfgData = advertisedDevice.getManufacturerData();

      // Hexdump ausgeben
      Serial.print("Manufacturer Data (Hex): ");
      for (size_t i = 0; i < mfgData.length(); i++) {
        Serial.printf("%02X ", (uint8_t)mfgData[i]);
      }
      Serial.println();

      // Mopeka Filter: Nordic Semiconductor ID = 0x0059 → in little-endian: 59 00
      if ((uint8_t)mfgData[0] == 0x59 && (uint8_t)mfgData[1] == 0x00) {
        Serial.println("✅ Mopeka Sensor erkannt (via Manufacturer ID 0x0059)");
      }
    } else {
      Serial.println("Keine Manufacturer Data.");
    }

    Serial.println();  // Trennung
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
  Serial.printf("Scan beendet. Geräte gefunden: %d\n", foundDevices->getCount());
  pBLEScan->clearResults();  // Speicher freigeben
  delay(3000);
}
*/
