#include <TimerOne.h>
const int pingPin = 7;
void setup() {
  
  Serial.begin(9600);
    Timer1.initialize(125000);         // initialize timer1, and set a 1/2 second period
  Timer1.attachInterrupt(recAndStore);
}
const int len=16;
int bytestring[len];

int i = 0;
bool flip = false;
void loop()
{
  if(i==len-1){
    flip=true;
  }
  if(i==0 && flip){
    for(int j=0;j<len;j++){
      Serial.print(bytestring[j]);
    }
    Serial.print("\n");
    flip = false;
  }
}

long microsecondsToInches(long microseconds)
{
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds)
{
   return microseconds / 29 / 2;
}
int counter = 0;
int sum =0;
void recAndStore(){
  sum += rec();
  if(counter ==4){
    if(sum>0){
      bytestring[i] = true;
    }
    else{
      bytestring[i] = false;
    }
    i = (i+1)%len;
    counter=0;
    sum=0;
  }
  counter ++;
}

int rec(){
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
      return 1;
    }
    else {
      return 0;
    }
}

