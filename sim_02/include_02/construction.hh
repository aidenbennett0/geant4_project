#ifndef CONSTRUCTION_HH
#define CONSTRUCTION_HH

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

#include "constructionMessenger.hh"
#include "materials.hh"

class ConstructionMessenger;

class DetectorConstruction : public G4VUserDetectorConstruction
{
    public:
        DetectorConstruction();
        ~DetectorConstruction();

        G4LogicalVolume *GetScoringVolume() const { return fScoringVolume; }

        virtual G4VPhysicalVolume *Construct();

        void SetDetectorPosition(G4ThreeVector value);

    private:        
        void ConstructWorldVolume(double sizeX, double sizeY, double sizeZ);

        virtual void ConstructSDandField();

        G4RotationMatrix* detectorRotation;
        G4ThreeVector* detectorTranslation;

        G4Box* solidWorld;
        G4LogicalVolume *logicWorld;
        G4VPhysicalVolume *physicalWorld;

        materials materialInstance;

        ConstructionMessenger *messenger;

        3x3NaICylinderDetector *detectorConstructionNaI;
};

#endif