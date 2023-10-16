
void tmpInfo(String teks) {
  
  static uint32_t pM;
  static uint32_t x;
  int width = Disp.width();
  int fullScroll = Disp.textWidth(teks) + width + 30;
  
  if((millis() - pM) > 75) { 
    
    pM = millis();
    Disp.setFont(ElektronMart6x8);
    Disp.drawText(74, 0, " ");
    Disp.drawText(width - x, 8, teks);
    
    if (x < fullScroll) {
      ++x;
    } else {
      x = 0;
      Disp.clear();
      tmputama++;
      if(tmputama>5){
        Disp.clear();
        tmputama=0;
      }
      return ;
    } 
  }  
}

void tmpMasjid(String teks) {
  
  static uint32_t pM;
  static uint32_t x;
  int width = Disp.width();
  int fullScroll = Disp.textWidth(teks) + width;
  
  if((millis() - pM) > 75) { 
    
    pM = millis();
    // Disp.setFont(ElektronMart6x8);
    // Disp.drawText(39, 0, "#");
    // Disp.drawRect(0,6,Disp.width(),6,1,1);
    // Disp.drawText(width - x, 8, teks);
    
    Disp.setFont(TimesNewRoman12);
    Disp.drawText(width - x, 1, teks);  
      
    if (x==0) Disp.clear();
    if (x < fullScroll) {
      ++x;
    } else {
      x = 0;
      Disp.clear();
      tmputama++;
      if(tmputama>5){
        Disp.clear();
        tmputama=0;
      }
      return;
    } 
  }  
}

void tmpJadwalSholat() {
  static uint32_t pM;
  static uint32_t x=0,i=1;
  char Buffer[20]; 
  int jam,menit;
  
  if((millis() - pM) > 3000) { 
    pM = millis();
    Disp.clear();
    i++;
    if(i>8)i=1;
   }
   Disp.setFont(SmallCap4x6);
   if (i==1){ 
    jam=jadwal.imsak/100; menit=jadwal.imsak%100;
    sprintf(bufferText,"IMSAK %02d:%02d",jam,menit);
    Disp.drawText(40, 0, bufferText);
   }else if (i==2){ 
    jam=jadwal.shubuh/100; menit=jadwal.shubuh%100;
    sprintf(bufferText,"SHUBUH %02d:%02d",jam,menit);
    Disp.drawText(36, 0, bufferText);
   }else if (i==3){ 
    jam=jadwal.shuruq/100; menit=jadwal.shuruq%100;
    sprintf(bufferText,"SHURUQ %02d:%02d",jam,menit);
    Disp.drawText(36, 0, bufferText);
   }else if(i==4){
    jam=jadwal.dhuha/100; menit=jadwal.dhuha%100;
    sprintf(bufferText,"DHUHA %02d:%02d",jam,menit);
    Disp.drawText(40, 0, bufferText);
   }else if (i==5){ 
    jam=jadwal.dzuhur/100; menit=jadwal.dzuhur%100;
    sprintf(bufferText,"DZUHUR %02d:%02d",jam,menit);
    Disp.drawText(36, 0, bufferText);
   }else if(i==6){
    jam=jadwal.ashar/100; menit=jadwal.ashar%100;
    sprintf(bufferText,"ASHAR %02d:%02d",jam,menit);
    Disp.drawText(40, 0, bufferText);
   }else if(i==7){
    jam=jadwal.magrib/100; menit=jadwal.magrib%100;
    sprintf(bufferText,"MAGRIB %02d:%02d",jam,menit);
    Disp.drawText(36, 0, bufferText);
   }else if(i==8){
    jam=jadwal.isya/100; menit=jadwal.isya%100;
    sprintf(bufferText,"ISYA' %02d:%02d",jam,menit);
    Disp.drawText(40, 0, bufferText);
   }
}

//----------------------------------------------------------------------
// ANIMASI LOGO

void logoA(uint32_t x) {

  static const uint8_t LogoA[] PROGMEM = {

    16, 16,

    0x00, 0x00, 0x7f, 0xfe, 0x7f, 0xfe, 0x00, 0x00, 0x7e, 0x66, 0x7e, 0x66, 0x06, 0x66, 0x06, 0x66, 0x7e, 0x66, 0x7e, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x7f, 0xfe, 0x7f, 0xfe, 0x00, 0x00

  };
  
  Disp.drawBitmap(x, 0, LogoA);
}


