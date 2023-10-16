#include<HX711_ADC.h>
#include<EEPROM.h>

#include <Wire.h> 
#include<LiquidCrystal_I2C.h>

#include <DallasTemperature.h>
#include <OneWire.h>

#include <Servo.h>

#define OK 2
#define UP 3
#define DN 4
#define CL 5
#define KATUP 8
#define ELEMEN 17
#define BUZZER 16
#define ON 0
#define OFF 1


const int beratFeCl3_1 = 100;// gram
const int beratFeCl3_2 = 50; // gram
const int beratFeCl3_3 = 25; // gram

const float standartSuhu = 40; // celcius
const int waktuTuang = 10; // detik 
const int waktuGoyang_1 = 20; // menit
const int waktuGoyang_2 = 15; // menit
const int waktuGoyang_3 = 10; // menit
const int derajat = 30; // derajat

int menit=1,detik=0,pos = 0;

int tmpLoop = 0;


Servo myservo;
LiquidCrystal_I2C lcd(0x27,16,2);
char bufferLCD[16];


//variable and function sensor suhu
OneWire wiring(7);
DallasTemperature sensor(&wiring);
 
float suhu() {
  sensor.setResolution(9);
  sensor.requestTemperatures();
  float dataSuhu = sensor.getTempCByIndex(0);
  return dataSuhu;  
}


// variable and function sensor loadcell

const int HX711_dout = A0;
const int HX711_sck = A1;
HX711_ADC LoadCell(HX711_dout, HX711_sck);
const int calVal_eepromAdress = 0;
long t;

void loadCellInit(){
  pinMode(HX711_dout, INPUT);
  delay(10);
  LoadCell.begin();
  float calibrationValue; 
  calibrationValue = 696.0; 
  EEPROM.get(calVal_eepromAdress, calibrationValue);
  long stabilizingtime = 2000; 
  boolean _tare = true; 
  LoadCell.start(stabilizingtime, _tare);
  if (LoadCell.getTareTimeoutFlag()) {
    Serial.println("Timeout, cek kabel MCU>HX711 pastikan sudah tepat");
    while (1);
  }
  else {
    LoadCell.setCalFactor(calibrationValue);
    Serial.println("Startup selesai");
  }
}

int tombol(){
 int ok = digitalRead(OK);
 int up = digitalRead(UP);
 int dn = digitalRead(DN);
 int cl = digitalRead(CL);

 if (ok == 0){
  delay(150);
  Serial.println("ok");
  return 1;
 }else if(up == 0){
  delay(150);
  Serial.println("up");
  return 2;
 }else if(dn == 0){
  delay(150);
  Serial.println("down");
  return 3;
 }else if(cl == 0){
  delay(150);
  Serial.println("cancel");
  return 4;
 }else{
  return 0; 
 }
}

int PCB, opsiPCB = 1;

void pilihPCB(){

  lcd.setCursor(0,0);
  lcd.print("Pilih Ukuran PCB : ");  
  lcd.setCursor(0,1);

  int opsi = tombol();

  if (opsi == 1){
   lcd.clear();
   tmpLoop = 1;
  }else if(opsi == 2){
    opsiPCB++;  
  }else if(opsi == 3){
    opsiPCB--;
  }

  if (opsiPCB > 3) opsiPCB = 1;
  if (opsiPCB < 1) opsiPCB = 3;
  
  if(opsiPCB == 1)
    lcd.print("1. 10x20 cm");  
  else if(opsiPCB == 2)
    lcd.print("2. 10x10 cm");
  else if(opsiPCB == 3)
    lcd.print("3. 10x5 cm");
}

