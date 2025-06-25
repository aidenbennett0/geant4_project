#ifndef PHYSICS_HH
#define PHYSICS_HH

/**
 * @brief These have been ruthlessly stolen from Ron's repo, maybe not all apply :)
 */
#include "G4VModularPhysicsList.hh"
#include "G4SystemOfUnits.hh"
#include "G4DecayPhysics.hh"
#include "G4RadioactiveDecayPhysics.hh"
#include "G4EmPenelopePhysics.hh"
#include "G4OpticalPhysics.hh"
#include "G4HadronElasticPhysics.hh"
#include "G4HadronPhysicsFTFP_BERT.hh"
#include "G4IonElasticPhysics.hh"
#include "G4IonPhysics.hh"
#include "G4NuclideTable.hh"
#include "G4EmExtraPhysics.hh"
#include "G4EmParameters.hh"


class PhysicsList : public G4VModularPhysicsList {
    public:
        PublicList();
        ~PublicList();

        void SetCuts() override;
};

#endif