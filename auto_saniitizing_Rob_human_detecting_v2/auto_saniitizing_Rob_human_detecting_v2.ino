#include<NewPing.h>
#include<Servo.h>

#define light  18       //LED Front         pin A4 for Arduino Uno
#define serv 19         //SERVO       pin A5 for Arduino Uno

#define ENA_m1 5        // Enable/speed motor Front Right 
#define ENB_m1 6        // Enable/speed motor Back Right
#define ENA_m2 10       // Enable/speed motor Front Left
#define ENB_m2 11       // Enable/speed motor Back Left

#define IN_11  2        // L298N #1 in 1 motor Front Right
#define IN_12  3        // L298N #1 in 2 motor Front Right
#define IN_13  4        // L298N #1 in 3 motor Back Right
#define IN_14  7        // L298N #1 in 4 motor Back Right

#define IN_21  8        // L298N #2 in 1 motor Front Left
#define IN_22  9        // L298N #2 in 2 motor Front Left
#define IN_23  12       // L298N #2 in 3 motor Back Left
#define IN_24  13       // L298N #2 in 4 motor Back Left

#define RIGHT A0
#define LEFT A1
#define TRIGGER_PIN A2
#define ECHO_PIN A3
#define MAX_DISTANCE 100

  
// starting loaction
const int startAngle = 90;

// rotation limits
const int minimumAngle = 6;
const int maximumAngle = 175;

// speed
const int degreesPerCycle = 1;

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

Servo myservo;
 
int pos =0;

int command;            //Int to store app command state.
int speedCar = 100;     // 50 - 255.
int speed_Coeff = 4;
boolean lightFront = false;


int sweep();
void SerialOutput(int,int);

void setup() {  
   
    pinMode(light, OUTPUT);;
    //pinMode(serv, OUTPUT);
    
    pinMode(ENA_m1, OUTPUT);
    pinMode(ENB_m1, OUTPUT);
    pinMode(ENA_m2, OUTPUT);
    pinMode(ENB_m2, OUTPUT);
  
    pinMode(IN_11, OUTPUT);
    pinMode(IN_12, OUTPUT);
    pinMode(IN_13, OUTPUT);
    pinMode(IN_14, OUTPUT);
    
    pinMode(IN_21, OUTPUT);
    pinMode(IN_22, OUTPUT);
    pinMode(IN_23, OUTPUT);
    pinMode(IN_24, OUTPUT);

    myservo.attach(serv);
/*{
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
}*/
pinMode(RIGHT, INPUT);
pinMode(LEFT, INPUT);


  Serial.begin(115200); 

  } 

void goAhead(){ 

      digitalWrite(IN_11, HIGH);
      digitalWrite(IN_12, LOW);
      analogWrite(ENA_m1, speedCar);

      digitalWrite(IN_13, LOW);
      digitalWrite(IN_14, HIGH);
      analogWrite(ENB_m1, speedCar);


      digitalWrite(IN_21, LOW);
      digitalWrite(IN_22, HIGH);
      analogWrite(ENA_m2, speedCar);


      digitalWrite(IN_23, HIGH);
      digitalWrite(IN_24, LOW);
      analogWrite(ENB_m2, speedCar);

  }

void goBack(){ 

      digitalWrite(IN_11, LOW);
      digitalWrite(IN_12, HIGH);
      analogWrite(ENA_m1, speedCar);


      digitalWrite(IN_13, HIGH);
      digitalWrite(IN_14, LOW);
      analogWrite(ENB_m1, speedCar);


      digitalWrite(IN_21, HIGH);
      digitalWrite(IN_22, LOW);
      analogWrite(ENA_m2, speedCar);


      digitalWrite(IN_23, LOW);
      digitalWrite(IN_24, HIGH);
      analogWrite(ENB_m2, speedCar);

  }

