#ifndef TinyMySqlInterface_hh
#define  TinyMySqlInterface_hh

class TinyMySqlInterface{ 
 public:
  TinyMySqlInterface(const char *server, const char *db, const char *user, const char *pass) {
    mySql=Form("mysql  -h %s -u %s -p%s -D %s ",server,user,pass,db);
    enabled=true;
    //    printf(" TinyMySqlInterface:: cnstr mySql=%s=\n",mySql.Data());
    printf(" TinyMySqlInterface:: cnstr mySql -h %s -D %s\n",server ,db);
  }
  
  void disable(){enabled=false;}
  void command(const char *cmd) {
    if(!enabled) {
          printf("  TinyMySqlInterface:: IGNORED cmd=%s=\n",cmd);
	  return;
    }
    
    printf("  TinyMySqlInterface:: executed cmd=%s=\n",cmd);
    TString fullCmd=mySql+" -BNe \" "+cmd+"  ;\" " ;
    //printf("  TinyMySqlInterface::cmd=%s=\n",fullCmd.Data());
    gSystem->Exec(fullCmd);
  }
  TString mySql;
  int enabled;

};

#endif
