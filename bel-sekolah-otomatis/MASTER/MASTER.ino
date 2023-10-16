//#include <TimerOne.h>
#include <Wire.h>
#include "RTClib.h"
#include <EEPROM.h>
#include <SoftwareSerial.h>
#include <LiquidCrystal.h>

RTC_DS1307 rtc;
SoftwareSerial mySerial(10, 9); // RX, TX
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

//deklasi variable here
boolean music=false;
int p=5;
char tampil[20],play[4];
int  N_hari,hari,waktu,jam,men,det,tgl,bln,thn,volume,state,savemen;
char key_command,message[31],d_hari[3],d_waktu[3],d_jam[4],d_men[5],d_det[6],d_tgl[4],d_bln[5],d_thn[6],d_vol[4];

void H_hari()
{
 DateTime now = rtc.now();
 long tahun=now.year();
 int i,bulan;
 int m_kabisat,m_nonkabisat,m_kabisat1,t_kabisat;
 int kabisat=0,nonkabisat=0,kabisat1=0;
 long j_tahun=(tahun-1)*365;
 for(i=1;i<tahun;i++)
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
 switch(now.month())
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
 N_hari=((j_tahun+(kabisat-nonkabisat)+kabisat1)+bulan+(now.day()-1))%7;
 //N_weton=((j_tahun+(kabisat-nonkabisat)+kabisat1)+bulan+(now.day()-1))%5;
}

void setdefault()
{
   //senin
   EEPROM.write(0 , 6);  EEPROM.write(1 ,45);  //jam masuk
   EEPROM.write(2 , 6);  EEPROM.write(3 ,47);  //jam 1
   EEPROM.write(4 , 8);  EEPROM.write(5 ,10);  //jam 2
   EEPROM.write(6 , 9);  EEPROM.write(7 ,45);  //jam 3
   EEPROM.write(8 ,10);  EEPROM.write(9 ,50);  //jam 4
   EEPROM.write(10, 0);  EEPROM.write(11, 0);  //jam 5
   EEPROM.write(12, 0);  EEPROM.write(13, 0);  //jam 6
   EEPROM.write(14, 0);  EEPROM.write(15, 0);  //jam 7
   EEPROM.write(16, 0);  EEPROM.write(17, 0);  //jam 8
   EEPROM.write(18, 0);  EEPROM.write(19, 0);  //jam 9
   EEPROM.write(20, 0);  EEPROM.write(21, 0);  //jam 10
   EEPROM.write(22,12);  EEPROM.write(23, 0);  //jam pulang
   EEPROM.write(24, 9);  EEPROM.write(25,20);  //jam istirahat 1
   EEPROM.write(26, 0);  EEPROM.write(27, 0);  //jam istirahat 2
   //selasa
   EEPROM.write(28, 6); EEPROM.write(29,45);   //jam masuk
   EEPROM.write(30, 6); EEPROM.write(31,47);   //jam 1
   EEPROM.write(32, 8); EEPROM.write(33,10);   //jam 2
   EEPROM.write(34, 9); EEPROM.write(35,45);   //jam 3
   EEPROM.write(36,10); EEPROM.write(37,50);   //jam 4
   EEPROM.write(38, 0); EEPROM.write(39, 0);   //jam 5
   EEPROM.write(40, 0); EEPROM.write(41, 0);   //jam 6
   EEPROM.write(42, 0); EEPROM.write(43, 0);   //jam 7
   EEPROM.write(44, 0); EEPROM.write(45, 0);   //jam 8
   EEPROM.write(46, 0); EEPROM.write(47, 0);   //jam 9
   EEPROM.write(48, 0); EEPROM.write(49, 0);   //jam 10
   EEPROM.write(50,12); EEPROM.write(51, 0);   //jam pulang 
   EEPROM.write(52, 9); EEPROM.write(53,20);   //jam istirahat
   EEPROM.write(54, 0); EEPROM.write(55, 0);   //jam istirahat 2
   //rabu
   EEPROM.write(56, 6); EEPROM.write(57,45);   //jam masuk 
   EEPROM.write(58, 6); EEPROM.write(59,47);   //jam 1
   EEPROM.write(60, 8); EEPROM.write(61,10);   //jam 2
   EEPROM.write(62, 9); EEPROM.write(63,45);   //jam 3
   EEPROM.write(64,10); EEPROM.write(65,50);   //jam 4
   EEPROM.write(66,10); EEPROM.write(67, 0);   //jam 5
   EEPROM.write(68, 0); EEPROM.write(69, 0);   //jam 6
   EEPROM.write(70, 0); EEPROM.write(71, 0);   //jam 7
   EEPROM.write(72, 0); EEPROM.write(73, 0);   //jam 8
   EEPROM.write(74, 0); EEPROM.write(75, 0);   //jam 9
   EEPROM.write(76, 0); EEPROM.write(77, 0);   //jam 10
   EEPROM.write(78,12); EEPROM.write(79, 0);   //jam pulang 
   EEPROM.write(80, 9); EEPROM.write(81,20);   //jam istirahat
   EEPROM.write(82, 0); EEPROM.write(83, 0);   //jam istirahat 2
   //kamis
   EEPROM.write(84, 6);  EEPROM.write(85,45);  //jam masuk
   EEPROM.write(86, 6);  EEPROM.write(87,47);  //jam 1
   EEPROM.write(88, 8);  EEPROM.write(89,10);  //jam 2
   EEPROM.write(90, 9);  EEPROM.write(91,45);  //jam 3
   EEPROM.write(92,10);  EEPROM.write(93,50);  //jam 4
   EEPROM.write(94, 0);  EEPROM.write(95, 0);  //jam 5
   EEPROM.write(96, 0);  EEPROM.write(97, 0);  //jam 6
   EEPROM.write(98, 0);  EEPROM.write(99, 0);  //jam 7
   EEPROM.write(100,0);  EEPROM.write(101,0);  //jam 8
   EEPROM.write(102,0);  EEPROM.write(103,0);  //jam 9
   EEPROM.write(104,0);  EEPROM.write(105,0);  //jam 10
   EEPROM.write(106,12); EEPROM.write(107,0);  //jam pulang 
   EEPROM.write(108, 9); EEPROM.write(109,20); //jam istirahat 
   EEPROM.write(110, 0); EEPROM.write(111, 0); //jam istirahat 2
   //jum at
   EEPROM.write(112, 6); EEPROM.write(113,45); //jam masuk
   EEPROM.write(114, 6); EEPROM.write(115,47); //jam 1
   EEPROM.write(116, 8); EEPROM.write(117, 0); //jam 2
   EEPROM.write(118, 9); EEPROM.write(119, 0); //jam 3
   EEPROM.write(120, 0); EEPROM.write(121, 0); //jam 4
   EEPROM.write(122, 0); EEPROM.write(123, 0); //jam 5
   EEPROM.write(124, 0); EEPROM.write(125, 0); //jam 6
   EEPROM.write(126, 0); EEPROM.write(127, 0); //jam 7
   EEPROM.write(128, 0); EEPROM.write(129, 0); //jam 8
   EEPROM.write(130, 0); EEPROM.write(131, 0); //jam 9
   EEPROM.write(132, 0); EEPROM.write(133, 0); //jam 10
   EEPROM.write(134,10); EEPROM.write(135, 0); //jam pulang 
   EEPROM.write(136, 0); EEPROM.write(137, 0); //jam istirahat 
   EEPROM.write(138, 0); EEPROM.write(139, 0); //jam istirahat 2
   //sabtu
   EEPROM.write(140, 6); EEPROM.write(141,45); //jam masuk 
   EEPROM.write(142, 6); EEPROM.write(143,47); //jam 1
   EEPROM.write(144, 9); EEPROM.write(145,45); //jam 2
   EEPROM.write(146,10); EEPROM.write(147,50); //jam 3
   EEPROM.write(148, 0); EEPROM.write(149, 0); //jam 4
   EEPROM.write(150, 0); EEPROM.write(151, 0); //jam 5
   EEPROM.write(152, 0); EEPROM.write(153, 0); //jam 6
   EEPROM.write(154, 0); EEPROM.write(155, 0); //jam 7
   EEPROM.write(156, 0); EEPROM.write(157, 0); //jam 8
   EEPROM.write(158, 0); EEPROM.write(159, 0); //jam 9
   EEPROM.write(160, 0); EEPROM.write(161, 0); //jam 10 
   EEPROM.write(162,12); EEPROM.write(163, 0); //jam pulang 
   EEPROM.write(164, 9); EEPROM.write(165,20); //jam istirahat 
   EEPROM.write(166, 0); EEPROM.write(167, 0); //jam istirahat 2
}

