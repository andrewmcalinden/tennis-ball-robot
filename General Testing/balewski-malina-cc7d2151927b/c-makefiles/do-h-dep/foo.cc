#include <stdio.h>
#include <vector>
#include <string>
using namespace std;



#include "janHead.h"
#include "kot.h"
int main() {
  printf("M: start\n");
  float yy=func1(3);
  float zz=func2(5);
  printf("M: end1 yy=%f zz=%f\n",yy,zz);
  vector<float> v;
  v.push_back(yy);
  printf("M: end2 v.size=%d\n", (int)v.size());

  vector<string> userString;      
  string word,sentence;
  word="abc";
  userString.push_back(word);
  word="jan23";
  userString.push_back(word);

  unsigned int j;
  for(j=0;j< userString.size(); j++){
    sentence += userString[j] + " ";
    printf("i=%u word=%s\n",j,userString[j].c_str());
  }
  printf(" sentence len=%d val=%s=\n", (int)sentence.length(), sentence.c_str());
  
  return 0;
} 
