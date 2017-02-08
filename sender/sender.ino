#include <TimerOne.h>

const int pingPin = 7;
int index =0;
void setup() {
  Serial.begin(9600);
    Timer1.initialize(500000);         // initialize timer1, and set a 1/2 second period
  Timer1.attachInterrupt(increment);
  
  
}
const int len=8;
int bytestring[len] = {1,0,1,1,0,1,1,0};
void loop()
{
  if(bytestring[index] == 1){
    long duration, inches, cm;
  
    
    
    pinMode(pingPin, OUTPUT);
    digitalWrite(pingPin, LOW);
    delayMicroseconds(2);
    digitalWrite(pingPin, HIGH);
    delayMicroseconds(5);
    digitalWrite(pingPin, LOW);
    
  }
  
}

void increment(){
  index = (index +1)%len;

}

