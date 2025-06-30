#include "physics.hh"

PhysicsList::PhysicsList() {

    G4int verb = 1;// verbosity, 0 silent, 1 warning messages, 2 more
    SetVerboseLevel(verb);

    RegisterPhysics (new G4DecayPhysics(verb));
    RegisterPhysics (new G4RadioactiveDecayPhysics(verb));
    RegisterPhysics (new G4EmPenelopePhysics(verb));

    /**
     * @todo Ron's repo has a definition for G4EmExtraPhysics in this section 
     *       but I couldn't tell if it was only needed for hadronic processes; likely yes
     */
}

void PhysicsList::SetCuts() {

    G4VUserPhysicsList::SetCuts();

}

PhysicsList::~PhysicsList() {}