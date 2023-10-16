void moveLiftAzan(int waktu)
{
 display.clear();
 display.setFont(TimesNewRoman12);
 for(int y=0;y<3;++y){
  for(int x=0;x<480;++x){
   //di isi tampilAnimasi
   strcpy_P(bufferText1,(char *)pgm_read_word(&(waktuTabel[waktu])));
   sprintf(bufferText,"Saatnya sholat %s",bufferText1);
   display.drawText(display.width()-x,1,bufferText);
   display.swapBuffers();
   display.clear();
   delay(20);
  }
 }
}
void moveLiftIqomah(int index)
{
  display.clear();
  display.setFont(TimesNewRoman12);
  for(int x=0;x<700;++x){
   strcpy_P(bufferText,(char *)pgm_read_word(&(infoTabel[index]))); 
   display.drawText(display.width()-x,1,bufferText);
   display.swapBuffers();
   display.clear();
   delay(20);
  }
}
void tmpWaktu(int imsak, int shubuh, int suruq, int dhuha, int dzuhur, int ashar, int magrib, int isya, int x)
{
 int p=x,jam1,jam2,menit1,menit2;
 display.setFont(SmallCap4x6);
 if(p<110){
  jam1=dzuhur/100; menit1=dzuhur%100;
  jam2=ashar /100; menit2=ashar %100; p=x;
  sprintf(bufferText,"DZUHUR:%d%d:%d%d ASHAR:%d%d:%d%d",jam1/10,jam1%10,menit1/10,menit1%10,jam2/10,jam2%10,menit2/10,menit2%10);
  display.drawText(71,0,bufferText);
  display.drawFilledRect(64,0,134-p,6,0);
  display.drawFilledRect(135+p,0,192,6,0);
  display.drawLine(134-p,0,134-p,6);
  display.drawLine(134+p,0,134+p,6);
  }
 else if(p>110&&p<240){
  jam1=magrib/100; menit1=magrib%100;
  jam2=isya  /100; menit2=isya  %100; p=x-110;
  sprintf(bufferText,"MAGRIB:%d%d:%d%d ISYA':%d%d:%d%d",jam1/10,jam1%10,menit1/10,menit1%10,jam2/10,jam2%10,menit2/10,menit2%10);
  display.drawText(71,0,bufferText);
  display.drawFilledRect(64,0,134-p,6,0);
  display.drawFilledRect(135+p,0,192,6,0);
  display.drawLine(134-p,0,134-p,6);
  display.drawLine(134+p,0,134+p,6);
  }
 else if(p>240&&p<360){
  jam1=imsak/100; menit1=imsak%100;
  jam2=shubuh /100; menit2=shubuh %100; p=x-240;
  sprintf(bufferText,"IMSAK:%d%d:%d%d SHUBUH:%d%d:%d%d",jam1/10,jam1%10,menit1/10,menit1%10,jam2/10,jam2%10,menit2/10,menit2%10);
  display.drawText(71,0,bufferText);
  display.drawFilledRect(64,0,134-p,6,0);
  display.drawFilledRect(135+p,0,192,6,0);
  display.drawLine(134-p,0,134-p,6);
  display.drawLine(134+p,0,134+p,6);
  }
 else if(p>360){
  jam1=suruq/100; menit1=suruq%100;
  jam2=dhuha /100; menit2=dhuha %100; p=x-360;
  sprintf(bufferText,"SHURUQ:%d%d:%d%d DHUHA:%d%d:%d%d",jam1/10,jam1%10,menit1/10,menit1%10,jam2/10,jam2%10,menit2/10,menit2%10);
  display.drawText(71,0,bufferText);
  display.drawFilledRect(64,0,134-p,6,0);
  display.drawFilledRect(135+p,0,192,6,0);
  display.drawLine(134-p,0,134-p,6);
  display.drawLine(134+p,0,134+p,6);
  }
 DateTime now = rtc.now();
 int Now = now.hour()*100+now.minute();
 if(Now==dzuhur){
  buzzer(7);
  moveLiftAzan(0);
  countIqomah(lamaIqomahDzuhur);
  buzzer(7);
  moveLiftIqomah(1);
  moveLiftIqomah(2);
  matiSholat(10);
 }
 else if(Now==ashar){
  buzzer(7);
  moveLiftAzan(1);
  countIqomah(lamaIqomahAshar);
  buzzer(7);
  moveLiftIqomah(1);
  moveLiftIqomah(2);
  matiSholat(10);
 }
 else if(Now==magrib){
  buzzer(7);
  moveLiftAzan(2);
  countIqomah(lamaIqomahMagrib);
  buzzer(7);
  moveLiftIqomah(1);
  moveLiftIqomah(2);
  matiSholat(10);
 }
 else if(Now==isya){
  buzzer(7);
  moveLiftAzan(3);
  countIqomah(lamaIqomahIsya);
  buzzer(7);
  moveLiftIqomah(1);
  moveLiftIqomah(2);
  matiSholat(10);
 }
 else if(Now==shubuh){
  buzzer(7);
  moveLiftAzan(4);
  countIqomah(lamaIqomahShubuh);
  buzzer(7);
  moveLiftIqomah(1);
  moveLiftIqomah(2);
  matiSholat(10);
 }
}  
void tmpJam1(byte jam,byte menit,byte detik)
{
  display.setFont(SevSeg2);
  sprintf(bufferText,"%d%d    %d%d    %d%d  ",jam/10,jam%10,menit/10,menit%10,detik/10,detik%10);
  display.drawText(0,0,bufferText); 
  if(detik%2==0){
   display.drawCircle(21, 4, 1);display.drawCircle(21, 11, 1);
   display.drawCircle(45, 4, 1);display.drawCircle(45, 11, 1);
  }
  else {
   display.drawFilledCircle(21, 4, 1);display.drawFilledCircle(21, 11, 1);
   display.drawFilledCircle(45, 4, 1);display.drawFilledCircle(45, 11, 1);
  }
}

