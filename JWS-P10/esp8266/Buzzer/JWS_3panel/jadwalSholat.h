//------------------------------------------
// Function Jadwal Sholat
//------------------------------------------

boolean modeMurottal = false;

double times[sizeof(TimeName)/sizeof(char*)];

int8_t  detikiqmh;
int8_t  menitiqmh;
uint8_t tipealarm=1;
uint8_t tmputama;
uint8_t tmploop;

struct Jadwal { 
  int dzuhur;
  int ashar;
  int magrib;
  int isya;
  int imsak;
  int shubuh;
  int shuruq;
  int dhuha;
};

struct Murottal { 
  int dzuhur;
  int jumat;
  int ashar;
  int magrib;
  int isya;
  int tahajjud;
  int shubuh;
};

struct Tarhim { 
  int dzuhur;
  int jumat;
  int ashar;
  int magrib;
  int isya;
  int tahajjud;
  int shubuh;
};

Jadwal jadwal;
Murottal murottal;
Tarhim tarhim;

int selisih(int waktu, int selisih){
  int jam = waktu/100;
  int menit = waktu%100;
  menit+=selisih;
  if(selisih<0){
    if(menit<0){menit+=60;jam-=1;}
  }else {
    if(menit>59){menit-=60;jam+=1;}
  }
  return jam*100+menit;
}

void JadwalSholat() {
  /*
    CALCULATION METHOD
    ------------------
    Jafari,   // Ithna Ashari
    Karachi,  // University of Islamic Sciences, Karachi
    ISNA,     // Islamic Society of North America (ISNA)
    MWL,      // Muslim World League (MWL)
    Makkah,   // Umm al-Qura, Makkah
    Egypt,    // Egyptian General Authority of Survey
    Custom,   // Custom Setting

    JURISTIC
    --------
    Shafii,    // Shafii (standard)
    Hanafi,    // Hanafi

    ADJUSTING METHOD
    ----------------
    None,        // No adjustment
    MidNight,   // middle of night
    OneSeventh, // 1/7th of night
    AngleBased, // angle/60th of night

    TIME IDS
    --------
    Fajr,
    Sunrise,
    Dhuhr,
    Asr,
    Sunset,
    Maghrib,
    Isha
  */ 
 
  int waktuSholat[7];
  set_calc_method(Karachi);
  set_asr_method(Shafii);
  set_high_lats_adjust_method(AngleBased);
  set_fajr_angle(20);
  set_isha_angle(18);
  get_prayer_times(rTah, rBul, rTgl, configjws.latitude, configjws.longitude, configjws.zonawaktu, times);
  for (int i=0;i<sizeof(times)/sizeof(double);i++){
    int hours, minutes;
    get_float_time_parts(times[i], hours, minutes);
    waktuSholat[i] = hours*100+minutes;
  }
  jadwal.dzuhur   = selisih(waktuSholat[2],configjws.ihtid);
  murottal.dzuhur = selisih(jadwal.dzuhur,configmurottal.murottald*-1);
  tarhim.dzuhur   = selisih(jadwal.dzuhur,-5);

  murottal.jumat  = selisih(jadwal.dzuhur,configmurottal.murottalj*-1);
  tarhim.jumat    = selisih(jadwal.dzuhur,-10);
  
  jadwal.ashar    = selisih(waktuSholat[3],configjws.ihtia);
  murottal.ashar  = selisih(jadwal.ashar,configmurottal.murottala*-1);
  tarhim.ashar    = selisih(jadwal.ashar,-5);
  
  jadwal.magrib   = selisih(waktuSholat[5],configjws.ihtim);
  murottal.magrib = selisih(jadwal.magrib,configmurottal.murottalm*-1);
  tarhim.magrib   = selisih(jadwal.magrib,-5);
  
  jadwal.isya     = selisih(waktuSholat[6],configjws.ihtii);
  murottal.isya   = selisih(jadwal.isya,configmurottal.murottali*-1);
  tarhim.isya     = selisih(jadwal.isya,-5);
  
  jadwal.shubuh   = selisih(waktuSholat[0],configjws.ihtis);
  murottal.shubuh = selisih(jadwal.shubuh,configmurottal.murottals*-1);
  tarhim.shubuh   = selisih(jadwal.shubuh,-5);
  
  jadwal.imsak    = selisih(jadwal.shubuh,-10);
  murottal.tahajjud = selisih(jadwal.imsak,configmurottal.murottalt*-1);
  tarhim.tahajjud = selisih(jadwal.imsak,-20);
  
  jadwal.shuruq   = selisih(waktuSholat[1],configjws.ihtiq);
  jadwal.dhuha    = selisih(jadwal.shuruq,20);
}

