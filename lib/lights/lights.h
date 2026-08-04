#ifndef LIGHTS_H
#define LIGHTS_H

class Lights {
    public:
        Lights(int pin) : pin(pin) {
            pinMode(pin, OUTPUT);
        }

        void on(WiFiClient _client, String _domain);
        void off(WiFiClient _client, String _domain);

    private:
        int pin;
};

#endif