#include <assert.h>
#include <TString.h> 

class TH1;

#include "LinReg_Bevington_Pebay.h"
#include "Toy6DEvent.h"

class Jb6DRegress {

 private:
  double par_Pavr[mxP]; // Mean offsets of beam position for regression
 
  // correlations
  double par_Alpha[mxP]; // Ycorr=Ymeas-alpha_k*(P_k- avrP_k) for regression
  TString mCore;
  
  // sum of yield
  double mYmeas[mxHeli],mYcorr[mxHeli];
  double mSumP[mxP][mxHeli]; // for average beam position versus helicity 
  double mEve[mxHeli];

  // histograms
  enum {mxHA=128}; TH1 * hA[mxHA];
  void initHistos();
  void  printAsy(double *mY, const char * txt);
  LinRegBevPeb linReg;


 public:
  Jb6DRegress(const char *core); 
  void setMeanP( double A[]) { for(int i=0;i<mxP;i++)   par_Pavr[i]=A[i]; }
  void setAlphas( double *A) { for(int i=0;i<mxP;i++)   par_Alpha[i]=A[i]; }
  void print();
  void init();
  void finish();
  void addEvent(EVENTN *eve);
  

};

