#ifndef TEMPERATURE_H
#define TEMPERATURE_H

#include "sensor/sensor.h"

class Temperature {    
    public:
        struct tempHum {
            float temperature;
            float humidity;
        };

        tempHum getTemperatureAndHumidity();
        void setTemperatureAndHumidity(Sensor::SensorType _sensor);
        
        bool valid();

    private:
        tempHum data;
};

#endif