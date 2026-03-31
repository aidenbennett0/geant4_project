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
     * Option 1 - Lead box
     */
    if (geometryID == 0) {

        ConstructWorldVolume(0.5*m, 0.5*m, 0.5*m);
        
    }

    if (geometryID == 1) {
        ConstructWorldVolume(0.5*m,0.5*m,0.5*m);

        G4Transform3D orientation = G4Transform3D();
        G4double width = 25*cm;
        G4double length = 25*cm;
        G4double height = 25*cm;
        G4double wallThickness = 0.5*cm;

        shieldConstructionPb = new LeadBoxShield("shieldConstructionPb",
                                                    0,
                                                    logicalWorld,
                                                    orientation,
                                                    width,
                                                    length,
                                                    height,
                                                    wallThickness);

    }

    /** ---DETECTOR SELECTION---
     * 
     * @brief Select which detector to use
     * Additional options will be implemented over time
     * 
     * Option 0 - 3x3 NaI
     */

     if (detectorID == 0) { // Construct 3x3 NaI Cylinder Detector

        // Detector transformation
        detectorRotation = new G4RotationMatrix();
        detectorRotation->rotateX(0*deg);

        detectorConstructionNaI = new Cylinder3x3NaIDetector("detector",
                                                            logicalWorld,
                                                            100,
                                                            detectorRotation,
                                                            detectorTranslation);
    }
    // End the timing of how long it took to close geometry
    auto end = std::chrono::high_resolution_clock::now();

    // Calculate and print duration
    std::chrono::duration<double> elapsed = end - start;
    G4cout << "Time taken to close geometry: " << elapsed.count() << "seconds" << G4endl;

    return physicalWorld;
 }

 /**
  * @brief Constructs the sensitive detector
  */
 void DetectorConstruction::ConstructSDandField() {

    SensitiveDetector* sensitiveDetector = new SensitiveDetector("sensitiveDetector", "hitsCollection");

    if (detectorID == 0) { // NaI sensitive detector
        
        // Set GEB parameters for sensitive detector
        sensitiveDetector->SetGEBParameters(detectorConstructionNaI->GetGEBParameters());

        // Add sensitive detector to sensitive detector manager
        G4SDManager::GetSDMpointer()->AddNewDetector(sensitiveDetector);
        
        // Set logical volume as sensitive volume, method from G4LogicalVolume class
        SetSensitiveDetector(detectorConstructionNaI->GetSDLogicalVolume(), sensitiveDetector);

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

void DetectorConstruction::SetSourceOption(G4int value) {

        sourceID = value;
}

DetectorConstruction::~DetectorConstruction() {}