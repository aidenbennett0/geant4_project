#include "run.hh"

// This is executed as soon as the sim is executed
MyRunAction::MyRunAction() {

    /**
     * @brief Creates an instance of our analysis manager
     */
    G4AnalysisManager *man = G4AnalysisManager::Instance();

    /**
     * @brief This enable ntuple merging for output files created in multithreading mode
     */
    man->SetNtupleMerging(true);

    /**
     * @brief Creates ntuples to be filled in ProcessHits (detector.cc)
     * 
     * @note The 'FinishNtupleLine' is only needed if you will create multiple ntuples
     */

    man->CreateNtuple("Hits", "Hits");
    man->CreateNtupleIColumn("eventEntries");
    man->CreateNtupleDColumn("primaryEnergyDeposition");
    man->CreateNtupleDColumn("secondaryEnergyDeposition");
    man->CreateNtupleIColumn("detectorID");
    man->CreateNtupleDColumn("TotalDeposition");
    man->CreateNtupleDColumn("TotalDepositionGEB");
    // man->FinishNtuple(0);

}

MyRunAction::~MyRunAction() {}

void MyRunAction::BeginOfRunAction(const G4Run* run) {

    G4AnalysisManager *man = G4AnalysisManager::Instance();

    // While this isn't used, it could be added to an OpenFile string
    G4int runID = run->GetRunID();
    (void)runID; // To keep the compiler from having an issue with unused variables
    man->SetFileName("output");

    man->OpenFile();
 
}

void MyRunAction::EndOfRunAction(const G4Run*) {

    G4AnalysisManager *man = G4AnalysisManager::Instance();

    // Must properly write to the file or it will corrupt and be unrecoverable
    man->Write();

    // Close the file
    man->CloseFile();
}