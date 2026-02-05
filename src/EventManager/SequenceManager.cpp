// #include <Arduino.h>
// const int irPin = 7;      
// const int buzzerPin = 8;  

// int lastState = HIGH;

// void setup() {
//   pinMode(irPin, INPUT);
//   pinMode(buzzerPin, OUTPUT);
// }

// void loop() {
//   int currentState = digitalRead(irPin);

//   // Zodra ontvanger data detecteert
//   if (lastState == HIGH && currentState == LOW) {
//     tone(buzzerPin, 2000); // HOOG geluid
//     delay(200);            // korte piep
//     noTone(buzzerPin);
//   }

//   lastState = currentState;
// }