void SaveDataJadwal(byte Hari,byte jam,byte Hour,byte Min)
{
 if(Hari==0)
 {
   switch(jam)
   {
     case 0  : EEPROM.write(0,Hour);   EEPROM.write(1,Min); voicejadwal(Hari,jam,Hour,Min); break;
     case 1  : EEPROM.write(2,Hour);   EEPROM.write(3,Min); voicejadwal(Hari,jam,Hour,Min); break;
     case 2  : EEPROM.write(4,Hour);   EEPROM.write(5,Min); voicejadwal(Hari,jam,Hour,Min); break;
     case 3  : EEPROM.write(6,Hour);   EEPROM.write(7,Min); voicejadwal(Hari,jam,Hour,Min); break;
     case 4  : EEPROM.write(8,Hour);   EEPROM.write(9,Min); voicejadwal(Hari,jam,Hour,Min); break;
     case 5  : EEPROM.write(10,Hour);  EEPROM.write(11,Min);voicejadwal(Hari,jam,Hour,Min); break;
     case 6  : EEPROM.write(12,Hour);  EEPROM.write(13,Min);voicejadwal(Hari,jam,Hour,Min); break;
     case 7  : EEPROM.write(14,Hour);  EEPROM.write(15,Min);voicejadwal(Hari,jam,Hour,Min); break;
     case 8  : EEPROM.write(16,Hour);  EEPROM.write(17,Min);voicejadwal(Hari,jam,Hour,Min); break;
     case 9  : EEPROM.write(18,Hour);  EEPROM.write(19,Min);voicejadwal(Hari,jam,Hour,Min); break;
     case 10 : EEPROM.write(20,Hour);  EEPROM.write(21,Min);voicejadwal(Hari,jam,Hour,Min); break;
     case 11 : EEPROM.write(22,Hour);  EEPROM.write(23,Min);voicejadwal(Hari,jam,Hour,Min); break;
     case 12 : EEPROM.write(24,Hour);  EEPROM.write(25,Min);voicejadwal(Hari,jam,Hour,Min); break;
     case 13 : EEPROM.write(26,Hour);  EEPROM.write(27,Min);voicejadwal(Hari,jam,Hour,Min); break;
   }
 }
 else if(Hari==1)
 {
   switch(jam)
   {
     case 0  : EEPROM.write(28,Hour);  EEPROM.write(29,Min);voicejadwal(Hari,jam,Hour,Min); break;
     case 1  : EEPROM.write(30,Hour);  EEPROM.write(31,Min);voicejadwal(Hari,jam,Hour,Min); break;
     case 2  : EEPROM.write(32,Hour);  EEPROM.write(33,Min);voicejadwal(Hari,jam,Hour,Min); break;
     case 3  : EEPROM.write(34,Hour);  EEPROM.write(35,Min);voicejadwal(Hari,jam,Hour,Min); break;
     case 4  : EEPROM.write(36,Hour);  EEPROM.write(37,Min);voicejadwal(Hari,jam,Hour,Min); break;
     case 5  : EEPROM.write(38,Hour);  EEPROM.write(39,Min);voicejadwal(Hari,jam,Hour,Min); break;
     case 6  : EEPROM.write(40,Hour);  EEPROM.write(41,Min);voicejadwal(Hari,jam,Hour,Min); break;
     case 7  : EEPROM.write(42,Hour);  EEPROM.write(43,Min);voicejadwal(Hari,jam,Hour,Min); break;
     case 8  : EEPROM.write(44,Hour);  EEPROM.write(45,Min);voicejadwal(Hari,jam,Hour,Min); break;
     case 9  : EEPROM.write(46,Hour);  EEPROM.write(47,Min);voicejadwal(Hari,jam,Hour,Min); break;
     case 10 : EEPROM.write(48,Hour);  EEPROM.write(49,Min);voicejadwal(Hari,jam,Hour,Min); break;
     case 11 : EEPROM.write(50,Hour);  EEPROM.write(51,Min);voicejadwal(Hari,jam,Hour,Min); break;
     case 12 : EEPROM.write(52,Hour);  EEPROM.write(53,Min);voicejadwal(Hari,jam,Hour,Min); break;
     case 13 : EEPROM.write(54,Hour);  EEPROM.write(55,Min);voicejadwal(Hari,jam,Hour,Min); break;
   }
 }
 else if(Hari==2)
 {
   switch(jam)
   {
     case 0  : EEPROM.write(56,Hour);  EEPROM.write(57,Min);voicejadwal(Hari,jam,Hour,Min); break;
     case 1  : EEPROM.write(58,Hour);  EEPROM.write(59,Min);voicejadwal(Hari,jam,Hour,Min); break;
     case 2  : EEPROM.write(60,Hour);  EEPROM.write(61,Min);voicejadwal(Hari,jam,Hour,Min); break;
     case 3  : EEPROM.write(62,Hour);  EEPROM.write(63,Min);voicejadwal(Hari,jam,Hour,Min); break;
     case 4  : EEPROM.write(64,Hour);  EEPROM.write(65,Min);voicejadwal(Hari,jam,Hour,Min); break;
     case 5  : EEPROM.write(66,Hour);  EEPROM.write(67,Min);voicejadwal(Hari,jam,Hour,Min); break;
     case 6  : EEPROM.write(68,Hour);  EEPROM.write(69,Min);voicejadwal(Hari,jam,Hour,Min); break;
     case 7  : EEPROM.write(70,Hour);  EEPROM.write(71,Min);voicejadwal(Hari,jam,Hour,Min); break;
     case 8  : EEPROM.write(72,Hour);  EEPROM.write(73,Min);voicejadwal(Hari,jam,Hour,Min); break;
     case 9  : EEPROM.write(74,Hour);  EEPROM.write(75,Min);voicejadwal(Hari,jam,Hour,Min); break;
     case 10 : EEPROM.write(76,Hour);  EEPROM.write(77,Min);voicejadwal(Hari,jam,Hour,Min); break;
     case 11 : EEPROM.write(78,Hour);  EEPROM.write(79,Min);voicejadwal(Hari,jam,Hour,Min); break;
     case 12 : EEPROM.write(80,Hour);  EEPROM.write(81,Min);voicejadwal(Hari,jam,Hour,Min); break;
     case 13 : EEPROM.write(82,Hour);  EEPROM.write(83,Min);voicejadwal(Hari,jam,Hour,Min); break;
   }
 }
 else if(Hari==3)
 {
   switch(jam)
   {
     case 0  : EEPROM.write(84,Hour);  EEPROM.write(85,Min);voicejadwal(Hari,jam,Hour,Min); break;
     case 1  : EEPROM.write(86,Hour);  EEPROM.write(87,Min);voicejadwal(Hari,jam,Hour,Min); break;
     case 2  : EEPROM.write(88,Hour);  EEPROM.write(89,Min);voicejadwal(Hari,jam,Hour,Min); break;
     case 3  : EEPROM.write(90,Hour);  EEPROM.write(91,Min);voicejadwal(Hari,jam,Hour,Min); break;
     case 4  : EEPROM.write(92,Hour);  EEPROM.write(93,Min);voicejadwal(Hari,jam,Hour,Min); break;
     case 5  : EEPROM.write(94,Hour);  EEPROM.write(95,Min);voicejadwal(Hari,jam,Hour,Min); break;
     case 6  : EEPROM.write(96,Hour);  EEPROM.write(97,Min);voicejadwal(Hari,jam,Hour,Min); break;
     case 7  : EEPROM.write(98,Hour);  EEPROM.write(99,Min);voicejadwal(Hari,jam,Hour,Min); break;
     case 8  : EEPROM.write(100,Hour); EEPROM.write(101,Min);voicejadwal(Hari,jam,Hour,Min); break;
     case 9  : EEPROM.write(102,Hour); EEPROM.write(103,Min);voicejadwal(Hari,jam,Hour,Min); break;
     case 10 : EEPROM.write(104,Hour); EEPROM.write(105,Min);voicejadwal(Hari,jam,Hour,Min); break;
     case 11 : EEPROM.write(106,Hour); EEPROM.write(107,Min);voicejadwal(Hari,jam,Hour,Min); break;
     case 12 : EEPROM.write(108,Hour); EEPROM.write(109,Min);voicejadwal(Hari,jam,Hour,Min); break;
     case 13 : EEPROM.write(110,Hour); EEPROM.write(111,Min);voicejadwal(Hari,jam,Hour,Min); break;
   }
 }
 else if(Hari==4)
 {
   switch(jam)
   {
     case 0  : EEPROM.write(112,Hour);  EEPROM.write(113,Min);voicejadwal(Hari,jam,Hour,Min); break;
     case 1  : EEPROM.write(114,Hour);  EEPROM.write(115,Min);voicejadwal(Hari,jam,Hour,Min); break;
     case 2  : EEPROM.write(116,Hour);  EEPROM.write(117,Min);voicejadwal(Hari,jam,Hour,Min); break;
     case 3  : EEPROM.write(118,Hour);  EEPROM.write(119,Min);voicejadwal(Hari,jam,Hour,Min); break;
     case 4  : EEPROM.write(120,Hour);  EEPROM.write(121,Min);voicejadwal(Hari,jam,Hour,Min); break;
     case 5  : EEPROM.write(122,Hour);  EEPROM.write(123,Min);voicejadwal(Hari,jam,Hour,Min); break;
     case 6  : EEPROM.write(124,Hour);  EEPROM.write(125,Min);voicejadwal(Hari,jam,Hour,Min); break;
     case 7  : EEPROM.write(126,Hour);  EEPROM.write(127,Min);voicejadwal(Hari,jam,Hour,Min); break;
     case 8  : EEPROM.write(128,Hour);  EEPROM.write(129,Min);voicejadwal(Hari,jam,Hour,Min); break;
     case 9  : EEPROM.write(130,Hour);  EEPROM.write(131,Min);voicejadwal(Hari,jam,Hour,Min); break;
     case 10 : EEPROM.write(132,Hour);  EEPROM.write(133,Min);voicejadwal(Hari,jam,Hour,Min); break;
     case 11 : EEPROM.write(134,Hour);  EEPROM.write(135,Min);voicejadwal(Hari,jam,Hour,Min); break;
     case 12 : EEPROM.write(136,Hour);  EEPROM.write(137,Min);voicejadwal(Hari,jam,Hour,Min); break;
     case 13 : EEPROM.write(138,Hour);  EEPROM.write(139,Min);voicejadwal(Hari,jam,Hour,Min); break;
   }
 }
 else if(Hari==5)
 {
   switch(jam)
   {
     case 0  : EEPROM.write(140,Hour);  EEPROM.write(141,Min);voicejadwal(Hari,jam,Hour,Min); break;
     case 1  : EEPROM.write(142,Hour);  EEPROM.write(143,Min);voicejadwal(Hari,jam,Hour,Min); break;
     case 2  : EEPROM.write(144,Hour);  EEPROM.write(145,Min);voicejadwal(Hari,jam,Hour,Min); break;
     case 3  : EEPROM.write(146,Hour);  EEPROM.write(147,Min);voicejadwal(Hari,jam,Hour,Min); break;
     case 4  : EEPROM.write(148,Hour);  EEPROM.write(149,Min);voicejadwal(Hari,jam,Hour,Min); break;
     case 5  : EEPROM.write(150,Hour);  EEPROM.write(151,Min);voicejadwal(Hari,jam,Hour,Min); break;
     case 6  : EEPROM.write(152,Hour);  EEPROM.write(153,Min);voicejadwal(Hari,jam,Hour,Min); break;
     case 7  : EEPROM.write(154,Hour);  EEPROM.write(155,Min);voicejadwal(Hari,jam,Hour,Min); break;
     case 8  : EEPROM.write(156,Hour);  EEPROM.write(157,Min);voicejadwal(Hari,jam,Hour,Min); break;
     case 9  : EEPROM.write(158,Hour);  EEPROM.write(159,Min);voicejadwal(Hari,jam,Hour,Min); break;
     case 10 : EEPROM.write(160,Hour);  EEPROM.write(161,Min);voicejadwal(Hari,jam,Hour,Min); break;
     case 11 : EEPROM.write(162,Hour);  EEPROM.write(163,Min);voicejadwal(Hari,jam,Hour,Min); break;
     case 12 : EEPROM.write(164,Hour);  EEPROM.write(165,Min);voicejadwal(Hari,jam,Hour,Min); break;
     case 13 : EEPROM.write(166,Hour);  EEPROM.write(167,Min);voicejadwal(Hari,jam,Hour,Min); break;
   }
 }
 lcd.clear();
 lcd.setCursor(1,0);
 lcd.print("SETTING JADWAL");
 lcd.setCursor(3,1);
 lcd.print("SUCCEST.!");
 delay(2000);
 lcd.clear();
}

