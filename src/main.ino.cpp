# 1 "C:\\Users\\lucas\\AppData\\Local\\Temp\\tmpysgpxt_i"
#include <Arduino.h>
# 1 "C:/Users/lucas/Dropbox/Arduino/Arduino/fault-generator/src/main.ino"
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

char *ssid = "SeVaLaVida 2.4GHz";
char *password = "00436003571";


#if TYPE == FAULT_GENERATOR
IPAddress ip = IPAddress(192, 168, 0, 250);
#else
IPAddress ip = IPAddress(192, 168, 0, 251);
#endif
IPAddress gateway(192, 168, 0, 1);
IPAddress subnet(255, 255, 255, 0);
Connection connection = Connection(ssid, password, ip, gateway, subnet);

ESP8266WebServer server = ESP8266WebServer(80);

HTTPClient http;
WiFiClient client;
MyClient myClient = MyClient(http, client);

#if TYPE == FAULT_GENERATOR
FaultGenerator faultGenerator = FaultGenerator(&server, &myClient);
#else
SideEffect sideEffect = SideEffect(&server, &myClient);
#endif
void setup();
void loop();
#line 40 "C:/Users/lucas/Dropbox/Arduino/Arduino/fault-generator/src/main.ino"
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