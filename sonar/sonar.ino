// defines pins numbers
#define trigPin A0
#define echoPin A1
#define LED1 2
#define LED2 3
// defines variables
long duration;
int distance;
void setup() {
pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT); // Sets the echoPin as an Input
Serial.begin(9600); // Starts the serial communication
}
void loop() {
// Clears the trigPin
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);
// Calculating the distance
distance= duration*0.034/2;
// Prints the distance on the Serial Monitor
Serial.print("Distance: ");
Serial.println(distance);
if (distance>=50){
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  }
else if (distance >=15 && distance <=25){
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, HIGH);
  }
else if (distance < 15){
  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, HIGH);
  }
  

}