void opsiTimbang(){
  lcd.setCursor(0,0);
  int pcb = opsiPCB; 
  if(pcb == 1){
   sprintf(bufferLCD, "FeCl3 : %d gr",beratFeCl3_1);
  }else if(pcb == 2){
   sprintf(bufferLCD, "FeCl3 : %d gr",beratFeCl3_2);
  }else if(pcb == 3){
   sprintf(bufferLCD, "FeCl3 : %d gr",beratFeCl3_3);
  }
  lcd.print(bufferLCD);

  int opsi = tombol();
  if (opsi == 1){
    lcd.clear();
    tmpLoop = 2;
  }
  if(opsi == 4){
    lcd.clear();
    tmpLoop = 0;  
  }
}
void timbang(){
  opsiTimbang();
  static boolean newDataReady = 0;
  const int serialPrintInterval = 0; 
  if (LoadCell.update()) newDataReady = true;
  if (newDataReady) {
    if (millis() > t + serialPrintInterval) {
      int i = LoadCell.getData();
      if(i<0){
        i=0;
      }
      lcd.setCursor(0,1);
      sprintf(bufferLCD, "Berat : %03d gr",i);
      lcd.print(bufferLCD);
      newDataReady = 0;
      t = millis();
    }
  }
 
}

void pemanas(){

  digitalWrite(ELEMEN, ON);
  float Suhu = suhu();
  if (Suhu > standartSuhu){
   digitalWrite(ELEMEN, OFF);
   digitalWrite(BUZZER, 1);
   digitalWrite(KATUP, ON);
   delay(waktuTuang*1000);
   digitalWrite(ELEMEN, OFF);
   digitalWrite(BUZZER, 0);
   digitalWrite(KATUP, OFF);
   lcd.clear();
   if (opsiPCB == 1) menit = waktuGoyang_1;
   else if (opsiPCB == 2) menit = waktuGoyang_2;
   else if (opsiPCB == 3) menit = waktuGoyang_3;
   tmpLoop = 3;
  }

  static uint32_t pM;
  static uint32_t x;
  if ((millis() - pM) > 1000) {

    pM = millis();
    x++;
  }
  char tmp[5];
  dtostrf(Suhu, -3, 1, tmp);
  int t = x;

  lcd.setCursor(0,0);
  lcd.print("Proses Pemanasan");
  lcd.setCursor(0,1);
  sprintf(bufferLCD," %02d:%02d  %s'C",t/60,t%60,tmp);
  lcd.print(bufferLCD);
  
  int opsi = tombol();
  if (opsi == 1){
    lcd.clear();
    tmpLoop = 3;
  }
  if(opsi == 4){
    lcd.clear();
    tmpLoop = 1;  
  }
}


void goyang(){
  
  static uint32_t pM;
  uint32_t cM = millis();  
  lcd.setCursor(0,0);
  lcd.print(" Proses  Goyang ");
  lcd.setCursor(0,1);
  lcd.print("  Time :  ");
  lcd.setCursor(9,1);
  sprintf(bufferLCD, "%02d:%02d ", menit, detik);
  lcd.print(bufferLCD);
  
  if (detik == 60) {
    detik = 0;
  }

  if (cM - pM >= 1000) {
    pM = cM;
    detik--;
    
    if ((detik % 2) == 0) pos-=derajat;
    else pos+=derajat;
    myservo.write(pos);
    
    if (menit == 0 && detik < 0) {
        digitalWrite(BUZZER, 1);
        delay(2000);
        digitalWrite(BUZZER, 0);
        tmpLoop=0;
      }
    Serial.println(pos);
    
    }

    if (detik < 0) {
      detik = 59;
      menit--;
    }
    
}

void setup() {

  pinMode(OK, INPUT_PULLUP);
  pinMode(UP, INPUT_PULLUP);
  pinMode(DN, INPUT_PULLUP);
  pinMode(CL, INPUT_PULLUP);

  pinMode(KATUP,  OUTPUT);
  pinMode(ELEMEN, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  digitalWrite(KATUP,OFF);
  digitalWrite(ELEMEN,OFF);
  digitalWrite(BUZZER,0);
  
  
  Serial.begin(9600);
  
  lcd.begin();
  
  sensor.begin();

  loadCellInit();

  myservo.attach(9);
  myservo.write(0); 

  lcd.setCursor(0,0);
  
}

void loop() {

  if(tmpLoop == 0)
    pilihPCB();
  else if(tmpLoop == 1){
    timbang();
  }else if(tmpLoop == 2){
    pemanas();      
  }else if(tmpLoop == 3){
    goyang();
  }
  
}
