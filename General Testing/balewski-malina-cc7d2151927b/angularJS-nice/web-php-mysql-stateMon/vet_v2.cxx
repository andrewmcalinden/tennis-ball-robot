// $Id: $
// Descripion: VMevalTool ver2 , allows for stres-test of VM
// Author: Jan Balewski  , PanAlgo, 2013-12
//
#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <assert.h>
#include <math.h>
#include <ctime>
using namespace std;

double *bigArray;
int sizeN=0;

FILE *fpOut=0, *fpInp=0;
int writeBlock=0, readBlock=0;
double writeTotMB=0, readTotMB=0;

double compTot=0; // sums all computation in a.u.

//=========================================
void initRamArray(int sizeMB){
  int sizeB=sizeMB*1024*1024;
  assert(sizeB>0);
  sizeN=sizeB/sizeof(double)-10; // just in case do not use all
  bigArray= (double*)malloc(sizeB);
  printf("bigArray/MB=%d  sizeN=%d*double*1e6  p=%p\n",sizeMB,sizeN/1024/1024,bigArray);
  if(bigArray==NULL) { printf("initRamArray malloc(%d) failed, abort\n",sizeB); exit(1);}

}

//=========================================
double ioRamArray(int iter, int nOps, int nL){
 
  clock_t begin = clock(); // CPU time in usec
  time_t beginWallT; time(& beginWallT); // 1 second accuracy

  //................ compute & RAM access ..........
  for(int k=0;k<nL;k++) { 
    for(int i=0;i<nOps;i++) { // goal: 1ms per internal loop
      int j=random()%sizeN;
      double x=random()*1./RAND_MAX;
      double y=random()*1./RAND_MAX;
      double z=sin(x)*pow(y,1.123);
      bigArray[j]=z;
      j=random()%sizeN;
      bigArray[j]=pow( bigArray[j],2.3);
    }// end-msec-loop

    compTot+=nOps;
    //................ OUTPUT FILE
    if(fpOut) { // write output file
      writeTotMB+=writeBlock/1024./1024.;
      int j=random()%sizeN/2;
      fwrite(bigArray+j, 1, writeBlock, fpOut);
      //  size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream);
    }

    //................ input FILE
    if(fpInp) { // write output file
      readTotMB+=readBlock/1024./1024.;
      int j=random()%sizeN/2;
      int ret=fread(bigArray+j, 1, readBlock, fpInp);
      //printf("xx %f %d  ret=%d\n", readTotMB,readBlock,ret);
       if(ret!= readBlock ) {
	 printf("end of input file, ret=%d, closed\n",ret);
	fclose(fpInp);
	fpInp=0;
      }
    }

  } // end-of-external loop

  clock_t end = clock();
  double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
  time_t endWallT;  time(&endWallT);
  int elapsed_wall_sec = (endWallT - beginWallT); // 1 sec accuracy
  
  printf("%d  pass: %.2f MOps , elapsed(sec) CPU=%.3g  wallTime=%d, write=%.1fMB, read=%.1fMB \n", iter, nOps*nL/1e6,elapsed_secs,elapsed_wall_sec,writeTotMB,readTotMB);
  return elapsed_secs;

}


