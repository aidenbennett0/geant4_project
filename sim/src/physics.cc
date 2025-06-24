#include "physics.hh"

MyPhysicsList::MyPhysicsList()
{
  G4int verb = 1;
 // SetVerboseLevel(verb);

  RegisterPhysics(new G4EmStandardPhysics());
  RegisterPhysics(new G4OpticalPhysics());
  RegisterPhysics(new G4DecayPhysics());
  RegisterPhysics(new G4RadioactiveDecayPhysics());
}

MyPhysicsList::~MyPhysicsList()
{}
