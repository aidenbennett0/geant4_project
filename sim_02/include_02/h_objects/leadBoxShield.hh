/**
 * @brief Lead box open on bottom 
 * 
 * @note  NOT its own world volume, use in tandem with world.
 */
#ifndef leadBoxShield_hh
#define leadBoxShield_hh

#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4RotationMatrix.hh"
#include "G4ThreeVector.hh"
#include "G4Transform3D.hh"
#include "G4Box.hh"
#include "G4VisAttributes.hh"
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
#include "G4AssemblyVolume.hh"
#include "G4SubtractionSolid.hh"

#include "materials.hh"

class LeadBoxShield {
public:

    /**
     * @brief Construct a new lead box shield with empty bottom object
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

    // Construct the lead box object
     LeadBoxShield(G4String name,
        G4int copyNumber,
        G4LogicalVolume* motherLogical, 
        G4Transform3D orientation,
        G4double width,
        G4double length,
        G4double height,
        G4double wallThickness);

    // Deconstruct the lead box object
    ~LeadBoxShield();

  private:
 /**
  * @todo move measurements (height, width, length) from construction.cc here
  */
};

#endif