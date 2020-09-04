#include <TVector3.h>
#include <vector>

void wrWtree(int nEve=4) {
  assert(gSystem->Load("libWtreeCode.so")==0);
  Wevent2011 myEve; myEve.clear();
  
  TString mTreePath="./";
  TString treeName=mTreePath+"toyEve.tree.root";
  TFile*  mHfile=new TFile(treeName,"RECREATE"," histograms & trees Qweak M-C events");
  assert(mHfile->IsOpen());
  // create tree file and event-branch
  mTree = new TTree("toy6D","M-C Qweak events for regression analysis.");
  mTree->Branch("eveJan",&myEve);

  WeventIO eveWrap; // util class to manipulate on event

  for(int k=0;k<nEve;k++) {
    // fill local event container with random data depending on k
    eveWrap.fillEve(&myEve,k);
    if(k<4) myEve->print();
    //..... save event in to tree
    mTree->Fill();
  }

  printf("\n\n::::::::::::::::JbToy6DGen::finish() :::::::::::\n");

  mTree->Show(1);// event id startting from 0
  mTree->Print(); 
  
 
 mHfile->Write();
 mHfile->Close();
 printf("\n Tree saved -->%s<\n",treeName.Data());
}
