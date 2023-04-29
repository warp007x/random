#define RED_LED 6
#define BLUE_LED 5
#define GREEN_LED 9

int brightness = 255;
int gBright = 55;
int rBright = 55;
int bBright = 55;
int fadeSpeed = 10;


void setup() {

   Serial.begin(115200);
   pinMode(GREEN_LED, OUTPUT);
   pinMode(RED_LED, OUTPUT);
   pinMode(BLUE_LED, OUTPUT);
  
}


void TurnOn() { 
   for (int i = 55; i < 256; i++) {
       analogWrite(RED_LED, rBright);
       rBright +=1;
       delay(fadeSpeed);
       Serial.println("R=");
       Serial.print(rBright);
       Serial.println();
   }
 
   for (int i = 55; i < 256; i++) {
       analogWrite(BLUE_LED, bBright);
       bBright += 1;
       delay(fadeSpeed);
       Serial.println("B=");
       Serial.print(bBright);
       Serial.println();
   } 
   for (int i = 55; i < 256; i++) {
       analogWrite(GREEN_LED, gBright);
       gBright +=1;
       delay(fadeSpeed);
       Serial.println("G=");
       Serial.print(gBright);
       Serial.println();
   } 
}

void TurnOff() {
   for (int i = 55; i < 256; i++) {
       analogWrite(GREEN_LED, brightness);
       analogWrite(RED_LED, brightness);
       analogWrite(BLUE_LED, brightness);
 
       brightness -= 1;
       delay(fadeSpeed);
   }
}
void loop() {
  TurnOn();
  delay(5000);
  TurnOff();
  
}
