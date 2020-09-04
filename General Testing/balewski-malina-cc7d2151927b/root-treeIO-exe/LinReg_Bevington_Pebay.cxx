#include <assert.h>
#include <math.h>
#include <iostream>
using namespace std;

#include "LinReg_Bevington_Pebay.h"

//=================================================
//=================================================
LinRegBevPeb::LinRegBevPeb() {

}

//=================================================
//=================================================
void LinRegBevPeb::init(){
  printf("Init LinReg dims: nP=%d \n",par_nP);
  mMY=0;
  mMP.ResizeTo(par_nP,1);
  mVPP.ResizeTo(par_nP,par_nP);
  mVPY.ResizeTo(par_nP,1);
  mVY2=0;
  mA.ResizeTo(par_nP,1);

  fGoodEventNumber=0;
 
}

//=================================================
//=================================================
void LinRegBevPeb::print(){
  printf("LinReg dims: nP=%d\n",par_nP);

   cout<<"MP:"; mMP.Print(); cout<<"MY: ="<< mMY<<endl;
  cout<<"VPP:";mVPP.Print();  cout<<"VPY:";mVPY.Print();  cout<<"VY2:="<<mVY2<<endl;
}


//==========================================================
//==========================================================
void LinRegBevPeb::accumulate(double *P, double Y){

  fGoodEventNumber++;
 
  // P-only matrices
  for (int i = 0; i <par_nP; i++) {
    double u=P[i];
    double udel=u-mMP(i,0);
 
    if(fGoodEventNumber<=1) mMP(i,0)=u;
    else mMP(i,0)+=udel/fGoodEventNumber;

    if(fGoodEventNumber<=2)  mVPP(i,i)=0;
    else mVPP(i,i)+=(u-mMP(i,0))*udel; // Note, it uses pre & post incremented means!
    for (int j = i+1; j < par_nP; j++) {// only upper triangle
      double v=P[j];
      double vdel=v-mMP(j,0);

      if(fGoodEventNumber<=1) mVPP(i,j)=0;
      else mVPP(i,j)+=udel*vdel*(fGoodEventNumber-1)/fGoodEventNumber;
    }// end of cov-PP
  } // end of P-only


  // Y-only matrices
  {
    double u=Y;
    double udel=u-mMY;
 
    if(fGoodEventNumber<=1) mMY=u;
    else mMY+=udel/fGoodEventNumber;

    if(fGoodEventNumber<=2)  mVY2=0;
    else mVY2+=(u-mMY)*udel; // Note, it uses pre & post incremented means!
  } // end of Y-only


  // Y-P correlation matrix
  {
    double v=Y;
    double vdel=v-mMY;
    for (int i = 0; i <par_nP; i++) {
      double u=P[i];
      double udel=u-mMP(i,0);
      if(fGoodEventNumber<=1) mVPY(i,0)=0;
      else mVPY(i,0)+=udel*vdel*(fGoodEventNumber-1)/fGoodEventNumber;
    }
  }
}


//==========================================================
//==========================================================
Int_t  LinRegBevPeb::getMeanP(const int i, Double_t &mean ){
   mean=-1e50;
   if(i<0 || i >= par_nP ) return -1;
   if( fGoodEventNumber<1) return -3;
   mean=mMP(i,0);    return 0;
}


//==========================================================
//==========================================================
Int_t  LinRegBevPeb::getMeanY( Double_t &mean ){
   mean=-1e50;
   if( fGoodEventNumber<1) return -3;
   mean=mMY;    return 0;
}


//==========================================================
//==========================================================
Int_t   LinRegBevPeb::getSigmaP(const int i, Double_t &sigma ){
    sigma=-1e50;
   if(i<0 || i >= par_nP ) return -1;
    if( fGoodEventNumber<2) return -3;
    sigma=sqrt(mVPP(i,i)/(fGoodEventNumber-1.));
    return 0;
  }


//==========================================================
//==========================================================
Int_t   LinRegBevPeb::getSigmaY( Double_t &sigma ){
    sigma=-1e50;
    if( fGoodEventNumber<2) return -3;
    sigma=sqrt(mVY2/(fGoodEventNumber-1.));
    return 0;
  }

//==========================================================
//==========================================================
Int_t  LinRegBevPeb::getCovarianceP( int i, int j, Double_t &covar ){
    covar=-1e50;
    if( i>j) { int k=i; i=j; j=k; }//swap i & j
    //... now we need only upper right triangle
     if(i<0 || i >= par_nP ) return -11;
    if( fGoodEventNumber<2) return -14;
    covar=mVPP(i,j)/(fGoodEventNumber-1.);
    return 0;
}

//==========================================================
//==========================================================
Int_t  LinRegBevPeb::getCovariancePY(  int i, Double_t &covar ){
    covar=-1e50;
    //... now we need only upper right triangle
    if(i<0 || i >= par_nP ) return -11;
    if( fGoodEventNumber<2) return -14;
    covar=mVPY(i,0)/(fGoodEventNumber-1.);
    return 0;
}



