/**
 * @brief This class inherits from G4UserEventAction. This is also used to obtain information
 * at the beginning and end of event. Also used to reset the energy deposition sum.
 */
#ifndef EVENT_HH
#define EVENT_HH

/**
 * @todo interesting header files. learn what these are for.
 */
#include "G4UserEventAction.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"

#include "Randomize.hh"
#include "CLHEP/Random/RandomEngine.h"

#include "g4root.hh"

#include "run.hh"

class SteppingAction;

class EventAction : public G4UserEventAction {
    public:
        EventAction(MyRunAction*);

        ~EventAction();

    public:
        /**
         * @brief Gets the information from before event
         */
        virtual void BeginOfEventAction(const G4Event* event);
        
        /**
         * @brief Gets the information after event is completed
         */
        virtual void EndOfEventAction(const G4Event* event);

        private:
};

#endif