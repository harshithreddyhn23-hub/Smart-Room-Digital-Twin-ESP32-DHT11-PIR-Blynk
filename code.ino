#define BLYNK_TEMPLATE_ID "YOUR_TEMPLATE_ID"
#define BLYNK_TEMPLATE_NAME "Smart Room Twin"
#define BLYNK_AUTH_TOKEN "YOUR_AUTH_TOKEN"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>

#define DHTPIN 4
#define DHTTYPE DHT11
#define PIRPIN 27

DHT dht(DHTPIN, DHTTYPE);

char ssid[] = "YOUR_WIFI_NAME";
char pass[] = "YOUR_WIFI_PASSWORD";

BlynkTimer timer;

void sendSensorData() {
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();
  int motion = digitalRead(PIRPIN);

  if (isnan(temp) || isnan(hum)) {
    Serial.println("DHT read failed, skipping this cycle");
    return;
  }

  Blynk.virtualWrite(V0, temp);
  Blynk.virtualWrite(V1, hum);
  Blynk.virtualWrite(V2, motion);

  Serial.printf("Temp: %.1f C  Humidity: %.1f %%  Motion: %d\n", temp, hum, motion);
}

void setup() {
  Serial.begin(115200);
  dht.begin();
  pinMode(PIRPIN, INPUT_PULLDOWN);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  timer.setInterval(3000L, sendSensorData);
}

void loop() {
  Blynk.run();
  timer.run();
}