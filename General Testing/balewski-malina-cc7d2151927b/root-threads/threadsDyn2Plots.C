/* Example of a simple script creating 2 threads to fill 2 histos
and 3rd thread 'joiner' watch this 2 to signal main when they finished

Plotted  PDF depends on thread ID.

 This script can only be executed via ACliC, first start Root, then enter:  .x threadsh1.C++.
*/

#include "TCanvas.h"
#include "TFrame.h"
#include "TH1F.h"
#include "TRandom.h"
#include "TThread.h"

/* Lock explained

Asynchronous Actions

Different threads can work simultaneously with the same object. Some actions can be dangerous. For example, when two threads create a histogram object, ROOT allocates memory and puts them to the same collection. If it happens at the same time, the results are undetermined. To avoid this problem, the user has to synchronize these actions with:

TThread::Lock()    // Locking the following part of code
...                // Create an object, etc...
TThread::UnLock()  // Unlocking
The code between Lock() and UnLock() will be performed uninterrupted. No other threads can perform actions or access objects/collections while it is being executed. The methods TThread::Lock() and TThread::UnLock() internally use a global TMutex instance for locking.
*/


enum {mxThr=2};

TCanvas *c[mxThr];
TH1F    *hpx[mxThr];
TThread *t[mxThr];
Bool_t finished;

void *handleFiller(void *ptr) {
   long nr = (long) ptr;
   Long64_t nfills = 10000000*(1+nr);
   int upd = 50000;
   TString name=Form("hpx%ld",nr);

   TThread::Lock(); //Static method to lock the main thread mutex.
   //now  Create an object, w/o worry of conflict 
   hpx[nr] = new TH1F(name,Form("nr%ld distribution",nr),100,-4,4);
   c[nr]->cd();
   hpx[nr]->Draw();
   printf("THR: %ld , created histo & draw, end mutex-lock\n",nr);
   TThread::UnLock();


   for (Int_t i = 0; i < nfills; i++) {
     Float_t px;

     if(nr==0) // PDF depends on thread ID
       px=gRandom->Gaus();
     else
       px=gRandom->Uniform(2.);


     hpx[nr]->Fill(px);
     
     if (i && (i%upd) == 0) { // tag Canvas for redraw
       if (c[nr]) c[nr]->Modified();
       gSystem->Sleep(10); // mSec
     }
   }

   // update again at the end of filling
   if (c[nr]) c[nr]->Modified();
   return 0;
}

//================================
//================================
void *handleJoiner(void *ptr) {
  int val=(int) ptr;
  printf("J:start inp=%d\n",val);
  t[0]->Join(); // wait untill thr0 is cancelled
  printf("J:pass t0\n");
  TThread::Ps();
  
  t[1]->Join();
  printf("J:pass t1\n");
  TThread::Ps();
  
  //printf("J:end\n");
  finished = kTRUE; // signals to main all threads cancelled

  return 0;
}

//================================
//================================
void killMyThr(Int_t id) {
  printf(" kill the thread =%d matching the canvas being closed\n",id); 
  t[id]->Kill();
  // and set the canvas pointer to 0
  c[id] = 0;
}

//================================
//================================
//      M A I N  
//================================
//================================
void threadsDyn2Plots()
{
#ifdef __CINT__
   printf("This script can only be executed via ACliC: .x threadsDyn2Plots.C++\n");
   return;
#endif

   memset(c,0,sizeof(c)); // flag indicating which thread has canvas constructed
   gRandom->SetSeed();
   finished = kFALSE;
   //gDebug = 1; // prints what is load to Root


   printf("M: draw both canvas\n");
   for(int it=0;it<mxThr; it++ ) {
     TString tit1=Form("c%d",it);
     TString tit2=Form("Dynamic Filling Example thr%d",it);
     c[it] = new TCanvas(tit1,tit2,100+410*it,20,400,300);
     c[it]->GetFrame()->SetBorderMode(-1);
     
     // connect to the Closed() signal to kill thread when a canvas is closed
     TString txcond=Form("killMyThr(Int_t=%d)",it);
     c[it]->Connect("Closed()", 0, 0, txcond);

     TString tit3=Form("myThr%d",it);
     printf("M:Starting Thread %s\n",tit3.Data());
     t[it] = new TThread(tit3, handleFiller, (void*) it); // Note, it is used to index canvas - do not change it
     t[it]->Run();

   }
 

   printf("M:Starting  joiner-thread needed to terminated other threads\n");
   TThread *tj = new TThread("myJoinThr", handleJoiner, (void*) 55);
   tj->Run();

   TThread::Ps();

   // main stays in infinite loop untill   joiner thread reports all threds are cancelled

   while (!finished) {
     for (int i = 0; i < mxThr; i++) {
       if (c[i] && c[i]->IsModified()) {
	 //printf("M:Update canvas %d\n", i);
	 c[i]->Update();
       }
     }
     gSystem->Sleep(100);
     gSystem->ProcessEvents();
   }

   printf("M: end at last\n");
   tj->Join(); // terminate joiner thread
   TThread::Ps(); // verify all threads 

   delete t[0];
   delete t[1];
   delete tj;

   printf("M: all threads are terminated, quit Root w/ .q\n");
}
