#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiManager.h>
#include <ESP8266HTTPClient.h>
#include <Wire.h>
#include <Adafruit_SHT31.h>

#include "lights.h"
#include "temperature.h"

WiFiClient client;
Adafruit_SHT31 sht31;
String domain;

Lights led(2);
Temperature temperature;
uint32_t identifier;

void setup() {
    Serial.begin(115200);
    WiFiManager wm;
    domain = "192.168.1.114"; // Hard coded IPs are the best

    bool res = wm.autoConnect("ESP8266", "12345678");
    if(!res) {
        Serial.println("Failed to auto connect WiFi!");
        wm.startConfigPortal("ESP8266", "12345678");
    }

    sht31 = Adafruit_SHT31();
    Wire.begin();
    sht31.begin(0x44);

    identifier = ESP.getChipId();
}

void loop() {
    led.on(client, domain);
    delay(1000);
    led.off(client, domain);
    delay(1000);

    temperature.setTemperatureAndHumidity(sht31.readTemperature(), sht31.readHumidity());

    if (temperature.valid()) {
        HTTPClient http;
        Serial.printf("Temp: %.2f C, Hum: %.2f %%\n", temperature.getTemperatureAndHumidity().temperature, temperature.getTemperatureAndHumidity().humidity);
        Serial.printf("Identifier: %u\n", identifier);

        http.begin(client, "http://192.168.1.114:3001/api/temperature");
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
