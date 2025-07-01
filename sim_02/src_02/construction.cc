#include "G4TwoVector.hh"
#include "G4ExtrudedSolid.hh"

#include "construction.hh"

DetectorConstruction::DetectorConstruction() {
    
    messenger = new ConstructionMessenger(this);
    
}

void DetectorConstruction::SetGeometryOption(G4int value) {

        geometryID = value;
}

void DetectorConstruction::SetDetectorOption(G4int value) {

        detectorID = value;
}

void DetectorConstruction::ConstructSDandField() {

    SensitiveDetector* sensitiveDetector = new SensitiveDetector("sensitiveDetector", "hitsCollection");
}