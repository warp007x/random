#include <SparkFun_TB6612.h>
 
#define XAIN1 22
#define XBIN1 24
#define XAIN2 26
#define XBIN2 28
#define XPWMA 5
#define XPWMB 6
#define XSTBY 7

# define buzz 13

#define YAIN1 30
#define YBIN1 32
#define YAIN2 34
#define YBIN2 36
#define YPWMA 2
#define YPWMB 3
#define YSTBY 4

#define ir1 A0
#define ir2 A1
#define ir3 A2
#define ir4 A3
#define ir5 A4

#define light1  10       //LED Front
#define light2  11  

const int xoffsetA = 1;
const int xoffsetB = 1;

const int yoffsetA = 1;
const int yoffsetB = 1;

char command=NULL;            //Int to store app command state.
int speedCar = 255;     // 50 - 255.
int speed_Coeff = 2;
boolean lightFront = false;


Motor xmotor1 = Motor(XAIN1, XAIN2, XPWMA, xoffsetA, XSTBY);
Motor xmotor2 = Motor(XBIN1, XBIN2, XPWMB, xoffsetB, XSTBY);

Motor ymotor1 = Motor(YAIN1, YAIN2, YPWMA, yoffsetA, YSTBY);
Motor ymotor2 = Motor(YBIN1, YBIN2, YPWMB, yoffsetB, YSTBY);

void lightEffects();
void buzzer(int);

void setup(){
      
      Serial.begin(115200);
      pinMode(ir1, INPUT);
      pinMode(ir2, INPUT);
      pinMode(ir3, INPUT);
      pinMode(ir4, INPUT);
      pinMode(ir5, INPUT); 
      Serial.println("A=Auto mode, F=Forward, B=Backward, L=Left, R=Right, I=Forward-Right, G=Forward-Left, J=Backward-Right, H=Backward-Left, S=Stop Robot, W=Light On, w=Light Off, D=Light Effects, Z=Buzzer");
}

void goAheadFS(){ 
  
      Serial.println("Going Ahead FULL SPEED.......");
      forward(xmotor1, xmotor2, 255);
      forward(ymotor1, ymotor2, 255);
   
      delay(20);
  }

void goBackFS(){
   
      Serial.println("Going Back FULL SPEED.......");
      back(xmotor1, xmotor2, -255);
      back(ymotor1, ymotor2, -255);
      
      delay(20);
  }

void goLeftFS(){
  
      Serial.println("Going Left FULL SPEED.......");
      back(xmotor1, xmotor2, -255);
      forward(ymotor1, ymotor2, 255);
      
      delay(20); 
  }

  void goRightFS(){ 
  
      Serial.println("Going Right FULL SPEED.......");
      forward(xmotor1, xmotor2, 255);
      back(ymotor1, ymotor2, -255);
      
      delay(20);
  }

void goAheadLS(){

      Serial.println("Going Ahead LOW SPEED.......");
      forward(xmotor1, xmotor2, (speedCar/speed_Coeff));
      forward(ymotor1, ymotor2, (speedCar/speed_Coeff));

      delay(20);
  }

void goBackLS(){

      Serial.println("Going Back LOW SPEED.......");
      back(xmotor1, xmotor2, -(speedCar/speed_Coeff));
      back(ymotor1, ymotor2, -(speedCar/speed_Coeff));
      
      delay(20);
  }

void goRightLS(){ 
  
      Serial.println("Going Right LOW SPEED.......");
      forward(xmotor1, xmotor2, (speedCar/speed_Coeff));
      back(ymotor1, ymotor2, -(speedCar/speed_Coeff));
      
      delay(20);
  }

void goLeftLS(){ 
  
      Serial.println("Going Left LOW SPEED.......");
      back(xmotor1, xmotor2, -(speedCar/speed_Coeff));
      forward(ymotor1, ymotor2, (speedCar/speed_Coeff));
      delay(20);
  }

void stopRobot(){  

      Serial.println("Robot Standby.......");
      brake(xmotor1, xmotor2);
      brake(ymotor1, ymotor2);
      delay(20);
  
  }