void cekAlarm(byte hari,byte jam,byte menit)
{
  DateTime now = rtc.now();
  if (hari==0&&jam!=0)
   { if     (jam==EEPROM.read(0) && menit==EEPROM.read(1) && now.second()==30){voiceAlarm(0);}
     else if(jam==EEPROM.read(2) && menit==EEPROM.read(3) && now.second()==30){voiceAlarm(1);}
     else if(jam==EEPROM.read(4) && menit==EEPROM.read(5) && now.second()==30){voiceAlarm(2);}
     else if(jam==EEPROM.read(6) && menit==EEPROM.read(7) && now.second()==30){voiceAlarm(3);}
     else if(jam==EEPROM.read(8) && menit==EEPROM.read(9) && now.second()==30){voiceAlarm(4);}
     else if(jam==EEPROM.read(10)&& menit==EEPROM.read(11)&& now.second()==30){voiceAlarm(5);}
     else if(jam==EEPROM.read(12)&& menit==EEPROM.read(13)&& now.second()==30){voiceAlarm(6);}
     else if(jam==EEPROM.read(14)&& menit==EEPROM.read(15)&& now.second()==30){voiceAlarm(7);}
     else if(jam==EEPROM.read(16)&& menit==EEPROM.read(17)&& now.second()==30){voiceAlarm(8);}
     else if(jam==EEPROM.read(18)&& menit==EEPROM.read(19)&& now.second()==30){voiceAlarm(9);}
     else if(jam==EEPROM.read(20)&& menit==EEPROM.read(21)&& now.second()==30){voiceAlarm(10);}
     else if(jam==EEPROM.read(22)&& menit==EEPROM.read(23)&& now.second()==30){voiceAlarm(11);}
     else if(jam==EEPROM.read(24)&& menit==EEPROM.read(25)&& now.second()==30){voiceAlarm(12);}
     else if(jam==EEPROM.read(26)&& menit==EEPROM.read(27)&& now.second()==30){voiceAlarm(13);}
    }
  else if (hari==1&&jam!=0)
   { if     (jam==EEPROM.read(28)&& menit==EEPROM.read(29)&& now.second()==30){voiceAlarm(0);}
     else if(jam==EEPROM.read(30)&& menit==EEPROM.read(31)&& now.second()==30){voiceAlarm(1);}
     else if(jam==EEPROM.read(32)&& menit==EEPROM.read(33)&& now.second()==30){voiceAlarm(2);}
     else if(jam==EEPROM.read(34)&& menit==EEPROM.read(35)&& now.second()==30){voiceAlarm(3);}
     else if(jam==EEPROM.read(36)&& menit==EEPROM.read(37)&& now.second()==30){voiceAlarm(4);}
     else if(jam==EEPROM.read(38)&& menit==EEPROM.read(39)&& now.second()==30){voiceAlarm(5);}
     else if(jam==EEPROM.read(40)&& menit==EEPROM.read(41)&& now.second()==30){voiceAlarm(6);}
     else if(jam==EEPROM.read(42)&& menit==EEPROM.read(43)&& now.second()==30){voiceAlarm(7);}
     else if(jam==EEPROM.read(44)&& menit==EEPROM.read(45)&& now.second()==30){voiceAlarm(8);}
     else if(jam==EEPROM.read(46)&& menit==EEPROM.read(47)&& now.second()==30){voiceAlarm(9);}
     else if(jam==EEPROM.read(48)&& menit==EEPROM.read(49)&& now.second()==30){voiceAlarm(10);}
     else if(jam==EEPROM.read(50)&& menit==EEPROM.read(51)&& now.second()==30){voiceAlarm(11);}
     else if(jam==EEPROM.read(52)&& menit==EEPROM.read(53)&& now.second()==30){voiceAlarm(12);}
     else if(jam==EEPROM.read(54)&& menit==EEPROM.read(55)&& now.second()==30){voiceAlarm(13);}
    }
  else if (hari==2&&jam!=0)
   { if     (jam==EEPROM.read(56)&& menit==EEPROM.read(57)&& now.second()==30){voiceAlarm(0);}
     else if(jam==EEPROM.read(58)&& menit==EEPROM.read(59)&& now.second()==30){voiceAlarm(1);}
     else if(jam==EEPROM.read(60)&& menit==EEPROM.read(61)&& now.second()==30){voiceAlarm(2);}
     else if(jam==EEPROM.read(62)&& menit==EEPROM.read(63)&& now.second()==30){voiceAlarm(3);}
     else if(jam==EEPROM.read(64)&& menit==EEPROM.read(65)&& now.second()==30){voiceAlarm(4);}
     else if(jam==EEPROM.read(66)&& menit==EEPROM.read(67)&& now.second()==30){voiceAlarm(5);}
     else if(jam==EEPROM.read(68)&& menit==EEPROM.read(69)&& now.second()==30){voiceAlarm(6);}
     else if(jam==EEPROM.read(70)&& menit==EEPROM.read(71)&& now.second()==30){voiceAlarm(7);}
     else if(jam==EEPROM.read(72)&& menit==EEPROM.read(73)&& now.second()==30){voiceAlarm(8);}
     else if(jam==EEPROM.read(74)&& menit==EEPROM.read(75)&& now.second()==30){voiceAlarm(9);}
     else if(jam==EEPROM.read(76)&& menit==EEPROM.read(77)&& now.second()==30){voiceAlarm(10);}
     else if(jam==EEPROM.read(78)&& menit==EEPROM.read(79)&& now.second()==30){voiceAlarm(11);}
     else if(jam==EEPROM.read(80)&& menit==EEPROM.read(81)&& now.second()==30){voiceAlarm(12);}
     else if(jam==EEPROM.read(82)&& menit==EEPROM.read(83)&& now.second()==30){voiceAlarm(13);}
    }
  else if (hari==3&&jam!=0)
   { if     (jam==EEPROM.read(84)&& menit==EEPROM.read(85)&& now.second()==30){voiceAlarm(0);}
     else if(jam==EEPROM.read(86)&& menit==EEPROM.read(87)&& now.second()==30){voiceAlarm(1);}
     else if(jam==EEPROM.read(88)&& menit==EEPROM.read(89)&& now.second()==30){voiceAlarm(2);}
     else if(jam==EEPROM.read(90)&& menit==EEPROM.read(91)&& now.second()==30){voiceAlarm(3);}
     else if(jam==EEPROM.read(92)&& menit==EEPROM.read(93)&& now.second()==30){voiceAlarm(4);}
     else if(jam==EEPROM.read(94)&& menit==EEPROM.read(95)&& now.second()==30){voiceAlarm(5);}
     else if(jam==EEPROM.read(96)&& menit==EEPROM.read(97)&& now.second()==30){voiceAlarm(6);}
     else if(jam==EEPROM.read(98)&& menit==EEPROM.read(99)&& now.second()==30){voiceAlarm(7);}
     else if(jam==EEPROM.read(100)&& menit==EEPROM.read(101)&& now.second()==30){voiceAlarm(8);}
     else if(jam==EEPROM.read(102)&& menit==EEPROM.read(103)&& now.second()==30){voiceAlarm(9);}
     else if(jam==EEPROM.read(104)&& menit==EEPROM.read(105)&& now.second()==30){voiceAlarm(10);}
     else if(jam==EEPROM.read(106)&& menit==EEPROM.read(107)&& now.second()==30){voiceAlarm(11);}
     else if(jam==EEPROM.read(108)&& menit==EEPROM.read(109)&& now.second()==30){voiceAlarm(12);}
     else if(jam==EEPROM.read(110)&& menit==EEPROM.read(111)&& now.second()==30){voiceAlarm(13);}
    }
  else if (hari==4&&jam!=0)
   { if     (jam==EEPROM.read(112)&& menit==EEPROM.read(113)&& now.second()==30){voiceAlarm(0);}
     else if(jam==EEPROM.read(114)&& menit==EEPROM.read(115)&& now.second()==30){voiceAlarm(1);}
     else if(jam==EEPROM.read(116)&& menit==EEPROM.read(117)&& now.second()==30){voiceAlarm(2);}
     else if(jam==EEPROM.read(118)&& menit==EEPROM.read(119)&& now.second()==30){voiceAlarm(3);}
     else if(jam==EEPROM.read(120)&& menit==EEPROM.read(121)&& now.second()==30){voiceAlarm(4);}
     else if(jam==EEPROM.read(122)&& menit==EEPROM.read(123)&& now.second()==30){voiceAlarm(5);}
     else if(jam==EEPROM.read(124)&& menit==EEPROM.read(125)&& now.second()==30){voiceAlarm(6);}
     else if(jam==EEPROM.read(126)&& menit==EEPROM.read(127)&& now.second()==30){voiceAlarm(7);}
     else if(jam==EEPROM.read(128)&& menit==EEPROM.read(129)&& now.second()==30){voiceAlarm(8);}
     else if(jam==EEPROM.read(130)&& menit==EEPROM.read(131)&& now.second()==30){voiceAlarm(9);}
     else if(jam==EEPROM.read(132)&& menit==EEPROM.read(133)&& now.second()==30){voiceAlarm(10);}
     else if(jam==EEPROM.read(134)&& menit==EEPROM.read(135)&& now.second()==30){voiceAlarm(11);}
     else if(jam==EEPROM.read(136)&& menit==EEPROM.read(137)&& now.second()==30){voiceAlarm(12);}
     else if(jam==EEPROM.read(138)&& menit==EEPROM.read(139)&& now.second()==30){voiceAlarm(13);}
    }
  else if (hari==5&&jam!=0)
   { if     (jam==EEPROM.read(140)&& menit==EEPROM.read(141)&& now.second()==30){voiceAlarm(0);}
     else if(jam==EEPROM.read(142)&& menit==EEPROM.read(143)&& now.second()==30){voiceAlarm(1);}
     else if(jam==EEPROM.read(144)&& menit==EEPROM.read(145)&& now.second()==30){voiceAlarm(2);}
     else if(jam==EEPROM.read(146)&& menit==EEPROM.read(147)&& now.second()==30){voiceAlarm(3);}
     else if(jam==EEPROM.read(148)&& menit==EEPROM.read(149)&& now.second()==30){voiceAlarm(4);}
     else if(jam==EEPROM.read(150)&& menit==EEPROM.read(151)&& now.second()==30){voiceAlarm(5);}
     else if(jam==EEPROM.read(152)&& menit==EEPROM.read(153)&& now.second()==30){voiceAlarm(6);}
     else if(jam==EEPROM.read(154)&& menit==EEPROM.read(155)&& now.second()==30){voiceAlarm(7);}
     else if(jam==EEPROM.read(156)&& menit==EEPROM.read(157)&& now.second()==30){voiceAlarm(8);}
     else if(jam==EEPROM.read(158)&& menit==EEPROM.read(159)&& now.second()==30){voiceAlarm(9);}
     else if(jam==EEPROM.read(160)&& menit==EEPROM.read(161)&& now.second()==30){voiceAlarm(10);}
     else if(jam==EEPROM.read(162)&& menit==EEPROM.read(163)&& now.second()==30){voiceAlarm(11);}
     else if(jam==EEPROM.read(164)&& menit==EEPROM.read(165)&& now.second()==30){voiceAlarm(12);}
     else if(jam==EEPROM.read(166)&& menit==EEPROM.read(167)&& now.second()==30){voiceAlarm(13);}
    } 

}

