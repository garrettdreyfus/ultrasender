#include <TimerOne.h>
#include <MatrixMath.h>
const int pingPin = 7;
const int decodingMatrix[8][4] =
  {
    {0,0,0,0},
    {0,0,0,0},
    {1,0,0,0},
    {0,0,0,0},
    {0,1,0,0},
    {0,0,1,0},
    {0,0,0,1},
    {0,0,0,0}
  };
const int checkMatrix[8][3] =
  {
    {1,0,0},
    {0,1,0},
    {1,1,0},
    {0,0,1},
    {1,0,1},
    {0,1,1},
    {0,1,1},
    {0,0,0},
  };
void setup() {
  
  Serial.begin(9600);
    Timer1.initialize(250000);         // initialize timer1, and set a 1/2 second period
  Timer1.attachInterrupt(recAndStore);
}
const int len=8;
int bytestring[len];
int finalstring[4];
int checkstring[3];

int i = 0;
bool flip = false;
void hammingCorrect(){
    Matrix.Multiply((int *)bytestring, (int *) checkMatrix,1,8,3,(int *)checkstring);
    int errorindex=0;
    for(int i=0;i<3;i++){
      if(checkstring[i] == 1){
        errorindex += pow(2,i);
      }
    }
    bytestring[errorindex] = (bytestring[errorindex]+1)%2;
}
void loop()
{
  if(i==len-1){
    flip=true;
  }
  if(i==0 && flip){
    hammingCorrect();
    Matrix.Multiply((int *)bytestring, (int *) decodingMatrix,1,8,4,(int *)finalstring);
    for(int i=0;i<4;i++){
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
  if(counter ==1){
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

