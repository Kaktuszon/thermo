#include <Wire.h>
#include <Arduino.h>
#include <Adafruit_SHT31.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#include "sensor.h"

void Sensor::setSensor() {
    currentSensor = None;

    Wire.begin();
    sht31 = new Adafruit_SHT31();
    if(sht31->begin(0x44)) {
        currentSensor = SHT31;
        Serial.println("Sensor of type SHT31 found!");
        return;
    }

    oneWire = new OneWire(4);
    ds18b20 = new DallasTemperature(oneWire);
    ds18b20->begin();
    if(ds18b20->getDeviceCount() > 0) {
        currentSensor = DS18B20;
        Serial.println("Sensor of type DS18B20 found!");
        return;
    }

    Serial.println("No sensors found!");
}

Sensor::SensorType Sensor::getSensor() {
    return currentSensor;
}

Sensor::Sensor() {}

Sensor::~Sensor() {
    if(sht31 != nullptr) {
        delete sht31;
        sht31 = nullptr;
    }

    if(ds18b20 != nullptr) {
        delete ds18b20;
        ds18b20 = nullptr;
    }

    if(oneWire != nullptr) {
        delete oneWire;
        oneWire = nullptr;
    }
}