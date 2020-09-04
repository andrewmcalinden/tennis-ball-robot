TString inpPath="./";
TFile* fd=0;

plGen(int page=1) {
  gStyle->SetFillStyle(0);
  gStyle->SetPalette(1,0);
  TString dataFinalRoot=inpPath+"toy6D.tree.root";

  fd=new TFile( dataFinalRoot); assert(fd->IsOpen());

  if(page==1) beamSpread("beamSpread");
  if(page==2) bpm1D("BPM_1D");
  
}

//============================================
//============================================
void   beamSpread(TString cCore){
  gStyle->SetOptStat(1001110);
  gStyle->SetOptFit(1);
  
  c=new TCanvas(cCore,cCore,600,600); c->SetFillColor(kWhite);
  c->Divide(2,2);
  
  c->cd(1);//..............
  h2=  beamXnX ;     h2->Draw("colz"); gPad->SetGrid();
  c->cd(2);//.............. free

  c->cd(3);//..............
  h2=  beamYnY ;     h2->Draw("colz"); gPad->SetGrid();
  c->cd(4);//..............
  h2=  beamEQa ;     h2->Draw("colz"); gPad->SetGrid();
}

//============================================
//============================================
void   bpm1D(TString cCore){
  gStyle->SetOptStat(1001110);
  gStyle->SetOptFit(1);
  
  c=new TCanvas(cCore,cCore,900,600); c->SetFillColor(kWhite);
  c->Divide(3,2);
  for(int i=0;i<6;i++) {
    c->cd(i+1);
    TH1F * h=(TH1F *)fd->Get(Form("bpm%d",i)); assert(h);
    //    h->Draw();
    h->Fit("gaus");
    TF1 *ff=h->GetFunction("gaus");
    ff->SetLineColor(kRed);    ff->SetLineWidth(1);
  }
}

//============================================
//============================================
void   corrYP(TString cCore, int ir=0){
  gStyle->SetOptStat(1001110);
  gStyle->SetOptFit(1);
  
  cCore+=ir;
  c=new TCanvas(cCore,cCore,900,600); c->SetFillColor(kWhite);
  c->Divide(3,2);
  for(int iy=0;iy<2;iy++) {
    for(int ip=0;ip<2;ip++) {
      c->cd(1+iy*3+ip);
      h=fd->Get(Form("corY%d_P%dreg%d",iy,ip,ir)); assert(h);
      h->Draw("colz");gPad->SetGrid();
    }
  }
}
