#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ArduinoOTA.h>
/*
#ifndef APSSID
#define APSSID "NERONEX_TEST"
#endif

const char *ssid = APSSID;

ESP8266WebServer server(80);


void handleRoot() {
  server.send(200, "text/html", "<h1>You are connected</h1>");
}


void FirstartFunction(){
  delay(1000);
  Serial.begin(115200);
  Serial.println();
  Serial.print("Настройка точки доступа...");
  WiFi.softAP(ssid);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);

  ArduinoOAT.begin()
  
  server.on("/", handleRoot);
  server.begin();
  Serial.println("HTTP server started");
  
}

*/
#ifndef STASSID
#define STASSID "KVV"
#define STAPSK  "148271Dv"
#endif

const char* ssid     = STASSID;
const char* password = STAPSK;

//const char* host = "http://127.0.0.1";
//const uint16_t port = 5000;

int analogpin = 1

int LogicFunction(){
  int digitValue = digitalRead(digit);
  int analogValue = analogRead(analog);
  Serial.println((String)digitValue + 't' + (String)analogValue);
  delay(100);
  return analogValue;
  
  
}


void setup() {
  Serial.begin(115200);

  

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
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
  

}
