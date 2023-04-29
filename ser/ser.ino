char state=NULL;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

}

void loop() {
  if(Serial.available()!=NULL){
  state = Serial.read();
  Serial.println(state);
  // put your main code here, to run repeatedly:
  }

}
