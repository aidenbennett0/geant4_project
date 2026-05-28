#include "DetectiveXHPGe.hh"

/**
 * @brief Constructs the HPGe detector
 * 
 * @note All bits about a source box will not be used outside of testing
 */

DetectiveXHPGe::DetectiveXHPGe(G4String name,
                                G4LogicalVolume *motherVolume,
                                G4int copyNumber,
                                G4RotationMatrix* orientationRot,
                                G4ThreeVector orientationTrans) {

    G4int copyNumberTracker = copyNumber; // copy number incremented for each volume but copyNum is reserved for sensitive volume.

    G4RotationMatrix *volumeRotation = new G4RotationMatrix(); // Creates identity matrix by default
    volumeRotation->isIdentity(); // Checks if this is an identity translation. Returns true if is.
    G4ThreeVector volumeTranslation(0*cm,0*cm,0*cm);

    G4ThreeVector sourceBoxTranslation(0, 0, 0); // The translation of the source box relative to the mother volume.
    
    /**
     * @brief Construct the detector casing
     */
    G4VSolid *detectorCasing;
    detectorCasing = new G4Tubs("detectorCasingSolid", 
                                0*cm,            
                                radius+caseThickness+reflectorThickness,
                                length/2+caseThickness,         
                                0,                 
                                2*pi);

    G4LogicalVolume *detectorCasingLogicalVolume;
    detectorCasingLogicalVolume = new G4LogicalVolume(detectorCasing,
                                                        detectorMaterialsInstance.Al(),
                                                        "logicalDetectorAluminumCase");

    G4VisAttributes *detectorVisualization = new G4VisAttributes();
    detectorVisualization->SetForceSolid(true);
    detectorVisualization->SetColor(G4Color::Magenta());
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
     * @brief Construct the detector reflector
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
     * @brief Construct the HPGe detector
     */
    G4VSolid *detectorHPGe;
    detectorHPGe = new G4Tubs("detectorHPGeSolid",
                                0,
                                radius,
                                length/2,
                                0,
                                2*pi);

    
    detectorHPGeLogical = new G4LogicalVolume(detectorHPGe,
                                                    detectorMaterialsInstance.Ge(),
                                                    name);

    G4VisAttributes *visualizationHPGe = new G4VisAttributes();
    visualizationHPGe->SetForceSolid(true);
    //visualizationHPGe->SetForceWireframe(true);

    visualizationHPGe->SetColor(G4Color::White());
    detectorHPGeLogical->SetVisAttributes(visualizationHPGe);

    new G4PVPlacement(volumeRotation,
                    volumeTranslation,
                    detectorHPGeLogical,
                    "detectorHPGe",
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
    //sourceBoxReflectorVis->SetForceWireframe(true);
    sourceBoxReflectorVis->SetForceSolid(true);
    sourceBoxReflectorVis->SetColor(G4Color::White());
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
 * @brief Returns the logical volume of the sensitive volume, to be used by G4RunManager
 *
 * @return G4LogicalVolume*
 */
G4LogicalVolume *DetectiveXHPGe::GetSDLogicalVolume() {

    return detectorHPGeLogical;
}

/**
 * @brief Deconstructs the HPGe disk object
 */
DetectiveXHPGe::~DetectiveXHPGe() {}


/**
 * @brief Return the gaussian energy broadening parameters
 * 
 * @todo fix, this isn't in the header file yet
 *
 * @return G4ThreeVector
 */ 
G4ThreeVector DetectiveXHPGe::GetGEBParameters() {

    return GEBParameters;
}

