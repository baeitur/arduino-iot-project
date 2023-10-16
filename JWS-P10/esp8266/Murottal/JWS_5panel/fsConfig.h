// ----------------------
// FS CONFIG

struct ConfigJws {
  uint8_t iqmhs; // menit
  uint8_t iqmhd; // menit
  uint8_t iqmha; // menit
  uint8_t iqmhm; // menit
  uint8_t iqmhi; // menit
  
  uint8_t durasiadzan; // Menit
  float latitude;
  float longitude;
  int8_t zonawaktu;
  uint8_t hilal;

  uint8_t ihtis; //menit
  uint8_t ihtiq; //menit
  uint8_t ihtid; //menit
  uint8_t ihtia; //menit
  uint8_t ihtim; //menit
  uint8_t ihtii; //menit
  
};

struct ConfigMurottal { 
  int8_t  murottalt; // menit
  uint8_t murottals; // menit
  uint8_t murottald; // menit
  uint8_t murottala; // menit
  uint8_t murottalm; // menit
  uint8_t murottali; // menit
  uint8_t murottalj; // menit  
};

struct ConfigJumat { 
  char jpahing[168];
  char jpon[168];
  char jwage[168];
  char jkliwon[168];
  char jlegi[168];
};

struct ConfigInfo { 
  char namamasjid[168];
  char info1[168];
  char info2[168];
  char info3[168];
};

const char *fileconfigjws = "/configjws.json";
const char *fileconfigmurottal = "/configmurottal.json";
const char *fileconfigjumat = "/configjumat.json";
const char *fileconfiginfo = "/configinfo.json";

ConfigJws configjws;
ConfigMurottal configmurottal;
ConfigJumat configjumat;
ConfigInfo configinfo;

const char *const jumat[] = {configjumat.jpahing,configjumat.jpon,configjumat.jwage,configjumat.jkliwon,configjumat.jlegi};


// -------------------------------------------
// Membuat file config JWS JSON di File Sistem

void membuatDataAwal() {

  String datajws      = "{\"iqmhs\":\"15\",\"iqmhd\":\"20\",\"iqmha\":\"15\",\"iqmhm\":\"15\",\"iqmhi\":\"5\",\"ihtis\":\"2\",\"ihtiq\":\"2\",\"ihtid\":\"2\",\"ihtia\":\"2\",\"ihtim\":\"2\",\"ihtii\":\"2\",\"durasiadzan\":\"1\",\"latitude\":\"-6.16\",\"longitude\":\"106.61\",\"zonawaktu\":\"7\",\"hilal\":\"0\"}";
  String datamurottal = "{\"murottalt\":\"0\",\"murottals\":\"0\",\"murottald\":\"0\",\"murottala\":\"0\",\"murottalm\":\"0\",\"murottali\":\"0\",\"murottalj\":\"0\"}";
  String datajumat    = "{\"jpahing\":\"Jumat Pahing  Imam : ..., Bilal : ... \",\"jpon\":\"Jumat Pon  Imam : ..., Bilal : ... \",\"jwage\":\"Jumat wage  Imam : ..., Bilal : ... \",\"jkliwon\":\"Jumat Kliwom  Imam : ..., Bilal : ... \",\"jlegi\":\"Jumat Legi  Imam : ..., Bilal : ... \"}";
  String datainfo     = "{\"namamasjid\":\"MASJID BAITUR RAHMAN \",\"info1\":\"info1 \",\"info2\":\"info2 \",\"info3\":\"info3 \"}";
  
  DynamicJsonDocument docjws(512);
  DeserializationError error1 = deserializeJson(docjws, datajws);

  DynamicJsonDocument docmurottal(512);
  DeserializationError error2 = deserializeJson(docmurottal, datajws);

  DynamicJsonDocument docjumat(512);
  DeserializationError error3 = deserializeJson(docjumat, datajumat);

  DynamicJsonDocument docinfo(512);
  DeserializationError error4 = deserializeJson(docinfo, datainfo);

  File configFileJws   = LittleFS.open(fileconfigjws, "w");
  File configFileMurottal   = LittleFS.open(fileconfigmurottal, "w");
  File configFileJumat = LittleFS.open(fileconfigjumat, "w");
  File configFileInfo  = LittleFS.open(fileconfiginfo, "w");
  
  if (!configFileJws||!configFileMurottal||!configFileJumat||!configFileInfo) {
    Serial.println("Gagal membuat file json");
    return;
  }
  
  serializeJson(docjws,configFileJws);
  serializeJson(docmurottal,configFileMurottal);
  serializeJson(docjumat,configFileJumat);
  serializeJson(docinfo,configFileInfo);
  
  if (error1||error2||error3||error4) {   
    Serial.print(F("deserializeJson() gagal kode sebagai berikut: "));
    Serial.println(error1.c_str());
    Serial.println(error2.c_str());
    Serial.println(error3.c_str());
    Serial.println(error4.c_str());
    return; 
  } else {
    configFileJws.close();
    configFileMurottal.close();
    configFileJumat.close();
    configFileInfo.close();
    Serial.println("Berhasil membuat file .json"); 
  }  
}

