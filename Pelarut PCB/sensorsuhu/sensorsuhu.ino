#include <DallasTemperature.h>
#include <OneWire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);

OneWire wiring(7);
DallasTemperature sensor(&wiring);

void setup() {
  lcd.begin();
  sensor.begin();
}

void loop() {
  sensor.setResolution(9);
  sensor.requestTemperatures();
  float dataSuhu = sensor.getTempCByIndex(0);
 lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print("Temperature");

  lcd.setCursor(5, 1);
  lcd.print(dataSuhu, 1);
  lcd.print((char)223);
  lcd.print("C");
  delay(1000);
}
