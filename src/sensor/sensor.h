#ifndef SENSOR_H
#define SENSOR_H

class Sensor {
    public:
        enum SensorType {
            None,
            SHT31,
            DS18B20
        };

        void setSensor();
        SensorType getSensor();
    
    private:
        SensorType currentSensor;
};

#endif