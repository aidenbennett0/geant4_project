#include "G4TwoVector.hh"
#include "G4ExtrudedSolid.hh"

#include "construction.hh"

DetectorConstruction::DetectorConstruction() {
    
    messenger = new ConstructionMessenger(this);
    
}

/**
 * @brief This method contains the actual physical construction of simulation geometries. This is invoked by G4RunManager::InitializeGeometry()
 * 
 * @return G4VPhysicalVolume*
 */
 G4VPhysicalVolume *DetectorConstruction::Construct() {

    // Begin timing how long geometry takes to construct
    auto start = std::chrono::high_resolution_clock::now();

    /** ---SOURCE GEOMETRY SELECTION---
     * 
     * @brief Select which geometry should be used for construction of source
     * Additional options will be implemented over time
     * 
     * @todo Fill out more
     * 
     * Option 0 - Left empty for custom user source construction
     */
    if (geometryID == 0) {

        ConstructWorldVolume(0.5*m, 0.5*m, 0.5*m);
        
    }

    /** ---DETECTOR SELECTION---
     * 
     * @brief Select which detector to use
     * Additional options will be implemented over time
     * 
     * @todo Fill out more
     * 
     * Option 0 - 3x3 NaI
     */

     if (detectorID == 0) { // Construct 3x3 NaI Cylinder Detector

     }

 }

 /**
  * @brief Constructs the sensitive detector
  */
 void DetectorConstruction::ConstructSDandField() {

    SensitiveDetector* sensitiveDetector = new SensitiveDetector("sensitiveDetector", "hitsCollection");

    if (detectorID == 0) { // NaI sensitive detector

        
    }
}

 /**
  * @brief Constructs the world volume
  */
void DetectorConstruction::ConstructWorldVolume(double sizeX, double sizeY, double sizeZ) {

    solidWorld = new G4Box("solidWorld", sizeX, sizeY, sizeZ);

    logicalWorld = new G4LogicalVolume(solidWorld, materialInstance.WorldAir(), "logicalWorldVolume");

    physicalWorld = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicalWorld, "physicalWorld", 0, false, 0, true);

}

void DetectorConstruction::SetGeometryOption(G4int value) {

        geometryID = value;
}

void DetectorConstruction::SetDetectorOption(G4int value) {

        detectorID = value;
}

DetectorConstruction::~DetectorConstruction() {
    
    messenger = new ConstructionMessenger(this);
    
}