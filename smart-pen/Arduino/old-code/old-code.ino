#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "MAX30100_PulseOximeter.h"
#include <EEPROM.h>

#include <Arduino.h>
#include "fpc1020a.h"

#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

const char* ssid = "Smart Pen and Medical Record";
const char* password = "12345678";
String serverName = "https://smartpenmedicalrecord.000webhostapp.com/";

DynamicJsonDocument doc(2048);

HardwareSerial hwSerial(2);
FPC1020 fp(&hwSerial);
extern unsigned char l_ucFPID;
extern unsigned char rBuf[192];

int ID_FINGER = 0;

Adafruit_SSD1306 display = Adafruit_SSD1306(128, 32, &Wire);

PulseOximeter pox;
uint32_t pM,pm = 0;
boolean enrollMode = false;
boolean findMode = false;


int BUZZER = 12; 

//button
int BUTTON = 13; 
int SHORT_TIME = 1000; 
int previousState = LOW;
int presentState;
unsigned long press_Time = 0; 
unsigned long release_Time = 0;

// Callback (registered below) fired when a pulse is detected
void onBeatDetected()
{
    Serial.println("Beat!");
}

void wifiBegin(){
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

void request(int id_finger){
  //Check WiFi connection status
  if(WiFi.status()== WL_CONNECTED){
    HTTPClient http;
    char buffer[50];
    sprintf(buffer,"finger/%d",id_finger);
    String serverPath = serverName + buffer;
      
    // Your Domain name with URL path or IP address with path
    http.begin(serverPath.c_str());
      
    // Send HTTP GET request
    int httpResponseCode = http.GET();
      
    if (httpResponseCode>0) {
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
      String payload = http.getString();
      Serial.println(payload);    
      DeserializationError error = deserializeJson(doc, payload);
      // Test if parsing succeeds.
      if (error) {
        Serial.print(F("deserializeJson() failed: "));
        Serial.println(error.f_str());
        return;
      }
    }else {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
    }
    // Free resources
    http.end();
   }else {
    Serial.println("WiFi Disconnected");
   }  
}

void oxiInit(){
  pox.begin(); 
  pox.setOnBeatDetectedCallback(onBeatDetected);

}

void tampJudul(){
  display.clearDisplay(); 
  display.setCursor(0,0);
  display.println(" Pen & Medical Record");
}

void enroll(){
  display.clearDisplay();
  display.setCursor(0,0);
  display.println("Add Fingerprint...");
  display.display(); 
  unsigned char rtf = fp.Enroll(ID_FINGER);
  if (rtf == TRUE){
    digitalWrite(BUZZER, HIGH);
    delay(300);
    digitalWrite(BUZZER, LOW);
    delay(50);
    digitalWrite(BUZZER, HIGH);
    delay(200);
    digitalWrite(BUZZER, LOW);
    display.setCursor(0,20);
    display.print("Success, ID is: ");
    display.println(ID_FINGER, DEC);
    ID_FINGER+=1;
    EEPROM.write(1,ID_FINGER);
    EEPROM.commit();
    Serial.print("IDFINGER : ");
    Serial.println(EEPROM.read(1));
    display.display();
    delay(4000);        
    oxiInit();
    enrollMode = false;
  }else if (rtf == FALSE){
    display.setCursor(0,20);
    display.println("Failed, please try again.");
    display.display(); 
    digitalWrite(BUZZER, HIGH);
    delay(1000);
    enrollMode = true;
  }else if (rtf == ACK_USER_OCCUPIED){
    display.setCursor(0,20);
    display.println("ID already exsits.");
    display.display(); 
    digitalWrite(BUZZER, HIGH);
    delay(1000);
    enrollMode = true;
  }else if (rtf == ACK_USER_EXIST){
    display.setCursor(0,20);
    display.println("fingerprint already exsits.");
    display.display(); 
    digitalWrite(BUZZER, HIGH);
    delay(1000);
    enrollMode = true;
  }    
}
void findID(){
  display.clearDisplay();
  display.setCursor(0,0);
  display.println("find Fingerprint...");
  display.display();
  if (fp.Search()){
    request(l_ucFPID);
    const char* Status = doc["status"];
    const char* nama = doc["nama"]; 
    if(nama){
    digitalWrite(BUZZER, HIGH);
    delay(250);
    digitalWrite(BUZZER, LOW);
    delay(50);
    digitalWrite(BUZZER, HIGH);
    delay(150);
    digitalWrite(BUZZER, LOW);  
    display.setCursor(0,20);
    display.print("Hello: ");
    display.print(l_ucFPID, DEC);
    display.print(" | ");
    display.println(nama);
    display.display();
    delay(4000);
    oxiInit();    
    }else{
      digitalWrite(BUZZER, HIGH);
      delay(500);
      digitalWrite(BUZZER, LOW);
      display.setCursor(0,20);
      display.println(Status);
      display.display();
      delay(4000);     
    }
    findMode = false;
  }else{
    display.setCursor(0,20);
    display.println("Failed, try again.");
    display.display();
    digitalWrite(BUZZER, HIGH);
    delay(1000);
    findMode = true;
  }  
}

void setup() {
  
  pinMode(BUTTON, INPUT_PULLUP);
  pinMode(BUZZER, OUTPUT);
  
  Serial.begin(115200);

  // set start id finger   
  EEPROM.begin(12); 
//  EEPROM.write(1,1); 
//  EEPROM.commit();

  
  wifiBegin();
  delay(1000);
  
  Serial.println("OLED FeatherWing test");
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // Address 0x3C for 128x32
    
  // Clear the buffer.
  display.clearDisplay();
  display.display();

  // text display tests
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.display(); 

  ID_FINGER = EEPROM.read(1);
  Serial.print("ID Finger : ");
  Serial.println(ID_FINGER);
   
  tombol();
  enrollMode = false;
  findMode = false;
  delay(3000);
  
  oxiInit();
}

void tombol(){
 presentState = digitalRead(BUTTON);
  if(previousState == HIGH && presentState == LOW)
    press_Time = millis();
  else if(previousState == LOW && presentState == HIGH) {
    release_Time = millis();
    long ON_TIME = release_Time - press_Time;     
      if( ON_TIME > 3000 ) {
        Serial.println("Mode enroll");
        enrollMode = true;
      }else if( ON_TIME > 500 ){
        Serial.println("Mode finding");
        findMode = true;
      }
  } 
}


void loop() {
 
  previousState = presentState;
  pox.update();
  if (enrollMode == true)
    enroll();
  else if (findMode == true)  
    findID();
  else{
    if (millis() - pM > 1000) { 
     tampJudul();
     display.setCursor(0,22);
     display.print(" Hr:");
     display.print(pox.getHeartRate());
     display.print(" | SpO2:");
     display.print(pox.getSpO2());
     display.println("%");
     display.display(); 
     pM = millis();    
    }
    display.clearDisplay();   
  }
   tombol();                            
   digitalWrite(BUZZER, LOW);      
}