void loop()
{

if(Serial.available()!=NULL)
{
  command = Serial.read();
  if(command == 'A' )
        {
          while(Serial.read()!='S')
              {
                //int k= Serial.read();
                //if (k=='S') break; 
                //Reading Sesor Values
                Serial.println("Auto LINE FOLLOWER Mode");
                int s1 = digitalRead(ir1);  //Left Most Sensor
                int s2 = digitalRead(ir2);  //Left Sensor
                int s3 = digitalRead(ir3);  //Middle Sensor
                int s4 = digitalRead(ir4);  //Right Sensor
                int s5 = digitalRead(ir5);  //Right Most Sensor

                //if only middle sensor detects black line
                if((s1 == 1) && (s2 == 1) && (s3 == 0) && (s4 == 1) && (s5 == 1))
                     {

                      goAheadLS();
                      //going forward with full speed 
   
                     }
  
                //if only left sensor detects black line
                if((s1 == 1) && (s2 == 0) && (s3 == 1) && (s4 == 1) && (s5 == 1))
                     {

                        goBackLS();
                       //going right with full speed 
    
                     }
  
                //if only left most sensor detects black line
                if((s1 == 0) && (s2 == 1) && (s3 == 1) && (s4 == 1) && (s5 == 1))
                     {
                       goRightLS();
                       //going right with full speed 
    
                     }

                 //if only right sensor detects black line
                 if((s1 == 1) && (s2 == 1) && (s3 == 1) && (s4 == 0) && (s5 == 1))
                     {

                       goLeftLS();
                       //going left with full speed 

                     }

                 //if only right most sensor detects black line
                 if((s1 == 1) && (s2 == 1) && (s3 == 1) && (s4 == 1) && (s5 == 0))
                     {
                       
                       goRightLS();
                       //going left with full speed 
    
                     }

                 //if middle and right sensor detects black line
                 if((s1 == 1) && (s2 == 1) && (s3 == 0) && (s4 == 0) && (s5 == 1))
                     {
                       
                       goLeftLS();
                       //going left with full speed 
    
                     }

                 //if middle and left sensor detects black line
                 if((s1 == 1) && (s2 == 0) && (s3 == 0) && (s4 == 1) && (s5 == 1))
                     {
                       
                       goRightLS();
                       //going right with full speed 
    
                     }

                //if middle, left and left most sensor detects black line
                if((s1 == 0) && (s2 == 0) && (s3 == 0) && (s4 == 1) && (s5 == 1))
                     {
                       
                       goRightLS();
                       //going right with full speed 
    
                     }

                //if middle, right and right most sensor detects black line
                if((s1 == 1) && (s2 == 1) && (s3 == 0) && (s4 == 0) && (s5 == 0))
                     {
                       
                       goRightLS();
                       //going left with full speed 
    
                     }

                   /*if(((s1 == 1) && (s2 == 1) && (s3 == 1) && (s4 == 1)) || ((s2 == 1) && (s3 == 1) && (s4 == 1)&&(s5 == 1))){
                        lightEffects();
                        //goAheadLS();
                    }*/

                //if all sensors are on a black line
                if((s1 == 0) && (s2 == 0) && (s3 == 0) && (s4 == 0) && (s5 == 0))
                     {
                       
                        stopRobot();
                        //stop
    
                     }
     
                delay(50);

              }
        }
           
  else if (command=='F'||command=='B'||command=='L'||command=='R'||command=='I'||command=='G'||command=='J'||command=='H'||command=='S'||command=='W'||command=='w'||command=='D') {
  /*command = Serial.read();*/
  
    if (lightFront) {digitalWrite(light1, HIGH);}
    if (lightFront) {digitalWrite(light2, HIGH);}
    if (!lightFront) {digitalWrite(light1, LOW);}
    if (!lightFront) {digitalWrite(light2, LOW);}


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
        case 'W':lightFront = true;break;
        case 'w':lightFront = false;break;
        case 'D':lightEffects(); break;
        case 'Z': buzzer(1); break;
        default: Serial.println("Invalid Input c(><c)");


            }
            
     }
//else{Serial.println("Invalid Input c(><c)");}
}
}

void lightEffects(){

     while(Serial.read() != 'S'){
        digitalWrite(light1, HIGH);
        delay(200);
        digitalWrite(light2, HIGH);
        delay(300);
        digitalWrite(light1, LOW);
        delay(200);
        digitalWrite(light2, LOW);
        delay(300);
     }
     }
void buzzer(int duration){

    int dx=duration;
    while(dx!=0){
        digitalWrite(buzz, HIGH);
        delay(1000);
        dx--;
    }


}
    
    
