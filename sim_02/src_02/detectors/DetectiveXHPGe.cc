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
    
                                                }