#ifndef CONSTRUCTION_HH
#define CONSTRUCTION_HH

#include <chrono>

#include "G4VUserDetectorConstruction.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4PVPlacement.hh"
#include "G4NistManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4GenericMessenger.hh"
#include "G4Tubs.hh"
#include "G4OpticalSurface.hh"
#include "G4LogicalSkinSurface.hh"

// Detector constructions
#include "Cylinder3x3NaIDetector.hh"

// Sensitive detector and materials
#include "sensitivedetector.hh"
#include "materials.hh"

// Messenger constructions
#include "constructionMessenger.hh"

class ConstructionMessenger;

class DetectorConstruction : public G4VUserDetectorConstruction
{
    public:
        DetectorConstruction();
        ~DetectorConstruction();

        virtual G4VPhysicalVolume *Construct();

        /**
         * @brief Set the Geometry option
         */
        void SetGeometryOption(G4int value);

        /**
         * @brief Set the Detector option
         */
        void SetDetectorOption(G4int value);


    private:        
        /**
         * @brief Virtual function. Setup of the world volume, a cuboid. 
         * Provide desired half-length for x, y, and z.
         * 
         * @param sizeX half-length in x-direction
         * @param sizeY half-length in y-direction
         * @param sizeZ half-length in z-direction
         */
        void ConstructWorldVolume(double sizeX, double sizeY, double sizeZ);

        /**
         * @brief Setup and construction of sensitive detectors
         */
        virtual void ConstructSDandField();

        // Used for geometry options selection
        G4int geometryID = 0.;
        G4int detectorID = 0.;

        // Detector translation
        G4RotationMatrix* detectorRotation;
        G4ThreeVector detectorTranslation;

        // World volume objects
        G4Box* solidWorld;
        G4LogicalVolume *logicalWorld;
        G4VPhysicalVolume *physicalWorld;

        materials materialInstance;

        ConstructionMessenger *messenger;

        Cylinder3x3NaIDetector *detectorConstructionNaI;
};

#endif