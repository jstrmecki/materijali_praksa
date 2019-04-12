bool Bstatus = 0;
int Button = 2; // button
int potPin =  A5; // potenciometar
int value;
int potencio;

void setup() {
  // port za button
  pinMode(Button, INPUT); 
  
  // portovi za ledice
  for(int pinLed= 4; pinLed <= 9; pinLed++){  // ledice
    pinMode(pinLed, OUTPUT);
    }

}

void setRulet(){
  for (int pinLed=4; i <=9 ; pinLed++){
    if(digitalRead(Button) == HIGH) //provjeravamo tipkalo
      break;
    digitalWrite(pinLed, HIGH);
    delay(300);
    digitalWrite(pinLed, LOW);
  }
}
int pom = 0;

void loop() {
  // put your main code here, to run repeatedly:
  while(digitalRead(Button) == HIGH)
    Bstatus = 1;
   if(Bstatus){
    potencio = analogRead(potPin);
    if(potencio == 0){
      value = 5000;
      }
    else{
      value = 5000 + 
      }
    }
}