void setJadwal(int shubuh, int shuruq, int dzuhur, int ashar, int magrib, int isya){
  Serial.println(dzuhur);
  jadwal.dzuhur   = selisih(dzuhur,configjws.ihtid);
  murottal.dzuhur = selisih(jadwal.dzuhur,configmurottal.murottald*-1);
  tarhim.dzuhur   = selisih(jadwal.dzuhur,-5);

  murottal.jumat  = selisih(jadwal.dzuhur,configmurottal.murottalj*-1);
  tarhim.jumat    = selisih(jadwal.dzuhur,-10);
  
  jadwal.ashar    = selisih(ashar,configjws.ihtia);
  murottal.ashar  = selisih(jadwal.ashar,configmurottal.murottala*-1);
  tarhim.ashar    = selisih(jadwal.ashar,-5);
  
  jadwal.magrib   = selisih(magrib,configjws.ihtim);
  murottal.magrib = selisih(jadwal.magrib,configmurottal.murottalm*-1);
  tarhim.magrib   = selisih(jadwal.magrib,-5);
  
  jadwal.isya     = selisih(isya,configjws.ihtii);
  murottal.isya   = selisih(jadwal.isya,configmurottal.murottali*-1);
  tarhim.isya     = selisih(jadwal.isya,-5);
  
  jadwal.shubuh   = selisih(shubuh,configjws.ihtis);
  murottal.shubuh = selisih(jadwal.shubuh,configmurottal.murottals*-1);
  tarhim.shubuh   = selisih(jadwal.shubuh,-5);
  
  jadwal.imsak    = selisih(jadwal.shubuh,-10);
  murottal.tahajjud = selisih(jadwal.imsak,configmurottal.murottalt*-1);
  tarhim.tahajjud = selisih(jadwal.imsak,-20);
  
  jadwal.shuruq   = selisih(shuruq,configjws.ihtiq);
  jadwal.dhuha    = selisih(jadwal.shuruq,20);
}

