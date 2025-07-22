/**
 * @brief Inherits from the G4VSensitiveDetector class. This holds data collected during hits within sensitive detector.
 */

#include "sensitivedetector.hh"

SensitiveDetector::SensitiveDetector(const G4String& name, const G4String& hitsCollectionName) : G4VSensitiveDetector(name) { // inherits the G4Sensitive volume
   
    collectionName.insert(hitsCollectionName);
    fTotalEnergyDeposited = 0.;

}

/**
 * @attention take extra looks at this section
 */
void SensitiveDetector::Initialize(G4HCofThisEvent* /*hce*/) {

    fHitsCollection = new G4THitsCollection<MyHit>(SensitiveDetectorName, collectionName[0]);

    if(fHCID < 0) {
        fHCID = G4SDManager::GetSDMpointer()->GetCollectionID(fHitsCollection);
    }

}

// aStep - objecty of each step
// ROhist - will be given only if a Readout geometry is defined to this
G4bool SensitiveDetector::ProcessHits(G4Step *aStep, G4TouchableHistory*) {

    // Get the total energy deposited
    G4double energyDeposition = aStep->GetTotalEnergyDeposit();

    // Get the detector ID i.e. the sensitive volume copy number
    G4int detectorID = aStep->GetPreStepPoint()->GetTouchableHandle()->GetCopyNumber();

    if (energyDeposition == 0.) { return false; }

    // Create a new hit and set energy deposition
    MyHit *newHit = new MyHit;
    newHit->SetEdep(energyDeposition);
    newHit->SetDetectorID(detectorID);

    // Check if the particle is a primary or secondary particle
    G4Track* track = aStep->GetTrack();
    if (track->GetParentID() == 0) // primary particle
    { 
        newHit->SetPrimaryParticle(true);
    }
    else 
    {
        newHit->SetPrimaryParticle(false);
    }

    // Adds the hit to the hit collection
    fHitsCollection->insert(newHit);

    return true;

}

void SensitiveDetector::EndOfEvent(G4HCofThisEvent* hce) {

    G4AnalysisManager* man = G4AnalysisManager::Instance();

    // This is commented out in case eventID is wanted in the future
    // G4int evt = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();

    G4double totalEdepPrimary = 0.;
    G4double totalEdepSecondary = 0.;
    G4double totalEdepAllHits = 0.;

    G4int detectorID = -1;

    /**
     * @attention
     */
    // Sum the total energy deposition from all hits in collection
    for (G4int i = 0; i < fHitsCollection->entries(); ++i) {

        MyHit* hit = (*fHitsCollection)[i];

        // Get the detector ID from the first entry
        if (i == 0) {
            detectorID = hit->GetDetectorID();
        }

        if (hit->IsPrimaryParticle()) {
            totalEdepPrimary += hit->GetEdep()/keV;
        }
        else {
            totalEdepSecondary += hit->GetEdep()/keV;
        }

        totalEdepAllHits += hit->GetEdep()/keV;

    }

    // Add the hit collection to the event
    hce->AddHitsCollection(fHCID, fHitsCollection);

    G4double totalEdep = totalEdepPrimary + totalEdepSecondary;

    /**
     * @brief GEB setup
     * 
     * @attention
     * 
     * @note FWHM - full width at half maximum
     */
    G4double GEBFWHM = a + b*sqrt(totalEdep+c*pow(totalEdep,2)); // Apply detector GEB parameters
    G4double GEBSigma = GEBFWHM/2.35482; // Convert from FWHM to Sigma
    G4double totalEdepGEB = G4RandGauss::shoot(totalEdep,GEBSigma);

    G4int numEntries = fHitsCollection->entries();
    
    /**
     * @brief Fill the ROOT tree with deposition data
     * 
     * Sets threshold and does not record any events below it
     */
    G4double lowEnergyThreshold = 10;

    

    G4cout << "Entries:" << numEntries << G4endl;
    G4cout << "TotalEdepPrimary: " << totalEdepPrimary << G4endl;
    G4cout << "TotalEdepSecondary: " << totalEdepSecondary << G4endl;
    G4cout << "DetectorID: " << detectorID << G4endl;
    G4cout << "TotalEdepAllHits: " << totalEdepAllHits << G4endl;
    G4cout << "TotalEdepGEB: " << totalEdepGEB << G4endl;

    if (totalEdep >= lowEnergyThreshold && totalEdepGEB >= lowEnergyThreshold) {
        man->FillNtupleIColumn(0, 0, numEntries); // Number of entries
        man->FillNtupleDColumn(0, 1, totalEdepPrimary);           // Primary particle deposition
        man->FillNtupleDColumn(0, 2, totalEdepSecondary);         //Secondary particle deposition
        man->FillNtupleIColumn(0, 3, detectorID);                 // Detector ID
        man->FillNtupleDColumn(0, 4, totalEdepAllHits);           //Energy deposition for each event
        man->FillNtupleDColumn(0, 5, totalEdepGEB);               // GEB-applied energy deposition
        man->AddNtupleRow(0); // Add the next row inside the ntuple
    }
}

    void SensitiveDetector::SetGEBParameters(G4ThreeVector parameters) {
        a = parameters.getX();
        b = parameters.getY();
        c = parameters.getZ();

    }


SensitiveDetector::~SensitiveDetector() 
{
    // delete fHitsCollection;
}