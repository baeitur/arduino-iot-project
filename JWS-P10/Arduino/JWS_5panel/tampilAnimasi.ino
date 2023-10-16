
void textCenter(int y,String Msg) {
  
  int center = int((display.width()-display.textWidth(Msg)) / 2);
  display.drawText(center,y,Msg); 
}

void tmpInfo(String text) {
  static uint32_t pM;
  uint32_t cM = millis();
  static uint8_t Kecepatan = 50;
  static uint32_t x=0;
  
  int width = display.width();
  int fullScroll = display.textWidth(text) + width;  
  display.setFont(DejaVuSansBold9);

  if(cM - pM > Kecepatan) {
    pM = cM;
    if (x < fullScroll) {
      ++x;
      delay(40);
    }else{
      x = 0;
    }
    if(nextStep==true){
      x=0;
      nextStep=false;
    }
    display.drawText(width - x, 7, text);
    tmpJamKecil();
    display.swapBuffers();
  }
}

void tmpMasjid(String text, int JumTampil)
{
 display.clear();
 int width = display.width();
 int fullScroll = display.textWidth(text) + width; 
 
 for(int y=0;y<JumTampil;++y){
  for(int x=0;x<fullScroll;++x){
   //di isi tampilAnimasi
   serialEvent();
   display.setFont(ElektronMart6x8);
   display.drawText(70,0,"#"); 
   display.drawRect(0,6,display.width(),6,1,1);
   display.drawText(display.width()-x,8,text);
   display.swapBuffers();
   display.clear();
   delay(70);
  }
 }
}

void animBuka(uint32_t x){
  display.drawFilledRect(60,0,115-x,6,0);
  display.drawFilledRect(115+x,0,175,6,0);
  display.drawLine(115-x,0,115-x,6);
  display.drawLine(115+x,0,115+x,6);
}

void animTutup(uint32_t x){
  display.drawFilledRect(60,0,60+x,6,0);
  display.drawFilledRect(175-x,0,175,6,0);
  display.drawLine(60+x,0,60+x,6);
  display.drawLine(175-x,0,175-x,6);
}
void infoIqomah()
{
 strcpy_P(bufferInfo,(char *)pgm_read_word(&(infoTabel[1]))); 
 tmpMasjid(bufferInfo,1);
}

void tmpWaktu(int imsaq, int shubuh, int shuruq, int dhuha, int dzuhur, int ashar, int magrib, int isya) {
  
  static uint32_t pM;
  uint32_t cM = millis();
  static uint8_t Kecepatan = 75;
  static uint32_t x=0,i=1;
  
  int jam,menit;
  char bufferText[16];
  
  if(cM - pM > Kecepatan) {
    pM = cM;
    if (x < 60) {
      
      delay(50);
      ++x;
      serialEvent();
      display.clear();
    } else {
      display.clear();
      x=0;
      i++;
      if(i>12){
       i=1;
       next++;
       nextStep=true;
      } 
      if(next>7)next=1;
    }
   display.setFont(SmallCap4x6);
   if (i==1){
    jam=imsaq/100; menit=imsaq%100;
    sprintf(bufferText,"IMSAQ : %02d:%02d",jam,menit);
    display.drawText(80, 0, bufferText);
    animBuka(x);
   }else if(i==2){
    jam=imsaq/100; menit=imsaq%100;
    sprintf(bufferText,"IMSAQ : %02d:%02d",jam,menit);
    display.drawText(80, 0, bufferText);
    animTutup(x);
//   }else if (i==1){
//    jam=shubuh/100; menit=shubuh%100;
//    sprintf(bufferText,"SHUBUH : %02d:%02d",jam,menit);
//    display.drawText(80, 0, bufferText);
//    animBuka(x);
//   }else if(i==2){
//    jam=shubuh/100; menit=shubuh%100;
//    sprintf(bufferText,"SHUBUH : %02d:%02d",jam,menit);
//    display.drawText(80, 0, bufferText);
//    animTutup(x);
   }else if(i==3){
    jam=shuruq/100; menit=shuruq%100;
    sprintf(bufferText,"SHURUQ : %02d:%02d",jam,menit);
    display.drawText(80, 0, bufferText);
    animBuka(x);
   }else if(i==4){
    jam=shuruq/100; menit=shuruq%100;
    sprintf(bufferText,"SHURUQ : %02d:%02d",jam,menit);
    display.drawText(80, 0, bufferText);
    animTutup(x);
   }else if(i==5){
    jam=dzuhur/100; menit=dzuhur%100;
    sprintf(bufferText,"DZUHUR : %02d:%02d",jam,menit);
    display.drawText(80, 0, bufferText);
    animBuka(x);
   }else if(i==6){
    jam=dzuhur/100; menit=dzuhur%100;
    sprintf(bufferText,"DZUHUR : %02d:%02d",jam,menit);
    display.drawText(80, 0, bufferText);
    animTutup(x);
   }else if(i==7){
    jam=ashar/100; menit=ashar%100;
    sprintf(bufferText," ASHAR : %02d:%02d",jam,menit);
    display.drawText(80, 0, bufferText);
    animBuka(x);
   }else if(i==8){
    jam=ashar/100; menit=ashar%100;
    sprintf(bufferText," ASHAR : %02d:%02d",jam,menit);
    display.drawText(80, 0, bufferText);
    animTutup(x);
   }else if(i==9){
    jam=magrib/100; menit=magrib%100;
    sprintf(bufferText,"MAGRIB : %02d:%02d",jam,menit);
    display.drawText(80, 0, bufferText);
    animBuka(x);
   }else if(i==10){
    jam=magrib/100; menit=magrib%100;
    sprintf(bufferText,"MAGRIB : %02d:%02d",jam,menit);
    display.drawText(80, 0, bufferText);
    animTutup(x);
   }else if(i==11){
    jam=isya/100; menit=isya%100;
    sprintf(bufferText," ISYA' : %02d:%02d",jam,menit);
    display.drawText(80, 0, bufferText);
    animBuka(x);
   }else if(i==12){
    jam=isya/100; menit=isya%100;
    sprintf(bufferText," ISYA' : %02d:%02d",jam,menit);
    display.drawText(80, 0, bufferText);
    animTutup(x);
   }

  DateTime now = rtc.now();
  int Now = now.hour()*100+now.minute();
  byte nowDay = now.dayOfWeek();
  int weton=wetonJawa();
  if(Now==dzuhur){
   buzzer(7);
   if(nowDay==5)
   {
    tmpMasjid("Adzan Jum'at",3);
    //matiSholat(25);
   }else{
    tmpMasjid("Adzan Dzuhur",3);
    countIqomah(lamaIqomahDzuhur);
    buzzer(7);
    infoIqomah();
    matiSholat(10);
   }
  }else if(Now==ashar){
   buzzer(7);
   tmpMasjid("Adzan Ashar",3);
   countIqomah(lamaIqomahAshar);
   buzzer(7);
   infoIqomah();
   matiSholat(10);
  }else if(Now==magrib){
   buzzer(7);
   tmpMasjid("Adzan Magrib",3);
   countIqomah(lamaIqomahMagrib);
   buzzer(7);
   infoIqomah();
   matiSholat(10);
  }else if(Now==isya){
   buzzer(7);
   tmpMasjid("Adzan Isya'",3);
   countIqomah(lamaIqomahIsya);
   buzzer(7);
   infoIqomah();
   matiSholat(10);
  }else if(Now==shubuh){
   buzzer(7);
   tmpMasjid("Adzan Shubuh",3);
   countIqomah(lamaIqomahDzuhur);
   buzzer(7);
   infoIqomah();
   matiSholat(10);
  }
}
}

