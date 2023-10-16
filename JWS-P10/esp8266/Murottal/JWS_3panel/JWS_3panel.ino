#include <Wire.h>
#include <RtcDS3231.h>
RtcDS3231<TwoWire> Rtc(Wire);
#include <F1kM_Hisab.h>
#include <PrayerTimes.h>

#include <FS.h>
#include <LittleFS.h>
#include <ArduinoJson.h>

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPUpdateServer.h>

#include <DFPlayer_Mini_Mp3.h>

#include "rtc.h"
#include "fsConfig.h"
#include "dfPlayer.h"
#include "webServer.h"
#include "webPage.h"
#include "jadwalSholat.h"

#include <DMDESP.h>

#include <fonts/ElektronMart6x8.h>
//#include <fonts/ElektronMartArabic5x6.h>
//#include <fonts/ElektronMartArabic6x16.h>

#include <font/angka6x13.h>
#include <font/arab6x13.h>
#include <font/SevSeg2.h>
#include <font/SmallCap4x6.h>


#define DISPLAYS_WIDE 3
#define DISPLAYS_HIGH 1
DMDESP Disp(DISPLAYS_WIDE, DISPLAYS_HIGH);



//----------------------------------------------------------------------
// SETUP

void setup() { 
  //MP3
  Serial.begin (9600);
  mp3_set_serial (Serial);
  delay(1);
  mp3_set_volume (15);
  
  //RTC
  mulaiRTC();

  //FILE SYSTEM
  LittleFS.begin();
  loadJwsConfig(fileconfigjws, configjws,fileconfigmurottal, configmurottal, fileconfigjumat, configjumat, fileconfiginfo, configinfo);
  bacaParameter();

  //connect wifi or AP
  wifiConnect();
  
  //menangani request
  server.on("/", []() {
    server.send_P(200, "text/html", web_page);
    cekUpadateDateTime();
  });
  server.on("/xmlwaktu", handleXMLWaktu); // http://192.168.4.1/xmlwaktu
  server.on("/xmldatajws", handleXMLDataJWS); // http://192.168.4.1/xmldatajws
  server.on("/simpandatajws", HTTP_POST, handleSettingJwsUpdate);
  server.on("/simpandatamurottal", HTTP_POST, handleSettingMurottalUpdate);
  server.on("/simpandatajumat", HTTP_POST, handleSettingJumatUpdate);
  server.on("/simpandatainfo", HTTP_POST, handleSettingInfoUpdate);

  //HTTP_Update
  httpUpdater.setup(&server);
  server.begin();
  Serial.println("HTTP server started"); 

  //RELAY PIN
  pinMode(RELAY, OUTPUT);

  //DMD
  Disp.start();  
  Disp.setBrightness(20);
  //Disp.setDoubleBuffer(true);
  
  UpdateWaktu();
  //playMurottal();
  //playMp3(26);

  //tmploop=1;
  Serial.print("Shubuh: ");
  Serial.println(jadwal.shubuh);
  Serial.print("Dzuhur: ");
  Serial.println(jadwal.dzuhur);
  Serial.print("Ashar: ");
  Serial.println(jadwal.ashar);
  Serial.print("Magrib: ");
  Serial.println(jadwal.magrib);
  Serial.print("Isya': ");
  Serial.println(jadwal.isya);

}

//----------------------------------------------------------------------
// LOOP
char bufferText[255];

void loop() {
  server.handleClient();  
  switch(tmploop) {

    case 0 :      
      Utama();
      break;

    case 1 :
      Adzan();
      break;

    case 2 :
      Iqomah();
      break;

    case 3 :
      Sholat();
      break;
      
    case 4 :
      Mati();
      break;

    case 5 :
      //Murottal();
      tmploop=0;
      break; 
  }
  //relay_state=true;
  //tmpJam();
  //Iqomah();
  //Adzan();
  //Sholat();
  //Mati();
  Disp.loop();
  UpdateWaktu();
  alarmSholat();
  alarmMurottal();
  relayLoop();
}
