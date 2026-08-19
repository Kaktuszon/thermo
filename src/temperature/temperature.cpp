#include <math.h>

#include "temperature.h"
#include "Adafruit_SHT31.h"
#include "DallasTemperature.h"
#include "OneWire.h"
#include "sensor/sensor.h"


Temperature::tempHum Temperature::getTemperatureAndHumidity() {
    return data;
}

void Temperature::setTemperatureAndHumidity(Sensor &_sensor) {
    Sensor::SensorType sensorType = _sensor.getSensor();
    if(sensorType == Sensor::SHT31) {
        Wire.begin();
        Adafruit_SHT31 *sht31 = _sensor.getSHT31();
        data.temperature = sht31->readTemperature();
        data.humidity = sht31->readHumidity();

        return;
    }

    if(sensorType == Sensor::DS18B20) {
        DallasTemperature *ds18b20 = _sensor.getDS18B20();
        ds18b20->begin();

        ds18b20->requestTemperatures();
        data.temperature = ds18b20->getTempCByIndex(0);
        data.humidity = -9999; // Since this sensor cannot read humidy, set to a high negative number

        return;
    }
}

bool Temperature::valid() {
    return !isnan(data.temperature) && !isnan(data.humidity);
}