#include <Arduino.h>

int led[] = {2, 3, 4, 5, 6, 7, 8, 9};
int ledLenght = sizeof(led)/sizeof(int);
int i = 0;
int delaySetup = 200;
int potenciometroDelay = 0;

void setup() {
  Serial.begin(9600);
  for(i = 0; i < ledLenght ; i++) {
    pinMode(led[i], OUTPUT);
  }
}

void loop() {
  delaySetup = analogRead(potenciometroDelay);
  // Serial.println(analogRead(potenciadorDelay));
  for(i = 0; i < ledLenght ; i++) {
    digitalWrite(led[i], HIGH);
    delay(delaySetup);
    if (delaySetup > 0) {
      digitalWrite(led[i], LOW);
    }
  }
}
