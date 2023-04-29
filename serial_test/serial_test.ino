char command=NULL;

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:

}

void loop() {
  if(Serial.available()>=0){
    command=Serial.read();
    Serial.println(command);
    delay(100);
    }
  // put your main code here, to run repeatedly:

}
