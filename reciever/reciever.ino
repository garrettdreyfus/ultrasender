#include <elapsedMillis.h>

elapsedMillis timeElapsed;
const int pingPin = 7;

void setup() {
  // initialize serial communication:
  Serial.begin(9600);
}
const int len=8;
int bytestring[len];
unsigned int interval = 250;
void loop()
{
  int counter = 0;
  int total = 0;
  long duration, inches, cm;
  for(int i=0;i<len;i++){
    timeElapsed=0;
    while(timeElapsed < interval){
    }
    bytestring[i] = rec();
    Serial.print(bytestring[i]);
    
  }
  Serial.print("\n");
  
}

long microsecondsToInches(long microseconds)
{
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds)
{
   return microseconds / 29 / 2;
}

bool rec(){
      pinMode(pingPin, OUTPUT);
    digitalWrite(pingPin, LOW);
    delayMicroseconds(2);
    digitalWrite(pingPin, HIGH);
    delayMicroseconds(5);
    digitalWrite(pingPin, LOW);
    int duration;
    pinMode(pingPin, INPUT);
    duration = pulseIn(pingPin, HIGH);
  
    if(microsecondsToCentimeters(duration) <330 ){
      return true;
    }
    else {
      return false;
    }
}

