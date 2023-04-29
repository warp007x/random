#include "DHT.h"
#define DHT11PIN 23
//#define led 23

DHT dht(DHT11PIN, DHT11);
void setup()
{
  
  Serial.begin(115200);
/* Start the DHT11 Sensor */
  dht.begin();
}

void loop()
{
  float humi = dht.readHumidity();
  float temp = dht.readTemperature();
  Serial.print("Temperature: ");
  Serial.print(temp);
  Serial.print("ºC ");
  Serial.print("Humidity: ");
  Serial.println(humi);
  //digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                      // wait for a second
 // digitalWrite(led, LOW);   // turn the LED on (HIGH is the voltage level)   
  
}
