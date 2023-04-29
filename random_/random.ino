

#define CH1 3
#define CH2 5
#define CH3 6
#define CH4 9
#define CH5 10
#define CH6 11
 

 
// Channel Values
 
int rcCH1 = 0; // Left - Right
int rcCH2 = 0; // Forward - Reverse
int rcCH3 = 0; // Acceleration
int rcCH4 = 0; // 
int rcCH5 = 0; // knob/sweep
//bool rcCH6 = 0; // Mode Control

char state = NULL;
// LED Connection
#define carLED 13
 
// Motor A Control Connections
#define pwmA 3
#define in1A 5
#define in2A 4
 
// Motor B Control Connections
#define pwmB 9
#define in1B 7
#define in2B 8
 
// TB6612FNG Standby Pin
#define stby 6
 
// Motor Speed Values - Start at zero
int MotorSpeedAX = 0;
int MotorSpeedBX = 0;
int MotorSpeedAY = 0;
int MotorSpeedBY = 0;
 
// Motor Direction Values - 0 = backward, 1 = forward
int MotorDirAX = 1;
int MotorDirBX = 1;
int MotorDirAY = 1;
int MotorDirBY = 1;
 
// Control Motor A
void mControlA(int mspeed, int mdir) {
 
  // Determine direction
  if (mdir == 0) {
    // Motor backward
    digitalWrite(in1A, LOW);
    digitalWrite(in2A, HIGH);
  } else {
    // Motor forward
    digitalWrite(in1A, HIGH);
    digitalWrite(in2A, LOW);
  }
 
  // Control motor
  analogWrite(pwmA, mspeed);
 
}
 
// Control Motor B
void mControlB(int mspeed, int mdir) {
 
  // Determine direction
  if (mdir == 0) {
    // Motor backward
    digitalWrite(in1B, LOW);
    digitalWrite(in2B, HIGH);
  } else {
    // Motor forward
    digitalWrite(in1B, HIGH);
    digitalWrite(in2B, LOW);
  }
 
  // Control motor
  analogWrite(pwmB, mspeed);
 
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
 
void setup()
 
{
 
  // Start serial monitor for debugging
  Serial.begin(115200);
 
  // Attach iBus object to serial port

  // Set all pins as inputs
  pinMode(CH1, INPUT);
  pinMode(CH2, INPUT);
  pinMode(CH3, INPUT);
  pinMode(CH4, INPUT);
  pinMode(CH5, INPUT);
  pinMode(CH6, INPUT);
 
  // Set all the motor control pins to outputs
 
  pinMode(pwmA, OUTPUT);
  pinMode(pwmB, OUTPUT);
  pinMode(in1A, OUTPUT);
  pinMode(in2A, OUTPUT);
  pinMode(in1B, OUTPUT);
  pinMode(in2B, OUTPUT);
  pinMode(stby, OUTPUT);
 
  // Set LED pin as output
  pinMode(carLED, OUTPUT);
 
  // Keep motors on standby for two seconds & flash LED
  digitalWrite(stby, LOW);
  digitalWrite(carLED, HIGH);
  delay (1000);
  digitalWrite(carLED, LOW);
  delay (1000);
  digitalWrite(stby, HIGH);
 
}
 
void loop() {
  
 if(Serial.available>0)
  // Get RC channel values
  rcCH1 = map(readChannel(CH1, -100, 100, 0), -80, 80, -100, 100);
  rcCH2 = map(readChannel(CH2, -100, 100, 0), -70, 70, -100, 100);
  rcCH3 = constrain(map(readChannel(CH3, 0, 155, 0), 20, 130, 0, 155), 0, 255);
  rcCH5 = readChannel(CH5, -100, 100, 0);
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
  MotorSpeedAX = rcCH3;
  MotorSpeedBX = rcCH3;
  MotorSpeedAY = rcCH3;
  MotorSpeedBY = rcCH3;
 
  // Set Mode with channel 6 value
//  if (rcCH6) {
//    // Spin Mode
// 
//    // Turn on LED
//    digitalWrite(carLED, HIGH);
// 
//    // Get Direction from channel 5 value
//    if (rcCH5 >= 0) {
//      //Clockwise
//      MotorDirA = 0;
//      MotorDirB = 1;
//      Serial.println("Clockwise");
//    } else {
//      //Counter-Clockwise
//      MotorDirA = 1;
//      MotorDirB = 0;
//      Serial.println("Counter-Clockwise");
//    }
// 
//    // Add Motorspeed to channel 5 value
//    MotorSpeedA = MotorSpeedA + abs(rcCH5);
//    MotorSpeedB = MotorSpeedB + abs(rcCH5);
// 
//  }  {
    // Normal Mode
 
    // Turn off LED
    digitalWrite(carLED, LOW);
 
    // Set forward/backward direction with channel 2 value
    if (rcCH2 >= 0) {
      //Forward
      MotorDirA = 1;
      MotorDirB = 1;
      Serial.println("Forward");
    } else {
      //Backward
      MotorDirA = 0;
      MotorDirB = 0;
      Serial.println("Backward");
    }
 
    // Add channel 2 speed
    MotorSpeedA = MotorSpeedA + abs(rcCH2);
    MotorSpeedB = MotorSpeedB + abs(rcCH2);
 
    // Set left/right offset with channel 1 value
    MotorSpeedA = MotorSpeedA - rcCH1;
    MotorSpeedB = MotorSpeedB + rcCH1;
 
  }
 
  // Ensure that speeds are between 0 and 255
  MotorSpeedA = constrain(MotorSpeedA, 0, 255);
  MotorSpeedB = constrain(MotorSpeedB, 0, 255);
 
  //Drive Motors
  mControlA(MotorSpeedA, MotorDirA);
  mControlB(MotorSpeedB, MotorDirB);
 
  // Print speed values to serial monitor for debugging
  Serial.print("Motor A Speed = ");
  Serial.print(MotorSpeedA);
  Serial.print(" | Motor B Speed = ");
  Serial.println(MotorSpeedB);
 
  // Slight delay
  delay(50);
 
}
