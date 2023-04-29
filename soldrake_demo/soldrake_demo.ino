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

#include <RobojaxBTS7960.h>
RobojaxBTS7960 motorX(R_EN_X,RPWM_X,R_IS_X, L_EN_X,LPWM_X,L_IS_X,debug);//define motor 1 object
RobojaxBTS7960 motorY(R_EN_Y,RPWM_Y,R_IS_Y, L_EN_Y,LPWM_Y,L_IS_Y,debug);//define motor 2 object and the same way for other motors


void setup() {
  // put your setup code here, to run once:
   Serial.begin(9600);// setup Serial Monitor to display information

   motorX.begin();
   motorY.begin();   

}

void loop() {
  for (int i=1; i<=100;i++){
  motorX.rotate(i,CW);
  motorY.rotate(i,CW);
  delay(100);
  }
  for (int i=100; i>=1;i--){
  motorX.rotate(i,CW);
  motorY.rotate(i,CW);
  delay(100);
  }
  delay(1000);
  motorX.stop();
  motorY.stop();
  delay(4000);
  
  for (int j=1; j<=100;j++){
  motorX.rotate(j,CCW);
  motorY.rotate(j,CCW);
  delay(100);
  }
  for (int j=100; j>=1;j--){
  motorX.rotate(j,CCW);
  motorY.rotate(j,CCW);
  delay(100);
  }
  delay(1000);
  motorX.stop();
  motorY.stop();
  delay(4000);
  // put your main code here, to run repeatedly:

}
