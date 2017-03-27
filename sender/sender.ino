#include <TimerOne.h>

const int pingPin = 7;
int index =0;
void setup() {
  Serial.begin(9600);
    Timer1.initialize(500000);         // initialize timer1, and set a 1/2 second period
  Timer1.attachInterrupt(increment);
  dataToHamming();
  
}
const int len=16;
int datastring[11] = {1,0,1,1,0,1,1,0,0,0,0};
int hammingstring[16] = {0};
void dataToHamming(){
  for(int i=0;i<16;i++){
    hammingstring[i]=0;
  }
  hammingstring[2] = datastring[0];
  hammingstring[4] = datastring[1];
  hammingstring[5] = datastring[2];
  hammingstring[6] = datastring[3];
  hammingstring[8] = datastring[4];
  hammingstring[9] = datastring[5];
  hammingstring[10] = datastring[6];
  hammingstring[11] = datastring[7];
  hammingstring[12] = datastring[8];
  hammingstring[13] = datastring[9];
  hammingstring[14] = datastring[10];
  for(int parityindex=0;parityindex<4;parityindex++){
    for(int index=parityindex; index<=14; index+=pow(2,parityindex+1)){
      for(int consecutive=0;consecutive<pow(2,parityindex);consecutive++){
        hammingstring[(int)(pow(2,parityindex)-1)]=(hammingstring[(int)(pow(2,parityindex)-1)]+hammingstring[consecutive])%2;
      }
    }
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

