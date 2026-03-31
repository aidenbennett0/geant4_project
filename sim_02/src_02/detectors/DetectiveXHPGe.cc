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

    /**
     * @brief Construct the HPGe disk (JUST the disk)
     */
    G4VSolid *diskHPGe;
    diskHPGe = new G4Tubs("diskHPGeSolid",
                                0,
                                radius,
                                length/2,
                                0,
                                2*pi);

    diskHPGeLogical = new G4LogicalVolume(diskHPGe,
                                                    detectorMaterialsInstance.Ge(),
                                                    name);

    G4VisAttributes *visualizationHPGe = new G4VisAttributes();
    visualizationHPGe->SetForceSolid(true);
    visualizationHPGe->SetColor(G4Color::White());
    diskHPGeLogical->SetVisAttributes(visualizationHPGe);

    new G4PVPlacement(volumeRotation,
                    volumeTranslation,
                    diskHPGeLogical,
                    "diskHPGe",
                    diskHPGeLogical,
                    0,
                    copyNumber,
                    false);

    }

/**
 * @brief Returns the logical volume of th sensitive volume, to be used by G4RunManager
 *
 * @return G4LogicalVolume*
 */
G4LogicalVolume *DetectiveXHPGe::GetSDLogicalVolume() {

    return diskHPGeLogical;
}

/**
 * @brief Deconstructs the HPGe disk object
 */
DetectiveXHPGe::~DetectiveXHPGe() {}


/**
 * @brief Return the gaussian energy broadening parameters
 * 
 * @todo fix
 *
 * @return G4ThreeVector
 
G4ThreeVector Cylinder3x3NaIDetector::GetGEBParameters() {

    return GEBParameters;
}
    */
