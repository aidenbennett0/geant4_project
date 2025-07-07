/**
 * @brief Defines user actions to be performed every step. 
 * Nothing is defined here beside the base requirement for Geant.
 */
#ifndef STEPPING_HH
#define STEPPING_HH

#include "G4UserSteppingAction.hh"

#include "G4Step.hh"
#include "G4Gamma.hh"
#include "G4Track.hh"

#include "globals.hh"

#include "construction.hh"
#include "event.hh"  // FIXME: define

class SteppingAction : public G4UserSteppingAction {
    public:
        SteppingAction(EventAction* event);

        ~SteppingAction();

        /**
         * @brief Definition of what actions to perform for every step
         */
        void UserSteppingAction(const G4Step*) override;

    public:
        /**
         * @brief Event action pointer
         */
        EventAction* feventAction = nullptr;

};



#endif