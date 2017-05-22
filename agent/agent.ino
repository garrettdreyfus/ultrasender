#include <TimerOne.h>
#include <MatrixMath.h>
const int pingPin = 7;
const int transmitterPin=6;
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
const int encodingMatrix[4][8] =
  {
    {1,1,1,0,0,0,0,0},
    {1,0,0,1,1,0,0,0},
    {0,1,0,1,0,1,0,0},
    {1,1,0,1,0,0,1,0}
  };
const int len=8;
int index =0;
int bytestring[len];
int finalstring[4];
int checkstring[3];
int datastring[4] = {1,0,1,0};
int hammingstring[8] = {0,0,0,0,0,0,0,0};
unsigned long chirpTime=0;
int state=0;
int i = 0;
#define RESTING  0
#define RECIEVING  1
#define SENDING  1
boolean sendMessage = true;
boolean transmitting = false;
boolean flip=false;

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
void dataToHamming(){
  Matrix.Multiply((int *)datastring, (int *) encodingMatrix,1,4,8,(int *) hammingstring);
  for(int i=0;i<len;i++){
    hammingstring[i]=hammingstring[i]%2;
  }
}
int chirp(){
  chirp(true);
}
int chirp(bool transmit){
    pinMode(transmitterPin,OUTPUT);
    digitalWrite(transmitterPin, transmit);
    pinMode(pingPin, OUTPUT);
    digitalWrite(pingPin, LOW);
    delayMicroseconds(2);
    digitalWrite(pingPin, HIGH);
    delayMicroseconds(5);
    digitalWrite(pingPin, LOW);
}
int rec(){
    pinMode(transmitterPin,OUTPUT);
    digitalWrite(2, LOW);
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

void initializationPhase(){
  randomSeed(analogRead(0));
  chirpTime = random(0, 10000);
  Serial.println(chirpTime);
}
void setup() {
  
  Serial.begin(9600);
  initializationPhase();
  pinMode(2, OUTPUT);
  
  dataToHamming();
}
int reccount =0;
void loop() {

   if((long)(millis()-chirpTime)>0){
      Serial.println("gonna start transmission");
      
      while(((long)(millis()-chirpTime)<500)){
        chirp(true);
      }
      Serial.println("done transmitting");
      Timer1.initialize(250000);         // initialize timer1, and set a 1/2 second period
      Timer1.attachInterrupt(increment);
      transmitting = true;
      while(true){
        //Serial.println(index);
        digitalWrite(2,HIGH);
        if(hammingstring[index] == 1){
          chirp();
        }
        
      }
  }
delay(5);
   if(rec()==1){
    reccount++;
    
   }
   else{
    reccount=0;
   }
   if(reccount >2){

    Serial.println("heard a chirp ready to recieve");

    Timer1.initialize(250000);         // initialize timer1, and set a 1/2 second period
    Timer1.attachInterrupt(recAndStore);
    while(true){
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
  }

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


long microsecondsToInches(long microseconds)
{
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds)
{
   return microseconds / 29 / 2;
}