void goRight(){ 

      digitalWrite(IN_11, LOW);
      digitalWrite(IN_12, HIGH);
      analogWrite(ENA_m1, speedCar);


      digitalWrite(IN_13, HIGH);
      digitalWrite(IN_14, LOW);
      analogWrite(ENB_m1, speedCar);


      digitalWrite(IN_21, LOW);
      digitalWrite(IN_22, HIGH);
      analogWrite(ENA_m2, speedCar);


      digitalWrite(IN_23, HIGH);
      digitalWrite(IN_24, LOW);
      analogWrite(ENB_m2, speedCar);


  }

void goLeft(){

      digitalWrite(IN_11, HIGH);
      digitalWrite(IN_12, LOW);
      analogWrite(ENA_m1, speedCar);


      digitalWrite(IN_13, LOW);
      digitalWrite(IN_14, HIGH);
      analogWrite(ENB_m1, speedCar);

        
      digitalWrite(IN_21, HIGH);
      digitalWrite(IN_22, LOW);
      analogWrite(ENA_m2, speedCar);


      digitalWrite(IN_23, LOW);
      digitalWrite(IN_24, HIGH);
      analogWrite(ENB_m2, speedCar);

        
  }

void goAheadRight(){
      
      digitalWrite(IN_11, HIGH);
      digitalWrite(IN_12, LOW);
      analogWrite(ENA_m1, speedCar/speed_Coeff);

      digitalWrite(IN_13, LOW);
      digitalWrite(IN_14, HIGH);
      analogWrite(ENB_m1, speedCar/speed_Coeff);


      digitalWrite(IN_21, LOW);
      digitalWrite(IN_22, HIGH);
      analogWrite(ENA_m2, speedCar);


      digitalWrite(IN_23, HIGH);
      digitalWrite(IN_24, LOW);
      analogWrite(ENB_m2, speedCar);
 
  }

void goAheadLeft(){
      
      digitalWrite(IN_11, HIGH);
      digitalWrite(IN_12, LOW);
      analogWrite(ENA_m1, speedCar);

      digitalWrite(IN_13, LOW);
      digitalWrite(IN_14, HIGH);
      analogWrite(ENB_m1, speedCar);


      digitalWrite(IN_21, LOW);
      digitalWrite(IN_22, HIGH);
      analogWrite(ENA_m2, speedCar/speed_Coeff);


      digitalWrite(IN_23, HIGH);
      digitalWrite(IN_24, LOW);
      analogWrite(ENB_m2, speedCar/speed_Coeff);
 
  }

void goBackRight(){ 

      digitalWrite(IN_11, LOW);
      digitalWrite(IN_12, HIGH);
      analogWrite(ENA_m1, speedCar/speed_Coeff);


      digitalWrite(IN_13, HIGH);
      digitalWrite(IN_14, LOW);
      analogWrite(ENB_m1, speedCar/speed_Coeff);


      digitalWrite(IN_21, HIGH);
      digitalWrite(IN_22, LOW);
      analogWrite(ENA_m2, speedCar);


      digitalWrite(IN_23, LOW);
      digitalWrite(IN_24, HIGH);
      analogWrite(ENB_m2, speedCar);

  }

void goBackLeft(){ 

      digitalWrite(IN_11, LOW);
      digitalWrite(IN_12, HIGH);
      analogWrite(ENA_m1, speedCar);


      digitalWrite(IN_13, HIGH);
      digitalWrite(IN_14, LOW);
      analogWrite(ENB_m1, speedCar);


      digitalWrite(IN_21, HIGH);
      digitalWrite(IN_22, LOW);
      analogWrite(ENA_m2, speedCar/speed_Coeff);


      digitalWrite(IN_23, LOW);
      digitalWrite(IN_24, HIGH);
      analogWrite(ENB_m2, speedCar/speed_Coeff);

  }

void stopRobot(){  

      digitalWrite(IN_11, LOW);
      digitalWrite(IN_12, LOW);
      analogWrite(ENA_m1, speedCar);


      digitalWrite(IN_13, LOW);
      digitalWrite(IN_14, LOW);
      analogWrite(ENB_m1, speedCar);

  
      digitalWrite(IN_21, LOW);
      digitalWrite(IN_22, LOW);
      analogWrite(ENA_m2, speedCar);

      
      digitalWrite(IN_23, LOW);
      digitalWrite(IN_24, LOW);
      analogWrite(ENB_m2, speedCar);
  
  }
  
