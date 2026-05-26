#include "DetectiveXHPGe.hh"

DetectiveXHPGe::DetectiveXHPGe(G4String name,
                                G4LogicalVolume *motherVolume,
                                G4int copyNumber,
                                G4RotationMatrix* orientationRot,
                                G4ThreeVector orientationTrans) {

    G4int copyNumberTracker = copyNumber; // copy number incremented for each volume but copyNum is reserved for sensitive volume.

    G4RotationMatrix *volumeRotation = new G4RotationMatrix(); // Creates identity matrix by default
    volumeRotation->isIdentity(); // Checks if this is an identity translation. Returns true if is.
    G4ThreeVector volumeTranslation(0*cm,0*cm,0*cm);


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

    // Setup reflector
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
     * @brief Construct the HPGe disk (JUST the disk)
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

    visualizationHPGe->SetColor(G4Color::Green());
    detectorHPGeLogical->SetVisAttributes(visualizationHPGe);

    new G4PVPlacement(volumeRotation,
                    volumeTranslation,
                    detectorHPGeLogical,
                    "detectorHPGe",
                    motherVolume,
                    0,
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

