using namespace std;

#include <TH1.h>
#include "WeventIO.h"
ClassImp(WeventIO)


//========================
//========================
void WeventIO::fillEve(Wevent2011 *eve, int k) {
  
  eve->clear(); // do not forget it or you get stalle events piled up
  // define event ID
  eve->id=10+k; 
  

  WeveVertex  vert;
  WeveEleTrack track;
 
  // we will 2nd vertices with  3 tracks, if eventID%5=0

  vert.clear(); // do it before use

  // define 1st vertex
  vert.z=rnd.Uniform(8.);

  // add 1st track to vertex 1
  track.P=TVector3(k,0,rnd.Uniform(12.)); track.hitSector=20*k;
  vert.eleTrack.push_back(track);

  // add 2nd track to vertex 1
  track.P=TVector3(k+1,rnd.Uniform(5.),0); track.hitSector=20*k+1;
  vert.eleTrack.push_back(track);

  // add vertex 1 to event
  eve->vertex.push_back(vert); //.... store 1st vertex

  if(  eve->id%5) return;

  //.....................
  vert.clear(); // do it before re-use
  // define 2st vertex 
  track.P=TVector3(-k,0,k); track.hitSector=30*k;
  vert.eleTrack.push_back(track);
  track.P=TVector3(-k-1,0,k); track.hitSector=30*k+1;
  vert.eleTrack.push_back(track);
  track.P=TVector3(-k-2,0,k); track.hitSector=30*k+1;
  vert.eleTrack.push_back(track);
  vert.z=300+k;
  eve->vertex.push_back(vert);//.... store 2nd vertex

}



//========================
//========================
void WeventIO::unpackEve(Wevent2011 *eve, TH1F *h){

  printf("\n WeventIO::unpackEve() ID=%d  nVert=%d\n",eve->id, (int)eve->vertex.size());
  for(unsigned int iv=0;iv< eve->vertex.size();iv++) {
    WeveVertex  *vert=&(eve->vertex[iv]);
    h->Fill(vert->z);
    printf("%d-vertex: Z=%f  nTrack=%d\n",iv,vert->z, (int)vert->eleTrack.size());
    for(unsigned int it=0;it< vert->eleTrack.size();it++){
      WeveEleTrack *tr=&(vert->eleTrack[it]);
      printf("   Track  Pxyz=%.1f,%.1f,%.1f \n",tr->P.X(), tr->P.Y(), tr->P.Z());
    }
  }
}
