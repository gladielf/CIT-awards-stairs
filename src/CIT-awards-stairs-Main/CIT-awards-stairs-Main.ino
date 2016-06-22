int led[] = {2, 3, 4, 5, 6, 7, 8, 9};
int i = 0;
int delaySetup = 200;

void setup() {
  for(i = 0; i < 8 ; i++) {
    pinMode(led[i], OUTPUT);  
  }
}

void loop() {
  for(i = 0; i < 8 ; i++) {
    digitalWrite(led[i], HIGH);
    delay(delaySetup);
    digitalWrite(led[i], LOW);
  }
}
