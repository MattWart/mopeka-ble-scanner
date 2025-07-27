# 🛢️ Mopeka BLE Scanner für Arduino

Ein einfacher Arduino-Sketch zum Auslesen von **Mopeka Pro BLE-Gassensoren** über Bluetooth Low Energy (BLE). Unterstützt RSSI, Batteriezustand, Temperatur, Füllstand, Signalqualität und mehr.

## 📦 Funktionen

- BLE-Scan nach Geräten mit Hersteller-ID `0x0059` (Mopeka)
- Auslesen und Parsen der Rohdaten
- Anzeige von:
  - Batteriespannung und -prozent
  - Temperatur in °C und °F
  - Tankfüllstand in mm und %
  - Signalqualität (Sterne)
  - MAC-Adresse & Gerätename (sofern vorhanden)

## 🚀 Beispielausgabe

```
✅ Mopeka-Sensor erkannt!
MopekaAdvertisement - Battery: 2.91V (100.0%) Temp: 22C/71.6F SyncButton: NO Level: 177mm (6.97")  Fill: 45.4% Signal: 3★
C4:DD:57:AB:12:34
```

## 📋 Voraussetzungen

- Arduino-kompatibles Board mit BLE (z. B. ESP32)
- Bibliotheken:
  - [`BLEDevice`](https://github.com/nkolban/ESP32_BLE_Arduino)
  - Keine zusätzliche Mopeka-Bibliothek notwendig

## 🔧 Installation

1. Repository klonen oder als ZIP herunterladen
2. Öffne `main.ino` in der Arduino IDE
3. Kompiliere & lade den Sketch auf dein ESP32-Board
4. Öffne den seriellen Monitor (`115200 Baud`)

## 📁 Dateistruktur

- `main.ino`: Enthält den BLE-Scanner
- `MopekaAdvertisement.h`: Klasse zum Parsen der Manufacturer Data

## 📜 Lizenz

Dieses Projekt steht unter der **MIT-Lizenz** – siehe [LICENSE](LICENSE) für Details.

## 🤝 Mitwirken

Pull Requests willkommen! Verbesserungsvorschläge, Issues oder neue Sensortypen gerne einbringen.
