void setup() {
  // put your setup code here, to run once:
pinMode(A3,OUTPUT);
pinMode(A2,OUTPUT);
pinMode(8,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
digitalWrite(A2,1);
digitalWrite(A3,1);
digitalWrite(8,1);
delay(1000);
digitalWrite(A2,0);
digitalWrite(A3,0);
digitalWrite(8,0);
delay(1000);
}
