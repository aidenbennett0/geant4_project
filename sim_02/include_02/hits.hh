/**
 * @brief This program tells the file what to do when a particle interacts with a sensitive detector
 * 
 * @brief Used to store hit information. Hit class to store energy deposition, primary/secondary particle 
 * information, and detector ID (copy number)
 */

#ifndef HITS_HH
#define HITS_HH

#include "G4VHit.hh"
#include "G4ThreeVector.hh"
#include "G4Allocator.hh"

class MyHit : public G4VHit {
    public:
        MyHit();

        ~MyHit();
        
};

#endif