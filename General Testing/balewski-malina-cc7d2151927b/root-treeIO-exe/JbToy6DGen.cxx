//#include <cstdio>
//#include <iostream>
using namespace std;

#include <TH2.h> 
#include <TList.h>
#include <TLine.h>
#include <TMarker.h> 
#include <TFile.h> 
#include <TTree.h> 


#include <math.h>
#include <TMath.h>
#include <TRandom3.h>
#include <TObjArray.h>

#include "JbToy6DGen.h"
static EVENTN myEvent;
TString Pname[mxP]={"beam-x","beam-nx","beam-y","beam-ny","beam-E","beam-Q"};

//========================
//========================
JbToy6DGen::JbToy6DGen() {
  printf("constr of JbToy6DGen\n");
  rnd=new TRandom3;
  rnd->SetSeed(12); // forces identical rnd-sequence
  mTree = new TTree("toy6D","M-C Qweak events for regression analysis.");
  mTree->Branch("qw6DEve",&myEvent,"heli/I:id:yield/F:B[6]");

  memset(mYield, 0, sizeof(mYield));

}



//________________________________________________
//________________________________________________
void
JbToy6DGen::throwEvent(int ieve){

  int heli=ieve%2; // assign helicity 0=+, 1=-
  myEvent.id=ieve;
  myEvent.heli=heli;

  double P[mxP]; // maps to true beam params: x,nx,y,ny,E,Q
  //........... generate new beam position  in X-nX plane
  for(int ix=0;ix<mXY;ix++) {
    double rnd1=rnd->Gaus(0,par_sig1[ix]);
    double rnd2=rnd->Gaus(0,par_sig2[ix]);

    P[0+2*ix]= par_P[0+2*ix][heli] + rnd1*mCosA[ix] - rnd2*mSinA[ix];//position
    P[1+2*ix]= par_P[1+2*ix][heli] + rnd1*mSinA[ix] + rnd2*mCosA[ix];//angle
  }

  //........ generate beam energy and charge fluctuation  
  P[4]=rnd->Gaus(par_P[4][heli],par_sigE);// energy
  P[5]=rnd->Gaus(par_P[5][heli],par_sigQ); // charge
  
  //..... add correlation resulting from  beam displacements
  double yield=1.;  // start with renormalized  charge
  for(int ip=0;ip<mxP;ip++){
    yield+= (P[ip]- par_Pavr[ip]) *  par_Alpha[ip];//introduce linear correlations
  } 
  myEvent.yield=yield;
  
  //..... smear true beam params as measured by BPMs, only diagonal
  for(int ip=0;ip<mxP;ip++){
    myEvent.Bpm[ip]= rnd->Gaus(P[ip],par_sigBpm[ip]);
  }
   
   //..... save event in to tree
  mTree->Fill();

  /*
  //  printf(" EE=%f QQ=%f\n",P[4], P[5]);
  printf("ieve=%d E=%f Q=%f\n", ieve, myEvent.Bpm[4], myEvent.Bpm[5]);
  myEvent.heli=1;
  myEvent.id=2;
  myEvent.yield=3;
  for(int j=0;j<mxP;j++) myEvent.Bpm[j]=100+j;
  */


  //.... accumulate internal sums for QA
  mYield[heli]+=yield;
  mYield[2]++; // count events
 
  // .... QA histos ....
  ((TH2F*)hA[1])->Fill( myEvent.Bpm[0], myEvent.Bpm[1],yield); 
  ((TH2F*)hA[2])->Fill( myEvent.Bpm[2], myEvent.Bpm[3],yield); 
  ((TH2F*)hA[3])->Fill( myEvent.Bpm[4], myEvent.Bpm[5],yield); 
  
  for(int ip=0;ip<mxP;ip++){
    hA[10+ip]->Fill(myEvent.Bpm[ip]);
  }
  
}

//========================
//========================
void JbToy6DGen::print() {

  printf("input params:\n   gen beam means \n");
  for(int i=0;i<mxP;i++) printf("%s :P%d avr=%f del=%f  alpha=%.3f sigBmp=%f\n",Pname[i].Data(),i,par_Pavr[i],par_P[i][kheliP]-par_P[i][kheliN], par_Alpha[i], par_sigBpm[i]);

  printf("beam in X  : s1=%.3f s2=%.3f corAngle=%.1f\n", par_sig1[0],par_sig2[0],par_phi[0]);
  printf("beam in Y : s1=%.3f s2=%.3f corAngle=%.1f\n", par_sig1[0],par_sig2[0],par_phi[0]);
  printf("beam spread in E=%.3f  Q=%.3f \n", par_sigE,par_sigQ);
  
}

