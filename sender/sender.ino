#include <elapsedMillis.h>

elapsedMillis timeElapsed;
const int pingPin = 7;
int index =0;
void setup() {
  
  Serial.begin(9600);
  
}
unsigned int interval = 250;
const int len=8;
int bytestring[len] = {1,0,1,1,0,1,1,0};
void loop()
{
  timeElapsed=0;
  while(timeElapsed < interval){
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
  
  index = (index +1)%len;
}


