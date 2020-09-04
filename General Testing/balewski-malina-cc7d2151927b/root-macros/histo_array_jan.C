

//static const int numb_graphs = 16;
enum {numb_graphs=4}; // is shorter if you need integer constant
TString partName[numb_graphs] = {"z", "t","kk","zz"}; // make sure you initialize all elements
TH1 *hp[numb_graphs*2];


void histo_array_jan(){
  
  initHisto1D();
  initHisto2D();	
  

  int numb_entries=50;
  for(int j=0;j<numb_graphs; j++){
    for (int i=0; i<numb_entries; i++){
      
      hp[j]->Fill(i);
      hp[j+numb_graphs]->Fill(i, i*2);
      
    }
    
  }

  new TBrowser();
 
  
  gStyle->SetPalette(1);
  TCanvas *c = new TCanvas("Try","Try", 600,500);
  c->Divide(2,1);
  c->cd(1);
  hp[1]->Draw();
  c->cd(2);
  hp[1+numb_graphs]->Draw("colz");
  
}

//====================================
//====================================

void initHisto1D(){
 
  memset(hp,0,sizeof(hp));

  for (int i=0; i<numb_graphs; i++) {
    TString tt1= "h"; tt1+=i;
    printf("mad %s\n",tt1.Data());
    TH1F *h2=new TH1F( tt1, "LAB mom "+partName[i]+"; p"+partName[i]+" (MeV/c);  Frequency", 60,-1,1); 
    hp[i]=h2;
    printf("swagg");    
  }
}

//====================================
//====================================
void initHisto2D(){
	
  double pZ1=-90, pZ2=180, pT2=90; 

  for ( int i=0; i<numb_graphs; i++) {
    TString tt1= "bh"; tt1+=i;
    TH2F *h4=new TH2F(tt1, "LAB mom "+partName[i]+"; p"+partName[i]+" (MeV/c);  (MeV/c)", 60,pZ1,pZ2,30,0.,pT2); 
    hp[i+numb_graphs]=h4;
  }
}
