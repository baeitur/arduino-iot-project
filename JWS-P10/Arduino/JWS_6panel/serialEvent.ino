char message[65];
int i; char data;
char d_jam[4],d_men[5],d_det[6],d_tgl[4],d_bln[5],d_thn[6];
int jam,men,det,tgl,bln,thn;
 
void serialEvent()
{
 while (Serial.available()>0) {
  delay(25);
  for(i=0;i<65;i++)
  {
   data = Serial.read();
   message[i]=data;delay(5);
  }
    Serial.println(message);
    if (message[0]>47 && message[0]<58 && message[1]>47 && message[1]<58 &&
        message[3]>47 && message[3]<58 && message[4]>47 && message[4]<58 &&
        message[6]>47 && message[6]<58 && message[7]>47 && message[7]<58 &&
        message[9]>47 && message[9]<58 && message[10]>47 && message[10]<58)
    {
      d_jam[0]=message[0];
      d_jam[1]=message[1];
      jam=atoi(d_jam);
      d_men[0]=message[3];
      d_men[1]=message[4];
      men=atoi(d_men);
      d_det[0]=message[6];
      d_det[1]=message[7];
      det=atoi(d_det);
      
      d_tgl[0]=message[9];
      d_tgl[1]=message[10];
      tgl=atoi(d_tgl);
      d_bln[0]=message[12];
      d_bln[1]=message[13];
      bln=atoi(d_bln);
      d_thn[0]=message[15];
      d_thn[1]=message[16];
      thn=atoi(d_thn);
      rtc.adjust(DateTime(2000+thn, bln, tgl, jam, men, det));
      buzzer(1);
    }
   else if(message[0]=='d' && message[1]>47 && 
   message[1]<58 && message[2]>47 && message[2]<58)
    {
      d_jam[0]=message[1];
      d_jam[1]=message[2];
      jam=atoi(d_jam);
      EEPROM.write(1,jam);
      lamaIqomahDzuhur  = EEPROM.read(1);
      buzzer(1);
      setIqomah('d',lamaIqomahDzuhur);
     }
   else if(message[0]=='a' && message[1]>47 && 
   message[1]<58 && message[2]>47 && message[2]<58)
    {
      d_jam[0]=message[1];
      d_jam[1]=message[2];
      jam=atoi(d_jam);
      EEPROM.write(2,jam);
      lamaIqomahAshar  = EEPROM.read(2);
      buzzer(1);
      setIqomah('a',lamaIqomahAshar);
     }
   else if(message[0]=='m' && message[1]>47 && 
   message[1]<58 && message[2]>47 && message[2]<58)
    {
      d_jam[0]=message[1];
      d_jam[1]=message[2];
      jam=atoi(d_jam);
      EEPROM.write(3,jam);
      lamaIqomahMagrib = EEPROM.read(3);
      buzzer(1);
      setIqomah('m',lamaIqomahMagrib);
     }
   else if(message[0]=='i' && message[1]>47 && 
   message[1]<58 && message[2]>47 && message[2]<58)
    {
      d_jam[0]=message[1];
      d_jam[1]=message[2];
      jam=atoi(d_jam);
      EEPROM.write(4,jam);
      lamaIqomahIsya   = EEPROM.read(4);
      buzzer(1);
      setIqomah('i',lamaIqomahIsya);
     }
   else if(message[0]=='s' && message[1]>47 && 
   message[1]<58 && message[2]>47 && message[2]<58)
    {
      d_jam[0]=message[1];
      d_jam[1]=message[2];
      jam=atoi(d_jam);
      EEPROM.write(5,jam);
      lamaIqomahShubuh  = EEPROM.read(5);
      buzzer(1);
      setIqomah('s',lamaIqomahShubuh);
     }
   else if(message[0]=='w'){for(int e=0;e<65;e++){EEPROM.write(50 +e,message[e]);}buzzer(1);}
   else if(message[0]=='x'){for(int e=0;e<65;e++){EEPROM.write(150+e,message[e]);}buzzer(1);}
   else if(message[0]=='y'){for(int e=0;e<65;e++){EEPROM.write(250+e,message[e]);}buzzer(1);}
   else if(message[0]=='z'){setDefault();buzzer(1);}
 }
}

void setDefault()
      {
        EEPROM.write(1,10);
        EEPROM.write(2,10);
        EEPROM.write(3,10);
        EEPROM.write(4, 5);
        EEPROM.write(5,10);
        EEPROM.put(56, "Masjid Baitur Rahman Waru Barat Waru Pamekasan\0");
        EEPROM.put(131,"Info 2\0");
        EEPROM.put(281,"Info 2\0");
      }
