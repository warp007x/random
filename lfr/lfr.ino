//Motor one
#define ENA 6
#define IN1 7
#define IN2 8

//Motor two
#define IN3 9
#define IN4 10
#define ENB 11

#define Speed 100

void setup() {
  //Sensor pins
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  //Motor one
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  //Motor two
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  Serial.begin(9600);

}
void loop() {
  bool SOne = digitalRead(2);
  bool STwo = digitalRead(3);
  bool SThree = digitalRead(4);
  bool SFour = digitalRead(5);

  if (SOne == 0 && STwo == 1 && SThree == 1 && SFour == 0 ) {
    forward();
  } else if (SOne == 1 && STwo == 1 && SThree == 1 && SFour == 1) {
    Stop();
  } else if (SOne == 0 && STwo == 0 && SThree == 0 && SFour == 0) {
    Stop();
  }  else if (SOne == 1 && STwo == 1 && SThree == 0 && SFour == 0) {
    turnleft();
  } else if (SOne == 0 && STwo == 0 && SThree == 1 && SFour == 1) {
    turnright();
  }
}

void forward() {
  analogWrite(ENA, Speed);
  analogWrite(ENB, Speed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  Serial.println("FORWARD");
}
void turnright() {
  analogWrite(ENA, Speed);
  analogWrite(ENB, Speed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  Serial.println("RIGHT");
}
void turnleft() {
  analogWrite(ENA, Speed);
  analogWrite(ENB, Speed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  Serial.println("LEFT");
}
void Stop() {
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  Serial.println("STOPPED");
}    