void satuan(byte angka)
{
  switch(angka)
  {
    case 1 : mySerial.print("1");delay(1000); break;
    case 2 : mySerial.print("2");delay(1000); break;
    case 3 : mySerial.print("3");delay(1000); break;
    case 4 : mySerial.print("4");delay(1000); break;
    case 5 : mySerial.print("5");delay(1000); break;
    case 6 : mySerial.print("6");delay(1000); break;
    case 7 : mySerial.print("7");delay(1000); break;
    case 8 : mySerial.print("8");delay(1000); break;
    case 9 : mySerial.print("9");delay(1000); break;
   }
}
void puluhan(byte angka)
{
  int temp1,temp2;
  temp1=angka/10;temp2=angka%10;
  if(temp1==1)
  {  
   if(temp2==0){mySerial.print("o"); delay(1000);}
   if(temp2==1){mySerial.print("p"); delay(1000);}
   if(temp2==2){mySerial.print("2"); delay(1000);mySerial.print("q");delay(900);}
   if(temp2==3){mySerial.print("3"); delay(1000);mySerial.print("q");delay(900);}
   if(temp2==4){mySerial.print("4"); delay(1000);mySerial.print("q");delay(900);}
   if(temp2==5){mySerial.print("5"); delay(1000);mySerial.print("q");delay(900);}
   if(temp2==6){mySerial.print("6"); delay(1000);mySerial.print("q");delay(900);}
   if(temp2==7){mySerial.print("7"); delay(1000);mySerial.print("q");delay(900);}
   if(temp2==8){mySerial.print("8"); delay(1000);mySerial.print("q");delay(900);}
   if(temp2==9){mySerial.print("9"); delay(1000);mySerial.print("q");delay(900);}
   }
  else 
  {
    satuan(temp1);mySerial.print("r");delay(900);satuan(temp2);
  }
}

