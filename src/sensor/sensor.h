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
    
    private:
        SensorType currentSensor;
        Adafruit_SHT31 *sht31 = nullptr;
        OneWire *oneWire = nullptr;
        DallasTemperature *ds18b20 = nullptr;
};

#endif