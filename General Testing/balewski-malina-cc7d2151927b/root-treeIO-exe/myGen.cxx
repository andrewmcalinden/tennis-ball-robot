#include <cstdio>  // C++ standard since 1999
#include <TObjArray.h>
#include <TFile.h>

#include "JbToy6DGen.h"

// use only double
 
int main() {
  printf("myGenerator:  START...\n");

  TString mTreePath="./";
  TString treeName=mTreePath+"/toy6D.tree.root";
  TFile*  mHfile=new TFile(treeName,"RECREATE"," histograms & trees Qweak M-C events");
  assert(mHfile->IsOpen());
  printf(" Setup output tree & histo to '%s' ,\n",treeName.Data());
  
  // order of  beam params: x,nx,y,ny,E,Q
  double inpSigBpm[mxP]={0.1, 0.1, 0.1, 0.1, 0.1, 0.1};
  memset(inpSigBpm,0,sizeof(inpSigBpm)); // turn off BPM spread

  double inpMeanP[mxP]={-0.22, -0.19, 0.10,  -0.21, 1260.1, 1.0};
  double inpMeanN[mxP]={-0.26, -0.11, 0.10,  -0.15, 1260.2, 1.0};

  double inpAlphas[mxP]={-0.23, 0.18, -0.35, -0.41, 0.27, -0.22};

  JbToy6DGen gen;
  gen.setMeanP(inpMeanP,kheliP); //  offsets for generator +heli
  gen.setMeanP(inpMeanN,kheliN); //  offsets for generator -heli
  gen.setBeamSpread(0.2, 0.1, 30.,0);// X-nX plane
  gen.setBeamSpread(0.23, 0.08, -20.,1);//Y-nY plane
  gen.setBeamSpreadEQ(0.14, 0.17);//beam energy and charge spread, no correlation
  //correlations: Ymeas=Ytrue+alpha_k*(P_k- avrP_k) 
  gen.setAlphasGen(inpAlphas); // Generator
  gen.setBpmSpread(inpSigBpm); // Generator
  
  gen.init();

  gen.print();

  printf("main  START...\n");
  for(int ieve=0;ieve<5e5;ieve++) 
    gen.throwEvent(ieve);
  
  gen.finish();
  
  mHfile->Write();
  mHfile->Close();
  printf("\n Histo saved -->%s<\n",treeName.Data());
  
  return 0;
}
