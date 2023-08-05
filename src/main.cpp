#include <Arduino.h>
#include <SSD1306Wire.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "wifi_config.h"
SSD1306Wire display(0x3c, SDA, SCL);

IPAddress local_IP(192, 168, 1, 184);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);

ESP8266WebServer server(80);
void handleRoot(){
  server.send(200, "text/plain", "Connected");
  display.clear();
  display.drawString(0, 0, "Client Connected");
  display.display();
}
void handleNotFound(){
  server.send(404, "text/plain", "Not Found");
  display.clear();
  display.drawString(0, 0, "Bad EndPoint");
  display.display();
}
void setup() {
  display.init();
  display.clear();

  WiFi.mode(WIFI_STA);
  WiFi.config(local_IP, gateway, subnet);
  WiFi.begin(SSID, PSWD);
  int wifiLoader = 0;
  while(WiFi.status() != WL_CONNECTED){
    if(wifiLoader >100){
      display.clear();
      display.drawString(0, 0, "Connecting to WiFi");
      wifiLoader = 0;
    }
    display.drawProgressBar(0, 16, 120, 10, wifiLoader);
    display.display();
    delay(10);
  }
  display.clear();
  display.drawString(0, 0, "Connected to WiFi\n");
  display.drawString(0, 16, "IP: ");
  display.drawString(0, 32, WiFi.localIP().toString());
  display.display();

  server.on("/",handleRoot);
  server.onNotFound(handleNotFound);

  server.on("/msg",[](){
    server.send(200, "text/plain", "Message Received");
    String value = server.arg("msg");
    int x = server.arg("x").toInt();
    int y = server.arg("y").toInt();
    bool clear = server.arg("clear").toInt();
    if(clear){
      display.clear();
    }
    display.drawString(x,y,value);
    display.display();
  });
  server.on("/box",[](){
    server.send(200, "text/plain", "Box Received");
    int w = server.arg("w").toInt();
    int h = server.arg("h").toInt();
    int x = server.arg("x").toInt();
    int y = server.arg("y").toInt();
    display.drawRect(x,y,w,h);
    display.display();
  });
  server.on("/clear",[](){
    server.send(200, "text/plain", "Cleared");
    display.clear();
    display.display();
  });
  server.begin();
}

void loop() {
  server.handleClient();
}

