#include "detector.hh"

MySensitiveDetector::MySensitiveDetector(G4String name) : G4VSensitiveDetector(name)
{}

MySensitiveDetector::~MySensitiveDetector()
{}

G4bool MySensitiveDetector::ProcessHits(G4Step *aStep, G4TouchableHistory *ROhist)
{
    G4Track *track = aStep->GetTrack();

    // KILLS PHOTON AS SOON AS IT ENTERS DETECTOR, PREVENT STRAY
    track->SetTrackStatus(fStopAndKill);

    G4StepPoint *preStepPoint = aStep->GetPreStepPoint();
    G4StepPoint *postStepPoint = aStep->GetPostStepPoint();

    G4ThreeVector posPhoton = preStepPoint->GetPosition();

    /* PRINT OUT THE POSITION OF THE PHOTON AS SOON AS THEY ENTER THE DETECTOR
     G4cout << "Photon position: " << posPhoton << G4endl;
     YOU WILL NOT HAVE THIS IN REALITY
    */

    const G4VTouchable *touchable = aStep->GetPreStepPoint()->GetTouchable();

    // GIVES COPY NUMBER TO DETECTOR THAT PHOTON ENTERS
     G4int copyNo = touchable->GetCopyNumber();

     G4cout << "Copy number: " << copyNo << G4endl;

     G4VPhysicalVolume *physVol = touchable->GetVolume();
     G4ThreeVector posDetector = physVol->GetTranslation();

     // GIVES POSITION OF DETECTOR FIRED
     G4cout << "Detector Position: " << posDetector << G4endl;

     G4int evt = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();

     G4AnalysisManager *man = G4AnalysisManager::Instance();
     man->FillNtupleIColumn(0, evt);
     man->FillNtupleDColumn(1, posDetector[0]);
     man->FillNtupleDColumn(2, posDetector[1]);
     man->FillNtupleDColumn(3, posDetector[2]);
     man->FillNtupleIColumn(4, copyNo);
     man->AddNtupleRow(0); 

     return true;
}
