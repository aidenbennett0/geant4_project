#ifndef DetectiveXHPGe_hh
#define DetectiveXHPGe_hh

#include "G4VUserDetectorConstruction.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"
#include "G4VisAttributes.hh"
#include "G4AssemblyVolume.hh"
#include "G4Tubs.hh"
#include "materials.hh"
#include "G4RotationMatrix.hh"
#include "G4ThreeVector.hh"
#include "G4AssemblyVolume.hh"
#include "G4Transform3D.hh"
#include "G4VSolid.hh"
#include "G4SubtractionSolid.hh"
#include "G4Box.hh"

class DetectiveXHPGe {
    public:
/**
         * @brief Creates a new HPGe Detector  object
         * 
         * @param name name of the sensitive volume
         * @param radius radius of detector
         * @param length the full length of the detector
         * @param motherVolume the mother logical volume
         * @param copyNumber copy number for sensitive volume
         * @param orientationRot detector rotation relative to MOTHER volume
         * @param orientationTrans detector tranlsation relative to MOTHER volume
         */

        DetectiveXHPGe(G4String name,
                        G4LogicalVolume *motherVolume,
                        G4int copyNumber,
                        G4RotationMatrix* orientationRot,
                        G4ThreeVector orientationTrans);
        
        ~DetectiveXHPGe();

        /**
         * @brief Returns the logical volume of the sensitive volume
         * @return *G4LogicalVolume
         */
        G4LogicalVolume *GetSDLogicalVolume();

                /**
         * @brief Returns a G4ThreeVector containing the gaussian energy broadening parameters
         * These values are used within the MySensitiveDetector class for creating a spectrum based on measured values.
         * 
         * @return G4ThreeVector
         */
        G4ThreeVector GetGEBParameters();

    private:
        /**
         * 
         */
        G4double radius = 32.5*mm;
        G4double length = 50*mm;
        

        G4LogicalVolume *detectorHPGeLogical;
        materials detectorMaterialsInstance;

        G4ThreeVector GEBParameters = G4ThreeVector(-1.14001e+01, 2.36321e+00 , 5.22111e-05);

};

#endif