#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ArduinoOTA.h>




#ifndef STASSID
#define STASSID "KVV"
#define STAPSK  "148271Dv"
#endif

const char* ssid     = STASSID;
const char* password = STAPSK;

const char* host = "http://127.0.0.1";
const uint16_t port = 5000;


int analogpin = 1;
int analog = A0;
int digit = 12;

//функция чтения данных с датчика
int LogicFunction() {
  int digitValue = digitalRead(digit);
  int analogValue = analogRead(analog);
  Serial.println((String)digitValue + 't' + (String)analogValue);
  delay(100);
  return analogValue;
}

void setup()
{
  Serial.begin(115200);


  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);


  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}



void loop() {
  Serial.print("connecting to ");
  Serial.print(host);
  Serial.print(':');
  Serial.println(port);


  WiFiClient client;
  if (!client.connect(host, port)) {
    Serial.println("connection failed");
    delay(5000);
    return;
  }

  //отправка данных на сервер
  Serial.println("отправка на сервер");
  if (client.connected()) {
    //код на сервер
  }

  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      delay(60000);
      return;
    }
  }

  // чтение данных с сервера
  Serial.println("receiving from remote server");
  while (client.available()) {
    char ch = static_cast<char>(client.read());
    Serial.print(ch);
    //обработка запроса с сервера
  }







}
