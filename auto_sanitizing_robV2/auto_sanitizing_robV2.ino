#include<NewPing.h>
#define RIGHT A2
#define LEFT A3
#define TRIGGER_PIN A1
#define ECHO_PIN A0
#define MAX_DISTANCE 100
#include <Servo.h>
  
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

#define ENA_m1 2       // Enable/speed motor Right 
#define ENB_m1 3        // Enable/speed motor Left
#define ENA_m2 4       // Enable/speed motor Reload
#define ENB_m2 5       // Enable/speed motor Fire

#define IN_11a  22        // L298N #1 in 1 motor Right
#define IN_12a  24        // L298N #1 in 2 motor Right
#define IN_13b  26       // L298N #1 in 3 motor Left
#define IN_14b  28       // L298N #1 in 4 motor Left

#define IN_21a  32        // L298N #2 in 1 motor Reload
#define IN_22a  34        // L298N #2 in 2 motor Arm
#define IN_23b  36       // L298N #2 in 3 motor Disengage
#define IN_24b  38       // L298N #2 in 4 motor Fire

int command;             //Int to store app command state.
int speedCar = 255;     // 50 - 255.
int led=19;
int brightness=0;
int pos=0;

Servo myservo;

void goAhead();
void goBack();
void goLeft();
void goRight();
void stopRobot();



void setup() {
  Serial.begin(115200);
    pinMode(ENA_m1, OUTPUT);
    pinMode(ENB_m1, OUTPUT);  // L298N #1
    pinMode(ENA_m2, OUTPUT);
    pinMode(ENB_m2, OUTPUT);  // L298N #2
  
    pinMode(IN_11a, OUTPUT);
    pinMode(IN_12a, OUTPUT);
    pinMode(IN_13b, OUTPUT);
    pinMode(IN_14b, OUTPUT);  // L298N #1
    
    pinMode(IN_21a, OUTPUT);
    pinMode(IN_22a, OUTPUT);
    pinMode(IN_23b, OUTPUT);
    pinMode(IN_24b, OUTPUT);  // L298N #2
    pinMode(14, OUTPUT);
    pinMode(15, OUTPUT);
    pinMode(led, OUTPUT);

    myservo.attach(10);
{
for(pos = 90; pos <= 180; pos += 1){
  myservo.write(pos);
  delay(15);
} for(pos = 180; pos >= 0; pos-= 1) {
  myservo.write(pos);
  delay(15);
}for(pos = 0; pos<=90; pos += 1) {
  myservo.write(pos);
  delay(15);
}
}
pinMode(RIGHT, INPUT);
pinMode(LEFT, INPUT);


}
        
void loop() {

  delay(50);
unsigned int distance = sonar.ping_cm();
Serial.print("distance");
Serial.println(distance);


int Right_Value = digitalRead(RIGHT);
int Left_Value = digitalRead(LEFT);

Serial.print("RIGHT");
Serial.println(Right_Value);
Serial.print("LEFT");
Serial.println(Left_Value);

if((Right_Value==1) && (distance>=10 && distance<=30)&&(Left_Value==1)){
  goAhead();
}else if((Right_Value==0) && (Left_Value==1)) {
  goLeft();
}else if((Right_Value==1)&&(Left_Value==0)) {
  goRight();
}else if((Right_Value==1)&&(Left_Value==1)) {
  stopRobot();
  delay(4500);
  goBack();
  delay(2000);
  goAhead(); 
}else if(distance > 1 && distance < 10) {
  goAhead();
  }
 if (Serial.available() > 0) {
  command = Serial.read();

  switch (command){
   case 1:goAhead();break;
   case 2:goBack();break;
   case 3:goLeft();break;
   case 4:goRight();break;
   
   case 0:stopRobot();break;
   default: break;
  }
 
 }
}

 void goAhead(){
      digitalWrite(IN_11a, HIGH);
      digitalWrite(IN_12a, LOW);
      analogWrite(ENA_m1, speedCar);

      digitalWrite(IN_13b, HIGH);
      digitalWrite(IN_14b, LOW);
      analogWrite(ENB_m1, speedCar);
      
      digitalWrite(IN_21a, HIGH);
      digitalWrite(IN_22a, LOW);
      analogWrite(ENA_m2, speedCar);

      digitalWrite(IN_23b, HIGH);
      digitalWrite(IN_24b, LOW);
      analogWrite(ENB_m2, speedCar);
      
      Serial.println("FORWAR4D");
      brightness=155;
      digitalWrite(led, HIGH);
      analogWrite(led, brightness);
}


void goBack(){
      digitalWrite(IN_11a, LOW);
      digitalWrite(IN_12a, HIGH);
      analogWrite(ENA_m1, speedCar);


      digitalWrite(IN_13b, LOW);
      digitalWrite(IN_14b, HIGH);
      analogWrite(ENB_m1, speedCar);
      Serial.println("BACKWARD");
      brightness=155;
      digitalWrite(led, HIGH);
      analogWrite(led, brightness);
}


void goRight(){
      digitalWrite(IN_11a, LOW);
      digitalWrite(IN_12a, HIGH);
      analogWrite(ENA_m1, speedCar);


      digitalWrite(IN_13b, HIGH);
      digitalWrite(IN_14b, LOW);
      analogWrite(ENB_m1, speedCar);
      Serial.println("RIGHT");
}


void goLeft(){
      digitalWrite(IN_11a, HIGH);
      digitalWrite(IN_12a, LOW);
      analogWrite(ENA_m1, speedCar);


      digitalWrite(IN_13b, LOW);
      digitalWrite(IN_14b, HIGH);
      analogWrite(ENB_m1, speedCar);
      Serial.println("LEFT");
}


void stopRobot(){  
       
      brightness=55;
      digitalWrite(led, HIGH);
      analogWrite(led, brightness);
      
      digitalWrite(IN_11a, LOW);
      digitalWrite(IN_12a, LOW);
      analogWrite(ENA_m1, speedCar);


      digitalWrite(IN_13b, LOW);
      digitalWrite(IN_14b, LOW);
      analogWrite(ENB_m1, speedCar);

  
      digitalWrite(IN_21a, LOW);
      digitalWrite(IN_22a, LOW);
      analogWrite(ENA_m2, speedCar);

      
      digitalWrite(IN_23b, LOW);
      digitalWrite(IN_24b, LOW);
      analogWrite(ENB_m2, speedCar);

      Serial.println("STOPPED");
  
  }
