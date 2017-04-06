#include <TimerOne.h>
#include <MatrixMath.h>

const int pingPin = 7;
int index =0;

const int len=8;
int datastring[4] = {0,0,1,0};
int hammingstring[8] = {0,0,0,0,0,0,0,0};
const int encodingMatrix[4][8] =
  {
    {1,1,1,0,0,0,0,0},
    {1,0,0,1,1,0,0,0},
    {0,1,0,1,0,1,0,0},
    {1,1,0,1,0,0,1,0}
  };

void dataToHamming(){
  Matrix.Multiply((int *)datastring, (int *) encodingMatrix,1,4,8,(int *) hammingstring);
  for(int i=0;i<len;i++){
    hammingstring[i]=hammingstring[i]%2;
  }
}
void setup() {
  Serial.begin(9600);
    Timer1.initialize(250000);         // initialize timer1, and set a 1/2 second period
  Timer1.attachInterrupt(increment);
  dataToHamming();
  for(int i=0;i<len;i++){
            Matrix.Print((int*)hammingstring,len,1,"v");
  }
  
  
}

boolean transmitting = false;
void loop()
{
  if(transmitting){
    if(hammingstring[index] == 1){
      long duration, inches, cm;
      pinMode(pingPin, OUTPUT);
      digitalWrite(pingPin, LOW);
      delayMicroseconds(2);
      digitalWrite(pingPin, HIGH);
      delayMicroseconds(5);
      digitalWrite(pingPin, LOW);
    
    }
  }
  else{
    transmitByte();
  }
  
}

void transmitByte(){
  transmitting = true;
}


void increment(){
  if (index !=len-1 && transmitting){
    index = (index +1)%len;
  }
  else{
    index = (index +1)%len;
    transmitting = false;
  }

}

