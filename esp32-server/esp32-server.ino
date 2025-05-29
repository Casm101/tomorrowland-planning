#include "WiFi.h"
#include "SPIFFS.h"
#include "ESPAsyncWebServer.h"
  
const char* ssid = "Duane mesh Network";
const char* password =  "Diet@vanilla@coke@101*wifi";
  
AsyncWebServer server(80);
  
void setup(){
  Serial.begin(115200);
  
  if(!SPIFFS.begin()){
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }

  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/index.html", "text/html");
  });
  
  server.begin();
}
  
void loop(){}