#include <Wire.h>
#include <TinyMPU6050.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

int message;
int LEDState = 0;
int btnPin = 2;
int btnNew;
int btnOld = 1;

MPU6050 mpu (Wire);
RF24 radio(7, 9); // CE, CSN

const byte address[6] = "00001";

void setup() {
  Serial.begin(9600);
  pinMode(btnPin, INPUT);
  // Initialization
  mpu.Initialize();
  // Calibration (wait for about 20s to calibrate)
  mpu.Calibrate();
  Serial.println("send started");
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}

void loop() {

  mpu.Execute();

  while (mpu.GetRawAccX() <= -8000) {

    //send msg to move front
    message = 1;
    radio.write(&message, sizeof(message));
    Serial.println("front");
    mpu.Execute();

  }

  while (mpu.GetRawAccX() >= 8000) {

    //send msg to move back
    message = 2;
    radio.write(&message, sizeof(message));
    Serial.println("back");
    mpu.Execute();

  }

  while (mpu.GetRawAccY() <= -8000) {

    //send msg to move left
    message = 3;
    radio.write(&message, sizeof(message));
    Serial.println("left");
    mpu.Execute();

  }

  while (mpu.GetRawAccY() >= 8000) {

    //send msg to move right
    message = 4;
    radio.write(&message, sizeof(message));
    Serial.println("right");
    mpu.Execute();
    
  }

  while (mpu.GetRawAccX() < 8000 and mpu.GetRawAccX() > -8000 and mpu.GetRawAccY() < 8000 and mpu.GetRawAccY() > -8000) {

    //send msg to stop
    message = 0;
    radio.write(&message, sizeof(message));;
    Serial.println("none");
    mpu.Execute();

  }
  
}