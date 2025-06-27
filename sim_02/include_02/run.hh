#ifndef RUN_HH
#define RUN_HH

#include "G4UserRunAction.hh"
#include "G4Run.hh"
#include "g4root.hh"

class MyRunAction : public G4UserRunAction {
    
    public:
        MyRunAction();
        ~MyRunAction();

        /**
         * @brief Sets up the analysis structure. Output filename is defined in this method.
         */
        virtual void BeginOfRunAction(const G4Run*);

        /**
         * @brief Writes all collected data (contained in G4AnalysisManager) to the output file 
         */
        virtual void EndOfRunAction(const G4Run*);

};

#endif