#ifndef SENSOR_H
#define SENSOR_H

#include "Adafruit_SHT31.h"
#include "DallasTemperature.h"

class Sensor {
    public:
        enum SensorType {
            None,
            SHT31,
            DS18B20
        };

        Sensor();
        ~Sensor();

        void setSensor();
        SensorType getSensor();

        Adafruit_SHT31 *getSHT31();
        OneWire *getOneWire();
        DallasTemperature *getDS18B20();
    
    private:
        SensorType _currentSensor;
        Adafruit_SHT31 *_sht31 = nullptr;
        OneWire *_oneWire = nullptr;
        DallasTemperature *_ds18b20 = nullptr;
};

#endif