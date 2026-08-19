#include <math.h>

#include "temperature.h"
#include "Adafruit_SHT31.h"
#include "DallasTemperature.h"
#include "OneWire.h"
#include "sensor/sensor.h"


Temperature::tempHum Temperature::getTemperatureAndHumidity() {
    return data;
}

void Temperature::setTemperatureAndHumidity(Sensor::SensorType _sensor) {
    if(_sensor == Sensor::SHT31) {
        Wire.begin();
        Adafruit_SHT31 sht31;
        data.temperature = sht31.readTemperature();
        data.humidity = sht31.readHumidity();

        return;
    }

    if(_sensor == Sensor::DS18B20) {
        OneWire oneWire(4);
        DallasTemperature ds18b20;
        ds18b20.begin();

        ds18b20.requestTemperatures();
        data.temperature = ds18b20.getTempCByIndex(0);
        data.humidity = -9999; // Since this sensor cannot read humidy, set to a high negative number

        return;
    }
}

bool Temperature::valid() {
    return !isnan(data.temperature) && !isnan(data.humidity);
}