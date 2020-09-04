{
  TH1F *h1=new TH1F("aa", "bb",10,0,10);
   c1 = new TCanvas("c1","sub data",200,10,700,500);
   h1->Fill(2);
   h1->Draw();
   c1->Print("all.pdf(","pdf"); 

   h1->Fill(3);
   h1->Draw();
   c1->Print("all.pdf","pdf");

   h1->Fill(5);
   h1->Draw();
   c1->Print("all.pdf)","pdf");

   printf("\nto display PDF execute:   evince all.pdf  \n");
}
