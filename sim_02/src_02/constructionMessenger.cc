/**
 * @brief This contains the messenger command used to make changes to the detector construction class.
 */
#include "constructionMessenger.hh"

ConstructionMessenger::ConstructionMessenger(DetectorConstruction* detectorConstruction):G4UImessenger(),construction(detectorConstruction) {

    // These aren't really necessary for now, seeing as I only have one option of construction for both, but good to prepare for future
    constructionDirectory = new G4UIdirectory("/construction/");
    constructionDirectory->SetGuidance("Simulation detector and source construction options.");

    constructionDetectorDirectory = new G4UIdirectory("/construction/detector/");
    constructionDetectorDirectory->SetGuidance("Detector Options.");

    geometryOptionCmd = new G4UIcmdWithAnInteger("/construction/geometry",this);
    geometryOptionCmd->SetGuidance("Set which geometry option to use.");
    geometryOptionCmd->SetGuidance("Option 0 - Left empty for custom user construction");
    geometryOptionCmd->SetGuidance("Option 1 - Lead box");  // @todo might need to move build source command elsewhere

    geometryOptionCmd->SetParameterName("geometryOption", false); // Tells  G4 to take param "geometryOption" and sets isOptional to false
    geometryOptionCmd->SetDefaultValue(0);

    detectorOptionCmd = new G4UIcmdWithAnInteger("/construction/detector/option", this);
    detectorOptionCmd->SetGuidance("Option -1 - No detector");
    detectorOptionCmd->SetGuidance("Option 0 - 3x3 NaI Detector");
    detectorOptionCmd->SetGuidance("Option 1 - HPGe Detector");

    detectorOptionCmd->SetDefaultValue(-1);

    sourceOptionCmd = new G4UIcmdWithAnInteger("/construction/source/option", this);
    sourceOptionCmd->SetGuidance("Option -1 - No source");
    sourceOptionCmd->SetGuidance("Option 0 - Sun source");
    sourceOptionCmd->SetGuidance("Option 1 - Soil source");
    sourceOptionCmd->SetGuidance("Option 2 - Soil and Sun Source");

    sourceOptionCmd->SetDefaultValue(-1);
}

ConstructionMessenger::~ConstructionMessenger() {

    // delete detectorPositionCmd;

}

/**
 * @brief This method takes the value from the command and applies it to the appropriate variable
 *  in the construction class.
 * 
 * @param command
 * @param newValue
 */

void ConstructionMessenger::SetNewValue(G4UIcommand* command, G4String newValue) {
    if (command == geometryOptionCmd) {

        construction->SetGeometryOption(geometryOptionCmd->GetNewIntValue(newValue));
    }
    
    if (command == detectorOptionCmd){

        construction->SetDetectorOption(detectorOptionCmd->GetNewIntValue(newValue));
    }

    if (command == sourceOptionCmd) {

        construction->SetSourceOption(sourceOptionCmd->GetNewIntValue(newValue));
    }
}