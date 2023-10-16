
// WIFI

String message, XML;

//WEB Server
ESP8266WebServer server(80);
ESP8266HTTPUpdateServer httpUpdater;

// Sebagai Station
const char* wifissid = "SSID"; //kalau gagal konek
const char* wifipassword = "";

// Sebagai AccessPoint
const char* ssid = "JWSP10"; //kalau gagal konek
const char* password = "12345678";

IPAddress local_ip(192, 168, 28, 1);
IPAddress gateway(192, 168, 28, 1);
IPAddress netmask(255, 255, 255, 0);



void wifiConnect() {
  WiFi.softAPdisconnect(true);
  WiFi.disconnect();
  delay(1000);

  Serial.println("Mencoba sambungan ke Hotspot atau Router");
  WiFi.mode(WIFI_STA);
  WiFi.begin(wifissid, wifipassword);
  
  unsigned long startTime = millis();
  
  while (WiFi.status() != WL_CONNECTED) {  
    delay(500);
    Serial.print(".");
    
    if (millis() - startTime > 3000) {
      Serial.println(" ");
      break;
    }   
  }
  
  if (WiFi.status() == WL_CONNECTED) {   
    Serial.print("MAC: ");
    Serial.println(WiFi.macAddress());
    Serial.print("IP: ");
    Serial.println(WiFi.localIP());
    
  } else {  
    Serial.println("Gagal tersambung ke Hotspot, mode Hotspot aktif.");
    
    WiFi.mode(WIFI_AP);
    WiFi.softAPConfig(local_ip, gateway, netmask);
    WiFi.softAP(ssid, password);
    Serial.print("MAC: ");
    Serial.println(WiFi.macAddress());
    Serial.print("IP: ");
    Serial.println(local_ip);
  }
}

void cekUpadateDateTime(){
 // Kalau ada perubahan tanggal
    if (server.hasArg("date")) {
      uint16_t jam;
      uint8_t menit;
      uint8_t detik;      
      String sd=server.arg("date");
      String lastSd;
    
      jam = ((sd[0]-'0')*1000)+((sd[1]-'0')*100)+((sd[2]-'0')*10)+(sd[3]-'0');
      menit = ((sd[5]-'0')*10)+(sd[6]-'0');
      detik = ((sd[8]-'0')*10)+(sd[9]-'0');
      
      if (sd != lastSd){
        RtcDateTime now = Rtc.GetDateTime();
        uint8_t hour = now.Hour();
        uint8_t minute = now.Minute();
        Rtc.SetDateTime(RtcDateTime(jam, menit, detik, hour, minute, 0));
        lastSd=sd;
      }
      BacaRTC();
      server.send ( 404 ,"text", message );
    }

 // Kalau ada perubahaan jam
    if (server.hasArg("time")) {
      
      String st=server.arg("time");
      String lastSt;
      uint8_t jam = ((st[0]-'0')*10)+(st[1]-'0');
      uint8_t menit = ((st[3]-'0')*10)+(st[4]-'0');
      
      if (st != lastSt){
         RtcDateTime now = Rtc.GetDateTime();
         uint16_t year = now.Year();
         uint8_t month = now.Month();
         uint8_t day = now.Day();
         Rtc.SetDateTime(RtcDateTime(year, month, day, jam, menit, 0));
         lastSt=st;
       }    
       BacaRTC(); 
       server.send ( 404 ,"text", message );
    }
}

//----------------------------------------------------------------------
// XML UNTUK JEMBATAN DATA MESIN DENGAN WEB

void XMLWaktu(){

  XML="<?xml version='1.0'?>";
  XML+="<t>";

    XML+="<Tahun>";
    XML+=rTah;
    XML+="</Tahun>";
    
    XML+="<Bulan>";
    XML+=rBul;
    XML+="</Bulan>";
    
    XML+="<Tanggal>";
    XML+=rTgl;
    XML+="</Tanggal>";
    
    XML+="<Jam>";
      if(rJam<10){
        XML+="0";
        XML+=rJam;
      }else{XML+=rJam;}
    XML+="</Jam>";
    
    XML+="<Menit>";
      if(rMen<10){
        XML+="0";
        XML+=rMen;
      }else{XML+=rMen;}
    XML+="</Menit>";
    
    XML+="<Detik>";
      if(rDet<10){
        XML+="0";
        XML+=rDet;
      }else{XML+=rDet;}
    XML+="</Detik>";
    
    XML+="<Suhu>";
    XML+= celsius - 5;
    XML+="</Suhu>";
    
  XML+="</t>"; 
}


