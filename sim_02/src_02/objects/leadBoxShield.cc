#include "leadBoxShield.hh"

/**
 * @brief Construct a new leadbox shield
 * 
 * @param name name of object
 * @param copyNumber copy number of object
 * @param motherLogical logical volume of mother volume
 * @param orientation orientation relative to mother volume
 * @param width width of box
 * @param length length of box
 * @param height height of box
 * @param wallThickness wall thickness of box
 */

 LeadBoxShield::LeadBoxShield(G4String name, 
                                G4int copyNumber,
                                G4LogicalVolume* motherLogical, 
                                G4Transform3D orientation,
                                G4double width,
                                G4double length,
                                G4double height,
                                G4double wallThickness) {
            
    materials materialsInstance;

    // construct solid lead box
    G4VSolid *leadBoxSolid = new G4Box("leadBoxSolid", length/2, height/2, width/2);

    // construct hollow box
    G4VSolid *hollowBoxSolid = new G4Box("hollowBoxSolid", 
                                            length/2-wallThickness,
                                            height/2-wallThickness+1*cm,
                                            width/2-wallThickness);

    // subtract hollow box from solid 
    G4ThreeVector leadBoxTranslate(0*cm,-1*cm,0*cm);
    G4Transform3D leadBoxTransform(G4RotationMatrix(), leadBoxTranslate);
    G4VSolid *leadBoxSub = new G4SubtractionSolid("leadBoxSubSolid",
                                                    leadBoxSolid,
                                                    hollowBoxSolid,
                                                    leadBoxTransform);

    // construct the logical volume
    G4LogicalVolume *leadBoxLogical = new G4LogicalVolume(leadBoxSub,
                                                            materialsInstance.Pb(),
                                                            "leadBoxLogical");

    // construct the physical volume and place
    new G4PVPlacement(orientation,
                        leadBoxLogical,
                        name,
                        motherLogical,
                        0,
                        copyNumber,
                        false);

    G4VisAttributes *leadBoxVis = new G4VisAttributes();
    leadBoxVis->SetColor(G4Color::Gray());
    leadBoxVis->SetForceSolid(true);
    leadBoxLogical->SetVisAttributes(leadBoxVis);
 }

 /**
 * @brief Destroy the Steelbox Shield:: Steelbox Shield object
 * 
 */
LeadBoxShield::~LeadBoxShield() {
    // Destructor implementation if needed
}
