//********************Line Following Robot Code**********************
//Created by Brandon Contino and Quentin Torgerson for Pitt RAS Line Following Robot

//Establishing Global Variables
const byte sensePinLeft = A6;
const byte sensePinRight = A7;
const byte motorPinLeft1 = 10;
const byte motorPinLeft2 = 11;
const byte motorPinRight1 = 9;
const byte motorPinRight2 = 3;
const byte emitterPin = 2;
int leftSense;
int rightSense;
int leftMotorSpeed;
int rightMotorSpeed;
int darkThreshold = 100;
int maxSpeed = 150;
int lowSpeed = -150; 

void setup()
{
  pinMode(motorPinLeft1,OUTPUT);
  digitalWrite(motorPinLeft1,LOW);
  pinMode(motorPinLeft2,OUTPUT);
  digitalWrite(motorPinLeft2,LOW);
  pinMode(motorPinRight1,OUTPUT);
  digitalWrite(motorPinRight1,LOW);
  pinMode(motorPinRight2,OUTPUT);
  digitalWrite(motorPinRight2,LOW);
  
  pinMode(emitterPin, OUTPUT);
  digitalWrite(emitterPin, HIGH);
  if(maxSpeed > 255)
    maxSpeed = 255;
  else if (maxSpeed < 0)
    maxSpeed = 0;
  
  //Serial.begin(9600); //Uncomment for Debugging
  delay(2000); //Allows time for operator to place after plugging in
}

void loop()
{
  //Check Line Sensors
  leftSense = analogRead(sensePinLeft);
  rightSense = analogRead(sensePinRight);

  //uncomment for debugging
  //Serial.println(leftSense);
  //Serial.println(rightSense);
  //Serial.println(" ");
  //delay(200);


  //Determining Motor Speeds  
  if((rightSense > darkThreshold) && (leftSense < darkThreshold))//rightSense sees white, leftSense sees black
  {
    //turn left
    leftMotorSpeed = lowSpeed;
    rightMotorSpeed = maxSpeed;
  }
  else if((leftSense > darkThreshold) && (rightSense < darkThreshold))//leftSense sees white, rightSense sees black
  {
    //turn right
    leftMotorSpeed = maxSpeed;
    rightMotorSpeed = lowSpeed;
  }
  else if((leftSense < darkThreshold) && (rightSense < darkThreshold))//both see black
  {
    //go straight
    leftMotorSpeed = maxSpeed;
    rightMotorSpeed = maxSpeed;
  }
  else//both see white, off the line
  {
    //continue the previous motor speeds
  }
  
  //Drives the Motors to the Set Speed
  driveMotors(leftMotorSpeed , rightMotorSpeed);
}


///////////// Motor Driving Function ////////////////////////////////////////////
void driveMotors(int left , int right){  // -255 means backwards, 255 means forwards
  // declare variables for function
  static int leftMotor1PWM;
  static int leftMotor2PWM;
  static int rightMotor1PWM;
  static int rightMotor2PWM;
  
  // define left motor movement
  if (left > 0)  // left motor forward
  {
    leftMotor1PWM = left;
    leftMotor2PWM = 0;
  }
  else if (left > 255) {
    leftMotor1PWM = 255;
    leftMotor2PWM = 0;
  }
  else if (left < 0)  // left motor backward
  {
    leftMotor1PWM = 0;
    leftMotor2PWM = -left;
  }
  else if (left < -255) {
    leftMotor1PWM = 0;
    leftMotor2PWM = 255;
  }
  else // left motor brake
  {  
    leftMotor1PWM = 255;
    leftMotor2PWM = 255;
  }


  
  // define right motor movement
  if (right > 0)  // right motor forward
  {
    rightMotor1PWM = right;
    rightMotor2PWM = 0;
  }
  else if (right > 255) {
    rightMotor1PWM = 255;
    rightMotor2PWM = 0;
  }
  else if (right < 0)  // right motor backward
  {
    rightMotor1PWM = 0;
    rightMotor2PWM = -right;
  }
  else if (right < -255) {
    rightMotor1PWM = 0;
    rightMotor2PWM = 255;
  }
  else 
  {
    rightMotor1PWM = 255;
    rightMotor2PWM = 255;
  }
  
  // assign pwm values to motor driving pins
  analogWrite(motorPinLeft1, leftMotor1PWM);
  analogWrite(motorPinLeft2, leftMotor2PWM); 
  analogWrite(motorPinRight1, rightMotor1PWM);
  analogWrite(motorPinRight2, rightMotor2PWM);
}
