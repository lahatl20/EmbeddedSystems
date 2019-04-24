#include <AccelStepper.h>
#define HALFSTEP 8

#define motorPin1  3     // IN1 on the ULN2003 driver 1
#define motorPin2  4     // IN2 on the ULN2003 driver 1
#define motorPin3  5     // IN3 on the ULN2003 driver 1
#define motorPin4  6     // IN4 on the ULN2003 driver 1

//Constants
const int pResistor1 = A0; // Photoresistor at Arduino analog pin A0
const int pResistor2 = A1;
const int ledPin1 = 9;       // Led pin at Arduino pin 9

// Initialize with pin sequence
AccelStepper stepper1(HALFSTEP, motorPin1, motorPin3, motorPin2, motorPin4);

//Variables
int value1;          // Store value from photoresistor (0-1023)
int value2;
int stepperSpeed = 1000; //speed of the stepper (steps per second)
int target = 100;

void setup(){
 pinMode(ledPin1, OUTPUT);  // Set lepPin1 - 9 pin as an output
 pinMode(pResistor1, INPUT); // Set pResistor - A0 pin as an input
 pinMode(pResistor2, INPUT); // Set pResistor - A1 pin as an input
 stepper1.setMaxSpeed(2000.0);
 stepper1.move(1);  // I found this necessary
 stepper1.setSpeed(stepperSpeed);
 
 Serial.begin(9600);
}

void loop(){
  value1 = analogRead(pResistor1);
  value2 = analogRead(pResistor2);
  
  if ((value1 - value2) > 256)
  {
    stepper1.moveTo(target);
    stepper1.setSpeed(stepperSpeed);
    digitalWrite(ledPin1, LOW); //Turn led_mid on
  }
  else if((value2 - value1) > 256)
  {
    stepper1.moveTo(-target);
    stepper1.setSpeed(stepperSpeed);
    digitalWrite(ledPin1, LOW); //Turn led_mid on
  }
  else
  {
    digitalWrite(ledPin1, HIGH); //Turn led_mid on
  }
  delay(500); //Small delay
}