void argUsage(char  *argv0 , const char *message=NULL);
//---------------------------------------------------------------------
//---------------------------------------------------------------------
//---------------------------------------------------------------------
int  main(int argc, char *argv[]) {
  char  *userName    = getenv("USER");
  const char *writePath="/tmp";

  // variables manipulated at exec time
  int useRAM_MB  = 300;
  int runTime_min = 60;
  int writeFile_MB = -1;
  int writeSpeed_MB2min = 100;
  char  *readFile  = (char *)"none"; 
  char  *coreName  = (char *)"vet-ver2.1"; 
  int    debugMode  = false;
  // working variables
  int    optInd   = 0;
  char   optChar  = 0;  

  static struct option optLong[] = {
    { "debug"      , 0 , &debugMode     , true},
    { "help"       , 0 , 0              , 'h' },
    { "useRAM"   , 1 , 0    , 'R' },
    { "runTime"   , 1 , 0   , 'T' },
    { "writeFile" , 1 , 0 , 'w' },
    { "writeSpeed" , 1 , 0 , 's' },
    { "readFile" , 1 , 0 , 'r' },
    { "coreName" , 1 , 0 , 'c' },
    { 0, 0, 0, 0}
  };


  // arguments and init
  char  * argv0 = strrchr(argv[0],'/');
  argv0 = ( argv0 == NULL )  ? argv[0] : ++argv0 ;
  
  opterr = 0;
  while((optChar = getopt_long(argc,argv,"hdR:T:c:w:s:r:",optLong,&optInd)) != EOF) {
    switch(optChar) {
    case  0  :   break;
    case 'c' : coreName = optarg;    break; 
    case 'r' : readFile = optarg;    break; 
    case 'R' : useRAM_MB  = atoi(optarg);     break; 
    case 'T' : runTime_min  = atoi(optarg);     break; 
    case 'w' : writeFile_MB  = atoi(optarg);     break; 
    case 's' : writeSpeed_MB2min  = atoi(optarg);     break; 
    case 'd' : debugMode= true;         break;

    case 'h' : argUsage(argv0); return(0);         break;
    case '?':   
      if (isprint (optopt))
	fprintf (stderr, "\nUnknown option `-%c'\n\n", optopt);
      else
	fprintf (stderr,"\nUnknown option character `\\x%x'.\n\n",optopt);
    default  : argUsage(argv0,"unknown option");    break;
    };
  }
  
 /* Print any remaining command line arguments (not options).   */
  if (optind < argc)    {
      printf ("\n WARN, non-options ARGV-elements: ");
      while (optind < argc)
	printf ("%s ", argv[optind++]);
      putchar ('\n');
      return -3;
  }

  printf("\n**** Final paramater choice made by user=%s  *** \n",userName);
  printf("Executing  %s  useRAM/MB=%d  runTime/min=%d  coreName='%s' \n",argv0,useRAM_MB,runTime_min,coreName);
  printf(" write: file size=%d MB, speed=%d MB/min; readFile=%s, debug=%d\n",writeFile_MB,writeSpeed_MB2min,readFile,debugMode);

  // set random generator
  srandom(123); 
  int nLoop=1000;
  initRamArray(useRAM_MB);

  ioRamArray(0,1e3,nLoop);// discard the 1st measurement beacuse is it is always slower

  printf(" test RAM I/O +math CPU speed ... \n");
  int nOps_try=5000;

  double sumT=0, nTry=0;
  for(int k=0;k<4;k++) { 
    sumT+= ioRamArray(k,nOps_try,nLoop);
   nTry+=1;
  }
  double avrT=sumT/nTry;

  int nOps_1sec=(int) nOps_try/avrT*.9;   //estimate # of Ops per second @ 100% CPU  

  printf("Estimated # of math ops/msec=%d for CPU, verify ...\n", nOps_1sec);
  nLoop*=10;
  ioRamArray(0,nOps_1sec,nLoop); // run it once to see if the scaling worked as expected

  //................ OUTPUT FILE
  char fileName[1024];  
  if(writeFile_MB>0) {
    sprintf(fileName,"%s/%s_%d.out",writePath,coreName,(int)(random()%1000000));
    writeBlock=(int)writeSpeed_MB2min*1.e6/60./nLoop; // writes 1 blocks/msec
    printf("open write-file =%s=, block=%d byte/msec, verify CPU speed  ...\n",fileName,writeBlock);
    assert( writeBlock <  useRAM_MB *1e6);
    fpOut=fopen(fileName, "wb");
    assert(fpOut);
    ioRamArray(0,nOps_1sec,nLoop); // run it once to see if writeing slows the math-ops loop
  }

  //................ input FILE
  char inputName[1024];  
  if(strstr(readFile,"none")==0) {
    if(strstr(readFile,"new")) {
      sprintf(inputName,"%s/%s_%d.inp",writePath,coreName,(int)(random()%1000000));
      printf("create input file=%s of size=%d MB ...\n", inputName,useRAM_MB);
      fpInp=fopen(inputName, "wb");
      assert(fpInp);
      int wrBlk= useRAM_MB*1024*1024;
      fwrite(bigArray, 1, wrBlk, fpInp);
      fclose(fpInp);
      printf(" done\n");
    }  else { 
      sprintf(inputName,"%s",readFile);
    }
    readBlock=(int)writeSpeed_MB2min*1.e6/60./nLoop; // reads 1 blocks/msec
    printf("open read-file =%s=, block=%d byte/msec,  verify CPU speed  ...\n",inputName,readBlock);
    
    fpInp=fopen(inputName, "rb");
    assert(fpInp);
    readTotMB=0;
    ioRamArray(0,nOps_1sec,nLoop); // run it once to see if writeing slows the math-ops loop
  }

  //..................... do the work ..........
  printf("Start the long loop (goal is %d minutes) \n",runTime_min);
  clock_t beginTot = clock(); // CPU time in usec
  time_t beginWallT; time(& beginWallT); // 1 second accuracy
  compTot=0;
  int k=0;
  while(true) {
    ioRamArray(k++,nOps_1sec,nLoop); // <== HERE do the work 
    clock_t end = clock();
    double elapsed_secs = double(end - beginTot) / CLOCKS_PER_SEC;
    double elapsed_min= elapsed_secs/60.;
    time_t endWallT;  time(&endWallT);
    double elapsed_wall_min = (endWallT - beginWallT)/60.;
    
    printf("  total: minutes: cpu=%.1f wall=%.1f work=%.1f MOps, speed (MOps/min):  CPU=%.1f  wallT=%.1f \n", elapsed_min, elapsed_wall_min, compTot/1e6, compTot/elapsed_min/1e6, compTot/elapsed_wall_min/1e6);


    if(  elapsed_wall_min > runTime_min ) { // do not continue
      printf("#vet-h,job-name,work(totMOps),totCpu(min),totWall(min),fractCpu,work/wallTime,write(MB),read(MB)\n");
      printf("#vet-d,%s, %.1f,%.1f,%.1f, %.2f, %.1f, %.1f,%.1f \n",coreName, compTot/1e6,elapsed_min,elapsed_wall_min, elapsed_min/elapsed_wall_min, compTot/elapsed_wall_min/1e6,writeTotMB, readTotMB);
      break;
    }
    
    if(fpOut && writeTotMB >  writeFile_MB){
      fclose(fpOut);
      writeTotMB=0;
      printf("    ----- re-open write-file =%s=\n",fileName);
      fpOut=fopen(fileName, "wb");
      assert(fpOut);
    }
    
    if(fpInp==0 && strstr(readFile,"none")==0) {
      printf("    ---- re-open input file=%s\n",inputName);
      fpInp=fopen(inputName, "rb");
      assert(fpInp);
    }
    
  }



  return 0; 
} 


//=============================================================
void argUsage(char  *argv0 , const char *message){
  if (message) fprintf(stderr,"%s: %s\n",argv0,message);
  fprintf(stderr,"usage: %s  [OPTIONS]\n",argv0);
  fprintf(stderr," -R | --useRAM [size/MB]    : size of the array, random accces, default 500 MB\n");
  fprintf(stderr," -T | --runTime [minutes] : wall-time duration of this job , default 1 hour\n");
  fprintf(stderr," -w | --writeFile [size/MB] : max output size, default 1GB \n");
  fprintf(stderr," -s | --writeSpeed [MB/min] : max write speed, default 6GB/hour if '-w' is enabled \n");
  fprintf(stderr," -r | --readFile [name] : use 'new' to generate it, 'none' to disable, size=RAM & speed=write\n");
  fprintf(stderr," -c | --coreName [vet-jan]         : for all outputs from this job\n");
  fprintf(stderr," -d | --debug        : set debug mode on\n");
  fprintf(stderr," -h | --help         : this short help\n");
  if(message) exit(-1);
  return;
}


// $Log: $