void XMLDataJWS(){

  XML="<?xml version='1.0'?>";
  XML+="<t>";

    XML+="<IqomahSubuh>";
    XML+= configjws.iqmhs;
    XML+="</IqomahSubuh>";
    
    XML+="<IqomahDzuhur>";
    XML+= configjws.iqmhd;
    XML+="</IqomahDzuhur>";
    
    XML+="<IqomahAshar>";
    XML+= configjws.iqmha;
    XML+="</IqomahAshar>";
    
    XML+="<IqomahMaghrib>";
    XML+= configjws.iqmhm;
    XML+="</IqomahMaghrib>";
    
    XML+="<IqomahIsya>";
    XML+= configjws.iqmhi;
    XML+="</IqomahIsya>";
    
    XML+="<DurasiAdzan>";
    XML+= configjws.durasiadzan;
    XML+="</DurasiAdzan>";
    
    XML+="<Latitude>";
    XML+= configjws.latitude;
    XML+="</Latitude>";
    
    XML+="<Longitude>";
    XML+= configjws.longitude;
    XML+="</Longitude>";
    
    XML+="<ZonaWaktu>";
    XML+= configjws.zonawaktu;
    XML+="</ZonaWaktu>";
    
    XML+="<Hilal>";
    XML+= configjws.hilal;
    XML+="</Hilal>";

    XML+="<Ihtiyatis>";
    XML+= configjws.ihtis;
    XML+="</Ihtiyatis>";

    XML+="<Ihtiyatiq>";
    XML+= configjws.ihtiq;
    XML+="</Ihtiyatiq>";

    XML+="<Ihtiyatid>";
    XML+= configjws.ihtid;
    XML+="</Ihtiyatid>";

    XML+="<Ihtiyatia>";
    XML+= configjws.ihtia;
    XML+="</Ihtiyatia>";

    XML+="<Ihtiyatim>";
    XML+= configjws.ihtim;
    XML+="</Ihtiyatim>";

    XML+="<Ihtiyatii>";
    XML+= configjws.ihtii;
    XML+="</Ihtiyatii>";
       
    XML+="<Murottalt>";
    XML+= configmurottal.murottalt;
    XML+="</Murottalt>";

    XML+="<Murottals>";
    XML+= configmurottal.murottals;
    XML+="</Murottals>";

    XML+="<Murottald>";
    XML+= configmurottal.murottald;
    XML+="</Murottald>";

    XML+="<Murottala>";
    XML+= configmurottal.murottala;
    XML+="</Murottala>";

    XML+="<Murottalm>";
    XML+= configmurottal.murottalm;
    XML+="</Murottalm>";

    XML+="<Murottali>";
    XML+= configmurottal.murottali;
    XML+="</Murottali>";

    XML+="<Murottalj>";
    XML+= configmurottal.murottalj;
    XML+="</Murottalj>";

    XML+="<Jpahing>";
    XML+= configjumat.jpahing;
    XML+="</Jpahing>";

    XML+="<Jpon>";
    XML+= configjumat.jpon;
    XML+="</Jpon>";

    XML+="<Jwage>";
    XML+= configjumat.jwage;
    XML+="</Jwage>";

    XML+="<Jkliwon>";
    XML+= configjumat.jkliwon;
    XML+="</Jkliwon>";

    XML+="<Jlegi>";
    XML+= configjumat.jlegi;
    XML+="</Jlegi>";
    
    XML+="<NamaMasjid>";
    XML+= configinfo.namamasjid;
    XML+="</NamaMasjid>";

    XML+="<Info1>";
    XML+= configinfo.info1;
    XML+="</Info1>";

    XML+="<Info2>";
    XML+= configinfo.info2;
    XML+="</Info2>";

    XML+="<Info3>";
    XML+= configinfo.info3;
    XML+="</Info3>";

  XML+="</t>"; 
}


void handleXMLWaktu(){
  XMLWaktu();
  server.send(200,"text/xml",XML);
}

void handleXMLDataJWS(){
  XMLDataJWS();
  server.send(200,"text/xml",XML);
}

void handleSettingJwsUpdate() {
  String datajws = server.arg("plain");
  updateJwsConfig(datajws);
}

void handleSettingMurottalUpdate() {
  String datamurottal = server.arg("plain");
  updateMurottalConfig(datamurottal);
}

void handleSettingJumatUpdate() {
  String datajumat = server.arg("plain");
  updateJumatConfig(datajumat);
}

void handleSettingInfoUpdate() {
  String datainfo = server.arg("plain");
  updateInfoConfig(datainfo);
}
