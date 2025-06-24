#include <iostream>

#include "G4RunManager.hh"
#include "G4MTRunManager.hh"
#include "G4UImanager.hh"
#include "G4VisManager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include "QGSP_BERT.hh"

#include "construction.hh"
#include "physics.hh"
#include "action.hh"

int main(int argc, char** argv)
{
    G4RunManager *runManager = nullptr;

    if (argc == 1) {
      runManager = new G4RunManager();
    }
    else {
      runManager = new G4MTRunManager();
    }

    runManager->SetUserInitialization(new MyDetectorConstruction());
    runManager->SetUserInitialization(new MyPhysicsList());
    runManager->SetUserInitialization(new MyActionInitialization());

    G4UIExecutive* ui = 0;

    if (argc == 1) {
        ui = new G4UIExecutive(argc, argv);
    }

    G4VisManager *visManager = new G4VisExecutive;
    visManager->Initialize();

    G4UImanager* UImanager = G4UImanager::GetUIpointer();

    if(ui) {
        UImanager->ApplyCommand("/control/execute vis.mac");
        ui->SessionStart();
    }
    else {
        G4String command = "/control/execute ";
        G4String fileName = argv[1];
        UImanager->ApplyCommand(command+fileName);
    }

    if(!ui) {
      G4cout << "Simulation: completed successfully" << G4endl;

      if(argc == 2) {
        G4cout << "Macro used: " << argv[1] << G4endl;
      }
    }

    delete runManager;
    delete visManager;

    return 0;
}