/* Example 4

Lanuches:
-  1 thread   generating record vs. time, adding to TGraph
-  1 thread updates canvas untill joiner tells it to stop
-  main thread  awaiting for filller thread to finish

*/

#include "TStyle.h"
#include "TCanvas.h"
#include "TFrame.h"
#include "TGraph.h"
#include "TAxis.h"
#include "TRandom.h"
#include "TThread.h"
#include "TH1.h"


TCanvas *can=0;
TThread *trdFlr=0, *trdPlt=0;

int fillPeriod_ms=200;
int plotPeriod_ms=500;
long fillDuration_s=12;

//================================
void killMyThr() {
  printf(" kill the fill-thread  matching the canvas being closed\n"); 
  // and set the canvas pointer to 0

  trdFlr->Kill();
  trdPlt->Kill();

  can = 0;
}

//------------------------
//------------------------
void *handleFiller(void *ptr) {
   long nSec = (long) ptr;
   printf("F:start Filler inp=%ld\n",nSec);
   
   TThread::Lock(); //Static method to lock the main thread mutex.
   TGraph *gr=new TGraph();
   gr->SetLineColor(2);
   gr->SetLineWidth(2);
   gr->SetMarkerColor(4);
   gr->SetMarkerStyle(4);

   gr->SetPoint(0,-0.5,0.);
   gr->SetPoint(1,-0.1,0.);
   printf("fillThr  will run for  nSec=%d created TGraph & draw, end mutex-lock\n",nSec);
   TThread::UnLock();

   int j=0;
   while (can==0) {
     printf("F:wait for Canvas j=%d\n",j);
     j++;
     gSystem->Sleep(fillPeriod_ms); // mSec 
   }


   printf("F:plot 1st time\n");
   can->cd(0); // assumes hP histo is already displayed on Canvas(0)
   gr->Draw("pl");


   //can->Modified();

   int time0=time(0);
  
   printf("F:add data \n");
   j=0;
   while ( time(0) <time0+nSec) {
     float tx=j*fillPeriod_ms/1000.;
     j++;
     float py=sin(tx);
     printf("F: added j=%d t/sec=%.2f\n",j,tx);
     TThread::Lock();
     int n=gr->GetN();     
     gr->SetPoint(n,tx,py);
     TThread::UnLock();
     gSystem->Sleep(fillPeriod_ms); // mSec 

   }

   printf(" filler thread is done, nPoint=%d\n",gr->GetN());

   return 0;
}

//================================
//================================
void *handlePlotter(void *ptr) {
  long val=(long) ptr;
  printf("P:start Plotter inp=%ld\n",val);
  
  TString tit1=Form("can0");
  TString tit2=Form("Dynamic Filling TGraph");
  can = new TCanvas(tit1,tit2,100,20,800,600);
  TH1F *hP=new TH1F("aa","graph updated by a thread;time(sec); amplitude (a.u.)",10,0.,12.);
  hP->SetMinimum(-1.2);   hP->SetMaximum(1.2);
  can->cd(0);
  printf("P:draw now\n");
  hP->Draw();
  gPad->SetGrid();
  gStyle->SetOptStat(0);
  
  // connect to the Closed() signal to kill thread when a canvas is closed
  can->Connect("Closed()", 0, 0, "killMyThr()");

  printf("P: infinite loop updating plot ..\n");
  while (can) {
       if ( can->IsModified()) {
	 printf("P:Update canvas\n" );
	 can->Update();
       }
       gSystem->Sleep(plotPeriod_ms);
       gSystem->ProcessEvents();
  }
  
}




//================================
//================================
//      M A I N  
//================================
//================================
void threadsDAQ_Plot_Fill()
{
#ifdef __CINT__
   printf("This script can only be executed via ACliC: .x threadsDAQ_Plot_Fill.C++\n");
   return;
#endif

   gRandom->SetSeed();

   //gDebug = 1; // prints what is load to Root
   
  
   TString tit4=Form("myPltTrd");
   printf("M:Starting Thread %s\n",tit4.Data());
   trdPlt = new TThread(tit4, handlePlotter, (void*) 44);
   trdPlt->Run();
 
     
   TString tit3=Form("myFlrTrd");
   printf("M:Starting Thread %s\n",tit3.Data());
   trdFlr = new TThread(tit3, handleFiller, (void*) fillDuration_s); // Note, it is used to index canvas - do not change it
   trdFlr->Run();
   
 
   
   TThread::Ps();
   printf("M:wait for fill-thread to finish...\n");
   trdFlr->Join(); // wait untill thread is cancelled
   printf("M:fill-done, wait for plt-thr to finish ...\n");


   trdPlt->Join(); 
   printf("M:plot-done, wiat for plt-thr to finish ...\n");
   TThread::Ps();

   delete trdPlt; 
   delete trdFlr;

   printf("M: all threads are terminated, quit Root w/ .q\n");
}
