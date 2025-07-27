 #ifndef MOPEKAADVERTISEMENT_H
#define MOPEKAADVERTISEMENT_H

#include <Arduino.h>

#define MOPEKA_MANUFACTURER_ID 0x0059

class MopekaAdvertisement {
public:
    int rssi;
    String name;
    String mac;

    float batteryVoltage = 0.0f;
    float batteryPercent = 0.0f;
    bool syncButtonPressed = false;
    int temperatureC = 0;
    float temperatureF = 0.0f;
    int tankLevelMM = 0;
    float tankLevelInches = 0.0f;
    uint8_t readingQualityStars = 0;
    float fillPercent = 0.0f;  // Neues Feld


    uint8_t raw_mfg_data[13] = {0};

    MopekaAdvertisement() {}

    // Parse Manufacturer Data from Arduino String
    bool parse(const String& data, size_t len) {
        if (len < 7 || data.length() < 7) {
            Serial.println("❌ Ungültige Länge der Manufacturer Data.");
            return false;
        }

        // Raw-Zugriff auf Bytes in Arduino String
        const uint8_t* bytes = (const uint8_t*)data.c_str();

        // Optional: Herstellerkennung prüfen (0x0059 → 59 00, little endian)
        if (bytes[0] != 0x59 || bytes[1] != 0x00) {
            Serial.println("❌ Kein Mopeka Sensor (Manufacturer ID ungleich 0x0059)");
            return false;
        }

        // Kopiere die Rohdaten
        size_t copyLen = (len >= 13) ? 13 : len;
        memcpy(raw_mfg_data, bytes, copyLen);

        // Debug-Ausgabe
        Serial.print("Manufacturer Data (Hex): ");
        for (size_t i = 0; i < copyLen; i++) {
            Serial.printf("%02X ", raw_mfg_data[i]);
        }
        Serial.println();

        // Mopeka-Dekodierung
        uint8_t rawBattery = bytes[3] & 0x7F;
        syncButtonPressed = (bytes[4] & 0x80) > 0;
        uint8_t rawTemp = bytes[4] & 0x7F;
        int rawTankLevel = ((int)bytes[6] << 8 | bytes[5]) & 0x3FFF;
        readingQualityStars = bytes[6] >> 6;

        batteryVoltage = rawBattery / 32.0f;
        batteryPercent = ((batteryVoltage - 2.2f) / 0.65f) * 100.0f;
        batteryPercent = constrain(batteryPercent, 0.0f, 100.0f);

        temperatureC = rawTemp - 40;
        temperatureF = (temperatureC * 9.0f / 5.0f) + 32.0f;

        // Formel aus Mopeka SDK (für Pro Sensor)
        float levelMM = rawTankLevel * (
            0.573045f + (-0.002822f * rawTemp) + (-0.00000535f * rawTemp * rawTemp));

        tankLevelMM = static_cast<int>(levelMM);
        tankLevelInches = tankLevelMM / 25.4f;
        fillPercent = ((float)tankLevelMM / 390.0f) * 100.0f;
        fillPercent = constrain(fillPercent, 0.0f, 100.0f);

        return true;
    }

    String toString() {
        String out = "MopekaAdvertisement - ";
        out += "Battery: " + String(batteryVoltage, 2) + "V (" + String(batteryPercent, 1) + "%) ";
        out += "Temp: " + String(temperatureC) + "C/" + String(temperatureF, 1) + "F ";
        out += "SyncButton: " + String(syncButtonPressed ? "YES" : "NO") + " ";
        out += "Level: " + String(tankLevelMM) + "mm (" + String(tankLevelInches, 2) + "\") ";
        out += " Fill: " + String(fillPercent, 1) + "% ";

        out += "Signal: " + String(readingQualityStars) + "★";
        return out;
    }

    void Dump() {
        Serial.println(toString());
        Serial.print("Raw Mfg Data: ");
        for (int i = 0; i < 13; ++i) {
            Serial.printf("0x%02X ", raw_mfg_data[i]);
        }
        Serial.println();
    }
};


#endif  
