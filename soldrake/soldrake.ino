// pins for motor driver X
#define RPWM_X 3 // define pin 3 for RPWM pin (output)
#define R_EN_X 4 // define pin 2 for R_EN pin (input)
#define R_IS_X 5 // define pin 5 for R_IS pin (output)

#define LPWM_X 6 // define pin 6 for LPWM pin (output)
#define L_EN_X 7 // define pin 7 for L_EN pin (input)
#define L_IS_X 8 // define pin 8 for L_IS pin (output)
// motor driver X pins end here

// pins for motor driver Y
#define RPWM_Y 9 // define pin 9 for RPWM pin (output)
#define R_EN_Y 10 // define pin 10 for R_EN pin (input)
#define R_IS_Y 12 // define pin 12 for R_IS pin (output)

#define LPWM_Y 11 // define pin 11 for LPWM pin (output)
#define L_EN_Y 2 // define pin 7 for L_EN pin (input)
#define L_IS_Y 13 // define pin 8 for L_IS pin (output)
// motor driver Y pins end here

#define CW 1 //
#define CCW 0 //
#define debug 1 //

//// R/C Channel Pin-Map
#define CH1 A0
#define CH2 A1
#define CH3 A2
#define CH4 A3
//#define CH5 A4

#define carLED A5

#include <RobojaxBTS7960.h>
RobojaxBTS7960 motorX(R_EN_X,RPWM_X,R_IS_X, L_EN_X,LPWM_X,L_IS_X,debug);//define motor 1 object
RobojaxBTS7960 motorY(R_EN_Y,RPWM_Y,R_IS_Y, L_EN_Y,LPWM_Y,L_IS_Y,debug);//define motor 2 object and the same way for other motors



char command=NULL;            //Int to store app command state.
int speedCar = 100;     // 50 - 255.
int speed_Coeff = 3;

int rcCH1 = 0; // Left - Right
int rcCH2 = 0; // Forward - Reverse
int rcCH3 = 0; // Acceleration
int rcCH4 = 0; // 
int rcCH5 = 0; // knob/sweep


// Motor Speed Values - Start at zero 
int MotorSpeedX = 0;
int MotorSpeedY = 0;

// Motor Direction Values - 0 = backward, 1 = forward 
int MotorDirX = 1;
int MotorDirY = 1;

void fwdX(int speed_pwm){
  motorX.rotate(speed_pwm,CW);
  delay(10);
  }
void fwdY(int speed_pwm){
  motorY.rotate(speed_pwm,CW);
  delay(10);
  }
void backX(int speed_pwm){
  motorX.rotate(speed_pwm,CCW);
  delay(10);
  }
void backY(int speed_pwm){
  motorY.rotate(speed_pwm,CCW);
  delay(10);
  }

void stop_disable(){
  motorX.stop();
  motorY.stop();
  delay(20);
  }

// Control MotorDriver X
void mControlX(int mspeed, int mdir) {

  // Determine direction
  if (mdir == 0) {
    // Motor backward
    Serial.print("Going Back X | Motor Speed: ");
    backX(mspeed);
    Serial.println(mspeed);
    
  } else {
    // Motor forward
    Serial.println("Going Ahead X | Motor Speed: ");
    fwdX(mspeed);
    Serial.println(mspeed);
  }

}

// Control MotorDriver Y
void mControlY(int mspeed, int mdir) {

  // Determine direction
  if (mdir == 0) {
    // Motor backward
    Serial.println("Going Back Y | Motor Speed: ");
    backY(mspeed);
    Serial.println(mspeed);
    
  } else {
    // Motor forward
    Serial.println("Going Ahead Y | Motor Speed: ");
    fwdY(mspeed);
    Serial.println(mspeed);
  }

}

// Read the number of a given channel and convert to the range provided.
// If the channel is off, return the default value
int readChannel(byte channelInput, int minLimit, int maxLimit, int defaultValue) {
   int ch = pulseIn(channelInput, HIGH, 30000);
  if (ch < 100) return defaultValue;
  return map(ch, 1000, 2000, minLimit, maxLimit);
}

// Read the channel and return a boolean value
bool readSwitch(byte channelInput, bool defaultValue) {
  int intDefaultValue = (defaultValue) ? 100 : 0;
  int ch = readChannel(channelInput, 0, 100, intDefaultValue);
  return (ch > 50);
}


void setup(){
      
 
   Serial.begin(9600);


  motorX.begin();
  motorY.begin();  

  pinMode(CH1, INPUT);
  pinMode(CH2, INPUT);
  pinMode(CH3, INPUT);
  pinMode(CH4, INPUT);
 // pinMode(CH5, INPUT);

  rcCH1 = map(readChannel(CH1, -100, 100, 0), -80, 80, -100, 100);
  rcCH2 = map(readChannel(CH2, -100, 100, 0), -70, 70, -100, 100);
  rcCH3 = constrain(map(readChannel(CH3, 0, 155, 0), 20, 130, 0, 155), 0, 255);
  //rcCH5 = readChannel(CH5, -100, 100, 0);
  rcCH4 = map(readChannel(CH4, -100, 100, 0), -80, 80, -100, 100);

  // Set LED pin as output

  Serial.println("Initiating Rover");
  // Keep motors on standby for two seconds & flash LED
  stop_disable();
  digitalWrite(carLED, HIGH);
  delay (1000);
  digitalWrite(carLED, LOW);
  delay (1000);
  Serial.println("Rover Standby.....");
  delay(1000);
  Serial.println("Select Options");
  Serial.println("A=RC-Mode, F=Forward, B=Backward, L=Left, R=Right, I=Forward LOW SPEED, G=Backward LOW SPEED, J=Right LOW SPEED, H=Left LOW SPEED, S=Stop Robot");
}