void logoM(uint32_t x) {

  static const uint8_t LogoM[] PROGMEM = {

    16, 16,

    0x00, 0x00, 0x66, 0x7e, 0x66, 0x7e, 0x66, 0x66, 0x66, 0x66, 0x7e, 0x7e, 0x7e, 0x7e, 0x60, 0x60, 0x60, 0x60, 0x7e, 0x7e, 0x7e, 0x7e, 0x66, 0x06, 0x66, 0x06, 0x7f, 0xfe, 0x7f, 0xfe, 0x00, 0x00

  };
  
  Disp.drawBitmap(x, 0, LogoM);
}

void tmpJam(){
  static uint32_t pM;
  static uint32_t x;
  char bufferJam[15];
  //int jam=rJam; if(jam>12)jam-=12;

  if((millis() - pM) > 1000) { 
    pM = millis();
    if (x < 20) {
      ++x;
    } else {
      x = 0;
      Disp.clear();
      return ;
    }
  } 
  //logoA(112);
  //logoM(32);
  Disp.setFont(angka6x13);
  sprintf(bufferJam,"%02d    %02d ",rJam,rMen);
  Disp.drawText(0,1,bufferJam); 
  if(rDet%2==0){
   Disp.drawCircle(15, 4, 1);Disp.drawCircle(15, 11, 1);
  }
  else {
   Disp.drawFilledCircle(15, 4, 1);Disp.drawFilledCircle(15, 11, 1);
  }
}

void tmpjam(){
  static uint32_t pM;
  static uint32_t x;
  char bufferJam[15];
  //int jam=rJam; if(jam>12)jam-=12;

  if((millis() - pM) > 1000) { 
    pM = millis();
    if (x < 20) {
      ++x;
    } else {
      x = 0;
      Disp.clear();
      return ;
    }
  } 
  //logoA(112);
  //logoM(32);
  //Disp.setFont(arab6x13);
  Disp.setFont(angka6x13);
  sprintf(bufferJam,"%02d    %02d ",rJam,rMen);
  Disp.drawText(0,1,bufferJam); 
  if(rDet%2==0){
   Disp.drawCircle(15, 4, 1);Disp.drawCircle(15, 11, 1);
  }
  else {
   Disp.drawFilledCircle(15, 4, 1);Disp.drawFilledCircle(15, 11, 1);
  }
}

void Utama(){
  if(tmputama==0){
   tmpMasjid(configinfo.namamasjid);
  }else if(tmputama==1){
   sprintf(bufferText,"%s, %d %s %d ",namaHari[rHar],rTgl,namaBulan[rBul],rTah);
   tmpInfo(bufferText);
   tmpJam();
   tmpJadwalSholat();
  }else if(tmputama==2){
   sprintf(bufferText,"%s, %d %s %dH ",hariHijriah[rHar],Hjr_Date,bulanHijriah[Hjr_Month],Hjr_Year);
   tmpInfo(bufferText);
   tmpjam();
   tmpJadwalSholat();
  }else if(tmputama==3){
   if(rHar==4 && rJam>16){
    tmpInfo(jumat[wHar1]);
    tmpJam();
    tmpJadwalSholat();
   }else if(rHar==5 && rJam<16){
    tmpInfo(jumat[wHar0]);
    tmpJam();
    tmpJadwalSholat();
   }else{
    tmpInfo(configinfo.info1);
    tmpJam();
    tmpJadwalSholat();
   }
  }else if(tmputama==4){
   if(rHar==4 && rJam>16){
    tmpInfo(jumat[wHar1]);
    tmpJam();
    tmpJadwalSholat();
   }else if(rHar==5 && rJam<16){
    tmpInfo(jumat[wHar0]);
    tmpJam();
    tmpJadwalSholat();
   }else{
    tmpInfo(configinfo.info2);
    tmpJam();
    tmpJadwalSholat();
   }
  }else if(tmputama==5){
   if(rHar==5 && rJam>16){
    tmpInfo("Pembacaan Sholawat Dilaksanakan Tiap Hari Jum'at Jam : 18:00 - 19:00 WIB       ");
    tmpJam();
    tmpJadwalSholat();
   }else if(rHar==2 && rJam>16){
    tmpInfo("Kajian Kitab Dilaksanakan Tiap Hari Selasa Jam : 18:00 - 19:00 WIB Oleh Ust Ach Nafik      ");
    tmpJam();
    tmpJadwalSholat();
   }
   else{
    tmpInfo(configinfo.info3);
    tmpJam();
    tmpJadwalSholat();
   }
  } 
}

