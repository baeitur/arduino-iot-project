/*-------------------------
 
Pengkabelan:


Arduino             Relay
D7                  CH 1
D8                  CH 2 

*/

#define LAMP 7
#define AMPL 8

#define ON 1
#define OFF 0

void setup() {
  pinMode(LAMP, OUTPUT);
  pinMode(AMPL, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(LAMP, ON);
  delay(1000);             
  digitalWrite(LAMP, OFF);   
  delay(1000);  
  
  digitalWrite(AMPL, ON); 
  delay(1000);        
  digitalWrite(AMPL, OFF);
  delay(1000);
}
