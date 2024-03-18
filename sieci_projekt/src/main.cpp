#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "SPIFFS.h"

const char* ssid = "TAB";
const char* password = "faustyna";
// Create AsyncWebServer object on port 80
AsyncWebServer server(80);
//esp32's outputs settings 
const int ledPin = 2;
const int ledPin2=4;
const int ledPin3=19;

// Stores LED state
String ledState;
String ledState2;
String ledState3;
// Initialize SPIFFS
void initSPIFFS() {
 if (!SPIFFS.begin()) {
 Serial.println("An error has occurred while mounting SPIFFS");
 }
 Serial.println("SPIFFS mounted successfully");
}
// Initialize WiFi
void initWiFi() {
 WiFi.mode(WIFI_STA);
 WiFi.begin(ssid, password);
 Serial.print("Connecting to WiFi ..");
 while (WiFi.status() != WL_CONNECTED) {
 Serial.print('.');
 delay(1000);
 }
 Serial.println(WiFi.localIP());
}
// Replaces placeholder with LED state value
String processor(const String& var){
 if(var == "STATE") {
 if(digitalRead(ledPin)) {
 ledState = "ON";
 }
 else {
 ledState = "OFF";
 }
 return ledState;
 }
 return String();
}


String processor2(const String& var){
 if(var == "STATE") {
 if(digitalRead(ledPin2)) {
 ledState2 = "ON";
 }
 else {
 ledState2 = "OFF";
 }
 return ledState2;
 }
 return String();
}

String processor3(const String& var){
 if(var == "STATE") {
 if(digitalRead(ledPin3)) {
 ledState3 = "ON";
 }
 else {
 ledState3 = "OFF";
 }
 return ledState3;
 }
 return String();
}
void setup() {

 Serial.begin(9600);
 initWiFi();
 initSPIFFS();
 
 // Set GPIO2 as an OUTPUT
 pinMode(ledPin , OUTPUT);
 pinMode(ledPin2 , OUTPUT);
  pinMode(ledPin3 , OUTPUT);
 server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
 request->send(SPIFFS, "/index.html", "text/html", false, processor);
 });
 server.serveStatic("/", SPIFFS, "/");
 server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
 request->send(SPIFFS, "/index.html", "text/html", false, processor2);
 });
 server.serveStatic("/", SPIFFS, "/");
 server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
 request->send(SPIFFS, "/index.html", "text/html", false, processor3);
 });
 server.serveStatic("/", SPIFFS, "/");
 // Route to set GPIO state to HIGH
 server.on("/on", HTTP_GET, [](AsyncWebServerRequest *request){
 digitalWrite(ledPin, HIGH);
 request->send(SPIFFS, "/index.html", "text/html", false, processor);
 });
 // Route to set GPIO state to LOW
 server.on("/off", HTTP_GET, [](AsyncWebServerRequest *request){
 digitalWrite(ledPin, LOW);
 request->send(SPIFFS, "/index.html", "text/html", false, processor);
 });
 server.on("/on1", HTTP_GET, [](AsyncWebServerRequest *request){
 digitalWrite(ledPin2, HIGH);
 request->send(SPIFFS, "/index.html", "text/html", false, processor2);
 });
 // Route to set GPIO state to LOW
 server.on("/off1", HTTP_GET, [](AsyncWebServerRequest *request){
 digitalWrite(ledPin2, LOW);
 request->send(SPIFFS, "/index.html", "text/html", false, processor2);
 });
  server.on("/on2", HTTP_GET, [](AsyncWebServerRequest *request){
 digitalWrite(ledPin2, HIGH);
 request->send(SPIFFS, "/index.html", "text/html", false, processor3);
 });
 // Route to set GPIO state to LOW
 server.on("/off2", HTTP_GET, [](AsyncWebServerRequest *request){
 digitalWrite(ledPin2, LOW);
 request->send(SPIFFS, "/index.html", "text/html", false, processor3);
 });
 // Start server
 server.begin();
}
void loop() {
}