void Adzan() {  
  static uint32_t pM;
  uint32_t cM = millis();
  static uint16_t det;
  
  if (tipealarm == 1) { 
    tmpMasjid("Adzan Shubuh ");
    menitiqmh = configjws.iqmhs;
  }else if(tipealarm == 2) {
    tmpMasjid("Adzan Dzuhur ");
    menitiqmh = configjws.iqmhd;
  }else if(tipealarm == 3) {
    tmpMasjid("Adzan Jum'at ");
  }else if(tipealarm == 4) {
    tmpMasjid("Adzan Ashar ");
    menitiqmh = configjws.iqmha;
  }else if(tipealarm == 5) {
    tmpMasjid("Adzan Magrib ");
    menitiqmh = configjws.iqmhm;   
  }else if(tipealarm == 6) {
    tmpMasjid("Adzan Isya' ");
    menitiqmh = configjws.iqmhi;    
  }  
  
  //logoA(144);
  //logoM(0);
  
  if (cM-pM >= 1000) {
    det++;   
    if (tipealarm == 3) {
      if (det == configjws.durasiadzan * 60) {
        det = 0;
        relay_state = false;
        tmploop = 0;
      } 
    }
    if (tipealarm == 1 or tipealarm == 2 or tipealarm == 4 or tipealarm == 5 or tipealarm == 6) {
          
      if (det == configjws.durasiadzan * 60) {
        Disp.clear();
        relay_state = false;
        det = 0;
        tmploop = 2;
      }
    }
    pM = cM;
  }  
}

void Iqomah() {
  static uint32_t pM;
  uint32_t cM = millis();
  static char bufferIqom[6];  

  Disp.setFont(ElektronMart6x8);
  Disp.drawText(6,4, "IQOMAH");
  sprintf(bufferIqom, "%02d:%02d", menitiqmh, detikiqmh);
  Disp.drawText(58,4, bufferIqom);
  
  if (detikiqmh == 60) {
    detikiqmh = 0;
  }

  if (cM - pM >= 1000) {
    pM = cM;
    detikiqmh--;

    if (menitiqmh == 0 && detikiqmh < 0) {
      if(modeMurottal==true){
        relay_state = true;
        delay(1000);
        playMp3(4);
        Disp.clear();
        tmploop=3;
      }else {
        Buzzer();
        Disp.clear();
        tmploop=3;
      }
    }

    if (detikiqmh < 0) {
      detikiqmh = 59;
      menitiqmh--;
    }
  }
}

void Sholat(){
  
  static uint32_t pM;
  uint32_t cM = millis();
  static uint32_t durasi = 40; // Detik
  static uint32_t det;

  tmpMasjid("Lurus dan Rapatnya Shaf Termasuk Kesempurnaan Sholat Berjemaah ");
  //logoA(144);
  //logoM(0);
  
  if (cM - pM >= 1000) {
    pM = cM;
    det++;
    if (durasi == det) {
      Disp.clear();
      det = 0;
      relay_state=false;
      tmploop = 4;
    }
  } 
}

void Mati(){
  static uint32_t pM;
  uint32_t cM = millis();
  static uint32_t durasi = 10; // menit
  static uint32_t det;
  
  if (cM - pM >= 1000) {
    pM = cM;
    det++;
    if (durasi*60 == det) {
      Disp.clear();
      det = 0;
      relay_state=false;
      tmploop = 0;
    }
    Disp.drawFilledCircle(48, 7, 1);
  }  
}