void goAheadFS(){ 
  
      Serial.println("Going Ahead FULL SPEED.......");
      fwdX(100);
      fwdY(100);
   
      delay(20);
  }

void goBackFS(){
   
      Serial.println("Going Back FULL SPEED.......");
      backX(100);
      backY(100);
      
      delay(20);
  }

void goLeftFS(){
  
      Serial.println("Going Left FULL SPEED.......");
      backY(100);
      fwdX(100);
      
      delay(20); 
  }

  void goRightFS(){ 
  
      Serial.println("Going Right FULL SPEED.......");
      fwdY(100);
      backX(100);
      
      delay(20);
  }

void goAheadLS(){

      Serial.println("Going Ahead LOW SPEED.......");
      fwdX(speedCar/speed_Coeff);
      fwdY(speedCar/speed_Coeff);

      delay(20);
  }

void goBackLS(){

      Serial.println("Going Back LOW SPEED.......");
      backX(speedCar/speed_Coeff);
      backY(speedCar/speed_Coeff);
      
      delay(20);
  }

void goRightLS(){ 
  
      Serial.println("Going Right LOW SPEED.......");
      fwdY(speedCar/speed_Coeff);
      backX(speedCar/speed_Coeff);
      
      delay(20);
  }

void goLeftLS(){ 
  
      Serial.println("Going Left LOW SPEED.......");
      backY(speedCar/speed_Coeff);
      fwdX(speedCar/speed_Coeff);
      delay(20);
  }

void stopRobot(){  

      Serial.println("Robot Standby.......");
      stop_disable();
      delay(20);
  
  }

////////////////////////////////////////////////

////////////////////////////////////////////////  

void loop()
{

if(Serial.available()>=0)
{
  command = Serial.read();
  if(command == 'A' )
        {
          while(Serial.read()!='S')
              {
                //int k= Serial.read();
                //if (k=='S') break; 
                digitalWrite(carLED, HIGH);
                //Reading channel Values
                Serial.println("....");
                Serial.println("R/C MODE ENABLED.  Press S to disable");
// Get RC channel values
  rcCH1 = map(readChannel(CH1, -100, 100, 0), -80, 80, -100, 100);
  rcCH2 = map(readChannel(CH2, -100, 100, 0), -70, 70, -100, 100);
  rcCH3 = constrain(map(readChannel(CH3, 0, 155, 0), 20, 130, 0, 155), 0, 255);
  //rcCH5 = readChannel(CH5, -100, 100, 0);
  rcCH4 = map(readChannel(CH4, -100, 100, 0), -80, 80, -100, 100);

  // Print values to serial monitor for debugging
  Serial.print("Ch1 = ");
  Serial.print(rcCH1);
 
  Serial.print(" Ch2 = ");
  Serial.print(rcCH2);
 
  Serial.print(" Ch3 = ");
  Serial.print(rcCH3);
 
  Serial.print(" Ch4 = ");
  Serial.print(rcCH4);
 
  Serial.print(" Ch5 = ");
  Serial.println(rcCH5);

  // Set speeds with channel 3 value
  MotorSpeedX = rcCH3;
  MotorSpeedY = rcCH3;

  // Set Mode with channel 6 value
 
    // Normal Mode

    // Turn off LED
//    digitalWrite(carLED, LOW);

    // Set forward/backward direction with channel 2 value
    if (rcCH2 >= 0) {
      //Forward
      MotorDirX = 1;
      MotorDirY = 1;
      Serial.println("Forward");
      delay(20);
    } else {
      //Backward
      MotorDirX = 0;
      MotorDirY = 0;
      Serial.println("Backward");
      delay(20);
    }

    // Add channel 2 speed
    MotorSpeedX = MotorSpeedX + abs(rcCH2);
    MotorSpeedY = MotorSpeedY + abs(rcCH2);

    // Set left/right offset with channel 1 value
    MotorSpeedX = MotorSpeedX - rcCH1;
    MotorSpeedY = MotorSpeedY + rcCH1;

  

  // Ensure that speeds are between 0 and 255
  MotorSpeedX = map(constrain(MotorSpeedX, 0, 255),0,255,0,100);
  MotorSpeedY = map(constrain(MotorSpeedY, 0, 255),0,255,0,100) + 2;

  if(MotorSpeedX <= 5){
    MotorSpeedX=0;
    }
  if(MotorSpeedY <= 5){
    MotorSpeedY=0;
    }

  //Drive Motors
  Serial.println("Driving Motors");
  mControlX(MotorSpeedX, MotorDirX);
  mControlY(MotorSpeedY, MotorDirY);

  // Print speed values to serial monitor for debugging
  Serial.print("MotorDriver X Speed = ");
  Serial.println(MotorSpeedX);
  Serial.print("MotorDriver Y Speed = ");
  Serial.println(MotorSpeedY);

  // Slight delay
  delay(50);


              }
        }
           
  else if (command=='F'||command=='B'||command=='L'||command=='R'||command=='I'||command=='G'||command=='J'||command=='H'||command=='S'||command=='W'||command=='w'||command=='D') 
  {
  /*command = Serial.read();*/
  digitalWrite(carLED, LOW);

    switch (command) {
        case 'F':goAheadFS();break;
        case 'B':goBackFS();break;
        case 'L':goLeftFS();break;
        case 'R':goRightFS();break;
        case 'I':goAheadLS();break;
        case 'G':goBackLS();break;
        case 'J':goRightLS();break;
        case 'H':goLeftLS();break;

        case 'S':stopRobot();break;
        
        default: Serial.println("Invalid Input c(><c)");


            }
            
     }
//else{Serial.println("Invalid Input c(><c)");}
}
}


    
    
