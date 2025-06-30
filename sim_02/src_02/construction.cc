#include "G4TwoVector.hh"
#include "G4ExtrudedSolid.hh"

#include "construction.hh"

DetectorConstruction::DetectorConstruction() {
    
    messenger = new ConstructionMessenger(this);
    
}
