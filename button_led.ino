Zadatak 3
Button - led


unsigned int val ;
//PRIMJER
void react(){
  Serial.println("Im not pressed");
  
  }
  
void setup() {
  interrupts();
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(2), react, LOW);

 

}

void loop() {

 
}




//PRIMJER

unsigned int val ;

void react(){
  //Serial.println("Im not pressed");
  
  }
  
void setup() {
  interrupts();
  pinMode(2, INPUT);
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(2), react, LOW);

 

}

void loop() {
  Serial.print("Pin Voltage :");
  Serial.println( digitalRead(2 ) ? "High" : "Low");
 
}





unsigned int val = 0;

void react(){
  //Serial.println("Im not pressed");
  val = (val+32)%255;
  }
  
void setup() {
  interrupts();
  pinMode(2, INPUT);
  pinMode(9 , OUTPUT);
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(2), react, FALLING);

 

}

void loop() {
  
 analogWrite(9, val);
}
