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
const int encodingMatrix[4][8] =
  {
    {1,1,1,0,0,0,0,0},
    {1,0,0,1,1,0,0,0},
    {0,1,0,1,0,1,0,0},
    {1,1,0,1,0,0,1,0}
  };
const int len=8;
int bytestring[len];
int finalstring[4];
int checkstring[3];
int datastring[4] = {0,0,1,0};
int hammingstring[8] = {0,0,0,0,0,0,0,0};
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

//Lsiten for opening ping
// Ping back
//4 Bits
//11 ack
//10 transmit
//openingbit
