// ------------------------
// SETUP RTC

RtcDateTime now;

char namaHari[][7] = {"Ahad", "Senin", "Selasa", "Rabu", "Kamis", "Jum'at", "Sabtu", "Ahad"}; // array hari, dihitung mulai dari senin, hari senin angka nya =0,
char namaBulan[][10] = { "Desember", "Januari", "Februari", "Maret", "April", "Mei", "Juni", "Juli", "Agustus", "September", "Oktober", "November", "Desember" };
char hariHijriah[][8] = {"Ahad", "Senin", "Selasa", "Rabu", "Kamis", "Jum'at", "Sabtu", "Ahad"};
char bulanHijriah[][14] = { "Zul hijjah", "Muharram", "Safar", "Rabiul Awal", "Rabiul Akhir", "Jumadil Awal", "Jumadil Akhir", "Rajab", "Sya'ban", "Ramadhan", "Syawal", "Zul Ko'dah", "Zul Hijjah" };

uint8_t rJam;
uint8_t rMen;
uint8_t rDet;
uint8_t rTgl;
uint8_t rHar;
uint8_t rBul;
uint16_t rTah;
uint8_t wHar0;
uint8_t wHar1;
uint8_t wHar2;
int celsius;


//----------------------------------------------------------------------
// I2C_ClearBus menghindari gagal baca RTC (nilai 00 atau 165)

int I2C_ClearBus() {
  
  #if defined(TWCR) && defined(TWEN)
    TWCR &= ~(_BV(TWEN)); //Disable the Atmel 2-Wire interface so we can control the SDA and SCL pins directly
  #endif

  pinMode(SDA, INPUT_PULLUP); // Make SDA (data) and SCL (clock) pins Inputs with pullup.
  pinMode(SCL, INPUT_PULLUP);
  delay(2500);

  boolean SCL_LOW = (digitalRead(SCL) == LOW); // Check is SCL is Low.
  if (SCL_LOW) { //If it is held low Arduno cannot become the I2C master. 
    return 1; //I2C bus error. Could not clear SCL clock line held low
  }

  boolean SDA_LOW = (digitalRead(SDA) == LOW);  // vi. Check SDA input.
  int clockCount = 20; // > 2x9 clock

  while (SDA_LOW && (clockCount > 0)) { //  vii. If SDA is Low,
    clockCount--;
  // Note: I2C bus is open collector so do NOT drive SCL or SDA high.
    pinMode(SCL, INPUT); // release SCL pullup so that when made output it will be LOW
    pinMode(SCL, OUTPUT); // then clock SCL Low
    delayMicroseconds(10); //  for >5uS
    pinMode(SCL, INPUT); // release SCL LOW
    pinMode(SCL, INPUT_PULLUP); // turn on pullup resistors again
    // do not force high as slave may be holding it low for clock stretching.
    delayMicroseconds(10); //  for >5uS
    // The >5uS is so that even the slowest I2C devices are handled.
    SCL_LOW = (digitalRead(SCL) == LOW); // Check if SCL is Low.
    int counter = 20;
    while (SCL_LOW && (counter > 0)) {  //  loop waiting for SCL to become High only wait 2sec.
      counter--;
      delay(100);
      SCL_LOW = (digitalRead(SCL) == LOW);
    }
    if (SCL_LOW) { // still low after 2 sec error
      return 2; // I2C bus error. Could not clear. SCL clock line held low by slave clock stretch for >2sec
    }
    SDA_LOW = (digitalRead(SDA) == LOW); //   and check SDA input again and loop
  }
  if (SDA_LOW) { // still low
    return 3; // I2C bus error. Could not clear. SDA data line held low
  }

  // else pull SDA line low for Start or Repeated Start
  pinMode(SDA, INPUT); // remove pullup.
  pinMode(SDA, OUTPUT);  // and then make it LOW i.e. send an I2C Start or Repeated start control.
  // When there is only one I2C master a Start or Repeat Start has the same function as a Stop and clears the bus.
  /// A Repeat Start is a Start occurring after a Start with no intervening Stop.
  delayMicroseconds(10); // wait >5uS
  pinMode(SDA, INPUT); // remove output low
  pinMode(SDA, INPUT_PULLUP); // and make SDA high i.e. send I2C STOP control.
  delayMicroseconds(10); // x. wait >5uS
  pinMode(SDA, INPUT); // and reset pins as tri-state inputs which is the default state on reset
  pinMode(SCL, INPUT);
  return 0; // all ok
  
}