//========================
//========================
void JbToy6DGen::init() {

  const double PI=TMath::Pi();
  const double deg2rad=PI/180.;
  
  for(int ix=0;ix<mXY;ix++) {
    mCosA[ix]=cos(par_phi[ix]*deg2rad);  
    mSinA[ix]=sin(par_phi[ix]*deg2rad);
  }
  
  for(int i=0;i<mxP;i++)  {
    par_Pavr[i]= (par_P[i][kheliP]+par_P[i][kheliN])/2.;
  }
  
  initHistos(); 

}


//________________________________________________
//________________________________________________
void
JbToy6DGen::initHistos(){
 
  //...... data histograms
  memset(hA,0,sizeof(hA));
  TList *Lx; TH1 *h; TMarker *mar;// TLine *ln; //TEllipse *el;
  hA[1]=h=new TH2F("beamXnX","Beam position X-nx; BPM x(mm); BPM nx",100,-1.4,1.4,100,-1.,1.);
   
  // center markers
  Lx=h->GetListOfFunctions(); 
  int heliC[mxHeli]={kBlack,kBlue};
  for(int heli=0;heli<mxHeli;heli++){
    mar=new TMarker(par_P[0][heli],par_P[1][heli],5);
    Lx->Add(mar);mar->SetMarkerColor(heliC[heli]); 
    mar->SetMarkerSize(2); 
  }
  
    hA[2]=h=new TH2F("beamYnY","Beam position Y-ny; BPM y(mm); BPM ny",100,-1.4,1.4,100,-1.,1.);
  // center markers
  Lx=h->GetListOfFunctions();
  for(int heli=0;heli<mxHeli;heli++){
    mar=new TMarker(par_P[2][heli],par_P[3][heli],5);
    Lx->Add(mar);mar->SetMarkerColor(heliC[heli]); 
    mar->SetMarkerSize(2); 
  }


  double fac=8;
  double x1=par_P[4][kheliP]-fac*par_sigE,x2=x1+2*fac*par_sigE;
  double y1=par_P[5][kheliP]-fac*par_sigQ,y2=y1+2*fac*par_sigQ;
  hA[3]=h=new TH2F("beamEQa","Beam true Q vs. E angle, as generated; true E (a.u.); true charge (a.u.)",100,x1,x2,100,y1,y2);
  Lx=h->GetListOfFunctions();
  // center markers
  Lx=h->GetListOfFunctions();
  for(int heli=0;heli<mxHeli;heli++){
    mar=new TMarker(par_P[4][heli],par_P[5][heli],5);
    Lx->Add(mar);mar->SetMarkerColor(heliC[heli]); 
    mar->SetMarkerSize(2); 
  }

  // free 6-9

  //..... BPM's histos [10-19] - reserved
  for(int ibp=0;ibp<mxP;ibp++) {
    float x1=-1,x2=1;
    if(ibp>=4) {// E or Q , have no correlation and average is NE 1
      x1=x2=par_P[ibp][kheliP];
      if(ibp==4) { x1-=fac*par_sigE; x2+=fac*par_sigE; }
      if(ibp==5) { x1-=fac*par_sigQ; x2+=fac*par_sigQ; }     
    } 
    hA[10+ibp]=h=new TH1F(Form("bpm%d",ibp),Form("BPM%d  matched to %s;(a.u.) ",ibp, Pname[ibp].Data()),1000.,x1,x2);
  }
  
  
}




//________________________________________________
//________________________________________________
void
JbToy6DGen::finish(){
  printf("::::::::::::::::JbToy6DGen::finish() :::::::::::\n");

 mTree->Show(1);// event id startting from 0
 mTree->Print(); 

 //...... 
 double asy=999, err=888;
 double sum=mYield[kheliP] + mYield[kheliN];
 double avrY=99999;
 if(sum>5) {
   asy=(mYield[kheliP] - mYield[kheliN])/sum;
   err=1./sqrt(sum);
   avrY=sum/mYield[2];
 }
 printf("Compute measured asy =%12.2g +/-%12.2g (nSig=%.2f), avrY=%f \n",asy,err,asy/err,avrY);

}