void jadwalSepanjangMasa()
{ 
 int tgl = rTgl;
 int bln = rBul;
    
 if     (bln==1)
 {
  if     (tgl<=5)           setJadwal(356,517,1133,1457,1749,1903);
  else if(tgl>=6 && tgl<=10)setJadwal(358,520,1136,1501,1752,1907);
  else if(tgl>=11&& tgl<=15)setJadwal(401,522,1138,1502,1754,1908);
  else if(tgl>=16&& tgl<=20)setJadwal(404,525,1140,1503,1755,1908);
  else if(tgl>=21&& tgl<=25)setJadwal(407,527,1141,1503,1756,1909);
  else if(tgl>=26)          setJadwal(409,529,1142,1502,1756,1909);
 }
 else if(bln==2)
 {
  if     (tgl<=5)           setJadwal(416,531,1146,1504,1759,1912);
  else if(tgl>=6 && tgl<=10)setJadwal(417,532,1146,1502,1758,1908);
  else if(tgl>=11&& tgl<=15)setJadwal(419,533,1146,1500,1757,1907);
  else if(tgl>=16&& tgl<=20)setJadwal(421,534,1146,1458,1756,1905);
  else if(tgl>=21&& tgl<=25)setJadwal(422,534,1146,1454,1755,1904);
  else if(tgl>=26)          setJadwal(422,534,1145,1450,1753,1903);  
 }
 else if(bln==3)
 {
  if     (tgl<=5)           setJadwal(422,534,1141,1447,1751,1900);
  else if(tgl>=6 && tgl<=10)setJadwal(422,534,1140,1449,1749,1858);
  else if(tgl>=11&& tgl<=15)setJadwal(423,534,1139,1451,1747,1855);
  else if(tgl>=16&& tgl<=20)setJadwal(422,533,1137,1451,1744,1853);
  else if(tgl>=21&& tgl<=25)setJadwal(422,533,1136,1452,1742,1850);
  else if(tgl>=26)          setJadwal(421,532,1134,1452,1739,1848);
 }
 else if(bln==4)
 {
  if     (tgl<=5)           setJadwal(410,533,1137,1453,1737,1845);
  else if(tgl>=6 && tgl<=10)setJadwal(409,531,1134,1452,1734,1842);
  else if(tgl>=11&& tgl<=15)setJadwal(409,531,1133,1451,1732,1841);
  else if(tgl>=16&& tgl<=20)setJadwal(408,531,1132,1451,1730,1839);
  else if(tgl>=21&& tgl<=25)setJadwal(407,530,1130,1450,1727,1836);
  else if(tgl>=26)          setJadwal(406,530,1129,1449,1725,1835);
 }
 else if(bln==5)
 {
  if     (tgl<=5)           setJadwal(416,530,1129,1449,1725,1835);
  else if(tgl>=6 && tgl<=10)setJadwal(416,531,1129,1449,1724,1834);
  else if(tgl>=11&& tgl<=15)setJadwal(416,531,1128,1448,1712,1834);
  else if(tgl>=16&& tgl<=20)setJadwal(416,532,1129,1449,1721,1834);
  else if(tgl>=21&& tgl<=25)setJadwal(417,533,1129,1449,1721,1834);
  else if(tgl>=26)          setJadwal(418,534,1130,1450,1721,1834);
 }
 else if(bln==6)
 {  
  if     (tgl<=5)           setJadwal(418,535,1130,1450,1721,1835);
  else if(tgl>=6 && tgl<=10)setJadwal(420,537,1131,1452,1721,1836);
  else if(tgl>=11&& tgl<=15)setJadwal(421,538,1132,1452,1722,1837);
  else if(tgl>=16&& tgl<=20)setJadwal(422,539,1133,1453,1723,1838);
  else if(tgl>=21&& tgl<=25)setJadwal(423,540,1134,1454,1724,1839);
  else if(tgl>=26)          setJadwal(424,541,1135,1454,1725,1840);
 } 
 else if(bln==7)
 {
  if     (tgl<=5)           setJadwal(425,542,1136,1458,1726,1840);
  else if(tgl>=6 && tgl<=10)setJadwal(426,543,1137,1458,1728,1841);
  else if(tgl>=11&& tgl<=15)setJadwal(426,543,1138,1458,1729,1842);
  else if(tgl>=16&& tgl<=20)setJadwal(426,543,1138,1458,1730,1842);
  else if(tgl>=21&& tgl<=25)setJadwal(426,542,1138,1458,1731,1843);
  else if(tgl>=26)          setJadwal(426,542,1138,1458,1731,1843);
 }
 else if(bln==8)
 {
  if     (tgl<=5)           setJadwal(426,542,1138,1458,1732,1843);
  else if(tgl>=6 && tgl<=10)setJadwal(426,541,1138,1458,1732,1843);
  else if(tgl>=11&& tgl<=15)setJadwal(425,539,1137,1457,1732,1842);
  else if(tgl>=16&& tgl<=20)setJadwal(423,537,1136,1455,1732,1842);
  else if(tgl>=21&& tgl<=25)setJadwal(422,535,1135,1453,1732,1841);
  else if(tgl>=26)          setJadwal(420,533,1133,1452,1731,1841);
 }
 else if(bln==9)
 {
  if     (tgl<=5)           setJadwal(415,527,1132,1450,1731,1840);
  else if(tgl>=6 && tgl<=10)setJadwal(413,525,1131,1447,1731,1839);
  else if(tgl>=11&& tgl<=15)setJadwal(410,522,1129,1445,1730,1838);
  else if(tgl>=16&& tgl<=20)setJadwal(408,519,1127,1442,1729,1838);
  else if(tgl>=21&& tgl<=25)setJadwal(405,516,1125,1438,1728,1836);
  else if(tgl>=26)          setJadwal(401,514,1124,1431,1727,1836);
 }  
 else if(bln==10)
 {
  if     (tgl<=5)           setJadwal(401,512,1122,1428,1727,1836);
  else if(tgl>=6 && tgl<=10)setJadwal(357,509,1120,1426,1726,1836);
  else if(tgl>=11&& tgl<=15)setJadwal(355,507,1119,1422,1722,1836);
  else if(tgl>=16&& tgl<=20)setJadwal(352,505,1118,1425,1725,1836);
  else if(tgl>=21&& tgl<=25)setJadwal(352,503,1117,1428,1728,1836);
  else if(tgl>=26)          setJadwal(347,502,1116,1431,1731,1838);
 }
 else if(bln==11)
 {
  if     (tgl<=5)           setJadwal(347,501,1116,1434,1728,1840);
  else if(tgl>=6 && tgl<=10)setJadwal(346,501,1117,1435,1730,1843);
  else if(tgl>=11&& tgl<=15)setJadwal(345,501,1117,1437,1731,1844);
  else if(tgl>=16&& tgl<=20)setJadwal(344,501,1118,1440,1733,1846);
  else if(tgl>=21&& tgl<=25)setJadwal(344,501,1120,1443,1735,1849);
  else if(tgl>=26)          setJadwal(344,502,1121,1445,1737,1851);
 }
 else if(bln==12)
 {
  if     (tgl<=5)           setJadwal(345,504,1123,1448,1739,1854);
  else if(tgl>=6 && tgl<=10)setJadwal(346,506,1125,1450,1741,1857);
  else if(tgl>=11&& tgl<=15)setJadwal(347,507,1127,1452,1744,1859);
  else if(tgl>=16&& tgl<=20)setJadwal(348,509,1129,1455,1746,1901);
  else if(tgl>=21&& tgl<=25)setJadwal(351,512,1132,1458,1749,1904);
  else if(tgl>=26)          setJadwal(353,514,1134,1500,1751,1906);
 }
}

