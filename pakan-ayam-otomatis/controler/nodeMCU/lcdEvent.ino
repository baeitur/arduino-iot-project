String msg;
boolean Start,End;
char inChar;

/*
 * type D = CHANGE DATETIME
 * type R = STATE RELAY
 * type T = CHANGE TIMER
 * type W = CHANGE WIFI CONFIG
 */

void serialEvent()
{
 if(Serial.available()>0)
 {
  inChar = (char)Serial.read();
  if (inChar == '*'){ 
    Start = true;
  }else if(inChar == '#'){
    Start = false;
    End = true;
  }
  if (Start)
    msg += inChar;
  }
 if(End){
  char type = msg.charAt(1);
  msg.remove(0,2);
  String data = msg;
  //Serial.println(msg);
  exeData(type,data);
  End=false;
  msg="";
 }
}

void exeData(char type, String data){
  if(type == 'R'){
    int data = msg.toInt();
    relay_state = data;
  }else if(type == 'D'){

    // data of time
    int jam = getValue(data,' ', 0).toInt(); 
    int men = getValue(data,' ', 1).toInt(); 
    int det = getValue(data,' ', 2).toInt(); 
    // data of date
    int tgl = getValue(data,' ', 3).toInt(); 
    int bln = getValue(data,' ', 4).toInt(); 
    int thn = getValue(data,' ', 5).toInt(); 

    char buffer[15];
    sprintf(buffer, "%02d:%02d:%02d %02d/%02d/%04d", jam,men,det,tgl,bln,thn);
    //Serial.print(buffer);
    Rtc.SetDateTime(RtcDateTime(thn, bln, tgl, jam, men, det));
  }else if(type == 'T'){
    // data of time
    int on1  = getValue(data,' ', 0).toInt(); 
    int off1 = getValue(data,' ', 1).toInt(); 
    int on2  = getValue(data,' ', 2).toInt(); 
    int off2 = getValue(data,' ', 3).toInt();
    int on3  = getValue(data,' ', 4).toInt(); 
    int off3 = getValue(data,' ', 5).toInt();

    char buffer[100];
    sprintf(buffer, "{\"on1\":\"%d\",\"off1\":\"%d\",\"on2\":\"%d\",\"off2\":\"%d\",\"on3\":\"%d\",\"off3\":\"%d\"}", on1,off1,on2,off2,on3,off3);
    //Serial.print(buffer);
    updateTimerConfig(buffer);
    bacaParameter();
  }else if(type == 'W'){
    // data of time
    String ssid     = getValue(data,' ', 0); 
    String password = getValue(data,' ', 1); 
    char buffer[50];
    sprintf(buffer, "{\"ssid\":\"%s\",\"pwd\":\"%s\"}", ssid,password);
    //Serial.print(buffer);
    updateWifiConfig(buffer);
    bacaParameter();
  }
}

void sendTime(){  
  char buffer[5];
  sprintf(buffer, "%02d", rJam);
  Serial.print("tH.txt=\"");
  Serial.print(buffer);
  Serial.print("\"");
  Serial.write(0xff);
  Serial.write(0xff);
  Serial.write(0xff);

  sprintf(buffer, "%02d", rMen);
  Serial.print("tM.txt=\"");
  Serial.print(buffer);
  Serial.print("\"");
  Serial.write(0xff);
  Serial.write(0xff);
  Serial.write(0xff);

  sprintf(buffer, "%02d", rDet);
  Serial.print("tS.txt=\"");
  Serial.print(buffer);
  Serial.print("\"");
  Serial.write(0xff);
  Serial.write(0xff);
  Serial.write(0xff);
}

void sendDate(){  
  char buffer[25];
  sprintf(buffer, "%s, %02d %s %04d", namaHari[rHar], rTgl, namaBulan[rBul], rTah);
  Serial.print("tDate.txt=\"");
  Serial.print(buffer);
  Serial.print("\"");
  Serial.write(0xff);
  Serial.write(0xff);
  Serial.write(0xff);
}

void sendTemp(){  
  char buffer[5];
  char tmp[5];
  dtostrf(rTmp, -3, 1, tmp);
  sprintf(buffer, "%s", tmp);
  Serial.print("ttmp.txt=\"");
  Serial.print(buffer);
  Serial.print("\"");
  Serial.write(0xff);
  Serial.write(0xff);
  Serial.write(0xff);
}

void sendState(boolean state){ 
  char buffer[5];
  if(state == true){
    sprintf(buffer, "ON");
  }else {
    sprintf(buffer, "OFF");
  } 
  Serial.print("state.txt=\"");
  Serial.print(buffer);
  Serial.print("\"");
  Serial.write(0xff);
  Serial.write(0xff);
  Serial.write(0xff);
}

void sendTimer(String timer1,String timer2,String timer3){  
  Serial.print("bodyt1.txt=\"");
  Serial.print(timer1.c_str());
  Serial.print("\"");
  Serial.write(0xff);
  Serial.write(0xff);
  Serial.write(0xff);
  
  Serial.print("bodyt2.txt=\"");
  Serial.print(timer2.c_str());
  Serial.print("\"");
  Serial.write(0xff);
  Serial.write(0xff);
  Serial.write(0xff);

  Serial.print("bodyt3.txt=\"");
  Serial.print(timer3.c_str());
  Serial.print("\"");
  Serial.write(0xff);
  Serial.write(0xff);
  Serial.write(0xff);
}


void conState(boolean state){ 
  char buffer1[5];
  char buffer2[40];
  if(state){
    sprintf(buffer1, "Connected");
    sprintf(buffer2, "PAKAN AYAM OTOMATIS BERBASIS IOT");
  }else {
    sprintf(buffer1, "Not Connect");
    sprintf(buffer2, "KONEKSI GAGAL PERIKSA KEMBALI SAMBUNGAN INTERNET ANDA");
  } 
  Serial.print("con.txt=\"");
  Serial.print(buffer1);
  Serial.print("\"");
  Serial.write(0xff);
  Serial.write(0xff);
  Serial.write(0xff);
  Serial.print("info.txt=\"");
  Serial.print(buffer2);
  Serial.print("\"");
  Serial.write(0xff);
  Serial.write(0xff);
  Serial.write(0xff);
}

void sendData(){  
  sendTime();
  sendDate();
  sendTemp();
  sendState(relay_state);
  conState(status_connect);
}
