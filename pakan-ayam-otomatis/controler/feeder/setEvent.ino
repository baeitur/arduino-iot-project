char message[65];
int i; char data;
char d_jam[4],d_men[5],d_det[6],d_tgl[4],d_bln[5],d_thn[6];
char on[6],off[6];
int jam,men,det,tgl,bln,thn;
 
void serialEvent()
{
 while (LCDHMI.available()>0) {
  delay(25);
  for(i=0;i<65;i++)
  {
   data = LCDHMI.read();
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
    }
   else if(message[0]=='a' && message[1]>47 && 
   message[1]<58 && message[2]>47 && message[2]<58 && 
   message[4]>47 && message[4]<58 && message[5]>47 && message[5]<58 &&
   message[7]>47 && message[7]<58 && message[8]>47 && message[8]<58 &&
   message[10]>47 && message[10]<58 && message[11]>47 && message[11]<58) 
    {
      on[0]=message[1];
      on[1]=message[2];
      on[2]=message[4];
      on[3]=message[5];
      ON1 = atoi(on);
      EEPROMWriteInt(10,ON1);
      
      off[0]=message[7];
      off[1]=message[8];
      off[2]=message[10];
      off[3]=message[11];
      OFF1 = atoi(off); 
      EEPROMWriteInt(15,OFF1);   
     }
   else if(message[0]=='b' && message[1]>47 && 
   message[1]<58 && message[2]>47 && message[2]<58 && 
   message[4]>47 && message[4]<58 && message[5]>47 && message[5]<58 &&
   message[7]>47 && message[7]<58 && message[8]>47 && message[8]<58 &&
   message[10]>47 && message[10]<58 && message[11]>47 && message[11]<58) 
    {
      on[0]=message[1];
      on[1]=message[2];
      on[2]=message[4];
      on[3]=message[5];
      ON2 = atoi(on);
      EEPROMWriteInt(20,ON2);
      
      off[0]=message[7];
      off[1]=message[8];
      off[2]=message[10];
      off[3]=message[11];
      OFF2 = atoi(off); 
      EEPROMWriteInt(25,OFF2);  
     }
   else if(message[0]=='c' && message[1]>47 && 
   message[1]<58 && message[2]>47 && message[2]<58 && 
   message[4]>47 && message[4]<58 && message[5]>47 && message[5]<58 &&
   message[7]>47 && message[7]<58 && message[8]>47 && message[8]<58 &&
   message[10]>47 && message[10]<58 && message[11]>47 && message[11]<58) 
    {
      on[0]=message[1];
      on[1]=message[2];
      on[2]=message[4];
      on[3]=message[5];
      ON3 = atoi(on);
      EEPROMWriteInt(30,ON3);
      
      off[0]=message[7];
      off[1]=message[8];
      off[2]=message[10];
      off[3]=message[11];
      OFF3 = atoi(off); 
      EEPROMWriteInt(35,OFF3);     
    }
   else if(message[0]=='d' && message[1]>47 && 
   message[1]<58 && message[2]>47 && message[2]<58 && 
   message[4]>47 && message[4]<58 && message[5]>47 && message[5]<58 &&
   message[7]>47 && message[7]<58 && message[8]>47 && message[8]<58 &&
   message[10]>47 && message[10]<58 && message[11]>47 && message[11]<58) 
    {
      on[0]=message[1];
      on[1]=message[2];
      on[2]=message[4];
      on[3]=message[5];
      ONL = atoi(on);
      EEPROMWriteInt(40,ONL);
      
      off[0]=message[7];
      off[1]=message[8];
      off[2]=message[10];
      off[3]=message[11];
      OFFL = atoi(off); 
      EEPROMWriteInt(45,OFFL);     
    }    
   else if(message[0]== 'A'){
     controlManual = true;
    }
   else if(message[0]== 'B'){
    controlManual = false;
    }
  }
}
