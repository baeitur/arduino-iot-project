#include <SPI.h>
#include <SdFat.h>
#include <SdFatUtil.h>
#include <SFEMP3Shield.h>
#include <EEPROM.h>

SdFat sd;
SFEMP3Shield MP3player;

char key_command,message[10],d_vol[3],d_putar[3];
int volume, kondisi, putar;

void bacaData()
{
  if      (message[0]=='1')MP3player.playMP3("1.mp3");
  else if (message[0]=='2')MP3player.playMP3("2.mp3");
  else if (message[0]=='3')MP3player.playMP3("3.mp3");
  else if (message[0]=='4')MP3player.playMP3("4.mp3");
  else if (message[0]=='5')MP3player.playMP3("5.mp3");
  else if (message[0]=='6')MP3player.playMP3("6.mp3");
  else if (message[0]=='7')MP3player.playMP3("7.mp3");
  else if (message[0]=='8')MP3player.playMP3("8.mp3");
  else if (message[0]=='9')MP3player.playMP3("9.mp3");
  
  else if (message[0]=='q' && message[1]=='0')MP3player.playMP3("q0.mp3");
  else if (message[0]=='q' && message[1]=='1')MP3player.playMP3("q1.mp3");
  else if (message[0]=='q' && message[1]=='2')MP3player.playMP3("q2.mp3");
  else if (message[0]=='q' && message[1]=='3')MP3player.playMP3("q3.mp3");
  else if (message[0]=='q' && message[1]=='4')MP3player.playMP3("q4.mp3");
  else if (message[0]=='q' && message[1]=='5')MP3player.playMP3("q5.mp3");
  
  else if (message[0]=='o')MP3player.playMP3("o.mp3");
  else if (message[0]=='p')MP3player.playMP3("p.mp3");
  else if (message[0]=='q')MP3player.playMP3("q.mp3");
  else if (message[0]=='r')MP3player.playMP3("r.mp3");
  
  else if (message[0]=='s')MP3player.playMP3("sn.mp3");
  else if (message[0]=='t')MP3player.playMP3("sl.mp3");
  else if (message[0]=='u')MP3player.playMP3("rb.mp3");
  else if (message[0]=='v')MP3player.playMP3("ks.mp3");
  else if (message[0]=='w')MP3player.playMP3("jt.mp3");
  else if (message[0]=='x')MP3player.playMP3("sb.mp3");
  else if (message[0]=='y') kondisi=1;
  
  else if (message[0]=='a')MP3player.playMP3("a.mp3");
  else if (message[0]=='b')MP3player.playMP3("b.mp3");
  else if (message[0]=='c')MP3player.playMP3("c.mp3");
  else if (message[0]=='d')MP3player.playMP3("d.mp3");
  else if (message[0]=='e')MP3player.playMP3("e.mp3");
  else if (message[0]=='f')MP3player.playMP3("f.mp3");  
  else if (message[0]=='g')MP3player.playMP3("g.mp3");
  else if (message[0]=='h')MP3player.playMP3("h.mp3");
  else if (message[0]=='i')MP3player.playMP3("i.mp3");
  else if (message[0]=='j')MP3player.playMP3("j.mp3");
  else if (message[0]=='k')MP3player.playMP3("k.mp3");
  else if (message[0]=='l')MP3player.playMP3("l.mp3");
  else if (message[0]=='m')MP3player.playMP3("m.mp3");
  else if (message[0]=='n')MP3player.playMP3("n.mp3");

  else if (message[0]=='A')MP3player.playMP3("ka.mp3");
  else if (message[0]=='B')MP3player.playMP3("kb.mp3");
  else if (message[0]=='C')MP3player.playMP3("kc.mp3");
  else if (message[0]=='D')MP3player.playMP3("kd.mp3");
  else if (message[0]=='E')MP3player.playMP3("ke.mp3");
  else if (message[0]=='F')MP3player.playMP3("kf.mp3");
  else if (message[0]=='G')MP3player.playMP3("kg.mp3");
  else if (message[0]=='H')MP3player.playMP3("kh.mp3");
  else if (message[0]=='I')MP3player.playMP3("ki.mp3");
  else if (message[0]=='J')MP3player.playMP3("kj.mp3");
  else if (message[0]=='K')MP3player.playMP3("kk.mp3");
  else if (message[0]=='L')MP3player.playMP3("kl.mp3");
  else if (message[0]=='M')MP3player.playMP3("km.mp3");
  else if (message[0]=='N')MP3player.playMP3("kn.mp3");
  
  else if (message[0]=='O')MP3player.playMP3("td.mp3");
  else if (message[0]=='P')MP3player.playMP3("jk.mp3");
  else if (message[0]=='Q')MP3player.playMP3("jd.mp3");
  else if (message[0]=='R')MP3player.playMP3("mt.mp3");
  else if (message[0]=='S')MP3player.playMP3("tg.mp3");
  else if (message[0]=='T')MP3player.playMP3("bu.mp3");
  else if (message[0]=='U')MP3player.playMP3("th.mp3");
  else if (message[0]=='V')MP3player.playMP3("dr.mp3");
  else if (message[0]=='W')MP3player.playMP3("sj.mp3");
  else if (message[0]=='X')MP3player.playMP3("oo.mp3");
  else if (message[0]=='Z')MP3player.playMP3("df.mp3");
}
  
