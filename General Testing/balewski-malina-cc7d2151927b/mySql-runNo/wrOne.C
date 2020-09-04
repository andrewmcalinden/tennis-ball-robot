void wrOne(int runId=77){
  printf("write one runId=%d to DB using gSyste->Exec()\n",runId);
  // gSystem->Exec("ls ");
  TString cmd="ls";

  cmd="echo ----; echo myCMD-start;";
  cmd+="MYSQL=\"mysql -h m3slow.lns.mit.edu  -ubalewski -pjan -D onlM3\" ;";

  //cmd+="$MYSQL  -BNe \" show databases;\";" ; 
  //cmd+="$MYSQL  -BNe \" show tables;\";" ; 
  
  cmd+=Form("$MYSQL  -BNe \" insert into  janTable  (runId,operator) VALUES  (%d,'jan-C') ;\"; ",runId) ;
  cmd+="$MYSQL  -BNe \" select * from janTable;\"; " ;
  
  cmd+="echo $MYSQL; echo myCMD-end;";
  gSystem->Exec(cmd);
  
  //printf("end11\n%s",cmd.Data());
  
}
