#include <Wire.h>
#include "RTClib.h"
#include <EEPROM.h>
#include <SoftwareSerial.h>
SoftwareSerial LCDHMI(2,3); //RX, TX 

char bufferText[50];

RTC_DS1307 rtc;

#define RELAY 13
#define NYALA 0
#define MATI  1

boolean relayState = false;
boolean controlManual = false;

int ON1;  // address EEPROM (10)
int ON2;  // address EEPROM (20)
int ON3;  // address EEPROM (30)
int ONL;  // address EEPROM (40)
int OFF1; // address EEPROM (15)
int OFF2; // address EEPROM (25)
int OFF3; // address EEPROM (35)
int OFFL; // address EEPROM (45)

void setup() {
  LCDHMI.begin(9600);
  Serial.begin(9600);
  #ifdef AVR
  Wire.begin();
  #else
  Wire1.begin();
  #endif
  rtc.begin();

  if (! rtc.isrunning()) {
    //Serial.println("RTC is NOT running!");
  }

  pinMode(RELAY,OUTPUT);
  digitalWrite(RELAY,MATI);
  
  ON1  = EEPROMReadInt(10);
  ON2  = EEPROMReadInt(20);
  ON3  = EEPROMReadInt(30);
  ONL  = EEPROMReadInt(40);
  OFF1 = EEPROMReadInt(15);
  OFF2 = EEPROMReadInt(25);
  OFF3 = EEPROMReadInt(35);
  OFFL = EEPROMReadInt(45);
}

void EEPROMWriteInt(int address, int value)
{
  byte two = (value & 0xFF);
  byte one = ((value >> 8) & 0xFF);
  
  EEPROM.update(address, two);
  EEPROM.update(address + 1, one);
}
 
int EEPROMReadInt(int address)
{
  long two = EEPROM.read(address);
  long one = EEPROM.read(address + 1);
 
  return ((two << 0) & 0xFFFFFF) + ((one << 8) & 0xFFFFFFFF);
}

void sendDate(){
  DateTime now = rtc.now();    
  char dateString[11];
  sprintf(dateString, "%02d/%02d/%04d", now.day(), now.month(), now.year());
  LCDHMI.print("t0.txt=\"");
  LCDHMI.print(dateString);
  LCDHMI.print("\"");
  LCDHMI.write(0xff);
  LCDHMI.write(0xff);
  LCDHMI.write(0xff);
}

void sendTime(){
  DateTime now = rtc.now();    
  char timeString[11];
  sprintf(timeString, "%02d:%02d:%02d", now.hour(), now.minute(), now.second());
  LCDHMI.print("t1.txt=\"");  
  LCDHMI.print(timeString);
  LCDHMI.print("\"");
  LCDHMI.write(0xff);
  LCDHMI.write(0xff);
  LCDHMI.write(0xff);
}

void sendStateRelay(){
  LCDHMI.print("t2.txt=\"");
  if(relayState == true)
    LCDHMI.print("ON");
  else 
    LCDHMI.print("OFF");  
  LCDHMI.print("\"");
  LCDHMI.write(0xff);
  LCDHMI.write(0xff);
  LCDHMI.write(0xff); 
}

void cekRelayOn(){
  DateTime now = rtc.now();    
  int jam = now.hour();
  int mnt = now.minute();
  int time_now = jam*100+mnt; 
    
  if(time_now >= ON1 and time_now < OFF1) {
   relayState = true;
  }
  else if(time_now >= ON2 and time_now < OFF2){
   relayState = true;
  }
  else if(time_now >= ON3 and time_now < OFF3){
    relayState = true;
  }
  else if(controlManual == true){
    relayState = true;  
  }
  else {
    relayState = false;
  }
}

void relayloop(){
  if(relayState == true){
    digitalWrite(RELAY,NYALA);    
  }else{
    digitalWrite(RELAY,MATI);
  }
}

void sendData(){
 sendDate();
 sendTime(); 
 sendStateRelay();
}

void loop() {
  // put your main code here, to run repeatedly:
  cekRelayOn();
  relayloop();
  static uint32_t pM;  
  if((millis() - pM) > 1000) { 
    pM = millis();
    sendData();
    
    Serial.println(relayState);
    sprintf(bufferText, "ON1 = %d OFF1 =  %d", ON1,OFF1);
    Serial.println(bufferText);
    sprintf(bufferText, "ON2 = %d OFF2 =  %d", ON2,OFF2);
    Serial.println(bufferText);
    sprintf(bufferText, "ON3 = %d OFF3 =  %d", ON3,OFF3);
    Serial.println(bufferText);
  }
  serialEvent();
}
