/**
 * @brief This is the abstract class for instantiating all the user action 
 * classes. It has a pure virtual method Build() which is invoked by 
 * G4RunManager for sequential execution and G4WorkerRunManager for 
 * multi-threaded execution. The additional virtual method BuildForMaster() 
 * will be invoked from G4MTRunManager for multi-threaded execution.
 */

#include "action.hh"

MyActionInitialization::MyActionInitialization() {}

/**
 * @brief Used to set the user action in the master thread. This is not invoked for sequential mode.
 */
void MyActionInitialization::BuildForMaster() const {

    /**
     * @brief My Run Action
     * 
     * Overrides any default run action within Geant4
     * Does the following:
     * - Instance of Analysis manager
     * - Sets up ROOT output files
     * - Sets up tree structure for ROOT output files
     * - Writes to ROOT file at end of run
     * - Closes ROOT file at end of run
     */
    MyRunAction *runAction = new MyRunAction();
    SetUserAction(runAction);

}

/**
 * @brief Used to set the user action classes for worker threads
 */
void MyActionInitialization::Build() const {

    /**
     * @brief Primary generator
     * 
     * MyPrimaryGenerator thread-local class. Class inherits from G4VUserPrimaryGeneratorAction.
     * Generator is where particle source terms is defined
     */
    Generator* generator = new Generator();
    SetUserAction(generator);

    /**
     * @brief My Run Action
     * 
     * Overrides any default run action within Geant4
     * Does the following:
     * - Instance of Analysis manager
     * - Sets up ROOT output files
     * - Sets up tree structure for ROOT output files
     * - Writes to ROOT file at end of run
     * - Closes ROOT file at end of run
     */
    MyRunAction *runAction = new MyRunAction();
    SetUserAction(runAction); 

    /**
     * @brief My Event Action
     * 
     * Sets actions to be setup for each event
     * 
     * Event action does the following:
     * - Resets energy deposition sum at the beginning of each event
     * - Fill ROOT file with results at end of event
     */
    MyEventAction *eventAction = new MyEventAction(runAction);
    SetUserAction(eventAction);

    /**
     * @brief My Stepping Action
     * 
     * Sets actions to be performed after every step (every interaction) within the simulation
     */
    MySteppingAction *steppingAction = new MySteppingAction(eventAction);
    SetUserAction(steppingAction);

}

MyActionInitialization::~MyActionInitialization() {}

