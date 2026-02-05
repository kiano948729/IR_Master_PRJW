#include <Wire.h>
 
const int altPin = A0;
int baseval = 0;
const int outpin = 7;   // buzzer zit hier
const int ledPin = 7;   // LED gebruikt dezelfde pin
bool ran = 0;
int status = 0;
 
void setup() {
  Wire.begin(1);              
  Wire.onRequest(sendData);   
  pinMode(altPin, INPUT);
  pinMode(outpin, OUTPUT);
  pinMode(ledPin, OUTPUT);
}
 
void loop() {
  if (ran == 0){
    int baseVal = analogRead(altPin);
 
    if (baseVal != 0){
      baseval = (baseVal * 10);
      ran = 1;
    }
 
  } else {
    int altStat = analogRead(altPin);
 
    if (altStat >= baseval)  {
      tone(outpin, 2000);        // buzzer hoog geluid
      digitalWrite(ledPin, HIGH); // LED aan
      delay(200);
      noTone(outpin);
      digitalWrite(ledPin, LOW);  // LED uit
   
      status = 1;
    } else {
      digitalWrite(ledPin, LOW);
      status = 0;
    }
  }
}
 
void sendData() {
  Wire.write(status);
}
