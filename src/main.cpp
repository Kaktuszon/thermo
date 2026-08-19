#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiManager.h>
#include <ESP8266HTTPClient.h>
#include <Wire.h>
#include <Adafruit_SHT31.h>

#include "lights/lights.h"
#include "temperature/temperature.h"
#include "sensor/sensor.h"

WiFiClient client;
Adafruit_SHT31 sht31;
String domain;

Lights led(2);
Temperature temperature;
uint32_t identifier;
Sensor sensor;

void setup() {
    Serial.begin(115200);
    WiFiManager wm;
    domain = "192.168.1.114"; // Hard coded IPs are the best
    identifier = ESP.getChipId();
    String apName = "ESP8266-" + String(identifier);

    bool res = wm.autoConnect(apName.c_str(), "12345678");
    if(!res) {
        Serial.println("Failed to auto connect WiFi!");
        wm.startConfigPortal(apName.c_str(), "12345678");
    }

    sensor.setSensor();
    Serial.printf("Sensor: %d\n", sensor.getSensor());
}

void loop() {
    led.on(client, domain);
    delay(1000);
    led.off(client, domain);
    delay(1000);

    temperature.setTemperatureAndHumidity(sensor);

    if (temperature.valid()) {
        HTTPClient http;
        Serial.printf("Temp: %.2f C, Hum: %.2f %%\n", temperature.getTemperatureAndHumidity().temperature, temperature.getTemperatureAndHumidity().humidity);
        Serial.printf("Identifier: %u\n", identifier);

        String url = "http://" + domain + ":3001/api/temperature";
        http.begin(client, url);
        http.addHeader("Content-Type", "application/json");

        String payload = String("{") +
        "\"temperature\":" + String(temperature.getTemperatureAndHumidity().temperature) + "," +
        "\"humidity\":" + String(temperature.getTemperatureAndHumidity().humidity) + "," +
        "\"identifier\":" + "\"" + String(identifier) + "\"" +
        String("}");
        int code = http.POST(payload);

        Serial.printf("POST /api/temperature -> %d\n", code);

        http.end();
    } else {
        Serial.println("Failed to read from SHT31");
    }
}