void loop(){

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


delay(50);
unsigned int distance = sonar.ping_cm();
Serial.println("distance Before Sweep");
Serial.println(distance);
int duration;
int dex=sweep();
distance = sonar.ping_cm();
Serial.println("Distance after sweep");
Serial.println(distance);
int Right_Value = digitalRead(RIGHT);
int Left_Value = digitalRead(LEFT);
if ((distance >= 0 && distance <= 15)||Left_Value==1||Right_Value==1){duration=50;}
else if(distance >=16 && distance <=60){duration=1000;}
else if(distance >=61 && distance <=100){duration=2000;}
else if(distance >=101 && distance <=150){duration=4000;}
else if(distance >150){duration=6000;}

if(Serial.available()>0)
{
  command = Serial.read();
if(dex>0 && command == 'A' )
{
 if(dex>=75 && dex<=105){
 goAhead();
 delay(duration);
 stopRobot();
 }
 else if(dex>=60 && dex<75){
 goAheadRight();
 delay(duration);
 stopRobot();
 }
 else if(dex>=0 && dex<60){
 goRight();
 delay(2000);
 goAhead();
 delay(duration);
 stopRobot();
 }
 else if(dex>105 && dex<=120){
 goAheadLeft();
 delay(duration);
 stopRobot();
 }
 else if(dex>120 && dex<180){
 goLeft();
 delay(2000);
 goAhead();
 delay(duration);
 stopRobot();
 }
Serial.println("PROXIMITY RIGHT: ");
Serial.print(Right_Value);
Serial.println("PROXIMITY  LEFT: ");
Serial.print(Left_Value);

if((Right_Value==1) && (distance>=10 && distance<=30)&&(Left_Value==1)){
  goAhead();
}else if((Right_Value==0) && (Left_Value==1)) {
  goLeft();
}else if((Right_Value==1)&&(Left_Value==0)) {
  goRight();
}else if((Right_Value==1)&&(Left_Value==1)) {
  stopRobot();
  delay(1000);
  goBack();
  delay(1000);
  stopRobot();
  delay(5000);
  
}else if(distance > 1 && distance < 15) {
  stopRobot();
  }
  distance = sonar.ping_cm();
  if(distance>0 && distance<10){
    goBack();
    delay(1000);
    stopRobot();
  }
}   
else if (command=='F'||command=='B'||command=='L'||command=='R'||command=='I'||command=='G'||command=='J'||command=='H'||command=='S'||command=='W'||command=='w') {
  /*command = Serial.read();*/
  
if (lightFront) {digitalWrite(light, HIGH);}
if (!lightFront) {digitalWrite(light, LOW);}


switch (command) {
case 'F':goAhead();break;
case 'B':goBack();break;
case 'L':goLeft();break;
case 'R':goRight();break;
case 'I':goAheadRight();break;
case 'G':goAheadLeft();break;
case 'J':goBackRight();break;
case 'H':goBackLeft();break;

case 'S':stopRobot();break;
case 'W':lightFront = true;break;
case 'w':lightFront = false;break;


}
}
else{stopRobot();}
}
}
int sweep()
{
    static int currentAngle = startAngle;
    static int motorRotateAmount = degreesPerCycle;
    while(1)
    {
    
    unsigned int dist = sonar.ping_cm();

    // move servo
    myservo.write(currentAngle);
    delay(10);
    // calculate the distance from the sensor, and write the value with location to serial
    SerialOutput(currentAngle,dist);
    
    
    // update motor location
    currentAngle += motorRotateAmount;

    // if the motor has reached the limits, change direction
    if(currentAngle <= minimumAngle || currentAngle >= maximumAngle) 
    {
        motorRotateAmount = -motorRotateAmount;
    }
    if(dist>0 && dist<=150){
    break;
    }
    }
    return currentAngle;
    currentAngle=0;
}
void SerialOutput(const int angle, const int distance)
{
    // convert the angle and distance to a string and serial print
    Serial.println(String(angle) + "," + String(distance));
}
