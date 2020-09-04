pl_fit() {
  /*opens the canvas and splits it into two. Draws hist1 on top and hist2 on 
bottom. A gaussian is fitted to the right half of hist2 and a line is drawn at
its mean.
  */
  gStyle->SetOptFit(1);
  TFile *fd =new TFile("histogram.root");
  assert(fd->IsOpen());
  fd->ls();
  //attach hist to pointer
  TH1F *h1=fd->Get("hist1");
  printf("h1=%p\n",h1);
  assert(h1);
  h1->Draw();
  TCanvas *c=new TCanvas;
  c->Divide(1,2);
  c->cd(1);
  h1->Draw();
  h1=(TH1F*) fd->Get("hist2");
  assert(h1);
  c->cd(2);//change to 2nd canvas
  //h1->Draw();
  h1->Fit("gaus","","Rh",6.,14.);
  TF1 *ff=h1->GetFunction("gaus");//acess the fit function
  assert(ff);
  double mean=ff->GetParameter(1);
  double meanerr=ff->GetParError(1);
  printf("mean=%f +/- %f\n",mean,meanerr);
  TLine *ln=new TLine(mean,0.,mean,h1->GetMaximum());
  ln->SetLineColor(kRed);
  ln->Draw();
}
