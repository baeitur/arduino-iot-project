#include <DMD3.h>
#include <Wire.h>
#include "RTClib.h"
#include <EEPROM.h>
#include <avr/pgmspace.h>
#include <font/SevSeg2.h>
#include <font/SmallCap4x6.h>
#include <font/DejaVuSansBold9.h>
#include <font/TimesNewRoman12.h>
#include <font/ElektronMart6x8.h>


#define BUZZER A0

DMD3 display(5,1);
RTC_DS1307 rtc;

byte lamaIqomahDzuhur;
byte lamaIqomahAshar;
byte lamaIqomahMagrib;
byte lamaIqomahIsya;
byte lamaIqomahShubuh;

typedef struct  
  { 
    uint8_t   hD;
    uint8_t   hM;
    uint16_t  hY;
  } hijir_date;
  
// Variable by Structure     
int8_t          Prm;
hijir_date      nowH;  


char bufferInfo[80];

const char namaMasjid[] PROGMEM = "MASJID DARUSSALAM KARANG TANDES DESA WARU BARAT KEC. WARU KAB. PAMEKASAN";
const char tmpIqomah[] PROGMEM = "LURUS DAN RAPATNYA SHAF TERMASUK KESEMPURNAAN SHOLAT BERJEMAAH";
const char imam1[] PROGMEM = "SHUBUH : K. TAYYIB/UST MISNALI DZUHUR : UST NURDI/IDI ASHAR : UST RUSDI/H. ALI";
const char imam2[] PROGMEM = "MAGRIB : K. TAYYIB/UST MISNALI ISYA' : SAMAUNI/H. ALI";

const char jpaing[]  PROGMEM  = "JUM'AT PAHING  KHOTIB : UST RUSDI BILAL : UST NURDI";
const char jpon[]    PROGMEM  = "JUM'AT PON  KHOTIB : UST ROSYIDI, BILAL : ROMLI";
const char jwage[]   PROGMEM  = "JUM'AT WAGE  KHOTIB : UST H. MUNIRI, BILAL : HOLLI";
const char jkliwon[] PROGMEM  = "JUM'AT KLIWON  KHOTIB : H. ALI, BILAL : HOLLI";
const char jlegi[]   PROGMEM  = "JUM'AT LEGI  KHOTIB : K. ABD GAFUR, BILAL : SAMAUNI";

const char dzuhur[]  PROGMEM  = "Dzuhur";
const char ashar[]   PROGMEM  = "Ashar";
const char magrib[]  PROGMEM  = "Magrib";
const char isya[]    PROGMEM  = "Isya'";
const char shubuh[]  PROGMEM  = "Shubuh";

const char hari0[]   PROGMEM  = "Ahad";
const char hari1[]   PROGMEM  = "Senin";
const char hari2[]   PROGMEM  = "Selasa";
const char hari3[]   PROGMEM  = "Rabu";
const char hari4[]   PROGMEM  = "Kamis";
const char hari5[]   PROGMEM  = "Jum'at";
const char hari6[]   PROGMEM  = "Sabtu";

const char bulanM0[]   PROGMEM  = "\0";
const char bulanM1[]   PROGMEM  = "Januari";
const char bulanM2[]   PROGMEM  = "Februari";
const char bulanM3[]   PROGMEM  = "Maret";
const char bulanM4[]   PROGMEM  = "April";
const char bulanM5[]   PROGMEM  = "Mei";
const char bulanM6[]   PROGMEM  = "Juni";
const char bulanM7[]   PROGMEM  = "Juli";
const char bulanM8[]   PROGMEM  = "Agustus";
const char bulanM9[]   PROGMEM  = "September";
const char bulanM10[]  PROGMEM  = "Oktober";
const char bulanM11[]  PROGMEM  = "November";
const char bulanM12[]  PROGMEM  = "Desember";

const char bulanH0[]   PROGMEM  = "\0";
const char bulanH1[]   PROGMEM  = "Muharram";
const char bulanH2[]   PROGMEM  = "Shafar";
const char bulanH3[]   PROGMEM  = "Rabi'ul Awal";
const char bulanH4[]   PROGMEM  = "Rabi'ul Akhir";
const char bulanH5[]   PROGMEM  = "Jumadil Awal";
const char bulanH6[]   PROGMEM  = "Jumadil Akhir";
const char bulanH7[]   PROGMEM  = "Rajab";
const char bulanH8[]   PROGMEM  = "Sha'ban";
const char bulanH9[]   PROGMEM  = "Ramadhan";
const char bulanH10[]  PROGMEM  = "Shawwal";
const char bulanH11[]  PROGMEM  = "Dhul Qa'dah";
const char bulanH12[]  PROGMEM  = "Dhul Hijjah";

