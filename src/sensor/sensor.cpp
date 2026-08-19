#include <Wire.h>
#include <Arduino.h>
#include <Adafruit_SHT31.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#include "sensor.h"

void Sensor::setSensor() {
    _currentSensor = None;

    Wire.begin();
    _sht31 = new Adafruit_SHT31();
    if(_sht31->begin(0x44)) {
        _currentSensor = SHT31;
        Serial.println("Sensor of type SHT31 found!");
        return;
    }

    _oneWire = new OneWire(4);
    _ds18b20 = new DallasTemperature(_oneWire);
    _ds18b20->begin();
    if(_ds18b20->getDeviceCount() > 0) {
        _currentSensor = DS18B20;
        Serial.println("Sensor of type DS18B20 found!");
        return;
    }

    Serial.println("No sensors found!");
}

Sensor::SensorType Sensor::getSensor() {
    return _currentSensor;
}

Adafruit_SHT31 *Sensor::getSHT31() {
    return _sht31;
}
OneWire *Sensor::getOneWire() {
    return _oneWire;
}
DallasTemperature *Sensor::getDS18B20() {
    return _ds18b20;
}


Sensor::Sensor() {}

Sensor::~Sensor() {
    if(_sht31 != nullptr) {
        delete _sht31;
        _sht31 = nullptr;
    }

    if(_ds18b20 != nullptr) {
        delete _ds18b20;
        _ds18b20 = nullptr;
    }

    if(_oneWire != nullptr) {
        delete _oneWire;
        _oneWire = nullptr;
    }
}