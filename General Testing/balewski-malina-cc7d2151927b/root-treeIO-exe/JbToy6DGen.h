/*********************************************************************
 * $Id: $
 * \author Jan Balewski, MIT, 2010
 *********************************************************************
 * Descripion:
 * Generator of   synthetic QW event
 *********************************************************************/

#include <assert.h>
class TRandom3 ;
class TH1;
class TTree;
#include "Toy6DEvent.h"

class JbToy6DGen {

 private:
  double par_P[mxP][mxHeli]; // Mean offsets of beam position for generator
  double par_Pavr[mxP]; // Mean offsets of beam position
  double par_sig1[mXY],par_sig2[mXY], par_phi[mXY]; // beam spread and correlation angle in 1 dim
  double par_sigE,par_sigQ; // beam energy and charge spread;
  double par_sigBpm[mxP]; // spread of BPM signals

  // correlations
  double par_Alpha[mxP]; // Ymeas=Ytrue+alpha_k*(P_k- avrP_k) for generator

  TRandom3 *rnd;
  double  mCosA[mXY],mSinA[mXY];
  TTree*  mTree;

  // sum of yield
  double mYield[mxHeli+1];

  // histograms
  enum {mxHA=32}; TH1 * hA[mxHA];
  void initHistos();

 public:
  JbToy6DGen(); 

  void setMeanP( double A[],int heli) {   assert(heli==kheliP || heli==kheliN);
    for(int i=0;i<mxP;i++)   par_P[i][heli]=A[i]; }

  void setAlphasGen( double *A) { for(int i=0;i<mxP;i++)   par_Alpha[i]=A[i]; }
  void setBpmSpread( double *A) { for(int i=0;i<mxP;i++)   par_sigBpm[i]=A[i]; }
 
  void setBeamSpread( double a,  double b,  double c, int idir ){
    par_sig1[idir]=a; par_sig2[idir]=b; par_phi[idir]=c;}
  void setBeamSpreadEQ( double a,  double b ){
    par_sigE=a; par_sigQ=b;}

  void print();
  void init();
  void finish();
  void throwEvent(int ieve);
  
};

