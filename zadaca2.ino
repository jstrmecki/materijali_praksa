zadaca_2

1. zadaatk ----

// kod za prvi arduino (onaj koji salje)
byte byteToSend = 0;
int counter = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  if (counter <= 255){
    byteToSend = counter;
    Serial.write(byteToSend);
    counter += 1;
  }
  else if ( 256 <= counter < 512){
    byteToSend = 511 - counter;
    Serial.write(byteToSend);
    counter += 1;
  }
  else {
    counter = 0;
    byteToSend = 0;
  }
  delay(10);
}

// kod za drugi arduino (prima)


int ledPin = 6;  
byte incomingByte;
int val = 0;

void setup()
{
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT); // sets the pin as output
}

void loop()
{
  if (Serial.available() > 0) {
    incomingByte = Serial.read();
    Serial.println(incomingByte);
    analogWrite(ledPin, incomingByte);
  }
}


2. zadatak ----

//radi na unix kompajlerima

#include <iostream>
#include <queue> 
using namespace std;

#define ANSI_COLOR_RED     "\x1b[41m" //red background
#define ANSI_COLOR_BLUE    "\x1b[44m" //blue background
#define ANSI_COLOR_RESET   "\x1b[0m"

unsigned int masterShiftRegisterValue[8] = {0,0,0,0,0,0,0,0};
unsigned int slaveShiftRegisterValue[8] = {1,0,1,1,0,1,0,1};
int i;

void colorMaster(queue<int> myqueue, int j){
  for (int i = 0; i < j; i++) { 
        cout << (ANSI_COLOR_BLUE);
        cout <<  myqueue.front();
        cout << (ANSI_COLOR_RESET);
        cout << " ";
        myqueue.pop();
    }
   for (int i = j; i < 8; i++) { 
        cout << (ANSI_COLOR_RED);
        cout <<  myqueue.front();
        cout << (ANSI_COLOR_RESET);
        cout << " ";
        myqueue.pop();
    }
  
}

void colorSlave(queue<int> myqueue, int j){
  cout << (ANSI_COLOR_RED);
  
  for (int i = 0; i < j; i++) { 
        cout << (ANSI_COLOR_RED);
        cout <<  myqueue.front();
        cout << (ANSI_COLOR_RESET);
        cout << " ";
        myqueue.pop();
    }
   for (int i = j; i < 8; i++) { 
        cout << (ANSI_COLOR_BLUE);
        cout <<  myqueue.front();
        cout << (ANSI_COLOR_RESET);
        cout << " ";
        myqueue.pop();
    }
  
}

int main ()
{
    queue<int> masterqueue;
    queue<int> slavequeue;
    for(i = 0; i < 8; i++){
        masterqueue.push(masterShiftRegisterValue[i]);
        slavequeue.push(slaveShiftRegisterValue[i]);
    }
    for(int j =8; j >= 0; j--){
        int tempSlave = slavequeue.front();
        int tempMaster = masterqueue.front();
        colorMaster(masterqueue, j);
        cout<<"   ";
        colorSlave(slavequeue, j);
        cout << endl;
        masterqueue.pop();
        slavequeue.pop();
        masterqueue.push(tempSlave);
        slavequeue.push(tempMaster);
        
    }
    return 0;
}

3. zadatak ------------------------------

cpp kod za rpi (master)---------

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#include <sys/ioctl.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>

union Float2Char{
  float f;
  unsigned char c[sizeof(float)];
};

int openI2CBus(int& fd){
  if((fd = open("/dev/i2c-1", O_RDWR)) < 0)
  {
    perror("Failed to open I2C bus");
    return -1;
  }
  return 1;
}

void connectToSlave(int& fd, unsigned char slaveAddr){
  if(ioctl(fd, I2C_SLAVE, slaveAddr) < 0){
    perror("Failed to connect to the Arduino :(");
    return;
  }
}

void sendFloat(int& fd, float value){
  Float2Char dataSending;
  dataSending.f = value;
  
  if(write(fd, dataSending.c, sizeof(float)) != sizeof(float)){
    perror("Failed to send data!\n");
    return;
  }
}


void receiveFloat(int& fd, float& value){
  Float2Char dataReceived;
  dataReceived.f = value;
  unsigned char bytes[sizeof(float)];
  if(read(fd, bytes, sizeof(float)) != sizeof(float)){
    perror("Failed to read data!\n");
    return;
  }
  
  for(unsigned int j = 0; j<sizeof(float); ++j)
    dataReceived.c[j] = bytes[j];
  
  value = dataReceived.f;
}

int main()
{
  
    int fd;
  
    openI2CBus(fd);
    connectToSlave(fd, 0x44);
    
    float value = 12.56;
    sendFloat(fd, value);
    
    printf("[MASTER] - float sent: %.2f\n", value);
    
    
    float dataReceived = 0;
    receiveFloat(fd, dataReceived);
    
    printf("[MASTER] - float received: %.2f\n", dataReceived);
    
    close(fd);
  
        

  
  return 1;
}


kod za arduino (slave) -----------

#include<Wire.h>

union Float2Char{
  float f;
  byte c[sizeof(float)];
};

const byte slaveAddr = 0x44;
Float2Char dataSent, dataReceived;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Wire.begin(slaveAddr);
  Wire.onReceive(receiveFloat);
  Wire.onRequest(sendFloat);
  

}

void loop() {}

void parseValues(byte data[]){
  for(int i = 0; i < sizeof(float); ++i)
    dataReceived.c[i] = data[i];
  

}


void receiveFloat(int i){
  //long bytes[sizeof(long)];
  byte bytes[sizeof(float)];
  byte index = 0;
  while(Wire.available())
    bytes[index++] = Wire.read();
  
  parseValues(bytes);
  
  Serial.print("[SLAVE] - float received: ");
  Serial.println(dataReceived.f);
  delay(500);
}

void sendFloat(){
  Float2Char dataSent;
  dataSent.f = dataReceived.f;

  Wire.write(dataSent.c, sizeof(float));
  Serial.print("[SLAVE] - float sent: ");
  Serial.println(dataSent.f);
  delay(500);
}