//----------------------------------------------------------------------
// TAMPILKAN SUHU

//----------------------------------------------------------------------
// TAMPILKAN JAM

void tmpJamKecil() {
  
 DateTime now = rtc.now();
 int jam   = now.hour();
 int menit = now.minute();
 int detik = now.second();
  jam=jam%12;if(jam==0)jam=12;
  display.setFont(SevSeg2);
  sprintf(bufferInfo,"%d%d    %d%d    %d%d  ",jam/10,jam%10,menit/10,menit%10,detik/10,detik%10);
  display.drawText(0,0,bufferInfo); 
  if(detik%2==0){
   display.drawCircle(21, 4, 1);display.drawCircle(21, 11, 1);
   display.drawCircle(45, 4, 1);display.drawCircle(45, 11, 1);
  }
  else {
   display.drawFilledCircle(21, 4, 1);display.drawFilledCircle(21, 11, 1);
   display.drawFilledCircle(45, 4, 1);display.drawFilledCircle(45, 11, 1);
  }
}

void countIqomah(byte l_iqomah)
{
  byte d_iqomah=1; //jangan di ubah
  int  w_iqomah=l_iqomah*60+1;
  for(int i=1;i<w_iqomah;i++)
  {
   d_iqomah--;
   if(d_iqomah==0)
   {
    l_iqomah--;
    d_iqomah=60;
   }
   display.clear();
   display.setFont(TimesNewRoman12);
   sprintf(bufferInfo,"Iqomah  %d%d:%d%d",l_iqomah/10,l_iqomah%10,d_iqomah/10,d_iqomah%10);
   display.drawText(((display.width()-display.textWidth(bufferInfo))/2)+1,1,bufferInfo);
   display.swapBuffers();
   delay(1000);
  }  
}

void setIqomah(char iqomah, int lama)
{
 display.clear();
 display.setFont(DejaVuSansBold9);
 switch(iqomah)
 {
  case 'd' : sprintf(bufferInfo,"Iqomah dzuhur %d%d menit",lama/10,lama%10);
             display.drawText(((display.width()-display.textWidth(bufferInfo))/2)+1,3,bufferInfo);
             break;
  case 'a' : sprintf(bufferInfo,"Iqomah ashar %d%d menit",lama/10,lama%10);
             display.drawText(((display.width()-display.textWidth(bufferInfo))/2)+1,3,bufferInfo);
             break;
  case 'm' : sprintf(bufferInfo,"Iqomah magrib %d%d menit",lama/10,lama%10);
             display.drawText(((display.width()-display.textWidth(bufferInfo))/2)+1,3,bufferInfo);
             break;
  case 'i' : sprintf(bufferInfo,"Iqomah isya' %d%d menit",lama/10,lama%10);
             display.drawText(((display.width()-display.textWidth(bufferInfo))/2)+1,3,bufferInfo);
             break;
  case 's' : sprintf(bufferInfo,"Iqomah shubuh %d%d menit",lama/10,lama%10);
             display.drawText(((display.width()-display.textWidth(bufferInfo))/2)+1,3,bufferInfo);
             break;
  }  
  display.swapBuffers();
  delay(5000);
}

void matiSholat(byte lama)
{
 for(int b=0;b<lama*60;b++){
 display.clear();
 display.swapBuffers();
  delay(1000);
  }
}

void buzzer(uint8_t state)
{
    for(int b=0;b<state;b++){
      digitalWrite(BUZZER,0);delay(200);
      digitalWrite(BUZZER,1);delay(200);
      digitalWrite(BUZZER,0);delay(200);
      digitalWrite(BUZZER,1);delay(200);
    }
}
