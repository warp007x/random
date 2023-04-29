// 
#define RPWM 9 // define pin 3 for RPWM pin (output)
#define R_EN 10 // define pin 2 for R_EN pin (input)
#define R_IS 12 // define pin 5 for R_IS pin (output)

#define LPWM 11 // define pin 6 for LPWM pin (output)
#define L_EN 2 // define pin 7 for L_EN pin (input)
#define L_IS 13 // define pin 8 for L_IS pin (output)
#define CW 1 //do not change
#define CCW 0 //do not change
#define debug 1 //change to 0 to hide serial monitor debugging information or set to 1 to view

#include <RobojaxBTS7960.h>
RobojaxBTS7960 motor(R_EN,RPWM,R_IS, L_EN,LPWM,L_IS,debug);

void setup() {
  // BTS7960 Motor Control Code by Robojax.com 20190622
  Serial.begin(9600);// setup Serial Monitor to display information

   motor.begin();
   //watch video for details: https://youtu.be/PUL5DZ9TA2o
   
    // BTS7960 Motor Control Code by Robojax.com 20190622 
}

void loop() {
   // BTS7960 Motor Control Code by Robojax.com 20190622 
      //watch video for details: https://youtu.be/PUL5DZ9TA2o
    motor.rotate(100,CW);// run motor with 100% speed in CW direction
    delay(5000);//run for 5 seconds
    motor.stop();// stop the motor
    delay(3000);// stop for 3 seconds
    motor.rotate(100,CCW);// run motor at 100% speed in CCW direction
    delay(5000);// run for 5 seconds
    motor.stop();// stop the motor
    delay(3000);  // stop for 3 seconds
  // slowly speed up the motor from 0 to 100% speed
    for(int i=0; i<=100; i++){ 
        motor.rotate(i,CCW);
        delay(50);
    } 
  
   // slow down the motor from 100% to 0 with 
    for(int i=100; i>0; i--){ 
        motor.rotate(i,CCW);
        delay(50);
    } 
  
   //watch video for details: https://youtu.be/PUL5DZ9TA2o  
    motor.stop();// stop motor
    delay(3000); // stop for 3 seconds        
 // BTS7960 Motor Control Code by Robojax.com 20190622  
}// loop ends
