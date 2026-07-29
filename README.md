Smart Room Digital Twin — ESP32 + DHT11 + PIR + Blynk

A real-hardware digital twin of a room: an ESP32 reads live temperature, humidity, and motion data and syncs it to a Blynk mobile dashboard in real time.

Overview

This project implements the core digital twin loop — sense → transmit → visualize/sync — using:

ESP32 as the sensing/networking node
DHT11 for temperature and humidity
PIR (HC-SR501) for motion/occupancy detection
Blynk as the cloud sync layer and mobile dashboard (acting as the "virtual" twin interface)
Hardware
Component	Pin on ESP32
DHT11 VCC	3.3V
DHT11 GND	GND
DHT11 DATA	GPIO4
PIR VCC	5V
PIR GND	GND
PIR OUT	GPIO27
Software setup
Arduino IDE with ESP32 board support installed
Libraries (Sketch → Include Library → Manage Libraries):
DHT sensor library (Adafruit)
Blynk (Blynk IoT)
Create a free account at blynk.cloud, create a new template and device, and note down:
BLYNK_TEMPLATE_ID
BLYNK_TEMPLATE_NAME
BLYNK_AUTH_TOKEN
In the Blynk web dashboard, add widgets bound to virtual pins:
V0 → Gauge/Value display for temperature
V1 → Gauge/Value display for humidity
V2 → LED widget for motion status
Firmware

The full sketch is in SmartRoomTwin.ino. Before uploading, fill in:

BLYNK_TEMPLATE_ID, BLYNK_TEMPLATE_NAME, BLYNK_AUTH_TOKEN (from your Blynk template)
ssid and pass (your WiFi credentials — must be 2.4GHz, ESP32 doesn't support 5GHz)
How it works
ESP32 boots and connects to WiFi, then authenticates with the Blynk cloud using the auth token.
Every 3 seconds, sendSensorData() reads the DHT11 and PIR, and pushes the values to Blynk's virtual pins (V0, V1, V2).
The Blynk mobile app dashboard, bound to those same virtual pins, updates live — giving a real-time "digital twin" view of the room's temperature, humidity, and occupancy from anywhere with internet access.
Known limitations / notes
DHT11 has lower precision than DHT22 (±2°C, ±5% RH vs DHT22's ±0.5°C, ±2% RH) — fine for a demo, worth noting in a portfolio writeup.
PIR needs 30–60 seconds after power-up to calibrate; ignore readings during that window.
Blynk free tier has limits on data rate/history — for production-grade time-series storage, an InfluxDB + Grafana pipeline (or Blynk's own datastream logging) would be the next step.
Possible extensions
Add a light sensor (LDR/BH1750) on another analog/I2C pin and a third Blynk widget.
Add threshold-based Blynk notifications (e.g. push alert if temp > 32°C).
Add a relay-controlled fan/light so the twin can act back on the room (bidirectional sync).
Log historical data externally (InfluxDB) for trend analysis, not just live values.
