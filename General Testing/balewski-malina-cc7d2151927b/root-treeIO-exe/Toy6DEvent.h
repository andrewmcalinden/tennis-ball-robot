#ifndef TOY6DEVENT_H
#define TOY6DEVENT_H
/*********************************************************************
 * $Id: $
 * \author Jan Balewski, MIT, 2010
 *********************************************************************
 * Descripion:
 * C-struct encapsulates  synthetic QW event
 *********************************************************************/

enum {mXY=2};
enum {mxP=6, kheliP=0, kheliN=1, mxHeli=2};


typedef struct {
  Int_t heli,id;
  Float_t yield;
  Float_t Bpm[mxP];
} EVENTN;  

#endif

