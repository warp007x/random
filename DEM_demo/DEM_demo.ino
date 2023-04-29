/******************************************************************************
TestRun.ino
TB6612FNG H-Bridge Motor Driver Example code
Michelle @ SparkFun Electronics
8/20/16
https://github.com/sparkfun/SparkFun_TB6612FNG_Arduino_Library
 
Uses 2 motors to show examples of the functions in the library.  This causes
a robot to do a little 'jig'.  Each movement has an equal and opposite movement
so assuming your motors are balanced the bot should end up at the same place it
started.
 
Resources:
TB6612 SparkFun Library
 
Development environment specifics:
Developed on Arduino 1.6.4
Developed with ROB-9457
******************************************************************************/
 
// This is the library for the TB6612 that contains the class Motor and all the
// functions
#include <SparkFun_TB6612.h>
 
// Pins for all inputs, keep in mind the PWM defines must be on PWM pins
// the default pins listed are the ones used on the Redbot (ROB-12097) with
// the exception of STBY which the Redbot controls with a physical switch
#define XAIN1 22
#define XBIN1 24
#define XAIN2 26
#define XBIN2 28
#define XPWMA 5
#define XPWMB 6
#define XSTBY 7

#define YAIN1 30
#define YBIN1 32
#define YAIN2 34
#define YBIN2 36
#define YPWMA 2
#define YPWMB 3
#define YSTBY 4
 
// these constants are used to allow you to make your motor configuration 
// line up with function names like forward.  Value can be 1 or -1
const int xoffsetA = 1;
const int xoffsetB = 1;

const int yoffsetA = 1;
const int yoffsetB = 1;

 
// Initializing motors.  The library will allow you to initialize as many
// motors as you have memory for.  If you are using functions like forward
// that take 2 motors as arguements you can either write new functions or
// call the function more than once.
Motor xmotor1 = Motor(XAIN1, XAIN2, XPWMA, xoffsetA, XSTBY);
Motor xmotor2 = Motor(XBIN1, XBIN2, XPWMB, xoffsetB, XSTBY);

Motor ymotor1 = Motor(YAIN1, YAIN2, YPWMA, yoffsetA, YSTBY);
Motor ymotor2 = Motor(YBIN1, YBIN2, YPWMB, yoffsetB, YSTBY);
 
void setup()
{
 Serial.begin(115200);//Nothing here
}
 
 
void loop()
{
   //Use of the drive function which takes as arguements the speed
   //and optional duration.  A negative speed will cause it to go
   //backwards.  Speed can be from -255 to 255.  Also use of the 
   //brake function which takes no arguements.
   /*xmotor1.drive(255,10000);
   Serial.println("xmotor1 forward");
   xmotor2.drive(255,10000);
   Serial.println("xmotor2 forward");
   ymotor1.drive(255,10000);
   Serial.println("ymotor1 forward");
   ymotor2.drive(255,10000);
   Serial.println("ymotor2 forward");
   
   

   ymotor1.drive(-255,5000);
   Serial.println("ymotor1 backwards");
   ymotor2.drive(-255,5000);
   Serial.println("ymotor2 backwards");  
   xmotor1.drive(-255,5000);
   Serial.println("xmotor1 backward ");
   xmotor2.drive(-255,5000);
   Serial.println("xmotor2 backwards");
   
   
   xmotor1.brake();
   xmotor2.brake();
   ymotor1.brake();
   ymotor2.brake();

   
   delay(1000);
   
   //Use of the drive function which takes as arguements the speed
   //and optional duration.  A negative speed will cause it to go
   //backwards.  Speed can be from -255 to 255.  Also use of the 
   //brake function which takes no arguements.
  /* xmotor1.drive(-255,1000);
   ymotor1.drive(-255,1000);
   xmotor2.drive(-255,1000);
   ymotor2.drive(-255,1000);
   

   xmotor1.drive(255,1000);
   ymotor1.drive(255,1000);  
   xmotor2.drive(255,1000);
   ymotor2.drive(255,1000);
   
   
   xmotor1.brake();
   xmotor2.brake();
   ymotor1.brake();
   ymotor2.brake();
   
   delay(1000);
   */
   //Use of the forward function, which takes as arguements two motors
   //and optionally a speed.  If a negative number is used for speed
   //it will go backwards
   delay(2000);
   forward(xmotor1, xmotor2, 255);
   Serial.println("x forward");
   delay(5000);
   forward(ymotor1, ymotor2, 255);
   Serial.println("y forward");
   delay(5000);
   
   //Use of the back function, which takes as arguments two motors 
   //and optionally a speed.  Either a positive number or a negative
   //number for speed will cause it to go backwards
   back(xmotor1, xmotor2, -255);
   Serial.println("x backward");
   delay(5000);
   back(ymotor1, ymotor2, -255);
   Serial.println("y backward");
   delay(5000);
   
   //Use of the brake function which takes as arguments two motors.
   //Note that functions do not stop motors on their own.
   brake(xmotor1, xmotor2);
   brake(ymotor1, ymotor2);
   delay(2000);
   
   //Use of the left and right functions which take as arguements two
   //motors and a speed.  This function turns both motors to move in 
   //the appropriate direction.  For turning a single motor use drive.
   /*left(xmotor1, ymotor1, 255);
   right(xmotor1, ymotor1, 255);
   Serial.println("x left, y right");
   delay(5000);
   
   right(xmotor2, ymotor2, 255);
   left(xmotor2, ymotor2, 255);
   Serial.println("x right, y left");
   delay(5000);
   
   //Use of brake again.
   brake(xmotor1, xmotor2);
   brake(ymotor1, ymotor2);
   delay(5000);*/
   
}