// MULAI RTC DS3231

void mulaiRTC() {
  int rtn = I2C_ClearBus(); // clear the I2C bus first before calling Wire.begin()
  if (rtn != 0) {
    Serial.println(F("I2C bus error. Could not clear"));
    if (rtn == 1) {
      Serial.println(F("SCL clock line held low"));
    } else if (rtn == 2) {
      Serial.println(F("SCL clock line held low by slave clock stretch"));
    } else if (rtn == 3) {
      Serial.println(F("SDA data line held low"));
    }
  }else { // bus clear, re-enable Wire, now can start Wire Arduino master
    Wire.begin();
  } 
  Rtc.Begin();
  if (!Rtc.GetIsRunning()) {
    Rtc.SetIsRunning(true); 
  } 
  Rtc.Enable32kHzPin(false);
  Rtc.SetSquareWavePin(DS3231SquareWavePin_ModeNone);
  Serial.println("Setup RTC selesai");
}

//------------------------------------------
// Function calculate pasaran jawa
//------------------------------------------

int wetonJawa(uint8_t cor)
{
 RtcDateTime now = Rtc.GetDateTime();
 long tahun=now.Year();
 int bulan;
 int m_kabisat,m_nonkabisat,m_kabisat1,t_kabisat;
 int kabisat=0,nonkabisat=0,kabisat1=0;
 long j_tahun=(tahun-1)*365;
 for(int i=1;i<tahun;i++)
   {
     m_kabisat=i%4;
     if(m_kabisat==0)
     kabisat++;
     m_nonkabisat=i%100;
     if(m_nonkabisat==0)
     nonkabisat++;
     m_kabisat1=i%400;
     if(m_kabisat1==0)
     kabisat1++;
    } 
 switch(now.Month())
 {
   case 1  : bulan = 0;   break; //31
   case 2  : bulan = 31;  break; //28
   case 3  : bulan = 59;  t_kabisat=tahun%4; if(t_kabisat==0) bulan++; break; //31
   case 4  : bulan = 90;  t_kabisat=tahun%4; if(t_kabisat==0) bulan++; break; //30
   case 5  : bulan = 120; t_kabisat=tahun%4; if(t_kabisat==0) bulan++; break; //31
   case 6  : bulan = 151; t_kabisat=tahun%4; if(t_kabisat==0) bulan++; break; //30
   case 7  : bulan = 181; t_kabisat=tahun%4; if(t_kabisat==0) bulan++; break; //31
   case 8  : bulan = 212; t_kabisat=tahun%4; if(t_kabisat==0) bulan++; break; //31
   case 9  : bulan = 243; t_kabisat=tahun%4; if(t_kabisat==0) bulan++; break; //30
   case 10 : bulan = 273; t_kabisat=tahun%4; if(t_kabisat==0) bulan++; break; //31
   case 11 : bulan = 304; t_kabisat=tahun%4; if(t_kabisat==0) bulan++; break; //30
   case 12 : bulan = 334; t_kabisat=tahun%4; if(t_kabisat==0) bulan++; break; //31
 }
 int sekarang = ((j_tahun+(kabisat-nonkabisat)+kabisat1)+bulan+(now.Day()-1))%5;
 if(cor == 0){
  return sekarang;
 }else {
  int besok = sekarang + cor;
  if (besok>4){
    besok = besok-5;
  }  
  return besok;
 }
}

//----------------------------------------------------------------------
// UPDATE WAKTU

void BacaRTC() {
  RtcDateTime now = Rtc.GetDateTime();
  RtcTemperature temp = Rtc.GetTemperature();
  celsius = temp.AsFloatDegC();
  rJam = now.Hour();
  rMen = now.Minute();
  rDet = now.Second();
  rTgl = now.Day();
  rHar = now.DayOfWeek();
  rBul = now.Month();
  rTah = now.Year();
  wHar0 = wetonJawa(0);
  wHar1 = wetonJawa(1);
  wHar2 = wetonJawa(3);
}
