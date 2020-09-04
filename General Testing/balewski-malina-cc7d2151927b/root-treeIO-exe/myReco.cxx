#include <cstdio>  // C++ standard since 1999
#include <TFile.h>
#include <TTree.h> 
#include <TChain.h>
#include <TObjArray.h>

#include "Jb6DRegress.h"

// use only double

int main() {

  // read TTree  with precompiled class
  int mxEve=9e7;
  const char * outPath="./";

  // .........   input  event file   .........
  TChain *chain = new TChain("toy6D");
  
  const char *inpPath=outPath;
  int i=0;
  char text[100];
  sprintf(text,"%stoy6D.tree.root",inpPath);
  chain->Add(text);
  printf("%d =%s=\n",i,text);
  
  int nEve=(int)chain->GetEntries();
  printf("tot nEve=%d expected in the chain\n",nEve);
  EVENTN myEve;

  chain->SetBranchAddress("qw6DEve",&myEve);
  chain->Print();
  chain->Show(1); // event id startting from 0
  //
 

  TString hfileName=outPath;  hfileName+="/toy6Dregr.hist.root";
  TFile*  mHfile=new TFile(hfileName,"RECREATE"," histograms w/ regressed Qweak yields");
  assert(mHfile->IsOpen());
  printf(" Setup output  histo to '%s' ,\n",hfileName.Data());

  double inpMeanP[mxP]={-0.24, -0.15, 0.10, -0.18, 1260.15, 1.};
  //memset(inpMeanP,0,sizeof(inpMeanP)); 
  double inpAlphas[mxP]={-0.23, 0.18, -0.35, -0.41, 0.27, -0.22}; // no BMP smear
  //double inpAlphas[mxP]={-0.146, 0.076, -0.22, -0.13, 0.18, -0.164}; // BMP smear=0.1
  //memset(inpAlphas,0,sizeof(inpAlphas)); 

  Jb6DRegress regrU("rgU"); // Uncorrected 

  regrU.setMeanP(inpMeanP); //  mean  offsets
  regrU.setAlphas(inpAlphas);
  regrU.print();
  regrU.init();   

  int t1=time(0);
  int ie;
  if(nEve>mxEve) nEve=mxEve;
  for( ie=0;ie<nEve;ie++) { 
    chain->GetEntry(ie);
    if(ie%50000==0)
      printf("--- done eve=%d of %d  ...  Bpm[0]=%f,  Bpm[5]=%f\n",ie,nEve,myEve.Bpm[0],myEve.Bpm[5]);
    regrU.addEvent(&myEve);
    
  }
  int t2=time(0);
  if(t1==t2) t2++;
  float rate=1.*ie/(t2-t1);
  float nMnts=(t2-t1)/60.;
  printf("sorting done, elapsed rate=%.1f Hz, tot %.1f minutes\n",rate,nMnts);

  regrU.finish(); 
  mHfile->Write();


}