// ------------------------------
// UPDATE HISAB TANGGAL

F1kM_Hisab HisabTanggal;

int Hjr_Date, Hjr_Month, Hjr_Year;

void TanggalHijriah() {

  HisabTanggal.setLocationOnEarth(configjws.latitude, configjws.longitude); //Latitude Longitude TANGERANG
  HisabTanggal.setHilalVisibilityFactor(configjws.hilal);
  HisabTanggal.Greg2HijrDate(rTgl,rBul,rTah,Hjr_Date,Hjr_Month,Hjr_Year);

}

//-----------------------------------
// UPDATE WAKTU

void UpdateWaktu() {

  static long pM;
  static uint16_t d;
 
  if (millis() - pM > 1000) {
    d++;
    if (d < 2) {
      BacaRTC();
      //JadwalSholat();
      jadwalSepanjangMasa();
      TanggalHijriah();
    } else if (d < 60) { // Update setiap 60 detik
      rDet++;
      if (rDet > 59) {
        rMen++;
        rDet=0;
        if (rMen > 59) {
          rJam++;
          rMen = 0;
        }
      }
    } else {
      d = 0; 
    }
    pM = millis();    
  }  
}

//-------------------------------------------------
// ALARM SHOLAT BERJALAN SAAT MASUK WAKTU SHOLAT

