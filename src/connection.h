#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#ifndef CONECTAR_H
#define CONECTAR_H
class Connection
{
public:
  char *ssid;
  char *password;
  IPAddress ip;
  IPAddress gateway;
  IPAddress subnet;
  IPAddress dns;
  uint32_t ultimoIntentoDeConexion;

  Connection(char *ssid_, char *password_, IPAddress &ip_, IPAddress &gateway_, IPAddress &subnet_)
  {
    ssid = ssid_;
    password = password_;
    ip = ip_;
    gateway = gateway_;
    subnet = subnet_;
    dns = IPAddress(8, 8, 8, 8);
    ultimoIntentoDeConexion = 0;
  }
  bool connect()
  {
    bool resultado = false;
    // Inicializa el módulo wifi
    WiFi.mode(WIFI_STA); // Establece el módulo como estación wifi
    WiFi.disconnect();   // Se desconecta de cualquier WiFi conectado previamente
    Serial.println();

    // conecta con la red wifi
    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.config(ip, dns, gateway, subnet);
    WiFi.begin(ssid, password);
    int intentos = 0;
    while (WiFi.status() != WL_CONNECTED && intentos < 20) // intenta por 10 segundos si no sale
    {                                                      // Espera por una conexión WiFi
      delay(500);
      Serial.print(".");
      intentos++;
    }
    if (WiFi.status() == WL_CONNECTED)
    {
      Serial.println("");
      Serial.println("WiFi connected");
      Serial.print("IP address: ");
      Serial.println(WiFi.localIP());
      resultado = true;
    }
    else
    {
      Serial.println("/nWiFi not connected");
    }

    return resultado;
  }

  bool handleReconnection()
  {
    if (WiFi.status() != WL_CONNECTED && millis() - ultimoIntentoDeConexion > 10000) // cada 10 segundos intenta reconectarse
    {
      if (ultimoIntentoDeConexion == 0) // esto me indica que es la primera vez que entra. Entonces indico que se detectó pérdida de conexión
      {
        Serial.println("\nConnection lost!");
      }
      bool resultado = Connection::connect();
      ultimoIntentoDeConexion = millis();

      if (resultado)
      {
        Serial.println("Reconnected!");
        ultimoIntentoDeConexion = 0;
      }
      else
      {
        Serial.println("Reconnection Failed!");
      }
      return resultado;
    }
    return false;
  }
};
#endif