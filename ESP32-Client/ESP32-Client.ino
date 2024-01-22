#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "";
const char* password = "";

//IP address + domain name with URL path
const char* serverNameDirection = "http://wind";

String direction;

void setup(){
  Serial.begin(9600);

  WiFi.begin(ssid, password);

  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop(){
  HTTPClient http;

  //ESP32's IP address or domain for the server
  http.begin(serverNameDirection);

  int httpCode = http.GET();

  if(httpCode > 0){
    if(httpCode == HTTP_CODE_OK){
      direction = http.getString();
      Serial.println("Wind Data: "+ direction);
    }
  }
  else{
    Serial.println("HTTP request failed");
  }

  http.end();

  delay(1000);
}