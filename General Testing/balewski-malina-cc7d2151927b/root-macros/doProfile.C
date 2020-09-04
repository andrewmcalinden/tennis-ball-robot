doProfile(int neve=5000){
  TCanvas *c1 = new TCanvas("c1","Profile histogram example",200,10,700,500);

  // http://root.cern.ch/root/html/TProfile.html 
  hprof  = new TProfile("hprof","Profile of pz versus px",100,-4,4,0,20,"s");
  /* 
     error dsiplay options:
     's'            Errors are the standard deviation of Y, S(Y)
     'i'            Errors are S(Y)/SQRT(N) (standard error on the mean as in the default)
     'g'            Errors are 1./SQRT(W) where W is the sum of the weights
  */
  Float_t px, py, pz;
  for ( Int_t i=0; i<neve; i++) {
    //  gRandom->Rannor(px,py);
    // pz = px*px + py*py;
    px=gRandom->Uniform(4)-2;
    pz=gRandom->Uniform(6)-px;
     hprof->Fill(px,pz,1);
  }
  hprof->Draw();
  gPad->SetGrid();
  //......
  for (int i=50 ;i<60;i++ ) {
    printf("bin=%d  Yavr=%f yerr=%f\n", i,hprof->GetBinContent(i),hprof->GetBinError(i));
  }
}
