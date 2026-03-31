#ifndef CONSTRUCTIONMESSENGER_HH
#define CONSTRUCTIONMESSENGER_HH

/**
 * @brief Sets up the messenger for modifying the detector construction class.
 *        This setup is not necessary for me, since I am only doing the one detector at present but good to have.
 */

#include "G4UImessenger.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWith3VectorAndUnit.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWithABool.hh"
#include "G4SystemOfUnits.hh"

#include "construction.hh"

class  G4UIcommand;
class  G4UIcmdWithAString;
class  G4UIcmdWithADoubleAndUnit;
class  G4UIcmdWith3Vector;
class  G4UIcmdWith3VectorAndUnit;
class  DetectorConstruction;
class  G4UIcmdWithABool;

class ConstructionMessenger : public G4UImessenger {
    public:
        ConstructionMessenger(DetectorConstruction*);

        virtual ~ConstructionMessenger() override;

        /**
         * @brief This takes the value from the command and assigns it to the correct variable through methods in the construction class
         */
        virtual void SetNewValue(G4UIcommand*, G4String);
        
    private:
        DetectorConstruction *construction;

        // commands for geometry option selection
        G4UIcmdWithAnInteger *geometryOptionCmd;
        G4UIcmdWithAnInteger *detectorOptionCmd;
        G4UIcmdWithAnInteger *sourceOptionCmd;

        /**
         * @note There are additional messenger constructions here but it is for stuff I don't need. hehe
         */
        
         G4UIdirectory *constructionDirectory;
         G4UIdirectory *constructionDetectorDirectory;
         G4UIdirectory *constructionSourceDirectory;

};
#endif