#include <Arduino.h>
#include <SSD1306Wire.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "wifi_config.h"
SSD1306Wire display(0x3c, SDA, SCL);

IPAddress local_IP(192, 168, 1, 184);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);

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
}

void loop() {
  // put your main code here, to run repeatedly:
}

