#include <Arduino.h>
#include <IRremote.h>
#include <citLib.h>

void IRDecoder();
void standarProgram(int);
void reverseStandarProgram(int);
void allOn();
void allOff();

volatile int cont = 0;
volatile int flag = 0;
int led[] = {31, 32, 33, 34, 35, 36, 37, 38};
int ledLenght = sizeof(led)/sizeof(int);
int i = 0;
int delaySetup = 200;
int delayChangeValue = 50;
int programCode = 0;
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

  /*if (flag) {
    Serial.print("delaySetup: ");
    Serial.println(delaySetup);
    flag = 0;
  }*/

  switch (programCode) {
    case 0:
    case 1:
        standarProgram(delaySetup);
        break;
    case 2:
        allOn();
        break;
    case 3:
        allOff();
        break;
    case 4:
        standarProgram(50);
        break;
    case 5:
        standarProgram(100);
        break;
    case 6:
        standarProgram(200);
        break;
    case 7:
        standarProgram(1000);
        break;
    case 8:
        reverseStandarProgram(50);
        break;
    case 9:
        reverseStandarProgram(100);
        break;
    case 10:
        reverseStandarProgram(200);
        break;
    case 11:
        reverseStandarProgram(1000);
        break;
    case 12:
        break;
    case 13:
        break;
    case 14:
        break;
    case 15:
        break;
    case 16:
        break;
    case 17:
        break;
    case 18:
        break;
    case 19:
        break;
    case 20:
        break;
    case 21:
        break;
    case 22:
        break;
    case 23:
        break;
    case 24:
        break;
    case 25:
        break;
    case 26:
        break;
    case 27:
        break;
    case 28:
        break;
    case 29:
        break;
    case 30:
        break;
    case 31:
        break;
    case 32:
        break;
    case 33:
        break;
    case 34:
        break;
    case 35:
        break;
    case 36:
        break;
    case 37:
        break;
    case 38:
        break;
    case 39:
        break;
    case 40:
        break;
    case 41:
        break;
    case 42:
        break;
    case 43:
        break;


    default:
        break;
  }

  // for(i = 0; i < ledLenght ; i++) {
  //   digitalWrite(led[i], LOW); //Turns ON Relays i
  //   delay(delaySetup);
  //   if (delaySetup > 0) {
  //     digitalWrite(led[i], HIGH); //Turns OFF Relays i
  //   }
  // }
}

void standarProgram(int delayValue) {
  //int i;
  //int ledLenght = sizeof(led)/sizeof(int);
  for(i = 0; i < ledLenght ; i++) {
    digitalWrite(led[i], LOW); //Turns ON Relays i
    delay(delayValue);
    if (delayValue > 0) {
      digitalWrite(led[i], HIGH); //Turns OFF Relays i
    }
  }
}

void reverseStandarProgram(int delayValue) {
  //int i;
  //int ledLenght = sizeof(led)/sizeof(int);
  for(i = ledLenght; i >= 0 ; i--) {
    digitalWrite(led[i], LOW); //Turns ON Relays i
    delay(delayValue);
    if (delayValue > 0) {
      digitalWrite(led[i], HIGH); //Turns OFF Relays i
    }
  }
}

void allOn() {
  for(i = 0; i < ledLenght ; i++) {
    digitalWrite(led[i], LOW); //Turns ON Relays i
  }
}

void allOff() {
  for(i = 0; i < ledLenght ; i++) {
    digitalWrite(led[i], HIGH); //Turns OFF Relays i
  }
}


