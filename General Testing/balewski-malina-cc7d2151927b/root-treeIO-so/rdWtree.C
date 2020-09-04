#include <TVector3.h>

void rdWtree() {
  gSystem->Load("libWtreeCode.so");
  
  // read TTree  with precompiled class
  
  // .........   input  event file   .........
  TChain *chain = new TChain("toy6D");
 
  TString mTreePath="./";
  TString tName1=mTreePath+"toyEve.tree.root";
  chain->Add(tName1);
  printf("add tree =%s=\n",tName1.Data());
  
  int nEve=(int)chain->GetEntries();
  printf("tot nEve=%d expected in the chain\n",nEve);
  Wevent2011 *myEve=new Wevent2011; 
  WeventIO eveWrap;


  assert(chain->SetBranchAddress("eveJan",&myEve)==0);
  chain->Print();
  chain->Show(1); // event id startting from 0

  TH1F *h=new TH1F("hz", "vertex Z",100,-2,10);
  
  int t1=time(0);
  int ie;

  for( ie=0;ie<nEve;ie++) { 
    chain->GetEntry(ie);
    if(ie%5==0)
      printf("--- done eve=%d of %d   eve.id=%d\n",ie,nEve,myEve->id);
    eveWrap.unpackEve(myEve,h);
  }

  //myEve->print(); // directly just the last event

  int t2=time(0);
  if(t1==t2) t2++;
  float rate=1.*ie/(t2-t1);
  float nMnts=(t2-t1)/60.;
  printf("sorting done, elapsed rate=%.1f Hz, tot %.1f minutes\n",rate,nMnts);

  h->Draw();
  return ;

}
