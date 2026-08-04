#ifndef TEMPERATURE_H
#define TEMPERATURE_H

class Temperature {    
    public:
        struct tempHum {
            float temperature;
            float humidity;
        };

        tempHum getTemperatureAndHumidity();
        void setTemperatureAndHumidity(float _temperature, float _humidity);
        
        bool valid();

    private:
        tempHum data;
};

#endif