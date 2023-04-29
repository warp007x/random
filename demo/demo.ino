/*
  RC Remote Car
  fsi6x-RC-car-spin.ino
  Uses Flysky FS-I6X RC receiver & FS-I6X 6-ch Controller
  Uses TB6612FNG H-Bridge Motor Controller
  Drives two DC Motors

  Two Drive Modes - Normal and Spin
  Map channel 6 on controller to switch SWA for mode control

  Right stick controls direction in Normal mode (CH1 & CH2)
  VRA controls speed and direction in Spin mode (CH5)
  Left stick is acceleration in both modes (CH3)

  Channel functions by Ricardo Paiva - https://gist.github.com/werneckpaiva/

  DroneBot Workshop 2021
  https://dronebotworkshop.com
*/

// Include iBus Library
#define CH1 3
#define CH2 5
#define CH3 6
#define CH4 9
#define CH5 10
#define CH6 11

// Create iBus Object

// Channel Values

int rcCH1 = 0; // Left - Right
int rcCH2 = 0; // Forward - Reverse
int rcCH3 = 0; // Acceleration
int rcCH5 = 0; // Spin Control
bool rcCH6 = 0; // Mode Control

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
int MotorSpeedA = 0;
int MotorSpeedB = 0;

// Motor Direction Values - 0 = backward, 1 = forward
int MotorDirA = 1;
int MotorDirB = 1;

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
int readChannel(int channelInput, int minLimit, int maxLimit, int defaultValue){
  int ch = pulseIn(channelInput, HIGH, 30000);
  if (ch < 100) return defaultValue;
  return map(ch, 1000, 2000, minLimit, maxLimit);
}
 
// Read the switch channel and return a boolean value
bool readSwitch(byte channelInput, bool defaultValue){
  int intDefaultValue = (defaultValue)? 100: 0;
  int ch = readChannel(channelInput, 0, 100, intDefaultValue);
  return (ch > 50);
}

void setup()

{

  // Start serial monitor for debugging
  Serial.begin(115200);

  // Attach iBus object to serial port

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

  // Get RC channel values
  rcCH1 = readChannel(CH1, -100, 100, 0);
  rcCH2 = readChannel(CH2, -100, 100, 0);
  rcCH3 = readChannel(CH3, 0, 155, 0);
  rcCH5 = readChannel(CH5, -100, 100, 0);
  rcCH6 = readSwitch(CH6, false);

  // Print values to serial monitor for debugging
  Serial.print("Ch1 = ");
  Serial.print(rcCH1);

  Serial.print(" Ch2 = ");
  Serial.print(rcCH2);

  Serial.print(" Ch3 = ");
  Serial.print(rcCH3);

  Serial.print(" Ch5 = ");
  Serial.print(rcCH5);

  Serial.print(" Ch6 = ");
  Serial.println(rcCH6);

  // Set speeds with channel 3 value
  MotorSpeedA = rcCH3;
  MotorSpeedB = rcCH3;

  // Set Mode with channel 6 value
  if (rcCH6) {
    // Spin Mode

    // Turn on LED
    digitalWrite(carLED, HIGH);

    // Get Direction from channel 5 value
    if (rcCH5 >= 0) {
      //Clockwise
      MotorDirA = 0;
      MotorDirB = 1;
      Serial.println("Clockwise");
    } else {
      //Counter-Clockwise
      MotorDirA = 1;
      MotorDirB = 0;
      Serial.println("Counter-Clockwise");
    }

    // Add Motorspeed to channel 5 value
    MotorSpeedA = MotorSpeedA + abs(rcCH5);
    MotorSpeedB = MotorSpeedB + abs(rcCH5);

  } else {
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
