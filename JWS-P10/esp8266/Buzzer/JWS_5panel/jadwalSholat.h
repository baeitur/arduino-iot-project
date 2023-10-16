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
      JadwalSholat();
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
