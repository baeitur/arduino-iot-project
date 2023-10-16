/*-------------------------
Pengkabelan:

Arduino             Matrix
---------------------------
D11                 DIN
D10                 CLK
D9                  CS(LOAD)

Arduino             Button
D2                  BTN 1
D3                  BTN 2
D4                  BTN 3
D5                  BTN 4

Arduino             Relay
D7                  CH 1
D8                  CH 2 

---------------------------*/

#include <Adafruit_GFX.h>
#include <Max72xxPanel.h>
#include "Fonts/Font3x78pt7b.h"

#include <EEPROM.h>

#include <Wire.h>
#include "RTClib.h"

#define BTN_1 2
#define BTN_2 3
#define BTN_3 4
#define BTN_4 5

#define LAMP 7
#define AMPL 8

#define ON 0
#define OFF 1

// RTC
RTC_DS1307 rtc;
DateTime dt;

char bufferText[100];
long clkTime = 0;
boolean stateLoop=0;
char hari[][8] = {"AHAD","SENIN","SELASA","RABU","KAMIS","JUM'AT","SABTU","AHAD"};

// Matrix Display
long period;
int offset=1,refresh=0;
int pinCS = 10; // Connecting the CS pin
int numberOfHorizontalDisplays = 4; // Number of LED matrices by Horizontal
int numberOfVerticalDisplays = 1; // Number of LED matrices per Vertical
Max72xxPanel matrix = Max72xxPanel(pinCS, numberOfHorizontalDisplays, numberOfVerticalDisplays);
int wait = 30; // Running speed
int spacer = 2;
int width = 5 + spacer; // Adjust the distance between the characters

int years   = EEPROM.read(0);
int months  = EEPROM.read(1);
int days    = EEPROM.read(2);
int hours   = EEPROM.read(3);
int minutes = EEPROM.read(4);
int seconds = EEPROM.read(5);
  
DateTime dt_stop(2000+years, months, days, hours, minutes, seconds);

void setup() {
  delay(1000);
  Serial.begin(115200);

  // setup RtC 
  #ifdef AVR
    Wire.begin();
  #else
    Wire1.begin(); // Shield I2C pins connect to alt I2C bus on Arduino Due
  #endif
    rtc.begin();

  //rtc.adjust(DateTime(2022, 6, 5, 21, 38, 0));

  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
  }

  // button
  pinMode(BTN_1, INPUT_PULLUP);
  pinMode(BTN_2, INPUT_PULLUP);
  pinMode(BTN_3, INPUT_PULLUP);
  pinMode(BTN_4, INPUT_PULLUP);

  // Relay
  pinMode(LAMP, OUTPUT);
  pinMode(AMPL, OUTPUT);

  //Matrix Display
  matrix.setIntensity(1); // Matrix brightness from 0 to 15
    
  // The initial coordinates of the matrices 8 * 8
  matrix.setRotation(0, 1);        // 1 matrix
  matrix.setRotation(1, 1);        // 2 matrix
  matrix.setRotation(2, 1);        // 3 matrix
  matrix.setRotation(3, 1);        // 4 matrix  
  
  stateLoop = EEPROM.read(6);  
}


void loop() {

  if(stateLoop == 0){
    digitalWrite(AMPL, OFF);
    digitalWrite(LAMP, ON);
  
    DateTime now = rtc.now();
    sprintf(bufferText,"%02d:%02d:%02d",now.hour(),now.minute(),now.second());
    TeksStatis(bufferText);

    if(millis()-clkTime > 15000) {  //Every 15 seconds, tampilkan tanggal
      sprintf(bufferText,"%s %02d-%02d-%02d",hari[now.dayOfWeek()],now.day(),now.month(),now.year());
      TeksBerjalan (bufferText);
      clkTime = millis();
    }
  }else if(stateLoop == 1){
    Booking();  
  }
  Opsi();  
}

