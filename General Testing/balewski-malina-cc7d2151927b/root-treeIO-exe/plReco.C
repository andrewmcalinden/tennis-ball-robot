TString inpPath="./";
TFile* fd=0;
TString hCore="rgU";

plReco(int page=1) {
  gStyle->SetFillStyle(0);
  gStyle->SetPalette(1,0);
  TString dataFinalRoot=inpPath+"toy6Dregr.hist.root";

  fd=new TFile( dataFinalRoot); assert(fd->IsOpen());

  if(page==1) P1D("P_1D heli + & -","Cr");
  if(page==2) asy1("corrected asy vs corr Ps","Cr"); 
  
}


//============================================
//============================================
void   P1D(TString cName, TString ext){
  gStyle->SetOptStat(1001110);
  gStyle->SetOptFit(1);
  
  c=new TCanvas(cName,cName,900,600); c->SetFillColor(kWhite);
  c->Divide(3,2);
  //  int i;
  for(int i=0;i<6;i++) {
    c->cd(i+1);
    TString tt="P"; tt+=i; tt+="p";
    TH1D * hp=(TH1D *)fd->Get(hCore+tt+ext); assert(hp);
    hp->Fit("gaus");
    TF1 *ff=hp->GetFunction("gaus");
    ff->SetLineColor(kRed);    ff->SetLineWidth(1);
    hp->GetXaxis()->SetNdivisions(5); 

    tt="P"; tt+=i; tt+="n";
    TH1D * hn=(TH1D *)fd->Get(hCore+tt+ext); assert(hn);
    hn->Draw("same");
 
  }
}

//============================================
//============================================
void   asy1(TString cName, TString ext=""){
  gStyle->SetOptStat(0);
  gStyle->SetOptFit(1);
  int nReb=5;
  int test=0; // show just 1 histo

  c=new TCanvas(cName,cName,900,600); c->SetFillColor(kWhite);
  c->Divide(3,2);
  for(int i=0;i<6;i++) {
    c->cd(i+1);
    TH1D * hp=(TH1D *)fd->Get(hCore+Form("P%dp",i)+ext); assert(hp);
    TH1D * hn=(TH1D *)fd->Get(hCore+Form("P%dn",i)+ext); assert(hn);
    hp->Rebin(nReb);    hn->Rebin(nReb);
    TString tt=hp->GetName(); 

    TH1D * hs=(TH1D *) hp->Clone(); 
    hs->SetName("S"+tt);     hs->SetTitle("Sum "+tt);
    hs->Add(hp);

    TH1D * hd=(TH1D *) hp->Clone(); 
    hd->SetName("D"+tt);     hd->SetTitle("Dif "+tt);
    hd->Add(hn,-1.);

    TH1D * ha=(TH1D *) hd->Clone(); 
    ha->SetName("A"+tt);     ha->SetTitle("Asy "+tt);
    ha->Reset();
   //  ha->Divide(hs);

    double yThres=100;
    // recompute errors for Asy
    for(int b=1;b<ha->GetXaxis()->GetNbins(); b++) {
      double sum=hs->GetBinContent(b); 
      double dif=hd->GetBinContent(b); 
      if(sum<yThres) {
	ha->SetBinContent(b,0);
	//	ha->SetBinError(b,1.);
      } else {
	double err=1./sqrt(sum);
	//	printf("%d %f %f\n",b,sum,err);
	ha->SetBinContent(b,dif/sum);
	ha->SetBinError(b,err);
      }
      // printf("b=%d %f %f \n",b, ha->GetBinContent(b), ha->GetBinError(b));
    }


    c->cd(i+1);
    ha->Draw("e");    ha->GetXaxis()->SetNdivisions(5); 
    ha->Fit("pol0");
    TF1 *ff=ha->GetFunction("pol0");
    ff->SetLineColor(kRed);    ff->SetLineWidth(1);

    //ln=new TLine(-1,0,1.5,0); ln->Draw();
    if(test) { 
      c->cd(i+5);  hp->Draw();
      c->cd(i+5);  hn->Draw("same");
    }
    

  }
}