void alarmSholat() {  
  
  int time_now = rJam*100 + rMen;
  
  if(time_now == jadwal.shubuh and rDet < 3){
    if(modeMurottal == true){
      relay_state=true;
      playMp3(2);  
      tipealarm=1;
      tmploop=1;    
    }else{
      Buzzer();
      tipealarm=1;
      tmploop=1; 
    }
  }

  //dzuhur atau jum'at
  
  if(time_now == jadwal.dzuhur and rDet < 3){
    if(rHar==5){
      tipealarm=3;
      tmploop=1;
    }else if(modeMurottal == true){
      relay_state=true;
      playMp3(2);  
      tipealarm=2;
      tmploop=1;
    }else{
      Buzzer();
      tipealarm=2;
      tmploop=1;
    }
  }

  //ashar
  if(time_now == jadwal.ashar and rDet < 3){
   if(modeMurottal == true){
      relay_state=true;
      playMp3(2);  
      tipealarm=4;
      tmploop=1;  
   }else{
      Buzzer(); 
      tipealarm=4;
      tmploop=1;  
    }
   }

  //magrib
 
  if(time_now == jadwal.magrib and rDet < 3){
    if(modeMurottal == true){
      relay_state=true;
      playMp3(2);  
      tipealarm=5;
      tmploop=1;    
    }else{
      Buzzer();
      tipealarm=5;
      tmploop=1; 
    }
  }
    
  //isya'
  
  if(time_now == jadwal.isya and rDet < 3){
    if(modeMurottal == true){
      relay_state=true;
      playMp3(2);  
      tipealarm=6;
      tmploop=1;    
    }else{
      Buzzer(); 
      tipealarm=6;
      tmploop=1;
    }
  }
}

void alarmMurottal() {  
  
  int time_now = rJam*100 + rMen;

  // tahajjud
  if (configmurottal.murottalt>0){  
   if(time_now == murottal.tahajjud and rDet < 3){
    relay_state=true;
    playMurottal();  
    tmploop=5;
   }else if(time_now == tarhim.tahajjud and rDet < 3){
    relay_state=false;
    stopMp3();
    tmploop=0;   
   }
  }
  
  // shubuh
  if (configmurottal.murottals>0){  
   if(time_now == murottal.shubuh and rDet < 3){
    relay_state=true;
    playMurottal();  
    tmploop=5;
   }else if(time_now == tarhim.shubuh and rDet < 3){
    relay_state=true;
    playMp3(1);   
   }
  }

  //dzuhur atau jum'at
  if(rHar==5){
   if (configmurottal.murottalj>0){  
    if(time_now == murottal.jumat and rDet < 3){
     relay_state=true;
     playMp3(26);  
     tmploop=5;
    }else if(time_now == tarhim.jumat and rDet < 3){
     relay_state=false;
     stopMp3();   
    }
   }
  }else{ 
   if (configmurottal.murottald>0){  
    if(time_now == murottal.dzuhur and rDet < 3){
     relay_state=true;
     playMurottal();  
     tmploop=5;
    }else if(time_now == tarhim.dzuhur and rDet < 3){
     relay_state=true;
     playMp3(1);   
    }
   }
  }

  //ashar
  if (configmurottal.murottala>0){  
   if(time_now == murottal.ashar and rDet < 3){
    relay_state=true;
    playMurottal();  
    tmploop=5;
   }else if(time_now == tarhim.ashar and rDet < 3){
    relay_state=true;
    playMp3(1);   
   }
  }

  //magrib
  if (configmurottal.murottalm>0){  
   if(time_now == murottal.magrib and rDet < 3){
    relay_state=true;
    playMurottal();  
    tmploop=5;
   }else if(time_now == tarhim.magrib and rDet < 3){
    relay_state=true;
    playMp3(1);   
   }
  }
  
  //isya'
  if (configmurottal.murottali>0){  
   if(time_now == murottal.isya and rDet < 3){
    relay_state=true;
    playMurottal();  
    tmploop=5;
   }else if(time_now == tarhim.isya and rDet < 3){
    relay_state=true;
    playMp3(1);   
   }
  }
}