// INTERRUPTION FUNCTION
void IRDecoder() {
  if (irrecv.decode(&results)) {
    switch (results.value) {
      //FILA 1
      /*** 1ª Fila con botones encencido ***/
      // mas: FF3AC5 >>> 16726725
      case 16726725: // Más velocidad (se REDUCE el delay)
          if (delaySetup > 50) {
            delaySetup -= delayChangeValue;
          }
          programCode = 0;
          break;
      // menos: FFBA45 >>> 16759365
      case 16759365: // Menos velocidad (se AUMENTA el delay)
          delaySetup += delayChangeValue;
          programCode = 1;
          break;
      // Play?: FF827D >>> 16745085
      case 16745085: //Enciende todos los led a la vez, NO se apagan
          programCode = 2;
          break;
      // On/Off: FF02FD >>> 16712445
      case 16712445: //Se apagan TODOS los led, NO se encienden
          programCode = 3;
          break;

      //FILA 2
      /*** 1ª Fila de colores con texto RGBW ***/
      // RED R: FF1AE5 >>> 16718565
      case 16718565: //
          programCode = 4;
          break;
      // GREEN G: FF9A65 >>> 16751205
      case 16751205: //
          programCode = 5;
          break;
      // BLUE B: FFA25D >>> 16753245
      case 16753245: //
          programCode = 6;
          break;
      // WHITE W: FF22DD >>> 16720605
      case 16720605: //
          programCode = 7;
          break;

      //FILA 3
      /*** 2ª Fila de colores ***/
      // Naranjita: FF2AD5 >>> 16722645
      case 16722645: //
          programCode = 8;
          break;
      // Verdecillo: FFAA55 >>> 16755285
      case 16755285: //
          programCode = 9;
          break;
      // azulillo: FF926D >>> 16749165
      case 16749165: //
          programCode = 10;
          break;
      // blaco roto?: FF12ED >>> 16716525
      case 16716525: //
          programCode = 11;
          break;

      //FILA 4
      /*** 3ª Fila de colores ***/
      // Amarillo huevo: FF0AF5 >>> 16714485
      case 16714485: //
          programCode = 12;
          break;
      // Azul: FF8A75 >>> 16747125
      case 16747125: //
          programCode = 13;
          break;
      // Morado: FFB24D >>> 16757325
      case 16757325: //
          programCode = 14;
          break;
      // color carne: FF32CD >>> 16724685
      case 16724685: //
          programCode = 15;
          break;

      //FILA 5
      /*** 4ª Fila de colores ***/
      // Marron: FF38C7 >>> 16726215
      case 16726215: //
          programCode = 16;
          break;
      // verde azulado: FFB847 >>> 16758855
      case 16758855: //
          programCode = 17;
          break;
      // rosita: FF7887 >>> 16742535
      case 16742535: //
          programCode = 18;
          break;
      // azul claro: FFF807 >>> 16775175
      case 16775175: //
          programCode = 19;
          break;

      //FILA 6
      /*** 5ª Fila de colores ***/
      // Amarillo: FF18E7 >>> 16718055
      case 16718055: //
          programCode = 20;
          break;
      // azul: FF9867 >>> 16750695
      case 16750695: //
          programCode = 21;
          break;
      // magenta: FF58A7 >>> 16734375
      case 16734375: //
          programCode = 22;
          break;
      // azul claro: FFD827 >>> 16767015
      case 16767015: //
          programCode = 23;
          break;

      //FILA 7
      /*** 1ª Fila de flechas ***/
      // UP RED: FF28D7 >>> 16722135
      case 16722135: //
          programCode = 24;
          break;
      // UP GREEN: FFA857 >>> 16754775
      case 16754775: //
          programCode = 25;
          break;
      // UP BLUE: FF6897 >>> 16738455
      case 16738455: //
          programCode = 26;
          break;
      // Quick: FFE817 >>> 16771095
      case 16771095: //
          programCode = 27;
          break;

      //FILA 8
      /*** 2ª Fila de flechas ***/
      // DOWN RED: FF08F7 >>> 16713975
      case 16713975: //
          programCode = 28;
          break;
      // DOWN GREEN: FF8877 >>> 16746615
      case 16746615: //
          programCode = 29;
          break;
      // DOWN BLUE: FF48B7 >>> 16730295
      case 16730295: //
          programCode = 30;
          break;
      // Slow: FFC837 >>> 16762935
      case 16762935: //
          programCode = 31;
          break;

      //FILA 9
      /*** 1ª Fila de DIY ***/
      // DIY1: FF30CF >>> 16724175
      case 16724175: //
          programCode = 32;
          break;
      // DIY2: FFB04F >>> 16756815
      case 16756815: //
          programCode = 33;
          break;
      // DIY3: FF708F >>> 16740495
      case 16740495: //
          programCode = 34;
          break;
      // auto: FFF00F >>> 16773135
      case 16773135: //
          programCode = 35;
          break;

      //FILA 10
      /*** 2ª Fila de DIY ***/
      // DIY4: FF10EF >>> 16716015
      case 16716015: //
          programCode = 36;
          break;
      // DIY5: FF906F >>> 16748655
      case 16748655: //
          programCode = 37;
          break;
      // DIY6: FF50AF >>> 16732335
      case 16732335: //
          programCode = 38;
          break;
      // FLASH: FFD02F >>> 16764975
      case 16764975: //
          programCode = 39;
          break;

      //FILA 11
      /*** Fila de Jumps y Fades ***/
      // JUMP3: FF20DF >>> 16720095
      case 16720095: //
          programCode = 40;
          break;
      // JUMP7: FFA05F >>> 16752735
      case 16752735: //
          programCode = 41;
          break;
      // FADE3: FF609F >>> 16736415
      case 16736415: //
          programCode = 42;
          break;
      // FADE7: FFE01F >>> 16769055
      case 16769055: //
          programCode = 43;
          break;

      default:
          // de momento no hago nada si recibe un dato diferente a los que yo quiero
          break;
    }
    irrecv.resume(); // Receive the next value
  }
}
