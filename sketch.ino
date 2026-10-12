#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "ESP32_Control";
const char* password = "12345678";

WebServer server(80);
const int ledPin = 2; // 板载LED通常接在GPIO2

void handleRoot() {
  String html = "<!DOCTYPE html><html><head><meta charset='UTF-8'>";
  html += "<meta name='viewport' content='width=device-width, initial-scale=1.0'>";
  html += "<title>ESP32 Control</title>";
  html += "<style>body{font-family:Arial;text-align:center;padding:20px;background:#f0f0f0;}";
  html += "h1{color:#333;}.btn{display:inline-block;padding:15px 40px;margin:10px;";
  html += "font-size:18px;border:none;border-radius:8px;cursor:pointer;}";
  html += ".on{background:#4CAF50;color:white;}.off{background:#f44336;color:white;}</style></head>";
  html += "<body><h1>ESP32 Web Control</h1>";
  html += "<p><a href='/on'><button class='btn on'>开灯 ON</button></a></p>";
  html += "<p><a href='/off'><button class='btn off'>关灯 OFF</button></a></p>";
  html += "</body></html>";
  server.send(200, "text/html", html);
}

void handleOn() {
  digitalWrite(ledPin, HIGH);
  server.sendHeader("Location", "/");
  server.send(303);
}

void handleOff() {
  digitalWrite(ledPin, LOW);
  server.sendHeader("Location", "/");
  server.send(303);
}

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  WiFi.softAP(ssid, password);
  Serial.print("AP IP address: ");
  Serial.println(WiFi.softAPIP());

  server.on("/", handleRoot);
  server.on("/on", handleOn);
  server.on("/off", handleOff);
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}
