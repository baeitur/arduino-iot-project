#include <Wire.h>
#include <Adafruit_INA219.h>
#include <LiquidCrystal_I2C.h>

//buffer text for display
char buffer_text[140];
char v1[3], a1[3], p1[3], v2[3], a2[3], p2[3], bat[3], ane[3];

// vareable and function Sensor INA 219

Adafruit_INA219 ina219_1 (0x41);
Adafruit_INA219 ina219_2 (0x44);

float voltage_1 = 0;
float current_1 = 0;
float power_1   = 0;

float voltage_2 = 0;
float current_2 = 0;
float power_2   = 0;


// variable sensor tegangan

const int voltageSensor = A2;
float vOUT = 0.0;
float vIN = 0.0;
float R1 = 30000.0;
float R2 = 7500.0;
int value = 0;

void battery(){
  value = analogRead(voltageSensor);
  vOUT = (value * 5.0) / 1024.0;
  vIN = vOUT / (R2/(R1+R2));  
}

// vareable and function Anemometer

# define windPin 2            // pin conection
const float pi  = 3.14159265; // pi number
int period      = 10000;      // Measurement period (miliseconds)
int delaytime   = 10000;      // Time between samples (miliseconds)
int radio       = 80;         // Distance from center windmill to outer cup (mm)
int jml_celah   = 18;         // jumlah celah sensor

unsigned int Sample  = 0;     // Sample number
unsigned int counter = 0;     // B/W counter for sensor
unsigned int RPM     = 0;     // Revolutions per minute
float speedwind      = 0;     // Wind speed (m/s)

void windvelocity() {
  speedwind = 0;
  counter = 0;
  attachInterrupt(0, addcount, CHANGE);
  unsigned long millis();
  long startTime = millis();
  while (millis() < startTime + period) {}
  detachInterrupt(1);
}

void RPMcalc() {
  RPM = ((counter / jml_celah) * 60) / (period / 1000); // Calculate revolutions per minute (RPM)
}

void WindSpeed() {
  speedwind = ((2 * pi * radio * RPM) / 60) / 1000; // Calculate wind speed on m/s
}

void addcount() {
  counter++;
}


// variable and function LCD

LiquidCrystal_I2C lcd(0x27, 20, 4);

int Li          = 21;
int Lii         = 1;
int Ri          = -1;
int Rii         = -1;

String Scroll_LCD_Left(String StrDisplay) {
  String result;
  String StrProcess = "                " + StrDisplay + "                ";
  result = StrProcess.substring(Li, Lii);
  Li++;
  Lii++;
  if (Li > StrProcess.length()) {
    Li = 20;
    Lii = 0;
  }
  return result;
}

void Clear_Scroll_LCD_Left() {
  Li = 20;
  Lii = 0;
}

void tmpLCD() {
  static uint32_t pM;
  static uint32_t x;
  int fullScroll = 140;

  if ((millis() - pM) > 300) {

    pM = millis();

    lcd.setCursor(5, 0);
    lcd.print("Explore IoT");

    lcd.setCursor(0, 1);
    lcd.print("--------------------");

    dtostrf(vIN,  -3, 1, bat);
    lcd.setCursor(0, 2);
    sprintf(buffer_text, "Bat:%sV", bat);
    lcd.print(buffer_text);

    dtostrf(speedwind, -3, 1, ane);
    lcd.setCursor(10, 2);
    sprintf(buffer_text, "Ane:%smps", ane);
    lcd.print(buffer_text);

    dtostrf(voltage_1, -3, 1, v1);
    dtostrf(current_1, -3, 1, a1);
    dtostrf(power_1,  -3, 1, p1);
    dtostrf(voltage_2, -3, 1, v2);
    dtostrf(current_2, -3, 1, a2);
    dtostrf(power_2,  -3, 1, p2);

    lcd.setCursor(0, 3);
    sprintf(buffer_text, "Ina1 -> Voltage : %sV Current : %smA Power : %smW                    Ina2 -> Voltage : %sV Current : %smA Power : %smW                 ", v1, a1, p1, v2, a2, p2);
    lcd.print(Scroll_LCD_Left(buffer_text));

    if (x < fullScroll) {
      ++x;
    } else {
      x = 0;
      bacaData();
      sendData();
      return ;
    }

  }
}


void setup(void) {

  // Serial Comunication
  Serial.begin(115200);

  // Setup LCD
  lcd.begin(20, 4);
  lcd.backlight();
  lcd.setCursor(2,1);
  lcd.print("M. TAUFIKURRAHMAN");
  lcd.setCursor(3,2);
  lcd.print("175100200111018");
  delay(5000);
  lcd.clear();

  // Sensor INA 219
  if (! ina219_1.begin()) {
    lcd.setCursor(0, 0);
    lcd.println("Failed find INA1");
    while (1) {
      delay(10);
    }
  }
  if (! ina219_2.begin()) {
    lcd.setCursor(0, 0);
    lcd.println("Failed find INA2");
    while (1) {
      delay(10);
    }
  }

  // reading data.
  bacaData();

  // Setup anemomiter
  pinMode(windPin, INPUT);
  digitalWrite(windPin, HIGH);

  //reset
  lcd.clear();

}

void bacaData() {
  lcd.setCursor(0, 2);
  lcd.print("   reading data..!  ");
  
  voltage_1 = ina219_1.getBusVoltage_V();
  current_1 = ina219_1.getCurrent_mA();
  power_1   = ina219_1.getPower_mW();

  voltage_2 = ina219_2.getBusVoltage_V();
  current_2 = ina219_2.getCurrent_mA();
  power_2   = ina219_2.getPower_mW();

  battery();

  windvelocity();
  RPMcalc();
  WindSpeed();
}

void sendData() {
  lcd.setCursor(0, 2);
  lcd.print("   sending data..!  ");
  dtostrf(vIN,  -3, 1, bat);
  dtostrf(speedwind, -3, 1, ane);
  dtostrf(voltage_1, -3, 1, v1);
  dtostrf(current_1, -3, 1, a1);
  dtostrf(power_1,  -3, 1, p1);
  dtostrf(voltage_2, -3, 1, v2);
  dtostrf(current_2, -3, 1, a2);
  dtostrf(power_2,  -3, 1, p2);
  sprintf(buffer_text, "ina1/%s/%s/%s\n", v1, a1, p1);
  Serial.print(buffer_text);
  delay(1000);
  sprintf(buffer_text, "ina2/%s/%s/%s\n", v2, a2, p2);
  Serial.print(buffer_text);
  delay(1000);
  sprintf(buffer_text, "anemo/%s\n", ane);
  Serial.print(buffer_text);
  delay(1000);
  sprintf(buffer_text, "bat/%s\n", bat);
  Serial.print(buffer_text);
  lcd.clear();
}


void loop(void) {
  tmpLCD();

}
