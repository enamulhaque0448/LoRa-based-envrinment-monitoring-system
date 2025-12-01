#include <SPI.h>
#include <LoRa.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>
#include "DHT.h"

#define SS_PIN    5
#define RST_PIN   14
#define DIO0_PIN  2
#define DHTPIN    4
#define DHTTYPE   DHT11

DHT dht(DHTPIN, DHTTYPE);
Adafruit_BMP280 bmp;

void setup() {
  Serial.begin(115200);
  while (!Serial);

  dht.begin();
  if (!bmp.begin(0x76)) {
    Serial.println("Could not find a valid BMP280 sensor, check wiring!");
    while (1);
  }

  Serial.println("Starting LoRa Sender...");
  LoRa.setPins(SS_PIN, RST_PIN, DIO0_PIN);

  if (!LoRa.begin(433E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  Serial.println("LoRa Initializing OK!");
}

void loop() {
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();
  float press = bmp.readPressure() / 100.0F;

  if (isnan(temp) || isnan(hum)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  String dataPacket = String(temp) + "," + String(hum) + "," + String(press);
  
  Serial.print("Sending packet: ");
  Serial.println(dataPacket);

  LoRa.beginPacket();
  LoRa.print(dataPacket);
  LoRa.endPacket();

  delay(5000);
}
