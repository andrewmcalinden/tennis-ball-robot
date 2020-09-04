TCanvas *c =0;
void drawMG3(int page=2, char *fname="moller5000.hist.root"){
  
  TFile *f1=new TFile(fname); assert(f1->IsOpen());
  gStyle->SetPalette(1);


  switch (page) {

  case 1: {//=========================
    c = new TCanvas("c1", "any electrons",1200,800);
    c->Divide(2,2);
    
    TH1F *h1=f1->Get(Form("nET")); assert(h1);
    TH1F *h22=f1->Get(Form("RPlot")); assert(h22);
    TH2F *h2=f1->Get(Form("R2Plot")); assert(h2);

    c->cd(1);
    h2->SetMaximum(30); h3->SetMinimum(0);
    h2->Draw("colz");

    c->cd(2);
    h22->Draw();  gPad->SetLogy(); gPad->SetLogx();

    c->cd(3);
    h1->Draw(); gPad->SetLogy();

    printf("page  %d is finished\n",page);
    break;}

  case 2: {//=========================
    c = new TCanvas("c1", "primary electrons",1200,800);
    c->Divide(2,2);
    
    TH1F *h1=f1->Get(Form("thPlot")); assert(h1);
    c->cd(1);
    h1->Draw();  gPad->SetLogy(); 
    printf("page  %d is finished\n",page);

    TH2F *h2=f1->Get(Form("Eth")); assert(h2);
    c->cd(2); h2->Draw("colz");
    break;}

  case 99: {//=========================
    printf("page is %d \n",page);
    break;}

  default:
    printf("page %d undefined\n",page);
  }// end of case

  printf("common end\n");
  c->Print(Form("page%04d.ps",page));

}