// -------------------------------------------
// Membaca file config JWS JSON di File Sistem

void loadJwsConfig(const char *fileconfigjws, ConfigJws &configjws, const char *fileconfigmurottal, ConfigMurottal &configmurottal, const char *fileconfigjumat, ConfigJumat &configjumat, const char *fileconfiginfo, ConfigInfo &configinfo) {  

  File configFileJws = LittleFS.open(fileconfigjws, "r");
  File configFileMurottal = LittleFS.open(fileconfigmurottal, "r");
  File configFileJumat = LittleFS.open(fileconfigjumat, "r");
  File configFileInfo = LittleFS.open(fileconfiginfo, "r");
  
  if (!configFileJws||!configFileMurottal||!configFileJumat||!configFileInfo) { 
    Serial.println("Gagal membuka json untuk dibaca");
    membuatDataAwal();
    Serial.println("Sistem restart...");
    ESP.restart(); 
  }

  size_t size1 = configFileJws.size();
  std::unique_ptr<char[]> buf1(new char[size1]);
  configFileJws.readBytes(buf1.get(), size1);

  size_t size2 = configFileMurottal.size();
  std::unique_ptr<char[]> buf2(new char[size2]);
  configFileMurottal.readBytes(buf2.get(), size2);

  size_t size3 = configFileJumat.size();
  std::unique_ptr<char[]> buf3(new char[size3]);
  configFileJumat.readBytes(buf3.get(), size3);

  size_t size4 = configFileInfo.size();
  std::unique_ptr<char[]> buf4(new char[size4]);
  configFileInfo.readBytes(buf4.get(), size4);

  DynamicJsonDocument docjws(512);
  DeserializationError error1 = deserializeJson(docjws, buf1.get());

  DynamicJsonDocument docmurottal(512);
  DeserializationError error2 = deserializeJson(docmurottal, buf2.get());

  DynamicJsonDocument docjumat(512);
  DeserializationError error3 = deserializeJson(docjumat, buf3.get());

  DynamicJsonDocument docinfo(512);
  DeserializationError error4 = deserializeJson(docinfo, buf4.get());

  if (error1||error2||error3||error4) {
    Serial.println("Gagal parse fileconfig...");
    return;
  }
  
  configjws.iqmhs = docjws["iqmhs"];
  configjws.iqmhd = docjws["iqmhd"];
  configjws.iqmha = docjws["iqmha"];
  configjws.iqmhm = docjws["iqmhm"];
  configjws.iqmhi = docjws["iqmhi"];
  
  configjws.durasiadzan = docjws["durasiadzan"];
  configjws.latitude = docjws["latitude"];
  configjws.longitude = docjws["longitude"];
  configjws.zonawaktu = docjws["zonawaktu"];
  configjws.hilal = docjws["hilal"];

  configjws.ihtis = docjws["ihtis"];
  configjws.ihtiq = docjws["ihtiq"];
  configjws.ihtid = docjws["ihtid"];
  configjws.ihtia = docjws["ihtia"];
  configjws.ihtim = docjws["ihtim"];
  configjws.ihtii = docjws["ihtii"];
  
  configmurottal.murottalt = docmurottal["murottalt"];
  configmurottal.murottals = docmurottal["murottals"];
  configmurottal.murottald = docmurottal["murottald"];
  configmurottal.murottala = docmurottal["murottala"];
  configmurottal.murottalm = docmurottal["murottalm"];
  configmurottal.murottali = docmurottal["murottali"];
  configmurottal.murottalj = docmurottal["murottalj"];
  
  strlcpy(configjumat.jpahing, docjumat["jpahing"] | "", sizeof(configjumat.jpahing));
  strlcpy(configjumat.jpon,    docjumat["jpon"] | "",    sizeof(configjumat.jpon));
  strlcpy(configjumat.jwage,   docjumat["jwage"] | "",   sizeof(configjumat.jwage));
  strlcpy(configjumat.jkliwon, docjumat["jkliwon"] | "", sizeof(configjumat.jkliwon));
  strlcpy(configjumat.jlegi,   docjumat["jlegi"] | "",   sizeof(configjumat.jlegi));
  
  strlcpy(configinfo.namamasjid, docinfo["namamasjid"] | "", sizeof(configinfo.namamasjid));
  strlcpy(configinfo.info1, docinfo["info1"] | "", sizeof(configinfo.info1));
  strlcpy(configinfo.info2, docinfo["info2"] | "", sizeof(configinfo.info2));
  strlcpy(configinfo.info3, docinfo["info3"] | "", sizeof(configinfo.info3));
  
  configFileJws.close(); 
  configFileMurottal.close(); 
  configFileJumat.close(); 
  configFileInfo.close(); 
}

