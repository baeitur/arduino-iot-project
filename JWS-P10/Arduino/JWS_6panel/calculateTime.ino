const float lunarY = 354.367068f;

//------------------------------------------
// Function calculate Hijriah Date
//------------------------------------------

long Days(uint16_t Y,uint8_t M,uint8_t D)
  {
    if (M < 3)
      { 
      Y -= 1; 
      M +=12;
      }
    Y = Y - 2000;
    long ndays= floor(365.25*Y)+floor(30.6001*(M + 1))+floor(Y/100)+floor(Y/400)+D+196;
    //long ndays= d1 + d2 - A + B + D + 196;
    return ndays;
  }

long DaysHijri(uint16_t Y,uint8_t M,uint8_t D)
  {
    Y = Y - 1420;   
    long hari = floor(29.5*M - 28.999)+floor(lunarY*Y)+D ;
    return hari;
  }
  
hijir_date toHijri(uint16_t Y, uint8_t M, uint8_t D,uint8_t cor) // core --> corection date today=0   yesterday=-1 tomorrow=1
  {
    hijir_date BuffDate;
    long nday = Days(Y, M, D)+ Prm+ cor;    
    long tahun = floor(nday/lunarY) + 1420;
    long bulan = 1;
    long harike = 1;
    while(DaysHijri(tahun, bulan, 1) <= nday){tahun++;};
    tahun--;
    while(DaysHijri(tahun, bulan, 1) <= nday){bulan++;};
    bulan--;
    harike = 1 + nday - DaysHijri(tahun, bulan, 1);
    if (bulan == 13){bulan = 12; harike += 29;};
    BuffDate.hD = harike;
    BuffDate.hM = bulan;
    BuffDate.hY = tahun;
    return BuffDate;
  }

//------------------------------------------
// Function calculate pasaran jawa
//------------------------------------------
  
int wetonJawa()
{
 DateTime now = rtc.now();
 long tahun=now.year();
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
 return ((j_tahun+(kabisat-nonkabisat)+kabisat1)+bulan+(now.day()-1))%5;
}


