#include <TimerOne.h>
const int pingPin = 7;
const float encodingMatrix[4][8] =
  {
    {1,1,1,0,0,0,0,0},
    {0,0,0,1,1,0,0,0},
    {1,1,0,1,0,1,0,0},
    {0,1,0,1,0,1,1,0}
  }
float decodingMatrix[8][4];
Matrix.Transpose((float *)encodingMatrix,4,8,(float *)decodingMatrix);

void setup() {
  
  Serial.begin(9600);
    Timer1.initialize(125000);         // initialize timer1, and set a 1/2 second period
  Timer1.attachInterrupt(recAndStore);
}
const int len=8;
int bytestring[len];
float finalstring[len];

int i = 0;
bool flip = false;
void loop()
{
  if(i==len-1){
    flip=true;
  }
  if(i==0 && flip){
    Matrix.Multiply((float *)bytestring, (float *) decodingMatrix,1,4,8,(float *)finalstring);
    for(int i=0;i<8;i++){
      Serial.print(finalstring[i]);
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

