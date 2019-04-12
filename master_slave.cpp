#include <iostream>
#include <queue> 
using namespace std;

#define ANSI_COLOR_RED     "\x1b[41m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

unsigned int masterShiftRegisterValue[8] = {1,0,1,1,0,1,0,1};
unsigned int slaveShiftRegisterValue[8] = {0,0,1,1,0,1,1,0};
int i;

void colorMaster(queue<int> myqueue, int j){
  cout << (ANSI_COLOR_RED);
  
  while (j > 0) { 
        cout << (ANSI_COLOR_RED);
        cout <<  myqueue.front();
        cout << (ANSI_COLOR_RESET);
        cout << " ";
        myqueue.pop();
        j--;
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
    //while(not masterqueue.empty()){
	//	cout<<masterqueue.front()<<" ";
	//	masterqueue.pop();
	//}
    colorMaster(slavequeue, 3);
    //cout << slavequeue.front();
    //cout << ("\t");
    //cout << (ANSI_COLOR_RED "6" ANSI_COLOR_RESET);
    return 0;
}
