/*********************************************************************
 * $Id: $
 * \author Jan Balewski, MIT, 2010
 *********************************************************************
 * Descripion:
 * Operations on Wevent2011
 *********************************************************************/

#include <assert.h>

#include "TRandom3.h"
#include "Wevent2011.h"

class TH1F;
class WeventIO : public TObject{
 private:
  TRandom3 rnd;
 public:
  WeventIO(){ rnd.SetSeed(123);}
  ~WeventIO(){}
  void fillEve(Wevent2011 *eve, int k);
  void unpackEve(Wevent2011 *eve, TH1F *h);
  ClassDef(WeventIO,1) 
};

