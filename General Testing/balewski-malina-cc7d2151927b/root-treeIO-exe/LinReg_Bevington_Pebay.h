#ifndef LINREGBEVPEB_h
#define LINREGBEVPEB_h

#include <TMatrixD.h>

//-----------------------------------------
class LinRegBevPeb {
  int  par_nP; // number of input independent variables
 
 private:

  Long64_t fGoodEventNumber;    ///< accumulated so far

  TMatrixD mMP;   ///< mean values
  double mMY;
  TMatrixD mVPP, mVPY; ///< variances
  double  mVY2;

  TMatrixD mA;  ///< found alphas from the data

 public:
  /// Default constructor
  LinRegBevPeb();
  
  /// Destructor
  virtual ~LinRegBevPeb(){};

  /// processing single events
  void accumulate(double *P, double Y);
  void solve();
  double Alpha(int ip){ return mA(ip,0);}

  // after last event
  void printSummaryP();
  void printSummaryY();
  void printSummaryYP();
  void printCky();

  void print();
  void init();
  void setDims(int a){ par_nP=a;}

  /// Get mean value of a variable, returns error code
  Int_t getMeanP(const int i, Double_t &mean );
  Int_t getMeanY( Double_t &mean );

  /// Get mean value of a variable, returns error code
  Int_t getSigmaP(const int i, Double_t &sigma );
  Int_t getSigmaY( Double_t &sigma );

  /// Get mean value of a variable, returns error code
  Int_t getCovarianceP( int i, int j, Double_t &covar );
  Int_t getCovariancePY(  int i, Double_t &covar );

  /// \brief Output stream operator
  friend std::ostream& operator<< (std::ostream& stream, const LinRegBevPeb& h);

};

/// Output stream operator
inline std::ostream& operator<< (std::ostream& stream, const LinRegBevPeb& h) {
  stream << Form("LinRegBevPeb::<< ");
  //  stream << Form("  tag correlation>%.3f ", h.par_highCorr);
  return stream;
}



#endif
