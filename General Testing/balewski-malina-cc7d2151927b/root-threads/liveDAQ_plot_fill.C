/* Example 

The data container is chopped in to small pices (LiveData.h)
and plotter adds to display only the most recent chunk.
For each data chunk  replicate last point for continues plot-line.
Note, this code creates memory leak, because objects created by:
  liveData=new LiveData(x,y);
are never deleted

Lanuches:
-  1 thread   generating record vs. time, adding to TGraph
-  1 thread updates canvas untill joiner tells it to stop
-  1 thread awaiting for filller thread to finish
-  main thread  shows prompt and allows display manipulation

*/

#include "TStyle.h"
#include "TCanvas.h"
#include "TFrame.h"
#include "TGraph.h"
#include "TAxis.h"
#include "TRandom.h"
#include "TThread.h"
#include "TH1.h"

//#include "LiveData.h"

class LiveData { //minimal TGraph holds chunk of fresh (not plotted) data
 public:
  TGraph *gr1;
  LiveData(double x, double y) { 
    gr1=new TGraph();
    gr1->SetLineColor(2);
    gr1->SetLineWidth(2);
    gr1->SetMarkerColor(4);
    gr1->SetMarkerStyle(4); 
    gr1->SetPoint(0,x,y);
    // printf("cnstr LiveData\n");
  }
};


TCanvas *can=0;
TThread *trdFlr=0, *trdPlt=0, *trdClo;
TH1F *hP;

LiveData *liveData=0;
int fillPeriod_ms=200;
int plotPeriod_ms=2000;
long fillDuration_s=20;

//================================
void killMyThr() { // executed when canvas is killed
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
   
   int time0=time(0);

   int j=0;
   while ( time(0) <time0+nSec) {
     float tx=j*fillPeriod_ms/1000.; j++;
     float py=sin(tx);
     //printf("F: added j=%d t/sec=%.2f\n",j,tx);
     TThread::Lock();     
     int n=liveData->gr1->GetN();     
     liveData->gr1->SetPoint(n,tx,py);
     TThread::UnLock();
     gSystem->Sleep(fillPeriod_ms); // mSec 
   }

   printf(" filler thread is done, end j=%d\n",j);

   return 0;
}

//================================
//================================
void *handleCloser(void *ptr) {
  long yMax=(long) ptr;
  printf("C:start closer  inp=%ld\n",yMax);
 
   TThread::Ps();
   printf("C:wait for fill-thread to finish...\n");
   trdFlr->Join(); // wait untill thread is cancelled
   printf("M:fill-done, wait for plt-thr to finish ...\n");


   trdPlt->Join(); 
   printf("C:plot-done, wait for plt-thr to finish ...\n");
   TThread::Ps();

   trdClo->Join();

   printf("C:stopped all threads\n");

   delete trdPlt; 
   delete trdFlr;
   delete trdClo;
 
   return 0;
}

//================================
//================================
void *handlePlotter(void *ptr) {
  long yMax=(long) ptr;
  printf("P:start Plotter yMax=%ld\n",yMax);
  int nUpd=0; // update counter
  int nData=0;

  TString tit1=Form("can0");
  TString tit2=Form("Dynamic Filling TGraph");
  can = new TCanvas(tit1,tit2,100,20,600,600);
  hP=new TH1F("hP"," updated by a thread;time(sec); amplitude (a.u.)",10,0.,12.);
 
  hP->SetMinimum(-yMax);   hP->SetMaximum(yMax);
  can->cd(0);
  printf("P:draw Canvas\n");
  hP->Draw();
  gPad->SetGrid();
  gStyle->SetOptStat(0);


  printf("P:plot 1st time\n");
  can->cd(0); // assumes hP histo is already displayed on Canvas(0)
  liveData->gr1->Draw("pl");

  
  // connect to the Closed() signal to kill thread when a canvas is closed
  can->Connect("Closed()", 0, 0, "killMyThr()");

  printf("P: infinite loop updating plot ..\n");
  while (can) {
    LiveData *lastData=0;      
    TThread::Lock(); //Static method to lock the main thread mutex.
    int np=liveData->gr1->GetN();
    // printf("P:sees %d live data\n",np);
    if (np >1 ) {
      //printf("P: grabs data\n",np);
      double x,y;
      liveData->gr1->GetPoint(np-1,x,y);
      lastData=liveData; // archive old instance and create new:
      liveData=new LiveData(x,y);// replicate last point for continues plot-line
    }
    TThread::UnLock();
    nData+=np-1;
    if (lastData) {
      lastData->gr1->Draw("pl");
      hP->SetTitle(Form(" nData=%d update counter=%d  update period=%.1f sec\n",nData,nUpd,plotPeriod_ms/1000.));
      nUpd++;
      //printf("P:Update canvas\n" );
      can->Update();
    }

    gSystem->Sleep(plotPeriod_ms);
    //gSystem->ProcessEvents();
  }
  
}




//================================
//================================
//      M A I N  
//================================
//================================
void liveDAQ_plot_fill()
{
#ifdef __CINT__
  printf("This script can only be executed via ACliC: .x liveDAQ_plot_fill.C++\n");
   return;
#endif

   gRandom->SetSeed();
   
   // initialize data container for the 1st time
   liveData=new LiveData(2,1.5);
   liveData->gr1->SetPoint(1,2,0.);
   
   //gDebug = 1; // prints what is load to Root
     
   TString tit4=Form("myPloterTrd");
   printf("M:Starting Thread %s\n",tit4.Data());
   trdPlt = new TThread(tit4, handlePlotter, (void*) 3);  // yMax
   trdPlt->Run();
    
   TString tit3=Form("myFlillerTrd");
   printf("M:Starting Thread %s\n",tit3.Data());
   trdFlr = new TThread(tit3, handleFiller, (void*) fillDuration_s); // Note, it is used to index canvas - do not change it
   trdFlr->Run();


   TString tit5=Form("myCloserTrd");
   printf("M:Starting Thread %s\n",tit5.Data());
   trdClo = new TThread(tit5, handleCloser, (void*) 3);  // yMax
   trdClo->Run();
    
   printf("M: all threads are  dispatched\n");


   printf("M: to change x-axis range execute:  hP->SetAxisRange(3,8); \n  or to quit Root:  .q ");

}
