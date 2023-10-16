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
  if     (tgl<=4)           setJadwal(352,512,1134,1500,1750,1904);
  else if(tgl>=5 && tgl<=7) setJadwal(354,514,1135,1501,1751,1905);
  else if(tgl>=8 && tgl<=10)setJadwal(356,516,1137,1501,1752,1906);
  else if(tgl>=11&& tgl<=14)setJadwal(358,517,1138,1501,1753,1907);
  else if(tgl>=15&& tgl<=18)setJadwal(400,519,1139,1501,1754,1908);
  else if(tgl>=19&& tgl<=21)setJadwal(402,520,1140,1501,1754,1908);
  else if(tgl>=22&& tgl<=26)setJadwal(404,522,1141,1501,1755,1908);
  else if(tgl>=26)          setJadwal(406,524,1141,1501,1755,1908);
 }
 else if(bln==2)
 {
  if     (tgl<=4)           setJadwal(408,525,1142,1501,1755,1907);
  else if(tgl>=5 && tgl<=7) setJadwal(410,526,1142,1501,1755,1906);
  else if(tgl>=8 && tgl<=11)setJadwal(411,527,1142,1500,1754,1905);
  else if(tgl>=12&& tgl<=14)setJadwal(412,527,1142,1458,1753,1904);
  else if(tgl>=15&& tgl<=18)setJadwal(413,528,1142,1456,1753,1903);
  else if(tgl>=19&& tgl<=22)setJadwal(414,528,1142,1454,1752,1902);
  else if(tgl>=23&& tgl<=25)setJadwal(414,528,1142,1452,1751,1900);
  else if(tgl>=26)          setJadwal(415,528,1141,1450,1750,1859);  
 }
 else if(bln==3)
 {
  if     (tgl<=4)           setJadwal(415,525,1141,1447,1749,1856);
  else if(tgl>=5 && tgl<=9) setJadwal(415,526,1140,1446,1748,1854);
  else if(tgl>=10&& tgl<=13)setJadwal(415,527,1139,1444,1746,1852);
  else if(tgl>=14&& tgl<=17)setJadwal(415,527,1138,1445,1744,1850);
  else if(tgl>=18&& tgl<=21)setJadwal(415,528,1137,1447,1742,1848);
  else if(tgl>=22&& tgl<=24)setJadwal(414,528,1136,1447,1740,1846);
  else if(tgl>=25&& tgl<=28)setJadwal(414,528,1135,1448,1739,1845);
  else if(tgl>=29)          setJadwal(414,528,1134,1448,1737,1843);
 }
 else if(bln==4)
 {
  if     (tgl<=3)           setJadwal(413,526,1133,1448,1734,1843);
  else if(tgl>=4 && tgl<=7) setJadwal(413,526,1132,1448,1733,1841);
  else if(tgl>=8 && tgl<=11)setJadwal(412,525,1131,1448,1732,1839);
  else if(tgl>=12&& tgl<=16)setJadwal(412,525,1130,1448,1731,1837);
  else if(tgl>=17&& tgl<=20)setJadwal(411,525,1129,1448,1729,1836);
  else if(tgl>=21&& tgl<=24)setJadwal(411,525,1127,1447,1725,1835);
  else if(tgl>=25&& tgl<=28)setJadwal(410,526,1127,1447,1725,1834);
  else if(tgl>=29)          setJadwal(410,526,1127,1447,1725,1833);
 }
 else if(bln==5)
 {
  if     (tgl<=4)           setJadwal(410,525,1126,1448,1723,1832);
  else if(tgl>=6 && tgl<=7) setJadwal(409,525,1125,1447,1721,1832);
  else if(tgl>=8 && tgl<=11)setJadwal(409,525,1125,1446,1720,1831);
  else if(tgl>=12&& tgl<=16)setJadwal(409,526,1125,1446,1720,1831);
  else if(tgl>=17&& tgl<=20)setJadwal(410,527,1125,1446,1720,1831);
  else if(tgl>=21&& tgl<=24)setJadwal(410,527,1126,1447,1718,1831);
  else if(tgl>=25&& tgl<=28)setJadwal(410,528,1126,1447,1718,1831);
  else if(tgl>=29)          setJadwal(411,529,1126,1457,1718,1832);
 }
 else if(bln==6)
 {  
  if     (tgl<=3)           setJadwal(411,529,1128,1449,1720,1832);
  else if(tgl>=6 && tgl<=7) setJadwal(412,530,1128,1449,1720,1833);
  else if(tgl>=8 && tgl<=10)setJadwal(412,531,1128,1449,1720,1833);
  else if(tgl>=11&& tgl<=14)setJadwal(413,532,1128,1449,1720,1834);
  else if(tgl>=15&& tgl<=19)setJadwal(414,533,1130,1451,1722,1835);
  else if(tgl>=20&& tgl<=24)setJadwal(415,534,1131,1452,1723,1836);
  else if(tgl>=25&& tgl<=28)setJadwal(416,535,1132,1453,1724,1837);
  else if(tgl>=29)          setJadwal(417,535,1133,1454,1725,1848);
 } 
 else if(bln==7)
 {
  if     (tgl<=3)           setJadwal(417,536,1133,1454,1725,1838);
  else if(tgl>=4 && tgl<=8) setJadwal(418,537,1134,1455,1726,1839);
  else if(tgl>=9 && tgl<=13)setJadwal(419,537,1134,1456,1727,1840);
  else if(tgl>=14&& tgl<=16)setJadwal(419,537,1135,1456,1728,1840);
  else if(tgl>=16&& tgl<=20)setJadwal(419,537,1135,1456,1728,1841);
  else if(tgl>=21&& tgl<=25)setJadwal(420,537,1135,1456,1728,1841);
  else if(tgl>=26&& tgl<=28)setJadwal(420,536,1136,1456,1730,1841);
  else if(tgl>=29)          setJadwal(419,536,1136,1456,1730,1841);
 }
 else if(bln==8)
 {
  if     (tgl<=5)           setJadwal(419,535,1134,1456,1730,1841);
  else if(tgl>=6 && tgl<=9) setJadwal(419,534,1134,1456,1730,1841);
  else if(tgl>=10&& tgl<=13)setJadwal(418,533,1134,1456,1730,1840);
  else if(tgl>=14&& tgl<=16)setJadwal(417,532,1134,1456,1730,1840);
  else if(tgl>=17&& tgl<=20)setJadwal(416,530,1133,1454,1729,1839);
  else if(tgl>=21&& tgl<=25)setJadwal(415,529,1131,1452,1729,1839);
  else if(tgl>=26&& tgl<=28)setJadwal(413,527,1131,1452,1729,1838);
  else if(tgl>=29)          setJadwal(412,526,1131,1452,1729,1838);
 }
 else if(bln==9)
 {
  if     (tgl<=5)           setJadwal(411,524,1129,1447,1728,1837);
  else if(tgl>=6 && tgl<=9) setJadwal(409,522,1127,1445,1727,1836);
  else if(tgl>=10&& tgl<=13)setJadwal(407,521,1126,1443,1727,1836);
  else if(tgl>=14&& tgl<=16)setJadwal(405,519,1124,1440,1727,1835);
  else if(tgl>=17&& tgl<=20)setJadwal(403,516,1123,1437,1726,1834);
  else if(tgl>=21&& tgl<=25)setJadwal(400,413,1122,1434,1725,1833);
  else if(tgl>=26&& tgl<=28)setJadwal(358,513,1121,1432,1725,1833);
  else if(tgl>=29)          setJadwal(356,509,1120,1430,1725,1832);
 }  
 else if(bln==10)
 {
  if     (tgl<=5)           setJadwal(355,508,1119,1427,1724,1832);
  else if(tgl>=6 && tgl<=9) setJadwal(353,506,1118,1425,1724,1832);
  else if(tgl>=10&& tgl<=13)setJadwal(351,504,1117,1423,1723,1832);
  else if(tgl>=14&& tgl<=16)setJadwal(349,503,1115,1420,1723,1832);
  else if(tgl>=17&& tgl<=20)setJadwal(347,501,1115,1422,1723,1832);
  else if(tgl>=21&& tgl<=25)setJadwal(345,459,1115,1422,1722,1832);
  else if(tgl>=26&& tgl<=28)setJadwal(343,458,1114,1424,1722,1833);
  else if(tgl>=29)          setJadwal(341,458,1114,1426,1723,1834);
 }
 else if(bln==11)
 {
  if     (tgl<=3)           setJadwal(340,456,1113,1430,1724,1835);
  else if(tgl>=4 && tgl<=7) setJadwal(339,455,1113,1431,1725,1836);
  else if(tgl>=8 && tgl<=10)setJadwal(338,455,1113,1433,1726,1837);
  else if(tgl>=11&& tgl<=15)setJadwal(337,455,1113,1435,1728,1839);
  else if(tgl>=16&& tgl<=19)setJadwal(337,455,1114,1437,1729,1841);
  else if(tgl>=20&& tgl<=23)setJadwal(336,455,1115,1439,1731,1843);
  else if(tgl>=24&& tgl<=27)setJadwal(337,456,1115,1439,1731,1845);
  else if(tgl>=28)          setJadwal(337,456,1116,1441,1732,1847);
 }
 else if(bln==12)
 {
  if     (tgl<=4)           setJadwal(338,458,1120,1446,1736,1849);
  else if(tgl>=5 && tgl<=7) setJadwal(339,459,1121,1448,1738,1851);
  else if(tgl>=8 && tgl<=11)setJadwal(340,500,1123,1450,1740,1853);
  else if(tgl>=12&& tgl<=15)setJadwal(342,502,1125,1452,1742,1855);
  else if(tgl>=16&& tgl<=19)setJadwal(343,504,1127,1454,1744,1857);
  else if(tgl>=20&& tgl<=24)setJadwal(345,506,1129,1456,1746,1859);
  else if(tgl>=25&& tgl<=28)setJadwal(348,508,1131,1458,1747,1901);
  else if(tgl>=29)          setJadwal(350,510,1131,1458,1747,1903);
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
   if(time_now == murottal.tahajjud and rDet < 2){
    relay_state=true;
    playMurottal();  
    tmploop=5;
   }else if(time_now == tarhim.tahajjud and rDet < 2){
    relay_state=false;
    stopMp3();
    tmploop=0;   
   }
  }
  
  // shubuh
  if (configmurottal.murottals>0){  
   if(time_now == murottal.shubuh and configmurottal.murottals != 5 and rDet < 2){
    relay_state=true;
    playMurottal();  
    tmploop=5;
   }else if(time_now == tarhim.shubuh and rDet < 2){
    relay_state=true;
    playMp3(1);   
   }
  }

  //dzuhur atau jum'at
  if(rHar==5){
   if (configmurottal.murottalj>0){  
    if(time_now == murottal.jumat and rDet < 2){
     relay_state=true;
     playMp3(26);  
     tmploop=5;
    }else if(time_now == tarhim.jumat and rDet < 2){
     relay_state=false;
     stopMp3();   
    }
   }
  }else{ 
   if (configmurottal.murottald>0){  
    if(time_now == murottal.dzuhur and configmurottal.murottald != 5 and rDet < 2){
     relay_state=true;
     playMurottal();  
     tmploop=5;
    }else if(time_now == tarhim.dzuhur and rDet < 2){
     relay_state=true;
     playMp3(1);   
    }
   }
  }

  //ashar
  if (configmurottal.murottala>0){  
   if(time_now == murottal.ashar and configmurottal.murottala != 5 and rDet < 2){
    relay_state=true;
    playMurottal();  
    tmploop=5;
   }else if(time_now == tarhim.ashar and rDet < 2){
    relay_state=true;
    playMp3(1);   
   }
  }

  //magrib
  if (configmurottal.murottalm>0){  
   if(time_now == murottal.magrib and configmurottal.murottalm != 5 and rDet < 2){
    relay_state=true;
    playMurottal();  
    tmploop=5;
   }else if(time_now == tarhim.magrib and rDet < 2){
    relay_state=true;
    playMp3(1);   
   }
  }
  
  //isya'
  if (configmurottal.murottali>0){  
   if(time_now == murottal.isya and configmurottal.murottali != 5 and rDet < 2){
    relay_state=true;
    playMurottal();  
    tmploop=5;
   }else if(time_now == tarhim.isya and rDet < 2){
    relay_state=true;
    playMp3(1);   
   }
  }
}
