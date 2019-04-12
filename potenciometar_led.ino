Zadatak 2
//vrtnjom poteciometra mjenja jacinu ledice

unsigned int val ;

void setup() {
  
  val = 0;
  pinMode(A1 , INPUT);
  pinMode(9 , OUTPUT);
  
 
 

}

void loop() {
val = analogRead(A1);
val = map(val, 0, 1023, 0, 255);
analogWrite(9, val);

 
}
