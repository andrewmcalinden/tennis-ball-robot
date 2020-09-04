#include "TinyMySqlInterface.hh"

void wrTiny(int runId=95){
  printf("write one runId=%d to DB using TinyMySqlInterface\n",runId);
  mySqlOnlM3=new TinyMySqlInterface("m3slow.lns.mit.edu", "onlM3", "balewski", "jan");

  mySqlOnlM3->command(Form("insert into janTable  (runId,operator) VALUES  (%d,'utime-%d') ",runId,time(0)));
  

  printf("end JanDAQ \n");
  exit(1);
 
  
}