void play(int on)
{
 switch(on)
     {
      case 1  : MP3player.stopTrack(); MP3player.playMP3("P1.mp3"); break;
      case 2  : MP3player.stopTrack(); MP3player.playMP3("P2.mp3"); break;
      case 3  : MP3player.stopTrack(); MP3player.playMP3("P3.mp3"); break;
      case 4  : MP3player.stopTrack(); MP3player.playMP3("P4.mp3"); break;
      case 5  : MP3player.stopTrack(); MP3player.playMP3("P5.mp3"); break;
      case 6  : MP3player.stopTrack(); MP3player.playMP3("P6.mp3"); break;
      case 7  : MP3player.stopTrack(); MP3player.playMP3("P7.mp3"); break;
      case 8  : MP3player.stopTrack(); MP3player.playMP3("P8.mp3"); break;
      case 9  : MP3player.stopTrack(); MP3player.playMP3("P9.mp3"); break;
      case 10 : MP3player.stopTrack(); MP3player.playMP3("P10.mp3");break;
     } 
}

void setup() {
  Serial.begin(1200);
  sd.begin(SD_SEL, SPI_HALF_SPEED);
  MP3player.begin();
  //EEPROM.write(254,50);
  int vol = EEPROM.read(254);
  MP3player.setVolume(10,10);
}

void loop() {
  byte i=0;
  while(kondisi==0)
    {
      while(Serial.available()>0)
      {
        MP3player.stopTrack();
        delay(25); byte i;
        for(i=0;i<10;i++)
         {
          key_command = Serial.read();
          message[i]=key_command;
          }
        bacaData();
       }
     } 
 
  while(kondisi==1)
  {  
    
    while(Serial.available()>0)
      {
        delay(25); byte i;
        for(i=0;i<10;i++)
        {
          key_command = Serial.read();
          message[i]=key_command;
         }
        //Serial.print(message[0]);
        if (message[0]=='v')
         {
          d_vol[0]=message[1];
          d_vol[1]=message[2];
          d_vol[2]=message[3];
          volume=atoi(d_vol);
          EEPROM.write(254,volume);
          MP3player.setVolume(volume,volume);
          }
        else if (message[0]=='p')
         {
          play(random(1,10));
          }
        else if (message[0]=='s'){MP3player.stopTrack();kondisi = 0;}
       }
      }
  //MP3player.playMP3("P1.mp3");
}
