
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

---------------------------*/

#include <Adafruit_GFX.h>
#include <Max72xxPanel.h>
#include "Fonts/Font3x78pt7b.h"

#define BTN_1 2
#define BTN_2 3
#define BTN_3 4
#define BTN_4 5


// Matrix Display
long period;
int offset=1,refresh=0;
int pinCS = 10; // Connecting the CS pin
int numberOfHorizontalDisplays = 4; // Number of LED matrices by Horizontal
int numberOfVerticalDisplays = 1; // Number of LED matrices per Vertical
Max72xxPanel matrix = Max72xxPanel(pinCS, numberOfHorizontalDisplays, numberOfVerticalDisplays);
int wait = 20; // Running speed
int spacer = 2;
int width = 5 + spacer; // Adjust the distance between the characters


void setup() {
  delay(1000);
  Serial.begin(115200);

  // button
  pinMode(BTN_1, INPUT_PULLUP);
  pinMode(BTN_2, INPUT_PULLUP);
  pinMode(BTN_3, INPUT_PULLUP);
  pinMode(BTN_4, INPUT_PULLUP);

  //Matrix Display
  matrix.setIntensity(1); // Matrix brightness from 0 to 15
    
  // The initial coordinates of the matrices 8 * 8
  matrix.setRotation(0, 1);        // 1 matrix
  matrix.setRotation(1, 1);        // 2 matrix
  matrix.setRotation(2, 1);        // 3 matrix
  matrix.setRotation(3, 1);        // 4 matrix  
}


void loop() {

  TeksBerjalan ("TEST BUTTON");

  int button_1 = digitalRead(BTN_1);
  int button_2 = digitalRead(BTN_2);
  int button_3 = digitalRead(BTN_3);
  int button_4 = digitalRead(BTN_4);

  if(button_1 == 0){
    TeksStatis("BTN-1");
    delay(1000);
  }
  if(button_2 == 0){
    TeksStatis("BTN-2");
    delay(1000);
  }
  if(button_3 == 0){
    TeksStatis("BTN-3");
    delay(1000);
  }
  if(button_4 == 0){
    TeksStatis("BTN-4");
    delay(1000);
  }

}

//==============================
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


// ===============================
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
