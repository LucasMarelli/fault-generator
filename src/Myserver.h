#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#ifndef SERVER_H
#define SERVER_H
class MyServer : public ESP8266WebServer
{
private:
    /* data */
public:
    MyServer(int port) : ESP8266WebServer(port){};
};
#endif