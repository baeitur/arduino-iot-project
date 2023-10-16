// ----------------------
// FS CONFIG

struct ConfigTimer {
  uint16_t on1;  // menit
  uint16_t off1; // menit
  uint16_t on2;  // menit
  uint16_t off2; // menit
  uint16_t on3;  // menit
  uint16_t off3; // menit
};

struct ConfigWifi { 
  char ssid[168];
  char pwd[168];
};

const char *fileconfigtimer = "/configjws.json";
const char *fileconfigwifi = "/configinfo.json";

ConfigTimer configtimer;
ConfigWifi configwifi;

// -------------------------------------------
// Membuat file config JWS JSON di File Sistem

void membuatDataAwal() {

  String datatimer      = "{\"on1\":\"600\",\"off1\":\"605\",\"on2\":\"1200\",\"off2\":\"1205\",\"on3\":\"1800\",\"off3\":\"1805\"}";
  String datawifi     = "{\"ssid\":\"smart sistem\",\"pwd\":\"smart123 \"}";
  
  DynamicJsonDocument doctimer(512);
  DeserializationError error1 = deserializeJson(doctimer, datatimer);

  DynamicJsonDocument docwifi(512);
  DeserializationError error2 = deserializeJson(docwifi, datawifi);

  File configFileTimer   = LittleFS.open(fileconfigtimer, "w");
  File configFileWifi   = LittleFS.open(fileconfigwifi, "w");
  
  if (!configFileTimer||!configFileWifi) {
    Serial.println("Gagal membuat file json");
    return;
  }
  
  serializeJson(doctimer,configFileTimer);
  serializeJson(docwifi,configFileWifi);
  
  if (error1||error2) {   
    Serial.print(F("deserializeJson() gagal kode sebagai berikut: "));
    Serial.println(error1.c_str());
    Serial.println(error2.c_str());
    return; 
  } else {
    configFileTimer.close();
    configFileWifi.close();
    Serial.println("Berhasil membuat file .json"); 
  }  
}

// -------------------------------------------
// Membaca file config JWS JSON di File Sistem

void loadDataConfig(const char *fileconfigtimer, ConfigTimer &configtimer,const char *fileconfigwifi, ConfigWifi &configwifi) {  

  File configFileTimer = LittleFS.open(fileconfigtimer, "r");
  File configFileWifi = LittleFS.open(fileconfigwifi, "r");
  
  if (!configFileTimer||!configFileWifi) { 
    Serial.println("Gagal membuka json untuk dibaca");
    membuatDataAwal();
    Serial.println("Sistem restart...");
    ESP.restart(); 
  }

  size_t size1 = configFileTimer.size();
  std::unique_ptr<char[]> buf1(new char[size1]);
  configFileTimer.readBytes(buf1.get(), size1);

  size_t size2 = configFileWifi.size();
  std::unique_ptr<char[]> buf2(new char[size2]);
  configFileWifi.readBytes(buf2.get(), size2);

  DynamicJsonDocument doctimer(512);
  DeserializationError error1 = deserializeJson(doctimer, buf1.get());

  DynamicJsonDocument docwifi(512);
  DeserializationError error2 = deserializeJson(docwifi, buf2.get());

  
  if (error1||error2) {
    Serial.println("Gagal parse fileconfig...");
    return;
  }
  
  configtimer.on1  = doctimer["on1"];
  configtimer.off1 = doctimer["off1"];
  configtimer.on2  = doctimer["on2"];
  configtimer.off2 = doctimer["off2"];
  configtimer.on3  = doctimer["on3"];
  configtimer.off3 = doctimer["off3"];
      
  strlcpy(configwifi.ssid, docwifi["ssid"] | "", sizeof(configwifi.ssid));
  strlcpy(configwifi.pwd,  docwifi["pwd"]  | "", sizeof(configwifi.pwd));
  
  configFileTimer.close(); 
  configFileWifi.close(); 
}

void updateTimerConfig(String datatimer){
  DynamicJsonDocument doc(512);
  DeserializationError error = deserializeJson(doc, datatimer);

  File configFileTimer = LittleFS.open(fileconfigtimer, "w");
  if (!configFileTimer) {
    Serial.println("Gagal membuka Info configFileTimer untuk ditulis");
    return;
  }
  
  serializeJson(doc, configFileTimer);

  if (error) {
    Serial.print(F("deserializeJson() gagal kode sebagai berikut: "));
    Serial.println(error.c_str());
    return; 
  } else {
    configFileTimer.close();
    Serial.println("Berhasil mengubah configFileTimer");
    loadDataConfig(fileconfigtimer, configtimer, fileconfigwifi, configwifi);
  }
}


void updateWifiConfig(String datawifi){
  DynamicJsonDocument doc(512);
  DeserializationError error = deserializeJson(doc, datawifi);

  File configFileWifi = LittleFS.open(fileconfigwifi, "w");
  if (!configFileWifi) {
    Serial.println("Gagal membuka file configFilewifi untuk ditulis");
    return;
  }
  
  serializeJson(doc, configFileWifi);

  if (error) {
    Serial.print(F("deserializeJson() gagal kode sebagai berikut: "));
    Serial.println(error.c_str());
    return; 
  } else {
    configFileWifi.close();
    Serial.println("Berhasil mengubah configFileWifi");
    loadDataConfig(fileconfigtimer, configtimer, fileconfigwifi, configwifi);
  }
}


// -------------------------------------------
// MEMBACA PARAMETER YANG TERSIMPAN

void bacaParameter() {

  Serial.println(" ");
  Serial.println("PARAMETER TERSIMPAN");
  Serial.print("TIMER ON1     : "); Serial.println(configtimer.on1);
  Serial.print("TIMER OFF1    : "); Serial.println(configtimer.off1);
  Serial.print("TIMER ON2     : "); Serial.println(configtimer.on2);
  Serial.print("TIMER OFF1    : "); Serial.println(configtimer.off2);
  Serial.print("TIMER ON3     : "); Serial.println(configtimer.on3);
  Serial.print("TIMER OFF3    : "); Serial.println(configtimer.off3);
  
  Serial.print("SSID          : "); Serial.println(configwifi.ssid);
  Serial.print("PWD           : "); Serial.println(configwifi.pwd);
  Serial.println(" ");
}
