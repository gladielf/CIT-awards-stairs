#include <Arduino.h>
#include <IRremote.h>

int led[] = {2, 3, 4, 5, 6, 7, 8, 9};
int ledLenght = sizeof(led)/sizeof(int);
int i = 0;
int delaySetup = 200;
int potenciometroDelay = 1;
int button = 0;
int programMode = 0;
int RECV_PIN = 11;

IRrecv irrecv(RECV_PIN);

decode_results results;

void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
  for(i = 0; i < ledLenght ; i++) {
    pinMode(led[i], OUTPUT);
  }
}

void loop() {
  delaySetup = analogRead(potenciometroDelay);

  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    irrecv.resume(); // Receive the next value
  }
  // Serial.println(analogRead(potenciadorDelay));
  for(i = 0; i < ledLenght ; i++) {
    digitalWrite(led[i], HIGH);
    delay(delaySetup);
    if (delaySetup > 0) {
      digitalWrite(led[i], LOW);
    }
  }
}
