void setDateTime() {
  // You can use your own timezone, but the exact time is not used at all.
  // Only the date is needed for validating the certificates.
  
  configTime(TZ_Asia_Jakarta, "pool.ntp.org", "time.nist.gov");

  Serial.print("Waiting for NTP time sync: ");
  time_t now = time(nullptr);
  
  unsigned long startTime = millis();
  while (now < 8 * 3600 * 2) {
    delay(100);
    Serial.print(".");
    now = time(nullptr);
    if (millis() - startTime > 1000) { 
      now = 1675493665;
      Serial.println();
      break;
    } 
  }
  Serial.println();

  struct tm timeinfo;
  gmtime_r(&now, &timeinfo);
  Serial.printf("%s %s", tzname[0], asctime(&timeinfo));
}

String getValue(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length()-1;
 
  for(int i=0; i<=maxIndex && found<=index; i++){
    if(data.charAt(i)==separator || i==maxIndex){
        found++;
        strIndex[0] = strIndex[1]+1;
        strIndex[1] = (i == maxIndex) ? i+1 : i;
    }
  }  
  return found>index ? data.substring(strIndex[0], strIndex[1]) : "";
}

void callback(char* topic, byte* payload, unsigned int length) {
  String topicStr = topic;
  String value;
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    value += ((char)payload[i]);
  }
  Serial.println(value);
  
  // Switch on the LED if the first character is present
  if (topicStr == "RELAY-STATE" and value == "1") {
    relay_state = true;
  } else if (topicStr == "RELAY-STATE" and value == "0"){
    relay_state = false;
  }else if(topicStr == "TIMER"){
    updateTimerConfig(value);
    bacaParameter();
  }
  else if(topicStr == "DATE-TIME"){
    
    // data of time
    int jam = getValue(value,' ', 0).toInt(); 
    int men = getValue(value,' ', 1).toInt(); 
    int det = getValue(value,' ', 2).toInt(); 
    // data of date
    int tgl = getValue(value,' ', 3).toInt(); 
    int bln = getValue(value,' ', 4).toInt(); 
    int thn = getValue(value,' ', 5).toInt(); 
    Rtc.SetDateTime(RtcDateTime(thn, bln, tgl, jam, men, det));
  }
  
}

void reconnect() {
  // Loop until we’re reconnected
  if(!client->connected()) {
    Serial.print("Attempting MQTT connection… ");
    String clientId = "ESP8266Client - MyClient";
    // Attempt to connect
    // Insert your password
    if (client->connect(clientId.c_str(), "smartsistem0101", "B4e1t.ur")) {
      Serial.println("connected");
      // … and resubscribe
      client->subscribe("RELAY-STATE");
      client->subscribe("TIMER");
      client->subscribe("DATE-TIME");
      
    } else {
      //Serial.print("failed, rc = ");
      //Serial.println(client->state());
      Serial.println("not connect");
      status_connect = false; 
    }
  }
}

void mqttInit(){
  int numCerts = certStore.initCertStore(LittleFS, PSTR("/certs.idx"), PSTR("/certs.ar"));
  Serial.printf("Number of CA certs read: %d\n", numCerts);
  if (numCerts == 0) {
    Serial.printf("No certs found. Did you run certs-from-mozilla.py and upload the LittleFS directory before running?\n");
    return; // Can't connect to anything w/o certs!
  }

  BearSSL::WiFiClientSecure *bear = new BearSSL::WiFiClientSecure();
  // Integrate the cert store with this connection
  bear->setCertStore(&certStore);

  client = new PubSubClient(*bear);

  client->setServer(mqtt_server, 8883);
  client->setCallback(callback);  
}

String getTimeString(){    
  char buffer[20];
  sprintf(buffer, "%02d:%02d:%02d", rJam,rMen,rDet);
  //client->publish("time", buffer);  
  return buffer;
}

String getDateString(){    
  char buffer[40];
  sprintf(buffer, "%s, %02d %s %04d", namaHari[rHar], rTgl, namaBulan[rBul], rTah);
  //client->publish("date", buffer);  
  return buffer;
}

String getTempString(){
  char tmp[5];
  dtostrf(rTmp, -3, 1, tmp);
  char buffer[10];
  sprintf(buffer, "%s C", tmp);
  //client->publish("tmp", buffer);
  return buffer;
}

String getTimer1String(){  
    uint8_t ONH,ONM,OFFH,OFFM;
    ONH  =  configtimer.on1/100;
    ONM  =  configtimer.on1%100;
    OFFH =  configtimer.off1/100;
    char buffer[20];
    OFFM =  configtimer.off1%100;
    sprintf(buffer, "%02d:%02d-%02d:%02d",ONH,ONM,OFFH,OFFM);
    //client->publish("timer1", buffer);
    return buffer;
}

String getTimer2String(){  
    uint8_t ONH,ONM,OFFH,OFFM;
    ONH  =  configtimer.on2/100;
    ONM  =  configtimer.on2%100;
    OFFH =  configtimer.off2/100;
    OFFM =  configtimer.off2%100;
    char buffer[20];
    sprintf(buffer, "%02d:%02d-%02d:%02d",ONH,ONM,OFFH,OFFM);
    //client->publish("timer2", buffer);
    return buffer;
}

String getTimer3String(){  
    uint8_t ONH,ONM,OFFH,OFFM;
    ONH  =  configtimer.on3/100;
    ONM  =  configtimer.on3%100;
    OFFH =  configtimer.off3/100;
    OFFM =  configtimer.off3%100;
    char buffer[20];
    sprintf(buffer, "%02d:%02d-%02d:%02d",ONH,ONM,OFFH,OFFM);
    //client->publish("timer3", buffer); 
    return buffer;
}