int tombol(){
  int button_1 = digitalRead(BTN_1);
  int button_2 = digitalRead(BTN_2);
  int button_3 = digitalRead(BTN_3);
  int button_4 = digitalRead(BTN_4);

  if(button_1 == 0){
    delay(250);
    Serial.println("btn 1");
    return 1;
  }
  else if(button_2 == 0){
    delay(250);
    Serial.println("btn 2");
    return 2;
  }
  else if(button_3 == 0){
    delay(250);
    Serial.println("btn 3");
    return 3;
  }
  else if(button_4 == 0){
    delay(250);
    Serial.println("btn 4");
    return 4;
  }
  else {
    return 0;  
  }
}

void simpan(){
  EEPROM.write(0, dt_stop.year()-2000); //addres year 
  EEPROM.write(1, dt_stop.month());     //addres month
  EEPROM.write(2, dt_stop.day());       //addres day
  EEPROM.write(3, dt_stop.hour());      //addres hour
  EEPROM.write(4, dt_stop.minute());    //addres minute
  EEPROM.write(5, dt_stop.second());    //addres second
  EEPROM.write(6, 1);                   //stateLoop
}

void Opsi(){
  int opsi = tombol();
  if(opsi == 1){
    // pesan 2 jam
    stateLoop = 1;
    DateTime now = rtc.now();
    dt_stop = now + TimeSpan(0, 1, 0, 0);
    simpan(); 
  }else if(opsi == 2){
    // pesan 2 jam
    stateLoop = 1;
    DateTime now = rtc.now();
    dt_stop = now + TimeSpan(0, 2, 0, 0);
    simpan();
  }else if(opsi == 3){
    // pesan 2 jam
    stateLoop = 1;
    DateTime now = rtc.now();
    dt_stop = now + TimeSpan(0, 3, 0, 0);
    simpan();
  }else if(opsi == 4){
    stateLoop = 0;
    EEPROM.write(6, 0);
    
  }
  
}

void Booking(){
  
  DateTime now = rtc.now();

  TimeSpan count = dt_stop - now;
  
  sprintf(bufferText,"%02d:%02d:%02d",count.hours(),count.minutes(),count.seconds());
  TeksStatis(bufferText);
  if (count.hours() == 0 && count.minutes() == 5 && count.seconds() <= 5){
   digitalWrite(LAMP, OFF);
   digitalWrite(AMPL, ON);
  }else{
   digitalWrite(LAMP, ON);
   digitalWrite(AMPL, ON);
  }
  if (count.hours() <= 0 && count.minutes() <= 0 && count.seconds() <= 0){
   digitalWrite(AMPL, OFF);
   digitalWrite(LAMP, ON);
   stateLoop = 0;
  }
}

//-----------------------------------------------------
//Membuat Format Teks Statis

void TeksStatis(String text){

  matrix.fillScreen(LOW);

  // Setting font untuk jam
  spacer = 2;
  width = 3 + spacer;
  matrix.setFont(&Font3x78pt7b);

  for (int i=0; i<text.length(); i++){
  
  int letter =(matrix.width())- i * (width-1);
  int x = (matrix.width() +0) -letter;
  int y = 11; // Set posisi vertikal font kadang suka terlalu atas atau terlalu bawah
  matrix.drawChar(x, y, text[i], HIGH, LOW, 1);
    
  matrix.write(); // Tampilkan

  }

}


// =======================================================================
void TeksBerjalan (String text){

  // Setting font untuk jam

  spacer = 2;
  width = 5 + spacer;
  matrix.setFont(); // Reset font to default
  
  for ( int i = 0 ; i < width * text.length() + matrix.width() - 1 - spacer; i++ ) {
    if (refresh==1) i=0;
    refresh=0;
    matrix.fillScreen(LOW);
    int letter = i / width;
    int x = (matrix.width() - 1) - i % width;
    int y = (matrix.height() - 8) / 2; // Center text on Vertical

    while ( x + width - spacer >= 0 && letter >= 0 ) {
      if ( letter < text.length() ) {
        matrix.drawChar(x, y, text[letter], HIGH, LOW, 1);
      }
      letter--;
      x -= width;
    }
  matrix.write(); // Display
  delay(wait);
  }
}