void baca(int angka)
{
  if(angka>9) puluhan(angka);
  else satuan(angka);
}

void dateTime(byte jam,byte mnt, byte tgl,byte bln,int thn)
{
  digitalWrite(A0, LOW);
  delay(2000);
  //sekarang jam
  mySerial.print("W");delay(1000);
  baca(jam);delay(1500);
  baca(mnt);
  //menit  
  if(mnt!=0)mySerial.print("R");delay(800); 
  //tanggal
  mySerial.print("S");delay(500);
  baca(tgl);delay(500);
  //bulan
  mySerial.print("T");delay(500);
  baca(bln);delay(500);
  //tahun 2000
  mySerial.print("U");delay(600);
  mySerial.print("V");delay(1000);
  baca(thn);
  delay(2000);
  digitalWrite(A0, HIGH);
}

void voicejadwal(byte Hari,byte jam,byte Hour,byte Min)
{
  digitalWrite(A0, LOW);
  delay(2000);
  mySerial.print("Q");delay(800);
  switch(Hari)
  {
    case 0 : mySerial.print("s"); delay(1500); break;
    case 1 : mySerial.print("t"); delay(1500); break;
    case 2 : mySerial.print("u"); delay(1500); break;
    case 3 : mySerial.print("v"); delay(1500); break;
    case 4 : mySerial.print("w"); delay(1500); break;
    case 5 : mySerial.print("x"); delay(1500); break;
  }
  switch(jam)
  {
    case 0  : mySerial.print("a"); delay(1000); break;
    case 1  : mySerial.print("b"); delay(1000); break; 
    case 2  : mySerial.print("c"); delay(1000); break;
    case 3  : mySerial.print("d"); delay(1000); break;
    case 4  : mySerial.print("e"); delay(1000); break;
    case 5  : mySerial.print("f"); delay(1000); break;
    case 6  : mySerial.print("g"); delay(1000); break;
    case 7  : mySerial.print("h"); delay(1000); break;
    case 8  : mySerial.print("i"); delay(1000); break;
    case 9  : mySerial.print("j"); delay(1000); break;
    case 10 : mySerial.print("k"); delay(1000); break;
    case 11 : mySerial.print("l"); delay(1000); break;
    case 12 : mySerial.print("m"); delay(1000); break;
    case 13 : mySerial.print("n"); delay(1000); break;
  }
  delay(500);
  mySerial.print("O"); delay(1400);
  mySerial.print("P"); delay(800);
  baca(Hour); //delay(500);
  if(Min==0){mySerial.print("X.mp3"); delay(900);}
  else {baca(Min);} 
  delay(2000);
  digitalWrite(A0, HIGH);
}

