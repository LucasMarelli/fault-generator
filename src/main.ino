#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include "connection.h"
#include "myClient.h"
#include "html.h"
#include "pin.h"
#include "faultGenerator.h"
#include "sideEffect.h"
#define FAULT_GENERATOR 0
#define FIREWORKS 1
#define TYPE FIREWORKS
// #include "server.h"
char *ssid = "SeVaLaVida 2.4GHz";
char *password = "00436003571";
// char *ssid = "Fibertel casaMi 2.4GHz_EXT";
// char *password = "NEWELLS1974";
#if TYPE == FAULT_GENERATOR
IPAddress ip = IPAddress(192, 168, 0, 250);
#else
IPAddress ip = IPAddress(192, 168, 0, 251);
#endif
IPAddress gateway(192, 168, 0, 1);
IPAddress subnet(255, 255, 255, 0);
Connection connection = Connection(ssid, password, ip, gateway, subnet);
// Server server = Server(80);
ESP8266WebServer server = ESP8266WebServer(80);
// Cliente
HTTPClient http;
WiFiClient client;
MyClient myClient = MyClient(http, client);

#if TYPE == FAULT_GENERATOR
FaultGenerator faultGenerator = FaultGenerator(&server, &myClient);
#else
SideEffect sideEffect = SideEffect(&server, &myClient);
#endif

void setup()
{
  pinMode(D5, OUTPUT);
  Serial.begin(9600);
  connection.connect();
  server.begin();
#if TYPE == FAULT_GENERATOR
  faultGenerator.setup();
#else
  sideEffect.setup();
#endif
}

void loop()
{
  server.handleClient();
  connection.handleReconnection();
}
