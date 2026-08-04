#include <math.h>

#include "temperature.h"


Temperature::tempHum Temperature::getTemperatureAndHumidity() {
    return data;
}

void Temperature::setTemperatureAndHumidity(float _temperature, float _humidity) {
    data.temperature = _temperature;
    data.humidity = _humidity;
}

bool Temperature::valid() {
    return !isnan(data.temperature) && !isnan(data.humidity);
}