void tmpTanggal(int posX, char mode,byte hari,byte tgl,byte bln,int thn)
{
  display.setFont(DejaVuSansBold9);
  //char buffHari [7];
  //char buffBulan[15];
  strcpy_P(bufferText1,  (char *)pgm_read_word(&(namaHari[hari])));
  if(mode=='m'){
              strcpy_P(bufferText2, (char *)pgm_read_word(&(bulanMasehi[bln])));
              sprintf (bufferText,"%s %d %s %d",bufferText1,tgl,bufferText2,thn);
  }
  else{ 
              strcpy_P(bufferText2, (char *)pgm_read_word(&(bulanHijriah[nowH.hM])));
              sprintf (bufferText,"%s %d %s %d",bufferText1,nowH.hD,bufferText2,nowH.hY);
  }
  display.drawText(display.width()-posX,7,bufferText); 
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
   sprintf(bufferText,"Iqomah  %d%d:%d%d",l_iqomah/10,l_iqomah%10,d_iqomah/10,d_iqomah%10);
   display.drawText(((display.width()-display.textWidth(bufferText))/2)+1,1,bufferText);
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
  case 'd' : sprintf(bufferText,"Iqomah dzuhur %d%d menit",lama/10,lama%10);
             display.drawText(((display.width()-display.textWidth(bufferText))/2)+1,3,bufferText);
             break;
  case 'a' : sprintf(bufferText,"Iqomah ashar %d%d menit",lama/10,lama%10);
             display.drawText(((display.width()-display.textWidth(bufferText))/2)+1,3,bufferText);
             break;
  case 'm' : sprintf(bufferText,"Iqomah magrib %d%d menit",lama/10,lama%10);
             display.drawText(((display.width()-display.textWidth(bufferText))/2)+1,3,bufferText);
             break;
  case 'i' : sprintf(bufferText,"Iqomah isya' %d%d menit",lama/10,lama%10);
             display.drawText(((display.width()-display.textWidth(bufferText))/2)+1,3,bufferText);
             break;
  case 's' : sprintf(bufferText,"Iqomah shubuh %d%d menit",lama/10,lama%10);
             display.drawText(((display.width()-display.textWidth(bufferText))/2)+1,3,bufferText);
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
      digitalWrite(BUZZER,1);delay(200);
      digitalWrite(BUZZER,0);delay(200);
      digitalWrite(BUZZER,1);delay(200);
      digitalWrite(BUZZER,0);delay(200);
    }
}


