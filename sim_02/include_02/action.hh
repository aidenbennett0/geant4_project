/**
 * @brief Required by G4. Sets up user action prior to simulation execution.
 * Includes the setup of primary generators, setup of analysis manager, event actions, and stepping actions.
 */

 #ifndef ACTION_HH
 #define ACTION_HH

 #include "G4VUserActionInitialization.hh"

 #include "generator.hh"
 #include "run.hh"
 #include "event.hh"
 #include "stepping.hh" // FIXME - make this lol

 /**
  * @brief Action initialization based on G4VUserActionInitialization
  */
 class MyActionInitialization : public G4VUserActionInitialization {
   
    public:
        MyActionInitialization();

        ~MyActionInitialization();

        /**
         * @brief Used to set the user action in the master thread. This is not invoked for in sequential mode
         */
        virtual void BuildForMaster() const; // built for master thread

        /**
         * @brief This is used for defining user action classes for worker threads in multi-threading
         */
        virtual void Build() const; // main stepping action for single worker thread
    
 };

 #endif