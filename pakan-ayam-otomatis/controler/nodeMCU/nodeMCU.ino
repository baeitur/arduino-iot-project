#include <Wire.h>
#include <RtcDS3231.h>
RtcDS3231<TwoWire> Rtc(Wire);

#include <FS.h>
#include <LittleFS.h>
#include <ArduinoJson.h>
#include <CertStoreBearSSL.h>

#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <time.h>
#include <TZ.h>
#include <Servo.h>
Servo myservo;

boolean relay_state = false;
boolean status_connect  = false;

#include "rtc.h"
#include "fsConfig.h"
#include "wifiConfig.h"

#define RELAYPIN D7
#define ON 0
#define OFF 1


void relayLoop(){
  if(relay_state==true){
   digitalWrite(RELAYPIN, ON);
   myservo.write(180);
  }else{
   digitalWrite(RELAYPIN, OFF);
   myservo.write(0);
  }
}

void setup() {
  // Servo
  myservo.attach(14);
  
  // LCD COM
  Serial.begin(9600);

  // RTC
  mulaiRTC();

  // FILE SYSTEM
  LittleFS.begin();
  loadDataConfig(fileconfigtimer, configtimer, fileconfigwifi, configwifi);
  bacaParameter();

  // wifi config
  setupWifi();
  setDateTime();

  // mqtt init
  mqttInit();
      
  // relay mode
  pinMode(RELAYPIN, OUTPUT);  
}

void loop() {
  if (!client->connected()) reconnect();
  else status_connect=true;

  client->loop();
  serialEvent();
  BacaRTC();
  relayLoop();
  
  int now_time = rJam*100+rMen;
  if     (configtimer.on1 ==now_time and rDet<5) relay_state = true;
  else if(configtimer.off1==now_time and rDet<5) relay_state = false;
  else if(configtimer.on2 ==now_time and rDet<5) relay_state = true;
  else if(configtimer.off2==now_time and rDet<5) relay_state = false;
  else if(configtimer.on3 ==now_time and rDet<5) relay_state = true;
  else if(configtimer.off3==now_time and rDet<5) relay_state = false;
  
  String jam = getTimeString();
  String tgl = getDateString();
  String tmp = getTempString();
  String timer1 = getTimer1String();
  String timer2 = getTimer2String();
  String timer3 = getTimer3String();
  String relay  = (relay_state)?"ON":"OFF";
  
  String data = jam+"|"+tgl+"|"+tmp+"|"+timer1+"|"+timer2+"|"+timer3+"|"+relay;
  
  if(rDet%2==0){
    client->publish("all-data", data.c_str());
    Serial.print(data);
  }
  
  static uint32_t pM;  
  if((millis() - pM) > 1000) { 
    pM = millis();
    sendData();
    sendTimer(timer1,timer2,timer3);
    //Serial.println(statusConnect);
  }
}