void updateJwsConfig(String datajws){
  DynamicJsonDocument doc(512);
  DeserializationError error = deserializeJson(doc, datajws);

  File configFileJws = LittleFS.open(fileconfigjws, "w");
  if (!configFileJws) {
    Serial.println("Gagal membuka Info configFileJws untuk ditulis");
    return;
  }
  
  serializeJson(doc, configFileJws);

  if (error) {
    Serial.print(F("deserializeJson() gagal kode sebagai berikut: "));
    Serial.println(error.c_str());
    return; 
  } else {
    configFileJws.close();
    Serial.println("Berhasil mengubah configFileJws");
    loadJwsConfig(fileconfigjws, configjws, fileconfigmurottal, configmurottal, fileconfigjumat, configjumat, fileconfiginfo, configinfo);
  }
}

void updateMurottalConfig(String datamurottal){
  DynamicJsonDocument doc(512);
  DeserializationError error = deserializeJson(doc, datamurottal);

  File configFileMurottal = LittleFS.open(fileconfigmurottal, "w");
  if (!configFileMurottal) {
    Serial.println("Gagal membuka Info configFileMurottal untuk ditulis");
    return;
  }
  
  serializeJson(doc, configFileMurottal);

  if (error) {
    Serial.print(F("deserializeJson() gagal kode sebagai berikut: "));
    Serial.println(error.c_str());
    return; 
  } else {
    configFileMurottal.close();
    Serial.println("Berhasil mengubah configFileMurottal");
    loadJwsConfig(fileconfigjws, configjws, fileconfigmurottal, configmurottal, fileconfigjumat, configjumat, fileconfiginfo, configinfo);
  }
}

void updateJumatConfig(String datajumat){
  DynamicJsonDocument doc(512);
  DeserializationError error = deserializeJson(doc, datajumat);

  File configFileJumat = LittleFS.open(fileconfigjumat, "w");
  if (!configFileJumat) {
    Serial.println("Gagal membuka file config jumat untuk ditulis");
    return;
  }
  
  serializeJson(doc, configFileJumat);

  if (error) {
    Serial.print(F("deserializeJson() gagal kode sebagai berikut: "));
    Serial.println(error.c_str());
    return; 
  } else {
    configFileJumat.close();
    Serial.println("Berhasil mengubah configFileJumat");
    loadJwsConfig(fileconfigjws, configjws, fileconfigmurottal, configmurottal, fileconfigjumat, configjumat, fileconfiginfo, configinfo);
  }
}

