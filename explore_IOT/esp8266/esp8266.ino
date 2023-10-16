#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

const char* ssid = "Wireless 2.4";
const char* password = "SMKPB2024";

//Your Domain name with URL path or IP address with path
String serverName = "http://exploreiot2021.000webhostapp.com/";

void request(String data)
{
    //Check WiFi connection status
    if(WiFi.status()== WL_CONNECTED){
      WiFiClient client;
      HTTPClient http;

      String serverPath = serverName + data;
      
      Serial.print(serverPath);
     
      // Your Domain name with URL path or IP address with path
      http.begin(client, serverPath.c_str());
      
      // Send HTTP GET request
      int httpResponseCode = http.GET();
      
      if (httpResponseCode>0) {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        String payload = http.getString();
        Serial.println(payload);
      }
      else {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
      }
      // Free resources
      http.end();
    }
    else {
      Serial.println("WiFi Disconnected");
    }
}

void setup() {
  Serial.begin(115200); 

  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
}


boolean Send=false;
String data;

void loop() {
 
 if(Serial.available()>0)
 {
  char inChar = (char)Serial.read();
  if (inChar == '\n') Send = true;
  else data += inChar;  
 }
 if(Send)
 {
  request(data);
  Send=false;
  data="";
 }
}
