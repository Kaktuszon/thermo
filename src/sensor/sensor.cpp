#include <Wire.h>
#include <Arduino.h>
#include <Adafruit_SHT31.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#include "sensor.h"

void Sensor::setSensor() {
    currentSensor = None;
    Adafruit_SHT31 sht31;

    Wire.begin();
    if(sht31.begin(0x44)) {
        currentSensor = SHT31;
        Serial.println("Sensor of type SHT31 found!");
        return;
    }

    OneWire oneWire(2);
    DallasTemperature ds18b20(&oneWire);
    ds18b20.begin();
    if(ds18b20.getDeviceCount() > 0) {
        currentSensor = DS18B20;
        Serial.println("Sensor of type DS18B20 found!");
        return;
    }
}

Sensor::SensorType Sensor::getSensor() {
    return currentSensor;
}