const char *const infoTabel[]    PROGMEM = {namaMasjid,tmpIqomah,imam1,imam2};
const char *const jumatTabel[]   PROGMEM = {jpaing,jpon,jwage,jkliwon,jlegi};
const char *const waktuTabel[]   PROGMEM = {dzuhur,ashar,magrib,isya,shubuh};
const char *const namaHari[]     PROGMEM = {hari0,hari1,hari2,hari3,hari4,hari5,hari6};
const char *const bulanMasehi[]  PROGMEM = {bulanM0,bulanM1,bulanM2,bulanM3,bulanM4,bulanM5,bulanM6,bulanM7,bulanM8,bulanM9,bulanM10,bulanM11,bulanM12};
const char *const bulanHijriah[] PROGMEM = {bulanH0,bulanH1,bulanH2,bulanH3,bulanH4,bulanH5,bulanH6,bulanH7,bulanH8,bulanH9,bulanH10,bulanH11,bulanH12};

void scan(){display.refresh();}

void setup() {
  pinMode(BUZZER,OUTPUT);
  digitalWrite(BUZZER,1);
  Serial.begin(9600);
  Timer1.initialize(2000);
  Timer1.attachInterrupt(scan);
  Timer1.pwm(9,100);
  display.setDoubleBuffer(1);
  Wire.begin();
  rtc.begin();
  lamaIqomahDzuhur=EEPROM.read(1);
  lamaIqomahAshar =EEPROM.read(2);
  lamaIqomahMagrib=EEPROM.read(3);
  lamaIqomahIsya  =EEPROM.read(4);
  lamaIqomahShubuh=EEPROM.read(5);
  //setDefault();
}

int next=1;
boolean nextStep;

void loop() {
 //DateTime now = rtc.now();
 //tmpJam1(now.hour(),now.minute(),now.second());
 //display.swapBuffers();
 char bufferText1[15];
 char bufferText2[15];
 while(next==1){
   strcpy_P(bufferInfo,(char *)pgm_read_word(&(infoTabel[0]))); 
   tmpMasjid(bufferInfo,1);
   next++;
  }
  while(next==2){
   DateTime now = rtc.now();
   strcpy_P(bufferText1, (char *)pgm_read_word(&(namaHari[now.dayOfWeek()])));
   strcpy_P(bufferText2, (char *)pgm_read_word(&(bulanMasehi[now.month()])));
   sprintf (bufferInfo,"%s %d %s %d",bufferText1,now.day(),bufferText2,now.year());
   tmpInfo(bufferInfo);
   jadwalSholat();
  }
  while(next==3){
   DateTime now = rtc.now();
   nowH=toHijri(now.year(),now.month(),now.day(),1);
   strcpy_P(bufferText1,  (char *)pgm_read_word(&(namaHari[now.dayOfWeek()])));
   strcpy_P(bufferText2, (char *)pgm_read_word(&(bulanHijriah[nowH.hM])));
   sprintf (bufferInfo,"%s %d %s %dH",bufferText1,nowH.hD,bufferText2,nowH.hY);
   tmpInfo(bufferInfo);
   jadwalSholat();
  }
  while(next==4){
    strcpy_P(bufferInfo,(char *)pgm_read_word(&(infoTabel[2])));
    tmpInfo(bufferInfo);
    jadwalSholat();
   }
  while(next==5){
    strcpy_P(bufferInfo,(char *)pgm_read_word(&(infoTabel[3])));
    tmpInfo(bufferInfo);
    jadwalSholat();
   }
  int weton=wetonJawa();
  int nextWeton=weton+1; if(nextWeton>4)nextWeton=0;
  while(next==6){
   DateTime now = rtc.now();
   if(now.dayOfWeek()==4 && now.hour()>16)
   {
    strcpy_P(bufferInfo,(char *)pgm_read_word(&(jumatTabel[nextWeton]))); 
    tmpInfo(bufferInfo);
    jadwalSholat();
    }
   else if(now.dayOfWeek()==5)
   {
    strcpy_P(bufferInfo,(char *)pgm_read_word(&(jumatTabel[weton])));
    tmpInfo(bufferInfo);
    jadwalSholat();
   }else{
    EEPROM.get(151,bufferInfo);
    tmpInfo(bufferInfo);
    jadwalSholat();
   }
  }
  while(next==7){
   DateTime now = rtc.now();
   if(now.dayOfWeek()==4 && now.hour()>16)
   {
    strcpy_P(bufferInfo,(char *)pgm_read_word(&(jumatTabel[nextWeton]))); 
    tmpInfo(bufferInfo);
    jadwalSholat();
    }
   else if(now.dayOfWeek()==5)
   {
    strcpy_P(bufferInfo,(char *)pgm_read_word(&(jumatTabel[weton])));
    tmpInfo(bufferInfo);
    jadwalSholat();
   }else{
    EEPROM.get(251,bufferInfo);
    tmpInfo(bufferInfo);
    jadwalSholat();
   }
  }
 //EEPROM.get(151,bufferInfo);
 //tmpInfo(bufferInfo);
 //jadwalSholat();
 //strcpy_P(bufferInfo,(char *)pgm_read_word(&(infoTabel[0]))); 
 //tmpMasjid(bufferInfo,1);
 //infoIqomah();
}
