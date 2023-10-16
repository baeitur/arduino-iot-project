#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup()
{
	// initialize the LCD
  pinMode(2,INPUT_PULLUP);
  pinMode(3,INPUT_PULLUP);
  pinMode(4,INPUT_PULLUP);
  pinMode(5,INPUT_PULLUP);
	lcd.begin();

	// Turn on the blacklight and print a message.
	lcd.backlight();
	
}

void loop()
{
	// Do nothing here...
 int btn1 = digitalRead(2);
 int btn2 = digitalRead(3);
 int btn3 = digitalRead(4);
 int btn4 = digitalRead(5);

 if(btn1==0){
  lcd.setCursor(0,0);
  lcd.print("tombol 1");
 }else if(btn2==0){
  lcd.setCursor(0,0);
  lcd.print("tombol 2");
 }else if(btn3==0){
  lcd.setCursor(0,0);
  lcd.print("tombol 3");
 }else if(btn4==0){
  lcd.setCursor(0,0);
  lcd.print("tombol 4");
 }
 
}
