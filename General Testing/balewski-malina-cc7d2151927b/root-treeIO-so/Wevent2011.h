// $Id: Wevent2011.h,v 1.2 2011/02/25 06:03:56 stevens4 Exp $
//
//*-- Author : Jan Balewski, MIT
#ifndef W_EVENT_2011_HH
#define W_EVENT_2011_HH

#include <TObject.h>
#include <TVector3.h>

//---------------
class WeveEleTrack  : public TObject{ // electron track info
 public:
  TVector3 P; // primary momentum vector
  int hitSector;

  WeveEleTrack() { clear();}
  
  void clear() {
    P=TVector3(0,0,0);
    hitSector=-888;    
  } 
  
  void print( int flag=0){
    printf("   Track  Pxyz=%.1f,%.1f,%.1f  PT=%.1f  hitSect=%d\n",P.X(), P.Y(), P.Z(),P.Pt(), hitSector);
  }
  
 private:
 protected:
  ClassDef(WeveEleTrack,1);

};


//---------------
//---------------
//---------------
class WeveVertex  : public TObject{ // info about vertex
 public:
  float z; // cm
  std::vector <WeveEleTrack> eleTrack;

  void clear() {
    z=-999; 
    eleTrack.clear(); 
  }
  
  void print( int flag=0){
    printf(" Vertex Z=%.1f cm  nTrack=%d\n",z, (int)eleTrack.size());
    for(unsigned int i=0;i< eleTrack.size();i++) 
      eleTrack[i].print();
  }

 private:
 protected:
  ClassDef(WeveVertex,1);
  
};

//---------------
class Wevent2011 : public TObject {
 public:
  // .....variables ....
  Int_t id; 
  std::vector <WeveVertex> vertex;
  // .... methods ....

  Wevent2011(){};
  
  void clear() { 
    id=-55;
    vertex.clear();
  }
  
  void print(int flag=0) {
    printf("\nprint W2011event:  ID=%d  nVert=%d\n",id, (int)vertex.size());
    for(unsigned int i=0;i< vertex.size();i++) vertex[i].print(flag);    
  }// end of PRINT


  
 private:
 protected:

  ClassDef(Wevent2011,1)

};

#endif


// $Log: Wevent2011.h,v $
//
