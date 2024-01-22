#include <WiFi.h>
#include <ESPAsyncWebServer.h>

#define RX_PIN_ESP32 16
#define TX_PIN_ESP32 17

// Wifi setup
const char* ssid = "";
const char* password = "";

AsyncWebServer server(80);

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);

  WiFi.begin(ssid, password);

  while(WiFi.status() != WL_CONNECTED){
    delay(1000);
    Serial.println("Connecting...");
  }
  Serial.println("Connected to WiFi");

  //Serial2.begin(9600, SERIAL_8N1, 16, 17);
  Serial2.begin(9600);
  Serial.println(WiFi.localIP());
  Serial.println("start");

  server.on("/wind", HTTP_GET, [](AsyncWebServerRequest *request){
    String response = "Received data: ";
    while (Serial2.available()){
      response += String(Serial2.readStringUntil('\n'));
    }
    request->send(200, "text/plain", response);
  });

  server.begin();
  Serial.println("HTTP server started");

}

void loop() {
  if (Serial2.available()) {
    String receivedData = Serial2.readStringUntil('\n');
    Serial.print("Received Wind Sensor Data: ");
    Serial.println(receivedData);
  }
  delay(1000);
}