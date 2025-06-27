#include "construction.hh"
#include "G4TwoVector.hh"
#include "G4ExtrudedSolid.hh"

DetectorConstruction::DetectorConstruction() {
    
    messenger = new ConstructionMessenger(this);
    detectorSegmentedOGS = new SegmentedOGS();
    
}
DetectorConstruction::Construct() {
    
}