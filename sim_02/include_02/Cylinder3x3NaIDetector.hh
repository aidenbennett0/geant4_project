#ifndef Cylinder3x3NaIDetector_hh
#define Cylinder3x3NaIDetector_hh

#include "construction.hh"

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

class Cylinder3x3NaIDetector {
    public:
        /**
         * @brief Creates a new Cylinder Detector (NaI) object
         * 
         * @param name name of the sensitive volume
         * @param radius radius of detector
         * @param length the full length of the detector
         * @param motherVolume the mother logical volume
         * @param copyNumber copy number for sensitive volume
         * @param orientationRot detector rotation relative to MOTHER volume
         * @param orientationTrans detector tranlsation relative to MOTHER volume
         */

        Cylinder3x3NaIDetector(G4String name,
                                G4LogicalVolume *motherVolume,
                                G4int copyNumber,
                                G4RotationMatrix* orientationRot,
                                G4ThreeVector orientationTrans);
        
        ~Cylinder3x3NaIDetector();

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
         * 
         * @todo Section in Ron's repo about getting Gaussian Energy Broadening Parameters but I wanted to understand it before I implemented it.
         */
        G4ThreeVector GetGEBParameters();

      private:
        /**
         * @todo These measurements have been directly taking from Ron's repo, need to find where to get them myself
         */
        G4double radius = 3.8*cm;
        G4double length = 7.6*cm;
        G4double reflectorThickness = 0.1*mm;
        G4double caseThickness = 0.5*mm; // I assume half-size for shell

        G4LogicalVolume *detectorScintillatorLogicalVolume;
        materials detectorMaterialsInstance;

        /**
         * @todo Another section for the gaussian energy broadening 
         */
        G4ThreeVector GEBparameters = G4ThreeVector(-1.14001e+01, 2.36321e+00 , 5.22111e-05);
};

#endif