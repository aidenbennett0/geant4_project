#include "Cylinder3x3NaIDetector.hh"

Cylinder3x3NaIDetector::Cylinder3x3NaIDetector(G4String name,
                                               G4LogicalVolume *motherVolume,
                                               G4int copyNumber,
                                               G4RotationMatrix* orientationRot,
                                               G4ThreeVector orientationTrans) {

    G4int copyNumberTracker = copyNumber; // copy number incremented for each volume but copyNum is reserved for sensitive volume.

    G4RotationMatrix *volumeRotation = new G4RotationMatrix(); // Creates an identity matrix by default
    volumeRotation->isIdentity();  // Checks if this is identity translation (meaning no rotation and no translation, essentially it does nothing, aka default state). Returns true if is default.
    G4ThreeVector volumeTranslation(0*cm, 0*cm, 0*cm);

    G4ThreeVector sourceBoxTranslation(0, 0, (length/2 + boxZ/2)); // The translation of the source box relative to the mother volume (in mm because the variables are passed as such by G4)

    /**
     * @brief Construct the detector casing
     */
    G4VSolid *detectorCasing;
    detectorCasing = new G4Tubs("detectorCasing",
                                0*cm,
                                radius+caseThickness+reflectorThickness,
                                length/2+caseThickness,
                                0,
                                2*pi);

    G4LogicalVolume *detectorCasingLogicalVolume;
    detectorCasingLogicalVolume = new G4LogicalVolume(detectorCasing, 
                                                      detectorMaterialsInstance.Al(),
                                                      "detectorCasingLogicalVolume");

    G4VisAttributes *detectorVisualization = new G4VisAttributes();
    //detectorVisualization->SetForceWireframe(true);
    detectorVisualization->SetForceSolid(true);
    detectorVisualization->SetColor(G4Color::Gray());
    detectorCasingLogicalVolume->SetVisAttributes(detectorVisualization);

    new G4PVPlacement(orientationRot, 
                      orientationTrans, 
                      detectorCasingLogicalVolume, 
                      "detectorCase", 
                      motherVolume, 
                      0,
                      copyNumberTracker++,
                      false);

    /**
     * @brief Set up the reflector for the detector casing
     */
    G4VSolid *detectorReflector;
    detectorReflector = new G4Tubs("detectorReflectorSolid",
                                    0*cm,
                                    radius+reflectorThickness,
                                    length/2,
                                    0,
                                    2*pi);

    G4LogicalVolume *detectorReflectorLogical;
    detectorReflectorLogical = new G4LogicalVolume(detectorReflector, 
                                                   detectorMaterialsInstance.Teflon(),
                                                   "detectorReflectorLogical");
    
    G4VisAttributes *reflectorVisualization = new G4VisAttributes();
    //reflectorVisualization->SetForceWireframe(true);
    reflectorVisualization->SetForceSolid(true);
    reflectorVisualization->SetColor(G4Color::Blue());
    detectorReflectorLogical->SetVisAttributes(reflectorVisualization);

    new G4PVPlacement(volumeRotation,
                      volumeTranslation,
                      detectorReflectorLogical,
                      "detectorReflector",
                      detectorCasingLogicalVolume,
                      0,
                      copyNumberTracker++,
                      false);

    /**
     * @brief Construct the NaI detector
     */
    G4VSolid *detectorScintillator;
    detectorScintillator = new G4Tubs("detectorScintillatorSolid",
                                      0,
                                      (radius-0.001),
                                      length/2,
                                      0,
                                      2*pi);
    
    detectorScintillatorLogicalVolume = new G4LogicalVolume(detectorScintillator,
                                                            detectorMaterialsInstance.NaI(),
                                                            name);

    G4VisAttributes *scintillatorVisualization = new G4VisAttributes();
    //scintillatorVisualization->SetForceWireframe(true);
    scintillatorVisualization->SetForceSolid(true);
    scintillatorVisualization->SetColor(G4Color::White());
    detectorScintillatorLogicalVolume->SetVisAttributes(scintillatorVisualization);

    new G4PVPlacement(volumeRotation,
                      volumeTranslation,
                      detectorScintillatorLogicalVolume,
                      "detectorScintillator",
                      detectorReflectorLogical,
                      0,
                      copyNumber,
                      false);

    /**
     * @brief Construct the box to surround the particle source to prevent leak
     */
    G4VSolid *sourceBox;
    sourceBox = new G4Box("particleSourceBox", 
                                  boxX, 
                                  boxY, 
                                  boxZ);

    
    /**
     * @brief Construct the reflector for the particle source box
     */
    G4VSolid *sourceBoxReflector;
    sourceBoxReflector = new G4Box("sourceBoxReflector",
                                   boxX+sourceReflectorThickness, 
                                   boxY+sourceReflectorThickness, 
                                   boxZ+sourceReflectorThickness);

    G4SubtractionSolid* sourceBoxSubtraction = new G4SubtractionSolid("sourceBoxSubtraction", sourceBoxReflector, sourceBox);

    G4LogicalVolume *sourceBoxReflectorLogical;
    sourceBoxReflectorLogical = new G4LogicalVolume(sourceBoxSubtraction, detectorMaterialsInstance.Teflon(), "sourceBoxReflectorLogical");

    G4VisAttributes* sourceBoxReflectorVis = new G4VisAttributes();
    sourceBoxReflectorVis->SetForceWireframe(true);
    //sourceBoxReflectorVis->SetForceSolid(true);
    sourceBoxReflectorVis->SetColor(G4Color::Blue());
    sourceBoxReflectorLogical->SetVisAttributes(sourceBoxReflectorVis);

    new G4PVPlacement(volumeRotation,
                      sourceBoxTranslation,
                      sourceBoxReflectorLogical,
                      "sourceBoxReflector",
                      motherVolume,
                      false,
                      copyNumber,
                      false);

}

/**
 * @brief Returns the logical volume of the sensitive volume. To be used by the G4RunManager
 * 
 * @return G4LogicalVolume*
 */
G4LogicalVolume *Cylinder3x3NaIDetector::GetSDLogicalVolume() {

    return detectorScintillatorLogicalVolume;

}

/**
 * @brief Deconstructs the Cylinder3x3NaIDetector object
 */
Cylinder3x3NaIDetector::~Cylinder3x3NaIDetector() {}

/**
 * @brief Return the gaussian energy broadening parameters
 * 
 * @return G4ThreeVector
 */
G4ThreeVector Cylinder3x3NaIDetector::GetGEBParameters() {

    return GEBParameters;  
}


