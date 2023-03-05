#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include "connection.h"
#include "myClient.h"
#include "html.h"
#include "pin.h"
#ifndef FAULT_GENERATOR_H
#define FAULT_GENERATOR_H
class FaultGenerator
{
private:
    ESP8266WebServer *server;
    MyClient *myClient;

    void handleFault()
    {
        String fault = FAULT_page;
        String url = "http://192.168.251";
        int code = myClient->httpPOSTRequest(url + "/start", "");
        if (code >= 200 || code <= 299)
        {
            server->send(200, "text/html", fault);
        }
        else
        {
            server->send(400, "text/plain", "Error intenrar de nuevo");
        }
    }

    void handleRoot()
    {
        String main = MAIN_page;
        server->send(200, "text/html", main);
    }

    void handleStart()
    {
        Serial.print("Fault!");
        server->send(204);
        digitalWrite(D5, HIGH);
        delay(500);
        digitalWrite(D5, LOW);
    }

public:
    FaultGenerator(ESP8266WebServer *server_, MyClient *myClient_)
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
        callback handleRoot_ = [this]()
        { this->handleRoot(); };
        callback handleFault_ = [this]()
        { this->handleFault(); };
        callback handleStart_ = [this]()
        { this->handleStart(); };

        server->on("/", handleRoot_);
        server->on("/fault", handleFault_);
        server->on("/started", handleStart_);
    }
};
#endif