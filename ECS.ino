#include <AccelStepper.h>
#include <SPI.h>
#include <SD.h>
#define HALFSTEP 8

#define motorPin1  2     // IN1 on the ULN2003 driver 1
#define motorPin2  3     // IN2 on the ULN2003 driver 1
#define motorPin3  4     // IN3 on the ULN2003 driver 1
#define motorPin4  5     // IN4 on the ULN2003 driver 1

#define motorPin5  6     // IN1 on the ULN2003 driver 2
#define motorPin6  7     // IN2 on the ULN2003 driver 2
#define motorPin7  8     // IN3 on the ULN2003 driver 2
#define motorPin8  9     // IN4 on the ULN2003 driver 2

//Constants
const int pResistor1 = A0; // Photoresistor at Arduino analog pin A0
const int pResistor2 = A1; // Photoresistor at Arduino analog pin A1
const int pResistor3 = A2; // Photoresistor at Arduino analog pin A2
const int pResistor4 = A3; // Photoresistor at Arduino analog pin A3

// Initialize with pin sequence
AccelStepper stepper1(HALFSTEP, motorPin1, motorPin3, motorPin2, motorPin4);
AccelStepper stepper2(HALFSTEP, motorPin5, motorPin7, motorPin6, motorPin8);

//Variables
int value1;          // Store value from photoresistors (0-1023)
int value2;
int value3;
int value4;

int uvLevel;

int stepperSpeed = 1500; //speed of the stepper (steps per second)
long stepPos = 100;
long stepNeg = -100;
long posOne;
long posTwo;

char filename[] = "UV_Data.CSV";
File myFile;
const int chipSelect = 10;

void setup(){
 pinMode(pResistor1, INPUT); // Set pResistor1 - A0 pin as an input
 pinMode(pResistor2, INPUT); // Set pResistor2 - A1 pin as an input
 pinMode(pResistor3, INPUT); // Set pResistor3 - A2 pin as an input
 pinMode(pResistor4, INPUT); // Set pResistor4 - A3 pin as an input
 
 stepper1.setMaxSpeed(2000.0);
 stepper1.move(1);  // I found this necessary
 stepper1.setSpeed(stepperSpeed);
 posOne = stepper1.currentPosition();

 stepper2.setMaxSpeed(2000.0);
 stepper2.move(-1);  // I found this necessary
 stepper2.setSpeed(stepperSpeed);
 posTwo = stepper2.currentPosition();

 Serial.print("Init SD CARD");
 // see if the card is present and can be initialized:
 if (!SD.begin(chipSelect)) 
 {
   Serial.print("Card failed");
   return;
 }
 Serial.print("CARD OK");
 
 Serial.begin(9600);
}

void loop(){
  value1 = analogRead(pResistor1);
  value2 = analogRead(pResistor2);
  value3 = analogRead(pResistor3);
  value4 = analogRead(pResistor4);

  solarTracker();
  
  uvLevel = getUV();
  
  WriteSD(uvLevel);
}

void solarTracker()
{
  if ((value1 - value2) > 42)
  {
    stepper1.move(stepPos);
    stepper1.setSpeed(stepperSpeed);
    posOne = stepper1.currentPosition();
  }
  else if((value2 - value1) > 42)
  {
    stepper1.move(stepNeg);
    stepper1.setSpeed(stepperSpeed);
    posOne = stepper1.currentPosition();
  }
  
  if ((value3 - value4) > 42)
  {
    stepper2.move(stepPos);
    stepper2.setSpeed(stepperSpeed);
    posTwo = stepper2.currentPosition();
  }
  else if((value4 - value3) > 42)
  {
    stepper2.move(stepNeg);
    stepper2.setSpeed(stepperSpeed);
    posTwo = stepper2.currentPosition();
  }
  
  stepper1.runSpeedToPosition();
  stepper2.runSpeedToPosition();
}

void WriteSD(int uvLevel)
{  
  if((value1 - value2 < 42 || value2 - value1 < 42) && (value3 - value4 < 42 || value4 - value3 < 42))
  {
    myFile = SD.open(filename, FILE_WRITE);//<<<<<<<<<<< OPEN
    myFile.println(uvLevel);
    myFile.close();//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>CLOSE
  }     
}

int getUV()
{
  int receivedVal;
  if (Serial.available() > 0) {
    // read the incoming byte:
    receivedVal = Serial.read();
  }

  return receivedVal;
}
