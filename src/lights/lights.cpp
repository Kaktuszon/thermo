#include <Arduino.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>

#include "lights.h"

void Lights::on(WiFiClient _client, String _domain) {
    digitalWrite(pin, LOW);
    HTTPClient http;
    http.begin(_client, "http://" + _domain + ":3001/api/light/on");
    http.end();
}

void Lights::off(WiFiClient _client, String _domain) {
    digitalWrite(pin, HIGH); 
    HTTPClient http;
    http.begin(_client, "http://" + _domain + ":3001/api/light/off");
    http.end();
}