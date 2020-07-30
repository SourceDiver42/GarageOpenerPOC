
int RELAY_PIN = 4;

void setup(){

  pinMode(RELAY_PIN, OUTPUT);
  Serial.begin(9600);
  while (!Serial){
    delay(1000);
  }
  
}

void loop(){
  
  int incoming = Serial.read();
  if (incoming == "trigger")
    digitalWrite(RELAY_PIN, HIGH); //or LOW, depending on the relay you use
    delay(50);
    digitalWrite(RELAY_PIN, LOW); //or HIGH, depending on the relay you use
  
}
