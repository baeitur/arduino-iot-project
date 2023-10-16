
void playMurottal() {
   // mp3_set_EQ (1);
    mp3_play(random(5,25));
    delay(500);
}

void playMp3(int song) {
 // mp3_set_EQ (1);
  mp3_play(song);
  delay(500);
}

void stopMp3() {
  mp3_stop();
  delay(500);
}

#define RELAY  2
boolean relay_state = false;
void relayLoop(){
  if(relay_state==true)
    digitalWrite(RELAY, LOW);
  else
    digitalWrite(RELAY, HIGH);
}

#define buzzer 2
void Buzzer(){  
  digitalWrite(buzzer, HIGH);
  delay(5000);
  digitalWrite(buzzer, LOW);
  delay(50);
}
