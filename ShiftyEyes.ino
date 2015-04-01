/*
 * Tutorial 6a: Introduction to Servo Motors
 * 
 * Simply rotates your server from 0 to 180 degrees and back.
 *
 * The circuit:
 * - Brown pin to ground
 * - Red pin to 5v
 * - Orange pin to digital pin 9
 *
 * by BARRAGAN <http://barraganstudio.com>
 * modified 14 August 2013
 * by Blaise Jarrett
 *
 * This example code is in the public domain.
 *
 * Derivative work from:
 * http://arduino.cc/en/Tutorial/Sweep
 *
 */

#include <Servo.h> 

// the Orange pin is connected to digital pin 9
int servoPin = 9;
int lastAngle = 0;
int nLoopSteps = 4;
  
// create servo object to control our servo
// a maximum of eight servo objects can be created 
Servo myServo;
int   waitTime = 150;
 
void setup() 
{
  Serial.begin(9600);
    // attaches the servo on pin 9 to the servo object 
    myServo.attach(servoPin);
}

void moveEye(int fromAngle, int toAngle, int nSteps, int stepWait)
{
  int iStep;
  int stepAngle = (toAngle - fromAngle) / nSteps;
  int nextAngle;
  
  Serial.print("Called moveEye from ");
  Serial.print(fromAngle);
  Serial.print(" to ");
  Serial.print(toAngle);
  Serial.print(" nSteps ");
  Serial.print(nSteps);
  Serial.print(" stepAngle ");
  Serial.print(stepAngle);
  Serial.print(" stepWait ");
  Serial.println(stepWait);

  for (nextAngle = fromAngle + stepAngle, iStep = 0;
       iStep < nSteps;
       iStep++, nextAngle += stepAngle) {
    Serial.print(nextAngle);
    Serial.print(" ");
    myServo.write(nextAngle);
    delay(stepWait);
  }
  Serial.println(" ");
}

void loop()
{
  if (Serial.available()) {
    nLoopSteps = Serial.parseInt();
    Serial.print("nLoopSteps set to ");
    Serial.println(nLoopSteps);
  } else {
    Serial.println("No input");
  }
    
    // Make sure the servo is where we think we
    //  left it
    myServo.write(lastAngle);

    // wait for it to move
    delay(150);
    
    moveEye(lastAngle, 20, nLoopSteps, 50);
    
    delay(500);
    
    moveEye(20, lastAngle, nLoopSteps, 100);
    
    delay(500);
    
    moveEye(lastAngle, 20, nLoopSteps, 20);
    
    delay(500);
}
