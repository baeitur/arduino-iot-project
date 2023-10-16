/*
  Sensor PH   Arduino
    v+          5v
    G           GND
    Po          A0  
*/

#include <SoftwareSerial.h>

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#include <DallasTemperature.h>
#include <OneWire.h>

SoftwareSerial mySerial(2, 3); // RX, TX

LiquidCrystal_I2C lcd(0x27, 16, 2);

OneWire wiring(7);
DallasTemperature sensor(&wiring);

const int phSensorPin  = A2; 
float kalibrasi = 0.165;
float TeganganPh;

float getPH(){
  TeganganPh = 0;
  for(int i=0; i<800; i++){
   TeganganPh += ((float)analogRead(phSensorPin)/1023)*5.0;
  }
  TeganganPh = TeganganPh/800;
  // rumus menentukan nilai pH cairan    
  float nilaiPh = 6.86+((2.68 - TeganganPh)/kalibrasi);  
  return nilaiPh;
}

float getSuhu(){
  sensor.requestTemperatures();
  float dataSuhu = sensor.getTempCByIndex(0);
  return dataSuhu;
}

int turbySensorPin = A1;
float volt;
float ntu;

float round_to_dp( float in_value, int decimal_place )
{
  float multiplier = powf( 10.0f, decimal_place );
  in_value = roundf( in_value * multiplier ) / multiplier;
  return in_value;
}

float getTurby(){
  volt = 0;
  for(int i=0; i<800; i++){
   volt += ((float)analogRead(turbySensorPin)/1023)*5;
  }
  volt = volt/800;
  volt = round_to_dp(volt,2);
  if(volt < 2.5){
   ntu = 3000;
  }else{
   ntu = -1120.4*square(volt)+5742.3*volt-4353.8; 
  }
  return ntu;
}

void setup() 
{
  // sensor suhu
  sensor.begin();

  //serial
  Serial.begin(9600);
  mySerial.begin(9600);

  //sensor PH
  pinMode (phSensorPin, INPUT);

  //sensor turbydity
  pinMode (turbySensorPin, INPUT);

  //buzzer
  pinMode(11, OUTPUT);
  digitalWrite(11,1);

  // lcd test
  lcd.begin();
  lcd.setCursor(0, 0);
  lcd.print("   Welcome...");
  delay(2000);
  lcd.clear();
}

char PH[5],SUHU[5],TURBY[8];

void loop() {
  float ph = getPH();
  float suhu = getSuhu();
  float turby = getTurby();

  dtostrf(ph,  -3, 1, PH);
  dtostrf(suhu,  -3, 1, SUHU);
  dtostrf(turby,  -3, 1, TURBY);

  char buffer[20];
  sprintf(buffer, "*%s %s %s#",PH,SUHU,TURBY);

  lcd.setCursor(0, 0);
  lcd.print("PH: ");
  lcd.setCursor(3, 0);
  lcd.print(ph);
  
  lcd.setCursor(8, 0);
  lcd.print("TMP: ");
  lcd.setCursor(12, 0);
  lcd.print(suhu);
  
  lcd.setCursor(1, 1);
  lcd.print("TURBI : ");
  lcd.setCursor(9, 1);
  lcd.print(turby);
  
  static uint32_t pM;  
  if((millis() - pM) > 1000) { 
    pM = millis();
    mySerial.print(buffer);
    Serial.print(buffer);
  }

  if(suhu > 30)
    digitalWrite(11,0);
  else if(suhu < 25)
    digitalWrite(11,0);
  else 
    digitalWrite(11,1);
 
}