//==========================================================
//==========================================================
void LinRegBevPeb::printSummaryP(){
  cout << Form("\nLinRegBevPeb::printSummaryP seen good eve=%lld",fGoodEventNumber)<<endl;

  size_t dim=par_nP;
  if(fGoodEventNumber>2) { // print full matrix
    cout << Form("\n         name:             ");
    for (size_t i = 0; i <dim; i++) {
      cout << Form(" %10sP%d "," ",(int)i);
    }
    cout << Form("\n  j                   mean          sig      corelation-matrix ....\n");
    for (size_t i = 0; i <dim; i++) {
      double meanI,sigI;
      assert( getMeanP(i,meanI)==0);
      assert( getSigmaP(i,sigI)==0);

      cout << Form(" %3d %6sP%d:  %+12.4g  %12.4g ",(int)i," ",(int)i,meanI,sigI);
      for (size_t j = 1; j <dim; j++) {
        if( j<=i) { cout << Form("  %12s",". . . ."); continue;}
        double sigJ,cov; assert( getSigmaP(j,sigJ)==0);
        assert( getCovarianceP(i,j,cov)==0);
        double corel=cov/sigI/sigJ;
        
        cout << Form("  %12.3g",corel);
      }
      cout << Form("\n");
    } 
  }
}


//==========================================================
//==========================================================
void LinRegBevPeb::printSummaryY(){
  cout << Form("\nLinRegBevPeb::printSummaryY seen good eve=%lld",fGoodEventNumber)<<endl;

      double meanI,sigI;
      assert( getMeanY(meanI)==0);
      assert( getSigmaY(sigI)==0);
      double err=sigI/sqrt(fGoodEventNumber);
      double nSigErr=meanI/err;
      cout << Form("  Y:  %+12.4g  %12.4g  %8.1f  %12.4g "" ",meanI,err,nSigErr,sigI)<<endl;
}


//==========================================================
//==========================================================
void LinRegBevPeb::printSummaryYP(){
  cout << Form("\nLinRegBevPeb::printSummaryYP seen good eve=%lld",fGoodEventNumber)<<endl;

  if(fGoodEventNumber>2) { // print full matrix
    cout << Form("            i=                         ");
    for (int i = 0; i <par_nP; i++) {
      cout << Form("  %10sP%d"," ",i);
      
      cout << Form("\n      mean          sig          \n");
      
      double meanJ,sigJ;
      assert( getMeanY(meanJ)==0);
      assert( getSigmaY(sigJ)==0);
      
      cout << Form(" Y:  %+12.4g  %12.4g ",meanJ,sigJ);
      
      double sigI,cov; assert( getSigmaP(i,sigI)==0);
      assert( getCovariancePY(i,cov)==0);
      double corel=cov/sigI/sigJ;
      
      cout << Form("  %12.3g",corel);
      cout << Form("\n");
    }
  }
}

//=================================================
//=================================================
void LinRegBevPeb::printCky(){
  //  cout<<"LinReg  Cky:"; mCky.Print();
}


//==========================================================
//==========================================================
void LinRegBevPeb::solve() {
  cout << Form("\n********LinRegBevPeb::solve...invert Rjk")<<endl;
  TMatrixD Rjk;Rjk.ResizeTo(mVPP);
  for (int j = 0; j < par_nP; j++) {
    double Sj; assert( getSigmaP(j,Sj)==0);
    for (int i = 0; i <par_nP; i++) {
       double Sk,Sjk2; assert( getSigmaP(i,Sk)==0);
       assert( getCovarianceP(j,i,Sjk2)==0);
       Rjk(j,i)=Sjk2/Sj/Sk;
     }
   }
  cout<<"new Rjk:"; Rjk.Print();

   TMatrixD invRjk(Rjk); double det;
   //cout<<"0 invRkl:"; invRjk.Print();
   invRjk.Invert(&det);
   cout<<Form("det=%f\n",det); //invRjk.Print();

   /* test
   TMatrixD M; M.ResizeTo(Rjk);//cout<<"0 M:"; M.Print();
   M.Mult(invRjk,Rjk);
   cout<<"check M*invM"; M.Print();
   */

   cout << Form("\n********LinRegBevPeb::solve... alphas ")<<endl;
   TMatrixD Rky;Rky.ResizeTo(mVPY); 
   double Sy; assert( getSigmaY(Sy)==0);
   for (int i = 0; i <par_nP; i++) {
     double Sk,Syk2; assert( getSigmaP(i,Sk)==0);
     assert( getCovariancePY(i,Syk2)==0);
     Rky(i,0)=Syk2/Sy/Sk;
   }
   
   //   cout<<"new Rky:"; Rky.Print();


   TMatrixD Djy; Djy.ResizeTo(Rky);	
   Djy.Mult(invRjk,Rky);
   //   cout<<"Djy:"; Djy.Print();


   assert( getSigmaY(Sy)==0);
   for (int i = 0; i <par_nP; i++) {
       double Sk; assert( getSigmaP(i,Sk)==0);
       mA(i,0)= Djy(i,0)*Sy/Sk;
   }
   
   cout<<"mA:"; mA.Print();

}

