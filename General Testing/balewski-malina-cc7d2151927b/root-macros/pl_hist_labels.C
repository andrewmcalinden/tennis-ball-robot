// assume you want to count animals: cat, dog, fish
// 20 of them  show up at random
// you want a histogram w/ names on the x-axis


enum{mxN=3};

pl_hist_labels() {
  TH1F* h=new TH1F("my","Counts types animals; type of animal; events",mxN+5,0,1);
  h->GetXaxis()->SetTitleOffset(0.4);  h->GetXaxis()->SetLabelSize(0.06);  h->GetXaxis()->SetTitleSize(0.05); h->SetMinimum(0.);
  h->SetLineColor(kBlue);h->SetLineWidth(2);
  h->SetMarkerSize(2);//<-- large text

  //  TString nameA[mxN]={"cat","dog","fish"};
  TString nameA[mxN]={"cat","dog-veryLong","fish"};
  // force order of labels
  for(int k=0;k<mxN;k++)  h->Fill(nameA[k],0.);


  TRandom3 *rnd=new  TRandom3(3233);

  for (int i=0; i<20; i++) {
    double x=rnd->Uniform();
    TString animal="fixMe";
    int k=x*mxN; // will be alwasy [0,mxN)
    animal=nameA[k];
    printf("i=%d x=%.3f k=%d  animal=%s\n",i,x,k,animal.Data());
    h->Fill(animal,1.);
  }

  c=new TCanvas();
  // c->Divide(1,2);
  //c->cd(1);
  h->Draw("e text ");

  // draw legend

   leg = new TLegend(0.6,0.3,0.8,0.7);
   leg->SetHeader("The Legend Title");
   leg->AddEntry(h,"some hist","f");
   leg->AddEntry("f1","Function abs(#frac{sin(x)}{x})","l");
   leg->AddEntry("h","myAnim","lep");
   leg->Draw();


}
