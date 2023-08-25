#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <LedControl.h>

RF24 radio(7, 8); // CE, CSN

int R_message;
int directionOfMovement;

int DIN = 4;
int CS =  3;
int CLK = 2;

byte ALL[] = {B11111111,B11111111,B11111111,B11111111,B11111111,B11111111,B11111111,B11111111};
byte EX[] = {B00000000,B00000000,B00000000,B0000000,B0000000,B00000000,B0000000,B00000000};
byte A[] = {B00000000,B00111100,B00100100,B00100100,B00111100,B00100100,B00100100,B00000000};
byte B[] = {B01111000,B01001000,B01001000,B01110000,B01001000,B01000100,B01000100,B01111100};
byte C[] = {B00000000,B00011110,B00100000,B01000000,B01000000,B01000000,B00100000,B00011110};
byte D[] = {B00000000,B00111000,B00100100,B00100010,B00100010,B00100100,B00111000,B00000000};
byte E[] = {B00000000,B00111100,B00100000,B00111000,B00100000,B00100000,B00111100,B00000000};
byte F[] = {B00000000,B00111100,B00100000,B00111000,B00100000,B00100000,B00100000,B00000000};
byte G[] = {B00000000,B00111110,B00100000,B00100000,B00101110,B00100010,B00111110,B00000000};
byte H[] = {B00000000,B00100100,B00100100,B00111100,B00100100,B00100100,B00100100,B00000000};
byte I[] = {B00000000,B00111000,B00010000,B00010000,B00010000,B00010000,B00111000,B00000000};
byte J[] = {B00000000,B00011100,B00001000,B00001000,B00001000,B00101000,B00111000,B00000000};
byte K[] = {B00000000,B00100100,B00101000,B00110000,B00101000,B00100100,B00100100,B00000000};
byte L0[] = {B00000000,B00000000,B00000000,B00000001,B00000001,B00000000,B00000000,B00000000};
byte L1[] = {B00000000,B00000000,B00000001,B00000011,B00000011,B00000001,B00000000,B00000000};
byte L2[] = {B00000000,B00000001,B00000011,B00000111,B00000111,B00000011,B00000001,B00000000};
byte L3[] = {B00000000,B00000010,B00000110,B00001111,B00001111,B00000110,B00000010,B00000000};
byte L4[] = {B00000000,B00000100,B00001100,B00011111,B00011111,B00001100,B00000100,B00000000};
byte L5[] = {B00000000,B00001000,B00011000,B00111111,B00111111,B00011000,B00001000,B00000000};
byte L6[] = {B00000000,B00010000,B00110000,B01111111,B01111111,B00110000,B00010000,B00000000};
byte L7[] = {B00000000,B00100000,B01100000,B11111111,B11111111,B01100000,B00100000,B00000000};
byte L8[] = {B00000000,B01000000,B11000000,B11111110,B11111110,B11000000,B01000000,B00000000};
byte L9[] = {B00000000,B10000000,B10000000,B11111100,B11111100,B10000000,B10000000,B00000000};
byte L10[] = {B00000000,B00000000,B00000000,B11111000,B11111000,B00000000,B00000000,B00000000};
byte L11[] = {B00000000,B00000000,B00000000,B11110000,B11110000,B00000000,B00000000,B00000000};
byte L12[] = {B00000000,B00000000,B00000000,B11100000,B11100000,B00000000,B00000000,B00000000};
byte L13[] = {B00000000,B00000000,B00000000,B11000000,B11000000,B00000000,B00000000,B00000000};
byte L14[] = {B00000000,B00000000,B00000000,B10000000,B10000000,B00000000,B00000000,B00000000};
byte M[] = {B00000000,B00000000,B01000100,B01101100,B01010100,B01000100,B01000100,B00000000};
byte N[] = {B00000000,B00100010,B00110010,B00101010,B00100110,B00100010,B00000000,B00000000};
byte O[] = {B00000000,B00111100,B01000010,B01000010,B01000010,B01000010,B00111100,B00000000};
byte P[] = {B00000000,B00111000,B00100100,B00100100,B00111000,B00100000,B00100000,B00000000};
byte Q[] = {B00000000,B00111100,B01000010,B01000010,B01000010,B01000110,B00111110,B00000001};
byte R0[] = {B00000000,B00000000,B00000000,B10000000,B10000000,B00000000,B00000000,B00000000};
byte R1[] = {B00000000,B00000000,B10000000,B11000000,B11000000,B10000000,B00000000,B00000000};
byte R2[] = {B00000000,B10000000,B11000000,B11100000,B11100000,B11000000,B10000000,B00000000};
byte R3[] = {B00000000,B01000000,B01100000,B11110000,B11110000,B01100000,B01000000,B00000000};
byte R4[] = {B00000000,B00100000,B00110000,B11111000,B11111000,B00110000,B00100000,B00000000};
byte R5[] = {B00000000,B00010000,B00011000,B11111100,B11111100,B00011000,B00010000,B00000000};
byte R6[] = {B00000000,B00001000,B00001100,B11111110,B11111110,B00001100,B00001000,B00000000};
byte R7[] = {B00000000,B00000100,B00000110,B11111111,B11111111,B00000110,B00000100,B00000000};
byte R8[] = {B00000000,B00000010,B00000011,B01111111,B01111111,B00000011,B00000010,B00000000};
byte R9[] = {B00000000,B00000001,B00000001,B00111111,B00111111,B00000001,B00000001,B00000000};
byte R10[] = {B00000000,B00000000,B00000000,B00011111,B00011111,B00000000,B00000000,B00000000};
byte R11[] = {B00000000,B00000000,B00000000,B00001111,B00001111,B00000000,B00000000,B00000000};
byte R12[] = {B00000000,B00000000,B00000000,B00000111,B00000111,B00000000,B00000000,B00000000};
byte R13[] = {B00000000,B00000000,B00000000,B00000011,B00000011,B00000000,B00000000,B00000000};
byte R14[] = {B00000000,B00000000,B00000000,B10000001,B10000001,B00000000,B00000000,B00000000};
byte S[] = {B00000000,B00111100,B00100000,B00111100,B00000100,B00000100,B00111100,B00000000};
byte T[] = {B00000000,B01111100,B00010000,B00010000,B00010000,B00010000,B00010000,B00000000};
byte U[] = {B00000000,B01000010,B01000010,B01000010,B01000010,B00100100,B00011000,B00000000};
byte V[] = {B00000000,B00100010,B00100010,B00100010,B00010100,B00010100,B00001000,B00000000};
byte W[] = {B00000000,B10000010,B10010010,B01010100,B01010100,B00101000,B00000000,B00000000};
byte X[] = {B00000000,B01000010,B00100100,B00011000,B00011000,B00100100,B01000010,B00000000};
byte Y[] = {B00000000,B01000100,B00101000,B00010000,B00010000,B00010000,B00010000,B00000000};
byte Z[] = {B00000000,B00111100,B00000100,B00001000,B00010000,B00100000,B00111100,B00000000};