void voiceAlarm(byte jam)
{
  music=false;
  digitalWrite(A0, LOW);
  digitalWrite(A1, HIGH);
  delay(2000);
  switch(jam)
  {
    case 0  : mySerial.print("A"); delay(60000);break;
    case 1  : mySerial.print("B"); delay(30000); break;
    case 2  : mySerial.print("C"); delay(30000); break;
    case 3  : mySerial.print("K"); delay(10000); 
              mySerial.print("D"); delay(30000); break;
    case 4  : mySerial.print("E"); delay(30000); break;
    case 5  : mySerial.print("F"); delay(30000); break;
    case 6  : mySerial.print("G"); delay(30000); break;
    case 7  : mySerial.print("H"); delay(30000); break;
    case 8  : mySerial.print("I"); delay(30000); break;
    case 9  : mySerial.print("J"); delay(30000); break;
    case 10 : mySerial.print("K"); delay(30000); break;
    case 11 : mySerial.print("L"); delay(30000); break;
    case 12 : mySerial.print("M"); delay(30000); 
              if(EEPROM.read(200)==1)music=true; break;
    case 13 : mySerial.print("N"); delay(30000); break;
  }
  delay(2000);
  digitalWrite(A0,HIGH);
}
void tampilLCD(byte hari, byte tgl,byte bln, byte thn, byte jam, byte menit, byte detik)
{
  if (detik==0)lcd.clear();
  switch(hari)
  {
    case 0 : sprintf(tampil,"SENIN - %d%d/%d%d/%d%d",tgl/10,tgl%10,bln/10,bln%10,thn/10,thn%10);
             lcd.setCursor(0,1);lcd.print(tampil); break;
    case 1 : sprintf(tampil,"SELASA  %d%d/%d%d/%d%d",tgl/10,tgl%10,bln/10,bln%10,thn/10,thn%10);
             lcd.setCursor(0,1);lcd.print(tampil); break;
    case 2 : sprintf(tampil,"RABU  - %d%d/%d%d/%d%d",tgl/10,tgl%10,bln/10,bln%10,thn/10,thn%10);
             lcd.setCursor(0,1);lcd.print(tampil); break;
    case 3 : sprintf(tampil,"KAMIS - %d%d/%d%d/%d%d",tgl/10,tgl%10,bln/10,bln%10,thn/10,thn%10);
             lcd.setCursor(0,1);lcd.print(tampil); break;
    case 4 : sprintf(tampil,"JUM'AT  %d%d/%d%d/%d%d",tgl/10,tgl%10,bln/10,bln%10,thn/10,thn%10);
             lcd.setCursor(0,1);lcd.print(tampil); break;
    case 5 : sprintf(tampil,"SABTU - %d%d/%d%d/%d%d",tgl/10,tgl%10,bln/10,bln%10,thn/10,thn%10);
             lcd.setCursor(0,1);lcd.print(tampil); break;
  }
  sprintf(tampil,"%d%d:%d%d:%d%d",jam/10,jam%10,menit/10,menit%10,detik/10,detik%10);
  lcd.setCursor(4,0);lcd.print(tampil);
}

