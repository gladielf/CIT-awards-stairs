#include <Arduino.h>
#include <IRremote.h>

void IRDecoder();

volatile int cont = 0;
volatile int flag = 0;
int led[] = {3, 4, 5, 6, 7, 8, 9, 10};
int ledLenght = sizeof(led)/sizeof(int);
int i = 0;
int delaySetup = 200;
int delayChangeValue = 50;
int potenciometroDelay = 1;
int button = 0;
int programMode = 0;
int RECV_PIN = 2;


IRrecv irrecv(RECV_PIN);
decode_results results;

void setup() {
  Serial.begin(9600);

  for(i = 0; i < ledLenght ; i++) {
    pinMode(led[i], OUTPUT);
  }

  attachInterrupt( 0, IRDecoder, CHANGE);
  irrecv.enableIRIn(); // Start the receiver
}

void loop() {
  // delaySetup = analogRead(potenciometroDelay);

  if (flag) {
    Serial.print("delaySetup: ");
    Serial.println(delaySetup);
    flag = 0;
  }

  for(i = 0; i < ledLenght ; i++) {
    digitalWrite(led[i], HIGH);
    delay(delaySetup);
    if (delaySetup > 0) {
      digitalWrite(led[i], LOW);
    }
  }
}

void IRDecoder() {
  if (irrecv.decode(&results)) {
    switch (results.value) {
      // mas: FF3AC5 >>> 16726725
      case 16726725: // Más velocidad (se REDUCE el delay)
          if (delaySetup > 0) {
            delaySetup -= delayChangeValue;
          }
          flag = 1;
          break;
      // menos: FFBA45 >>> 16759365
      case 16759365: // Menos velocidad (se AUMENTA el delay)
          delaySetup += delayChangeValue;
          flag = 1;
          break;
      default:
          // de momento no hago nada si recibe un dato diferente a los que yo quiero
          break;
    }
    irrecv.resume(); // Receive the next value
  }
}
