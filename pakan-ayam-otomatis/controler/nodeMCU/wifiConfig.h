const char* ssid = "FEDER";
const char* password = "ADMIN123";
const char* mqtt_server = "a59d0725a5d14015b08dfb45bc48a403.s2.eu.hivemq.cloud";

void serialEvent();

BearSSL::CertStore certStore;
WiFiClientSecure espClient;
PubSubClient * client;

void setupWifi() {
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(configwifi.ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(configwifi.ssid, configwifi.pwd);

  unsigned long startTime = millis();
  
  while (WiFi.status() != WL_CONNECTED) {  
    delay(500);
    Serial.print(".");
    status_connect=false;
    serialEvent();
    if (millis() - startTime > 10000) {
      Serial.println(" ");
      break;
    }   
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}
