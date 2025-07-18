#include <iostream>

#include "G4RunManager.hh"
#include "G4MTRunManager.hh"
#include "G4UImanager.hh"
#include "G4VisManager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include "QGSP_BERT.hh"

#include "action.hh"
#include "construction.hh"
#include "physics.hh"

int main(int argc, char **argv) {

    #ifdef G4MULTITHREADED
        G4RunManager *runManager = new G4MTRunManager();
    #else
        G4RunManager *runManager = new G4RunManager();
    #endif

    runManager->SetUserInitialization(new DetectorConstruction());
    runManager->SetUserInitialization(new PhysicsList());
    runManager->SetUserInitialization(new MyActionInitialization());

    G4UIExecutive *ui = 0;

    if (argc == 1) {
        ui = new G4UIExecutive(argc, argv);

        G4cout << "** UI initialized **" << G4endl;
    }

    G4VisManager *visManager = new G4VisExecutive;
    visManager->Initialize();

    G4UImanager* UImanager = G4UImanager::GetUIpointer();

   if(ui) {
        UImanager->ApplyCommand("/control/execute ../vis.mac");
        ui->SessionStart();
    }

    else {
        G4String command = "/control/execute ";
        G4String fileName = argv[1];
        UImanager->ApplyCommand(command+fileName);
    }

    if(!ui) {
        G4cout << "Simulation: completed successfully." << G4endl;

        if(argc == 2) {
            G4cout << "Macro used: " << argv[1] << G4endl;
        }
    }

    delete runManager;
    delete visManager;
}