void updateInfoConfig(String datainfo){
  DynamicJsonDocument doc(512);
  DeserializationError error = deserializeJson(doc, datainfo);

  File configFileInfo = LittleFS.open(fileconfiginfo, "w");
  if (!configFileInfo) {
    Serial.println("Gagal membuka file configFileInfo untuk ditulis");
    return;
  }
  
  serializeJson(doc, configFileInfo);

  if (error) {
    Serial.print(F("deserializeJson() gagal kode sebagai berikut: "));
    Serial.println(error.c_str());
    return; 
  } else {
    configFileInfo.close();
    Serial.println("Berhasil mengubah configFileInfo");
    loadJwsConfig(fileconfigjws, configjws, fileconfigmurottal, configmurottal, fileconfigjumat, configjumat, fileconfiginfo, configinfo);
  }
}


// -------------------------------------------
// MEMBACA PARAMETER YANG TERSIMPAN

void bacaParameter() {

  Serial.println(" ");
  Serial.println("PARAMETER TERSIMPAN");
  Serial.print("Iqomah Subuh   : "); Serial.println(configjws.iqmhs);
  Serial.print("Iqomah Dzuhur  : "); Serial.println(configjws.iqmhd);
  Serial.print("Iqomah Ashar   : "); Serial.println(configjws.iqmha);
  Serial.print("Iqomah Maghrib : "); Serial.println(configjws.iqmhm);
  Serial.print("Iqomah Isya    : "); Serial.println(configjws.iqmhi);
  Serial.print("Durasi Adzan   : "); Serial.println(configjws.durasiadzan);
  Serial.print("Latitude       : "); Serial.println(configjws.latitude);
  Serial.print("Longitude      : "); Serial.println(configjws.longitude);
  Serial.print("Zona Waktu     : "); Serial.println(configjws.zonawaktu);
  Serial.print("Derajat Hilal  : "); Serial.println(configjws.hilal);
  
  Serial.print("Ihtiyati Shubuh: "); Serial.println(configjws.ihtis);
  Serial.print("Ihtiyati Shuruq: "); Serial.println(configjws.ihtiq);
  Serial.print("Ihtiyati Dzuhur: "); Serial.println(configjws.ihtid);
  Serial.print("Ihtiyati Ashar : "); Serial.println(configjws.ihtia);
  Serial.print("Ihtiyati Magrib: "); Serial.println(configjws.ihtim);
  Serial.print("Ihtiyati Isya' : "); Serial.println(configjws.ihtii);
  
  Serial.print("Murot Tahajjud : "); Serial.println(configmurottal.murottalt);
  Serial.print("Murot Shubuh   : "); Serial.println(configmurottal.murottals);
  Serial.print("Murot Dzuhur   : "); Serial.println(configmurottal.murottald);
  Serial.print("Murot Ashar    : "); Serial.println(configmurottal.murottala);
  Serial.print("Murot Magrib   : "); Serial.println(configmurottal.murottalm);
  Serial.print("Murot Isya'    : "); Serial.println(configmurottal.murottali);
  Serial.print("Murot Jum'at   : "); Serial.println(configmurottal.murottalj);
  
  Serial.print("Jum'at Pahing  : "); Serial.println(configjumat.jpahing);
  Serial.print("Jum'at Pon     : "); Serial.println(configjumat.jpon);
  Serial.print("Jum'at Wage    : "); Serial.println(configjumat.jwage);
  Serial.print("Jum'at Kliwon  : "); Serial.println(configjumat.jkliwon);
  Serial.print("Jum'at Legi    : "); Serial.println(configjumat.jlegi);
  
  Serial.print("Nama Masjid    : "); Serial.println(configinfo.namamasjid);
  Serial.print("Info1          : "); Serial.println(configinfo.info1);
  Serial.print("Info2          : "); Serial.println(configinfo.info2);
  Serial.print("Info3          : "); Serial.println(configinfo.info3);
  Serial.println(" ");
}
