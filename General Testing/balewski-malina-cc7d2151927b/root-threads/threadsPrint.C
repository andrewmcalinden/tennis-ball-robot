//+ Example of a simple script creating 2 threads.
// This script can only be executed via ACliC: .x threads.C++.
//Author: Victor Perevovchikov
   
#include "TThread.h"
#include "TRandom.h"
//#include <Riostream.h>

void *handle(void *ptr) {
   long nr = (long) ptr;
   printf("THR:Starting Thread input= %ld \n",nr);
 
   for (int i = 0; i < 6; i++) {
     float del=gRandom->Uniform();
     TThread::Printf("Here I am loop index: %d , thread: %ld", i, nr);
     gSystem->Sleep(2000*del); // msec
   }
   return 0;
}


//=================  M A I N ===============
void threadsPrint()
{
#ifdef __CINT__
   printf("This script can only be executed via ACliC: .x threadsPrint.C++\n");
   return;
#endif
   gRandom->SetSeed();
   // gDebug = 1;  // prints what is load to Root

   printf("M: Starting Thread 1\n");
   TThread *hand1 = new TThread("hand1", handle, (void*) 111);
   hand1->Run();
   printf("M:Starting Thread 2\n");
   TThread *hand2 = new TThread("hand2", handle, (void*) 2222);
   hand2->Run();

   printf("M: do PS after start of all threads\n");
   TThread::Ps();


   printf("M: waits for hand1 to join ...\n");
   hand1->Join();
   TThread::Ps();

   printf("M: waits for hand2 to join ...\n");
   hand2->Join();
   TThread::Ps();


   printf("M: end, quit Root w/ .q\n");
   
}