void bazer()
{
  digitalWrite(8,0);
  delay(120);
  digitalWrite(8,1);
  delay(50);
  digitalWrite(8,0);
  delay(120);
  digitalWrite(8,1);
  }
  
void setup() {
  Serial.begin(9600);
  mySerial.begin(1200);
  lcd.begin(16, 2);
  #ifdef AVR
  Wire.begin();
  #else
  Wire1.begin(); 
  #endif
  rtc.begin();
  //rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  //rtc.adjust(DateTime(2017, 7, 12, 7, 00, 40));
  //inisialisasi pin Relay
  pinMode(A0, OUTPUT);
  digitalWrite(A0,1);
  pinMode(A1, OUTPUT);
  digitalWrite(A1,1);
  pinMode(8, OUTPUT);
  digitalWrite(8,1);
  //setdefault();
}
 
void loop() {
  
while(Serial.available()>0)
  {
  bazer();
  delay(25); byte i;
  for(i=0;i<30;i++)
    {
     key_command = Serial.read();
     message[i]=key_command;
    }
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
      DateTime now = rtc.now();
      dateTime(now.hour(),now.minute(),now.day(),now.month(),(now.year()-2000));
     }
  else if (message[0]>47 && message[0]<58 && message[1]>47 && message[1]<58&&
      message[2]>47 && message[2]<58 &&
      message[3]>47 && message[3]<58 &&message[4]>47 && message[4]<58 && 
      message[6]>47 && message[6]<58 &&message[7]>47 && message[7]<58 )
      {
      d_hari[0]=message[0];
      hari=atoi(d_hari);
      d_waktu[0]=message[1];
      d_waktu[1]=message[2];
      waktu=atoi(d_waktu);
      d_jam[0]=message[3];
      d_jam[1]=message[4];
      jam=atoi(d_jam);
      d_men[0]=message[6];
      d_men[1]=message[7];
      men=atoi(d_men);
      SaveDataJadwal(hari,waktu,jam,men); 
      }
  else if (message[0] == 'y'){
      digitalWrite(A0,0);
      delay(1000);
      mySerial.print("y"); 
      delay(1000);
      mySerial.print("p"); 
      }
  else if (message[0] == 'v') {
      d_vol[0]='v';
      d_vol[1]=message[1];
      d_vol[2]=message[2];
      d_vol[3]=message[3];
      mySerial.print(d_vol);
      } 
  else if (message[0] == 'T') {
      d_vol[0]=message[1];
      d_vol[1]=message[2];
      int test=atoi(d_vol);
      voiceAlarm(test);
      } 
  else if (message[0] == 'c'){
      DateTime now = rtc.now();
      dateTime(now.hour(),now.minute(),now.day(),now.month(),(now.year()-2000));
      }
  else if (message[0] == 'p'){
      digitalWrite(A0,0);
      digitalWrite(A1,0);
      }
  else if (message[0] == 's'){
      mySerial.print("s");
      delay(1000);
      digitalWrite(A0,1);
      }
  else if (message[0] == 'S'){
      digitalWrite(A0,1);
      digitalWrite(A1,1);
      }
  else if (message[0] == 'd'){
      setdefault();
      digitalWrite(A0,0);
      delay(1000);
      mySerial.print("Z");
      delay(20000);
      digitalWrite(A0,1);
      }
  else if (message[0] == 'n'){
      EEPROM.write(200,1);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("MUSIK ISTIRAHAT");
      lcd.setCursor(2,1);
      lcd.print("DINYALAKAN.!");
      delay(3000);
      lcd.clear();
      }
  else if (message[0] == 'f'){
      EEPROM.write(200,0);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("MUSIK ISTIRAHAT");
      lcd.setCursor(2,1);
      lcd.print("DIMATIKAN.!");
      delay(3000);
      lcd.clear();
      }
  }
 DateTime now = rtc.now();
 int datajam = now.hour();
 int datamen = now.minute();
 int datadet = now.second();
 H_hari();
 cekAlarm(N_hari,now.hour(),now.minute());
 tampilLCD(N_hari,now.day(),now.month(),now.year()-2000,now.hour(),now.minute(),now.second());
 if(music==true){digitalWrite(A0,0);digitalWrite(A1,0);}
 if (datajam==6&&datamen==30&&datadet==30)
 {
   switch(N_hari)
   {
     case 0 : digitalWrite(A0, LOW); digitalWrite(A1, LOW); delay (4000); mySerial.print("q0"); break;
     case 1 : digitalWrite(A0, LOW); digitalWrite(A1, LOW); delay (4000); mySerial.print("q1"); break;
     case 2 : digitalWrite(A0, LOW); digitalWrite(A1, LOW); delay (4000); mySerial.print("q2"); break;
     case 3 : digitalWrite(A0, LOW); digitalWrite(A1, LOW); delay (4000); mySerial.print("q3"); break;
     case 4 : digitalWrite(A0, LOW); digitalWrite(A1, LOW); delay (4000); mySerial.print("q4"); break;
     case 5 : digitalWrite(A0, LOW); digitalWrite(A1, LOW); delay (4000); mySerial.print("q5"); break;
   }
 }
}
