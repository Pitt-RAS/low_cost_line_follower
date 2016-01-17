//********************Line Following Robot Code**********************
//Created by Brandon Contino and Quentin Torgerson for Pitt RAS Line Following Robot
//May 16, 2015
//Last Updated: May 16, 2015
//DarkOnLight: This refers to the operation of the robot when utilizing a dark line on a lighter background
//LightOnDark: This refers to the operation of the robot when utilizing a light line on a darker background


//Establishing Global Variables
const byte sensePinLeft = 1;
const byte sensePinRight = 2;
const byte motorPinLeft1 = 3;
const byte motorPinLeft2 = 4;
const byte motorPinRight1 = 5;
const byte motorPinRight2 = 6;
int leftSense;
int rightSense;
int maxSense = 
int leftMotorSpeed;
int rightMotorSpeed;
int maxSpeed = 255;


void setup()
{
  pinMode(sensePinLeft,INPUT);
  pinMode(sensePinRight,INPUT);
  pinMode(motorPinLeft1,OUTPUT);
  digitalWrite(motorPinLeft1,LOW);
  pinMode(motorPinLeft2,OUTPUT);
  digitalWrite(motorPinLeft2,LOW);
  pinMode(motorPinRight1,OUTPUT);
  digitalWrite(motorPinRight1,LOW);
  digitalWrite(motorPinRight2,OUTPUT);
  digitalWrite(motorPinRight2,LOW);
  if(maxSpeed > 255)
    maxSpeed = 255;
  else if (maxSpeed < 0)
    maxSpeed = 0;
  int halfMaxSpeed = maxSpeed*.5;
  
  //Serial.begin(9600); //Uncomment for Debugging
  delay(2000); //Allows time for operator to place after plugging in
}

void loop()
{
  //Check Line Sensors
  leftSense = analogRead(sensePinLeft);
  rightSense = analogRead(sensePinRight);
  
  //Determining Motor Speeds  
  if(leftSense > rightSense) //(leftSense > righSense) for DarkOnLight Operation; (leftSense < rightSense) for LightOnDark Operation
  {
    leftMotorSpeed = maxSpeed;
    rightMotorSpeed = halfMaxSpeed;
  }
  else if(leftSense < rightSense)//(leftSense < righSense) for DarkOnLight Operation; (leftSense > rightSense) for LightOnDark Operation
  {
    leftMotorSpeed = halfMaxSpeed;
    rightMotorSpeed = maxSpeed;
  }
  else//Both are equal, not likely to happen
  {
    leftMotorSpeed = maxSpeed;
    rightMotorSpeed = maxSpeed;
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
