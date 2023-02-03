#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#ifndef MYCLIENT_H
#define MYCLIENT_H
class MyClient
{
public:
    HTTPClient *http; // defino como punteros para no hacer uso excesivo de memoria
    WiFiClient *client;

    MyClient(HTTPClient &http_, WiFiClient &client_) // Constructor. Los parámetros son pasados por referencia.
    {
        http = &http_;     // Asigno la referencia de memoria al puntero
        client = &client_; // Asigno la referencia de memoria al puntero'
        http->setTimeout(10000);
    }

    String httpGETRequest(String url)
    {
        if (WiFi.status() == WL_CONNECTED) // Verifica si hay conexión. Si no no hace nada
        {
            String payload = "";
            if (http->begin(*client, url)) // Iniciar conexión. Debo ponerle * a cliente porque es un puntero y yo debo pasarle un objeto. Al asignarle nuevamente * pasa el objeto y no el puntero
            {
                Serial.print("[HTTP] GET...\n");
                int httpCode = http->GET(); // Realizar petición

                if (httpCode > 0) // Si hay error el código devuelto es negativo.
                {
                    Serial.printf("[HTTP] GET... code: %d\n", httpCode);

                    if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY)
                    {
                        payload = http->getString(); // Obtener respuesta en string
                                                     // Serial.println(payload);   // Mostrar respuesta por serial
                    }
                }
                else // En caso que falle el GET
                {
                    Serial.printf("failed, error: %s\n", http->errorToString(httpCode).c_str());
                    Serial.print("Code: ");
                    Serial.println(httpCode);
                }

                http->end(); // libera recursos
            }
            else // Si no puede establecer conexión con el servidor
            {
                Serial.printf("[HTTP} Unable to connect\n");
            }

            return payload;
        }
        else // Si no hay conexión WiFi
        {
            Serial.printf("WiFi not connected\n");
            return "";
        }
    }

    int httpPOSTRequest(String url, String msj)
    {
        // Serial.println("1");
        int httpCode = -9999;
        if (WiFi.status() == WL_CONNECTED) // Verifica si hay conexión. Si no no hace nada
        {
            if (http->begin(*client, url)) // Iniciar conexión. Debo ponerle * a cliente porque es un puntero y yo debo pasarle un objeto al asignarle nuevamente * pasa el objeto y no el puntero
            {
                http->addHeader("Content-Type", "text/plain"); // añade cabecera

                httpCode = http->POST(msj); // Realiza el POST

                if (httpCode > 0) // Si no hay error en el POST. (Si hay error el POST devuelve valores negativos)
                {
                    Serial.printf("[HTTP] POST... code: %d\n", httpCode); // Solo inica por comunicación serial que se realizó un POST satisfactorio
                }
                else
                {
                    // Avisa por comunicación serial que se intentó hacer un POST sin éxito
                    Serial.printf("[HTTP] POST... failed, error: %s\n", http->errorToString(httpCode).c_str());
                    Serial.print("Code: ");
                    Serial.println(httpCode);
                }

                http->end(); // Libera recursos
            }

            else // Si la conexión con el servidor falló
            {
                Serial.printf("[HTTP} Unable to connect\n");
            }
        }
        else // Si no está conectado al WiFi
        {
            Serial.printf("WiFi not connected\n");
        }
        return httpCode;
    }
};
#endif