#include <Arduino.h>

int led[] = {2, 3, 4, 5, 6, 7, 8, 9};
int ledLenght = sizeof(led)/sizeof(int);
int i = 0;
int delaySetup = 200;

void setup() {
  Serial.begin(9600);
  for(i = 0; i < ledLenght ; i++) {
    pinMode(led[i], OUTPUT);
  }
}

void loop() {
  for(i = 0; i < ledLenght ; i++) {
    digitalWrite(led[i], HIGH);
    delay(delaySetup);
    digitalWrite(led[i], LOW);
  }
}
