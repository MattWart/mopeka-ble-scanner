# 🛢️ Mopeka BLE Scanner für Arduino / BLE Scanner for Mopeka Sensor (Arduino)

Ein Arduino-Sketch zum Auslesen von **Mopeka Pro BLE-Gassensoren**. Unterstützt Batteriespannung, Temperatur, Füllstand, Signalqualität uvm.

An Arduino sketch to read data from **Mopeka Pro BLE gas sensors**. Supports battery voltage, temperature, fill level, signal quality and more.

---

## 📦 Funktionen / Features

- Scan nach BLE-Geräten mit Hersteller-ID `0x0059` (Mopeka)  
  Scan for BLE devices with Manufacturer ID `0x0059` (Mopeka)
- Auslesen und Dekodieren der Rohdaten  
  Read and decode raw manufacturer data
- Anzeige von / Displays:
  - Batteriespannung / Battery voltage
  - Temperatur (°C / °F)
  - Tankfüllstand (mm / inch, %)
  - Signalqualität / Signal quality (stars)
  - MAC-Adresse & Gerätename / MAC address & name (if available)

---

## 🚀 Beispielausgabe / Example Output

```
✅ Mopeka-Sensor erkannt!
MopekaAdvertisement - Battery: 2.91V (100.0%) Temp: 22C/71.6F SyncButton: NO Level: 177mm (6.97")  Fill: 45.4% Signal: 3★
C4:DD:57:AB:12:34
```

---

## 📋 Voraussetzungen / Requirements

- Arduino-kompatibles Board mit BLE (z. B. ESP32)  
  Arduino-compatible board with BLE (e.g. ESP32)
- Benötigte Bibliotheken / Required libraries:
  - [`BLEDevice`](https://github.com/nkolban/ESP32_BLE_Arduino)
  - Keine externe Mopeka-Bibliothek notwendig  
    No external Mopeka library required

---

## 🔧 Installation

1. Repo klonen oder ZIP herunterladen  
   Clone the repo or download as ZIP  
2. Öffne `main.ino` in der Arduino IDE  
   Open `main.ino` in Arduino IDE  
3. Kompilieren und auf dein ESP32-Board laden  
   Compile and upload to your ESP32 board  
4. Seriellen Monitor öffnen (`115200 Baud`)  
   Open Serial Monitor (`115200 baud`)

---

## 📁 Dateien / Files

- `main.ino`: BLE Scanner
- `MopekaAdvertisement.h`: Klasse zum Parsen / parsing class for Mopeka data

---

## 📜 Lizenz / License

Dieses Projekt steht unter der MIT-Lizenz.  
This project is licensed under the MIT License.  
Siehe [LICENSE](LICENSE) / See [LICENSE](LICENSE)

---

## 🤝 Mitwirken / Contributing

Pull Requests willkommen!  
Pull requests are welcome – contributions, fixes or improvements appreciated.
