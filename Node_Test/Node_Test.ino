int Command=NULL;

void setup() {
  
  Serial.begin(115200);
  Serial.println("Initialiazed");

}

void loop() {
  if(Serial.available()!=NULL){
    
        Command=Serial.read();
        delay(50);
        
        Serial.println(char(Command));
    }
}
