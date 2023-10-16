#include <DMD3.h>
#include <Wire.h>
#include "RTClib.h"
#include <EEPROM.h>
#include <avr/pgmspace.h>
#include <font/SevSeg2.h>
#include <font/SmallCap4x6.h>
#include <font/DejaVuSansBold9.h>
#include <font/TimesNewRoman12.h>

//#include <font/arab6x13.h>
//#include <font/angka.h>
//#include <font/angka_2.h>
//#include <font/Bernard16.h>
//#include <font/BigBoss.h>
//#include <font/Font5x7.h>
//#include <font/System_Mid5x7.h>

#define BUZZER   A0 

DMD3 display(6,1);
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


char bufferText[65];
char bufferText1[65];
char bufferText2[17];

const char namaMasjid[] PROGMEM = "Selamat Datang di Masjid ";
const char tmpIqomah1[] PROGMEM = "Sebelum Sholat Berjamaah Hp Harap Dimatikan";
const char tmpIqomah2[] PROGMEM = "Lurus dan Rapatnya Shaf Termasuk Kesempurnaan Sholat Berjemaah";

const char jpaing[]  PROGMEM  = "JUM'AT PAHING  IMAM : KH. JAMALUDDIN, BILAL : UST MISNAWI";
const char jpon[]    PROGMEM  = "JUM'AT PON  IMAM : K. HISYAMUDDIN, BILAL : UST KARMAN";
const char jwage[]   PROGMEM  = "JUM'AT WAGE  IMAM : UST H. ABDULLAH, BILAL : UST ROFI'E";
const char jkliwon[] PROGMEM  = "JUM'AT KLIWON  IMAM : UST ABD BARI', BILAL : UST AHMADI";
const char jlegi[]   PROGMEM  = "JUM'AT LEGI  IMAM : KH. RUSDI, BILAL : UST SAMHADI";

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
const char bulanM3[]   PROGMEM  = "Mart";
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

const char *const infoTabel[]    PROGMEM = {namaMasjid,tmpIqomah1,tmpIqomah2};
const char *const jumatTabel[]   PROGMEM = {jpaing,jpon,jwage,jkliwon,jlegi};
const char *const waktuTabel[]   PROGMEM = {dzuhur,ashar,magrib,isya,shubuh};
const char *const namaHari[]     PROGMEM = {hari0,hari1,hari2,hari3,hari4,hari5,hari6};
const char *const bulanMasehi[]  PROGMEM = {bulanM0,bulanM1,bulanM2,bulanM3,bulanM4,bulanM5,bulanM6,bulanM7,bulanM8,bulanM9,bulanM10,bulanM11,bulanM12};
const char *const bulanHijriah[] PROGMEM = {bulanH0,bulanH1,bulanH2,bulanH3,bulanH4,bulanH5,bulanH6,bulanH7,bulanH8,bulanH9,bulanH10,bulanH11,bulanH12};

void scan(){display.refresh();}

void setup() {
  Serial.begin(9600);
  pinMode(BUZZER,OUTPUT);
  Timer1.initialize(2000);
  Timer1.attachInterrupt(scan);
  Timer1.pwm(9,120);
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

void loop() { 
 for(int x=0;x<450;++x){
  DateTime now = rtc.now();
  //di isi tampilAnimasi
  display.setFont(DejaVuSansBold9);
  //strcpy_P(bufferText1,(char *)pgm_read_word(&(infoTabel[0])));
  //sprintf(bufferText,"%s%s",bufferText1,EEPROM.get(51,bufferText2));
  EEPROM.get(51,bufferText1);
  display.drawText(display.width()-x,7,bufferText1);
  jadwalSholat(now.day(),now.month(),x);
  tmpJam1(now.hour(),now.minute(),now.second());
  serialEvent();
  display.swapBuffers();
  display.clear();
  delay(20);
 }
  
 for(int p=0;p<5;++p){
 for(int x=0;x<450;++x){
  DateTime now = rtc.now();
  nowH=toHijri(now.year(),now.month(),now.day(),1);
  //Serial.print(now.dayOfWeek());
  display.setFont(DejaVuSansBold9);
  if(x<225){strcpy_P(bufferText1,  (char *)pgm_read_word(&(namaHari[now.dayOfWeek()])));
            strcpy_P(bufferText2, (char *)pgm_read_word(&(bulanMasehi[now.month()])));
            sprintf (bufferText,"%s %d %s %d",bufferText1,now.day(),bufferText2,now.year());
            display.drawText(display.width()-x,7,bufferText);
           }
  if(x>225){strcpy_P(bufferText1,  (char *)pgm_read_word(&(namaHari[now.dayOfWeek()])));
            strcpy_P(bufferText2, (char *)pgm_read_word(&(bulanHijriah[nowH.hM])));
            sprintf (bufferText,"%s %d %s %dH",bufferText1,nowH.hD,bufferText2,nowH.hY);
            display.drawText(display.width()-(x-240),7,bufferText);
           }
  jadwalSholat(now.day(),now.month(),x);
  tmpJam1(now.hour(),now.minute(),now.second());
  serialEvent();
  display.swapBuffers();
  display.clear();
  delay(20);
 }
 for(int x=0;x<450;++x){
  DateTime now = rtc.now();
  //di isi tampilAnimasi
  int hari = now.dayOfWeek();
  display.setFont(DejaVuSansBold9);
  strcpy_P(bufferText,(char *)pgm_read_word(&(jumatTabel[p])));
  //else      {EEPROM.get(151,bufferText1);sprintf(bufferText,"%s",bufferText1);}
  display.drawText(display.width()-x,7,bufferText);
  jadwalSholat(now.day(),now.month(),x);
  tmpJam1(now.hour(),now.minute(),now.second());
  serialEvent();
  display.swapBuffers();
  display.clear();
  delay(20);
 }
 } 
 /*for(int x=0;x<450;++x){
  DateTime now = rtc.now();
  //di isi tampilAnimasi
  int hari = now.dayOfWeek();
  display.setFont(DejaVuSansBold9);
  if(hari==5)strcpy_P(bufferText,(char *)pgm_read_word(&(jumatTabel[pas])));
  else      {EEPROM.get(251,bufferText1);sprintf(bufferText,"%s",bufferText1);}
  display.drawText(display.width()-x,7,bufferText);
  jadwalSholat(now.day(),now.month(),x);
  tmpJam1(now.hour(),now.minute(),now.second());
  serialEvent();
  display.swapBuffers();
  delay(20);
 }*/
}