/**
 * @brief Inherits from the G4VSensitiveDetector class. This holds data collected during hits within sensitive detector.
 */

#include "sensitivedetector.hh"

SensitiveDetector::SensitiveDetector(const G4String& name, const G4String& hitsCollectionName) : G4VSensitiveDetector(name) // inherits the G4Sensitive volume 
{
    collectionName.insert(hitsCollectionName);
    fTotalEnergyDeposited = 0.;
}

/**
 * @attention take extra looks at this section
 */
void SensitiveDetector::Initialize(G4HCofThisEvent* /*hce*/)
{
    fHitsCollection = new G4THitsCollection<MyHit>(SensitiveDetectorName, collectionName[0]);

    if(fHCID < 0) {
        fHCID = G4SDManager::GetSDMpointer()->GetCollectionID(fHitsCollection);
    }

}

// aStep - objecty of each step
// ROhist - will be given only if a Readout geometry is defined to this
G4bool SensitiveDetector::ProcessHits(G4Step *aStep, G4TouchableHistory*)
{
    // Get the total energy deposited
    G4double energyDeposition = aStep->GetTotalEnergyDeposit();

    // Get the detector ID i.e. the sensitive volume copy number
    G4int detectorID = aStep->GetPreStepPoint()->GetTouchableHandle()->GetCopyNumber();

    if (energyDeposition == 0.) { return false; }

    // Create a new hit and set energy deposition
    MyHit *newHit = new MyHit;
    newHit->SetEdep(energyDeposition);


}

SensitiveDetector::~SensitiveDetector() 
{}