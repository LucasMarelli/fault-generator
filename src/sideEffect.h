#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include "connection.h"
#include "myClient.h"
#include "html.h"
#include "pin.h"
#ifndef SIDE_EFFECT_H
#define SIDE_EFFECT_H
class SideEffect
{
private:
    ESP8266WebServer *server;
    MyClient *myClient;

    void start()
    {
        Serial.println("Counting...");
        delay(2000);
        Serial.println("Start!");
        digitalWrite(D5, HIGH);
        delay(2000);
        digitalWrite(D5, LOW);
    }

    void handleStart()
    {
        server->send(204);
        Serial.println("Send confirm...");
        String url = "http://192.168.250";
        myClient->httpPOSTRequest(url + "/started", "");
        start();
    }

public:
    SideEffect(ESP8266WebServer *server_, MyClient *myClient_)
    {
        server = server_;
        myClient = myClient_;
    };

    // Defini un tipo para ahorrar escribir todo
    typedef std::function<void(void)> callback;
    void setup()
    {
        // Tuve que hacer esto por esto:
        // https://stackoverflow.com/questions/68138320/no-suitable-constructor-exists-to-convert-from-void-to-stdfunctionvoid
        callback handleStart_ = [this]()
        { this->handleStart(); };

        server->on("/start", handleStart_);
    }
};
#endif