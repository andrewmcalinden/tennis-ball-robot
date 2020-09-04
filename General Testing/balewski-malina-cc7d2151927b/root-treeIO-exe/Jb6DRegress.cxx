//#include <cstdio>
#include <iostream>
using namespace std;

#include <TH2.h> 
#include <TProfile.h> 
#include <TList.h>
#include <TLine.h>
#include <TFile.h> 
#include <TTree.h> 

#include <math.h>
#include <TMath.h>

//#include <TObjArray.h> //?

#include "Jb6DRegress.h"
TString Pname2[mxP]={"beam-x","beam-nx","beam-y","beam-ny","beam-E","beam-Q"};


//========================
//========================
Jb6DRegress::Jb6DRegress(const char *core) {
  mCore=core;
  printf("constr of Jb6DRegress=%s\n",mCore.Data());
  memset(mYmeas, 0, sizeof(mYmeas));
  memset(mYcorr, 0, sizeof(mYcorr));
  memset(mSumP, 0, sizeof(mSumP));
  memset(mEve, 0, sizeof(mEve));
 
}

//========================
//========================
void Jb6DRegress::print() {

  printf("input params:\n    beam means \n");
  for(int i=0;i<mxP;i++) printf("%10s : P%d avr=%f   alpha=%.3f\n",Pname2[i].Data(),i,par_Pavr[i], par_Alpha[i]);
}

//________________________________________________
//________________________________________________
void
Jb6DRegress::addEvent(EVENTN *myEve){
  
  double yieldRaw=myEve->yield;  // start with nominal charge input  
  int heli=myEve->heli; // assign helicity 0=+, 1=-
  assert(heli==kheliP || heli==kheliN);

  //...... reco  beam params from BPMs 
  double DelP[mxP], Praw[mxP];
  for(int ip=0;ip<mxP;ip++){
    Praw[ip]= myEve->Bpm[ip];// assume 1:1 mapping
    DelP[ip]= Praw[ip]- par_Pavr[ip]; //subtr heli-dependent mean
    mSumP[ip][heli]+=DelP[ip];
  }
  mEve[heli]++;
  mYmeas[heli]+=yieldRaw;//.... accumulate internal sums before
  
  //..... subtract correlations 
  double yieldCorr=yieldRaw;
  for(int ip=0;ip<mxP;ip++){
    yieldCorr-= DelP[ip]*  par_Alpha[ip];//reduce correlations
  }

  //.... monitor correlations
  linReg.accumulate(DelP,yieldRaw);
   
  mYcorr[heli]+=yieldCorr;//.... accumulate internal sums after

  // .... QA histos ....

  for(int ip=0;ip<mxP;ip++){
    double w=yieldCorr ;
    hA[10+ip+10*heli]->Fill(Praw[ip],w);
  }
 
}


//========================
//========================
void Jb6DRegress::init() {
  initHistos(); 
  linReg.setDims(mxP); linReg.init();

}


//________________________________________________
//________________________________________________
void
Jb6DRegress::initHistos(){
  printf("Jb6DRegress::initHistos()\n");
  //...... data histograms
  memset(hA,0,sizeof(hA));
  TH1 *h; 
  
  //.....1D  P raw Y +heli histos [10-19]   
  //.....1D  P raw Y -heli histos [20-29] 
  int heliC[mxHeli]={36,kBlue};

  for(int ibp=0;ibp<mxP;ibp++) {
    float x1=-1,x2=1;
    if(ibp==4) { x1=1259.1; x2=1261.3;}
    if(ibp==5) { x1=0.4; x2=1.6;}
    hA[10+ibp]=h=new TH1D(Form(mCore+"P%dpCr",ibp),Form("corr Y P%d heli +;meas %s (a.u.) ",ibp, Pname2[ibp].Data()),500.,x1,x2);
    h->SetLineColor(heliC[0]);

    hA[20+ibp]=h=new TH1D(Form(mCore+"P%dnCr",ibp),Form("corr Y P%d heli -; meas %s (a.u.) ",ibp, Pname2[ibp].Data()),500.,x1,x2);
    h->SetLineColor(heliC[1]);
  }
 
}


//________________________________________________
//________________________________________________
void
Jb6DRegress::finish(){

  printf("::::::::::::::::Jb6DRegress::finish(%s) :::::::::::\n",mCore.Data());
  linReg.printSummaryP();
  linReg.printSummaryY();
  linReg.solve();
  double DelP[mxP];
  double falseAsy=0;
  for(int ip=0;ip<mxP;ip++) {
    double avr[mxHeli];
    for(int ih=0;ih<mxHeli;ih++)  avr[ih]=mSumP[ip][ih]/mEve[ih];
    DelP[ip]=avr[kheliP]-avr[kheliN];
    falseAsy+=DelP[ip]*linReg.Alpha(ip);
    printf("%10s : P%d  avr +heli=%f -heli=%f del=%f  foundAlpha=%f\n",Pname2[ip].Data(),ip,avr[0],avr[1],DelP[ip],linReg.Alpha(ip));

  }
  falseAsy/=mYmeas[kheliP]/mEve[kheliP] + mYmeas[kheliN]/mEve[kheliN];
  printAsy(mYmeas,"uncorrected yields");
  printf("       Asy correction =%f  based on found alphas\n",falseAsy);
  printAsy(mYcorr,"corrected yields");
  
}

//________________________________________________
//________________________________________________
void
Jb6DRegress::printAsy(double *mY, const char * txt){
 //...... 
 double asy=999, err=888;
 double sum=mY[kheliP] + mY[kheliN];
 if(sum>5) {
   asy=(mY[kheliP] - mY[kheliN])/sum;
   err=1./sqrt(sum);
 }
 printf("Compute %s asy =%12.2g +/-%12.2g (nSig=%.2f)\n",txt,asy,err,asy/err);

}


