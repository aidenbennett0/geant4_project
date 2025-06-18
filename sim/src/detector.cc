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
    G4ThreeVector momPhoton = preStepPoint->GetMomentum();

    // EXPLANATION @ 11:50 OF PHYSMATTERS GEANT4 TUTORIAL 12
    G4double wlen = (1.239841939*eV/momPhoton.mag())*1E+03;

    /* PRINT OUT THE POSITION OF THE PHOTON AS SOON AS THEY ENTER THE DETECTOR
     G4cout << "Photon position: " << posPhoton << G4endl;
     YOU WILL NOT HAVE THIS IN REALITY
    */

    const G4VTouchable *touchable = aStep->GetPreStepPoint()->GetTouchable();

    // GIVES COPY NUMBER TO DETECTOR THAT PHOTON ENTERS
    G4int copyNo = touchable->GetCopyNumber();

    // G4cout << "Copy number: " << copyNo << G4endl;

    G4VPhysicalVolume *physVol = touchable->GetVolume();
    G4ThreeVector posDetector = physVol->GetTranslation();

    #ifndef G4MULTITHREADED
    // GIVES POSITION OF DETECTOR FIRED
    G4cout << "Detector Position: " << posDetector << G4endl;
    #endif
     
    G4int evt = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();

    G4AnalysisManager *man = G4AnalysisManager::Instance();

     
    man->FillNtupleIColumn(0, 0, evt);
    man->FillNtupleDColumn(0, 1, posPhoton[0]);
    man->FillNtupleDColumn(0, 2, posPhoton[1]);
    man->FillNtupleDColumn(0, 3, posPhoton[2]);
    man->FillNtupleDColumn(0, 4, wlen);
    man->AddNtupleRow(0);

    man->FillNtupleIColumn(1, 0, evt);
    man->FillNtupleDColumn(1, 1, posDetector[0]);
    man->FillNtupleDColumn(1, 2, posDetector[1]);
    man->FillNtupleDColumn(1, 3, posDetector[2]);
    man->FillNtupleIColumn(1, 4, copyNo);
    man->AddNtupleRow(1); 

    return true;
}
