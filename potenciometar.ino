Potenciometar
Lijevo ide minus, desno plus i sredina analogni input


unsigned int value ;

void setup() {
  
  value = 0;
  pinMode(A1 , INPUT);
  Serial.begin(9600);
 
 

}

void loop() {
value = analogRead(A1);
Serial.println(value);
delay(100);
 
}
