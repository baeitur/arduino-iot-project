/*-------------------------
 
Pengkabelan:

Arduino             Matrix
---------------------------
D11                 DIN
D10                 CLK
D9                  CS(LOAD)

---------------------------*/

#include <Adafruit_GFX.h>
#include <Max72xxPanel.h>
#include "Fonts/Font3x78pt7b.h"

#include <Wire.h>
#include "RTClib.h"

// RTC
RTC_DS1307 rtc;

char bufferText[100];
long clkTime = 0;
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

  //Matrix Display
  matrix.setIntensity(1); // Matrix brightness from 0 to 15
    
  // The initial coordinates of the matrices 8 * 8
  matrix.setRotation(0, 1);        // 1 matrix
  matrix.setRotation(1, 1);        // 2 matrix
  matrix.setRotation(2, 1);        // 3 matrix
  matrix.setRotation(3, 1);        // 4 matrix  
}


void loop() {

  DateTime now = rtc.now();
  sprintf(bufferText,"%02d:%02d:%02d",now.hour(),now.minute(),now.second());
  TeksStatis(bufferText);

  if(millis()-clkTime > 15000) {  //Every 15 seconds, tampilkan tanggal
    sprintf(bufferText,"%s %02d-%02d-%02d",hari[now.dayOfWeek()],now.day(),now.month(),now.year());
    TeksBerjalan (bufferText);
    clkTime = millis();
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