LedControl lc=LedControl(DIN,CLK,CS,0);

const byte address[6] = "00001";

void setup() {
  Serial.begin(9600);
  Serial.println("receive started");
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();

  lc.shutdown(0,false);       //The MAX72XX is in power-saving mode on startup
  lc.setIntensity(0,8);      // Set the brightness to maximum value
  lc.clearDisplay(0);         // and clear the display

}

void loop() {
  if (radio.available()) {
    Serial.println("Connected");
    radio.read(&R_message, sizeof(R_message)); // Note how '&' must be placed in front of the variable name.
    Serial.println(R_message);
    directionOfMovement = R_message;
    moveAccordingly();
  }
}

void moveAccordingly() {

  if (directionOfMovement == 1) {
    
    lc.setRow(0,0,ALL[0]);
    lc.setRow(0,1,ALL[1]);
    lc.setRow(0,2,ALL[2]);
    lc.setRow(0,3,ALL[3]);
    lc.setRow(0,4,ALL[4]);
    lc.setRow(0,5,ALL[5]);
    lc.setRow(0,6,ALL[6]);
    lc.setRow(0,7,ALL[7]);
    
  }

  else if (directionOfMovement == 2) {

    lc.setRow(0,0,EX[0]);
    lc.setRow(0,1,EX[1]);
    lc.setRow(0,2,EX[2]);
    lc.setRow(0,3,EX[3]);
    lc.setRow(0,4,EX[4]);
    lc.setRow(0,5,EX[5]);
    lc.setRow(0,6,EX[6]);
    lc.setRow(0,7,EX[7]);

  }

  else if (directionOfMovement == 3) {

    lc.setRow(0,0,L0[0]);
    lc.setRow(0,1,L0[1]);
    lc.setRow(0,2,L0[2]);
    lc.setRow(0,3,L0[3]);
    lc.setRow(0,4,L0[4]);
    lc.setRow(0,5,L0[5]);
    lc.setRow(0,6,L0[6]);
    lc.setRow(0,7,L0[7]);
    delay(50);
    lc.setRow(0,0,L1[0]);
    lc.setRow(0,1,L1[1]);
    lc.setRow(0,2,L1[2]);
    lc.setRow(0,3,L1[3]);
    lc.setRow(0,4,L1[4]);
    lc.setRow(0,5,L1[5]);
    lc.setRow(0,6,L1[6]);
    lc.setRow(0,7,L1[7]);
    delay(50);
    lc.setRow(0,0,L2[0]);
    lc.setRow(0,1,L2[1]);
    lc.setRow(0,2,L2[2]);
    lc.setRow(0,3,L2[3]);
    lc.setRow(0,4,L2[4]);
    lc.setRow(0,5,L2[5]);
    lc.setRow(0,6,L2[6]);
    lc.setRow(0,7,L2[7]);
    delay(50);
    lc.setRow(0,0,L3[0]);
    lc.setRow(0,1,L3[1]);
    lc.setRow(0,2,L3[2]);
    lc.setRow(0,3,L3[3]);
    lc.setRow(0,4,L3[4]);
    lc.setRow(0,5,L3[5]);
    lc.setRow(0,6,L3[6]);
    lc.setRow(0,7,L3[7]);
    delay(50);
    lc.setRow(0,0,L4[0]);
    lc.setRow(0,1,L4[1]);
    lc.setRow(0,2,L4[2]);
    lc.setRow(0,3,L4[3]);
    lc.setRow(0,4,L4[4]);
    lc.setRow(0,5,L4[5]);
    lc.setRow(0,6,L4[6]);
    lc.setRow(0,7,L4[7]);
    delay(50);
    lc.setRow(0,0,L5[0]);
    lc.setRow(0,1,L5[1]);
    lc.setRow(0,2,L5[2]);
    lc.setRow(0,3,L5[3]);
    lc.setRow(0,4,L5[4]);
    lc.setRow(0,5,L5[5]);
    lc.setRow(0,6,L5[6]);
    lc.setRow(0,7,L5[7]);
    delay(50);
    lc.setRow(0,0,L6[0]);
    lc.setRow(0,1,L6[1]);
    lc.setRow(0,2,L6[2]);
    lc.setRow(0,3,L6[3]);
    lc.setRow(0,4,L6[4]);
    lc.setRow(0,5,L6[5]);
    lc.setRow(0,6,L6[6]);
    lc.setRow(0,7,L6[7]);
    delay(50);
    lc.setRow(0,0,L7[0]);
    lc.setRow(0,1,L7[1]);
    lc.setRow(0,2,L7[2]);
    lc.setRow(0,3,L7[3]);
    lc.setRow(0,4,L7[4]);
    lc.setRow(0,5,L7[5]);
    lc.setRow(0,6,L7[6]);
    lc.setRow(0,7,L7[7]);
    delay(50);
    lc.setRow(0,0,L8[0]);
    lc.setRow(0,1,L8[1]);
    lc.setRow(0,2,L8[2]);
    lc.setRow(0,3,L8[3]);
    lc.setRow(0,4,L8[4]);
    lc.setRow(0,5,L8[5]);
    lc.setRow(0,6,L8[6]);
    lc.setRow(0,7,L8[7]);
    delay(50);
    lc.setRow(0,0,L9[0]);
    lc.setRow(0,1,L9[1]);
    lc.setRow(0,2,L9[2]);
    lc.setRow(0,3,L9[3]);
    lc.setRow(0,4,L9[4]);
    lc.setRow(0,5,L9[5]);
    lc.setRow(0,6,L9[6]);
    lc.setRow(0,7,L9[7]);
    delay(50);
    lc.setRow(0,0,L10[0]);
    lc.setRow(0,1,L10[1]);
    lc.setRow(0,2,L10[2]);
    lc.setRow(0,3,L10[3]);
    lc.setRow(0,4,L10[4]);
    lc.setRow(0,5,L10[5]);
    lc.setRow(0,6,L10[6]);
    lc.setRow(0,7,L10[7]);
    delay(50);
    lc.setRow(0,0,L11[0]);
    lc.setRow(0,1,L11[1]);
    lc.setRow(0,2,L11[2]);
    lc.setRow(0,3,L11[3]);
    lc.setRow(0,4,L11[4]);
    lc.setRow(0,5,L11[5]);
    lc.setRow(0,6,L11[6]);
    lc.setRow(0,7,L11[7]);
    delay(50);
    lc.setRow(0,0,L12[0]);
    lc.setRow(0,1,L12[1]);
    lc.setRow(0,2,L12[2]);
    lc.setRow(0,3,L12[3]);
    lc.setRow(0,4,L12[4]);
    lc.setRow(0,5,L12[5]);
    lc.setRow(0,6,L12[6]);
    lc.setRow(0,7,L12[7]);
    delay(50);
    lc.setRow(0,0,L13[0]);
    lc.setRow(0,1,L13[1]);
    lc.setRow(0,2,L13[2]);
    lc.setRow(0,3,L13[3]);
    lc.setRow(0,4,L13[4]);
    lc.setRow(0,5,L13[5]);
    lc.setRow(0,6,L13[6]);
    lc.setRow(0,7,L13[7]);
    delay(50);
    lc.setRow(0,0,L14[0]);
    lc.setRow(0,1,L14[1]);
    lc.setRow(0,2,L14[2]);
    lc.setRow(0,3,L14[3]);
    lc.setRow(0,4,L14[4]);
    lc.setRow(0,5,L14[5]);
    lc.setRow(0,6,L14[6]);
    lc.setRow(0,7,L14[7]);
    delay(50);
  }

  else if (directionOfMovement == 4) {

    lc.setRow(0,0,R0[0]);
    lc.setRow(0,1,R0[1]);
    lc.setRow(0,2,R0[2]);
    lc.setRow(0,3,R0[3]);
    lc.setRow(0,4,R0[4]);
    lc.setRow(0,5,R0[5]);
    lc.setRow(0,6,R0[6]);
    lc.setRow(0,7,R0[7]);
    delay(50);
    lc.setRow(0,0,R1[0]);
    lc.setRow(0,1,R1[1]);
    lc.setRow(0,2,R1[2]);
    lc.setRow(0,3,R1[3]);
    lc.setRow(0,4,R1[4]);
    lc.setRow(0,5,R1[5]);
    lc.setRow(0,6,R1[6]);
    lc.setRow(0,7,R1[7]);
    delay(50);
    lc.setRow(0,0,R2[0]);
    lc.setRow(0,1,R2[1]);
    lc.setRow(0,2,R2[2]);
    lc.setRow(0,3,R2[3]);
    lc.setRow(0,4,R2[4]);
    lc.setRow(0,5,R2[5]);
    lc.setRow(0,6,R2[6]);
    lc.setRow(0,7,R2[7]);
    delay(50);
    lc.setRow(0,0,R3[0]);
    lc.setRow(0,1,R3[1]);
    lc.setRow(0,2,R3[2]);
    lc.setRow(0,3,R3[3]);
    lc.setRow(0,4,R3[4]);
    lc.setRow(0,5,R3[5]);
    lc.setRow(0,6,R3[6]);
    lc.setRow(0,7,R3[7]);
    delay(50);
    lc.setRow(0,0,R4[0]);
    lc.setRow(0,1,R4[1]);
    lc.setRow(0,2,R4[2]);
    lc.setRow(0,3,R4[3]);
    lc.setRow(0,4,R4[4]);
    lc.setRow(0,5,R4[5]);
    lc.setRow(0,6,R4[6]);
    lc.setRow(0,7,R4[7]);
    delay(50);
    lc.setRow(0,0,R5[0]);
    lc.setRow(0,1,R5[1]);
    lc.setRow(0,2,R5[2]);
    lc.setRow(0,3,R5[3]);
    lc.setRow(0,4,R5[4]);
    lc.setRow(0,5,R5[5]);
    lc.setRow(0,6,R5[6]);
    lc.setRow(0,7,R5[7]);
    delay(50);
    lc.setRow(0,0,R6[0]);
    lc.setRow(0,1,R6[1]);
    lc.setRow(0,2,R6[2]);
    lc.setRow(0,3,R6[3]);
    lc.setRow(0,4,R6[4]);
    lc.setRow(0,5,R6[5]);
    lc.setRow(0,6,R6[6]);
    lc.setRow(0,7,R6[7]);
    delay(50);
    lc.setRow(0,0,R7[0]);
    lc.setRow(0,1,R7[1]);
    lc.setRow(0,2,R7[2]);
    lc.setRow(0,3,R7[3]);
    lc.setRow(0,4,R7[4]);
    lc.setRow(0,5,R7[5]);
    lc.setRow(0,6,R7[6]);
    lc.setRow(0,7,R7[7]);
    delay(50);
    lc.setRow(0,0,R8[0]);
    lc.setRow(0,1,R8[1]);
    lc.setRow(0,2,R8[2]);
    lc.setRow(0,3,R8[3]);
    lc.setRow(0,4,R8[4]);
    lc.setRow(0,5,R8[5]);
    lc.setRow(0,6,R8[6]);
    lc.setRow(0,7,R8[7]);
    delay(50);
    lc.setRow(0,0,R9[0]);
    lc.setRow(0,1,R9[1]);
    lc.setRow(0,2,R9[2]);
    lc.setRow(0,3,R9[3]);
    lc.setRow(0,4,R9[4]);
    lc.setRow(0,5,R9[5]);
    lc.setRow(0,6,R9[6]);
    lc.setRow(0,7,R9[7]);
    delay(50);
    lc.setRow(0,0,R10[0]);
    lc.setRow(0,1,R10[1]);
    lc.setRow(0,2,R10[2]);
    lc.setRow(0,3,R10[3]);
    lc.setRow(0,4,R10[4]);
    lc.setRow(0,5,R10[5]);
    lc.setRow(0,6,R10[6]);
    lc.setRow(0,7,R10[7]);
    delay(50);
    lc.setRow(0,0,R11[0]);
    lc.setRow(0,1,R11[1]);
    lc.setRow(0,2,R11[2]);
    lc.setRow(0,3,R11[3]);
    lc.setRow(0,4,R11[4]);
    lc.setRow(0,5,R11[5]);
    lc.setRow(0,6,R11[6]);
    lc.setRow(0,7,R11[7]);
    delay(50);
    lc.setRow(0,0,R12[0]);
    lc.setRow(0,1,R12[1]);
    lc.setRow(0,2,R12[2]);
    lc.setRow(0,3,R12[3]);
    lc.setRow(0,4,R12[4]);
    lc.setRow(0,5,R12[5]);
    lc.setRow(0,6,R12[6]);
    lc.setRow(0,7,R12[7]);
    delay(50);
    lc.setRow(0,0,R13[0]);
    lc.setRow(0,1,R13[1]);
    lc.setRow(0,2,R13[2]);
    lc.setRow(0,3,R13[3]);
    lc.setRow(0,4,R13[4]);
    lc.setRow(0,5,R13[5]);
    lc.setRow(0,6,R13[6]);
    lc.setRow(0,7,R13[7]);
    delay(50);
    lc.setRow(0,0,R14[0]);
    lc.setRow(0,1,R14[1]);
    lc.setRow(0,2,R14[2]);
    lc.setRow(0,3,R14[3]);
    lc.setRow(0,4,R14[4]);
    lc.setRow(0,5,R14[5]);
    lc.setRow(0,6,R14[6]);
    lc.setRow(0,7,R14[7]);
    delay(50);

  }

  else if (directionOfMovement == 0) {
    
    lc.setRow(0,0,EX[0]);
    lc.setRow(0,1,EX[1]);
    lc.setRow(0,2,EX[2]);
    lc.setRow(0,3,EX[3]);
    lc.setRow(0,4,EX[4]);
    lc.setRow(0,5,EX[5]);
    lc.setRow(0,6,EX[6]);
    lc.setRow(0,7,EX[7]);
  }

}