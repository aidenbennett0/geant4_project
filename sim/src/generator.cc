#include "generator.hh"

MyPrimaryGenerator::MyPrimaryGenerator()
{
  // ONLY ONE PRIMARY VERTEX PER RUN IS CREATED
  fParticleGun = new G4ParticleGun(1);

  // MOVED UP HERE BECAUSE THAT MEANS IT CAN BE OVERWRITTEN BY MACRO FILE WHEN RUN STARTS
  G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
  G4ParticleDefinition *particle = particleTable->FindParticle("geantino");

  G4ThreeVector pos(0., 0., 0.);
  G4ThreeVector mom(0., 0., 1.);

  fParticleGun->SetParticlePosition(pos);
  fParticleGun->SetParticleMomentumDirection(mom);
  fParticleGun->SetParticleMomentum(100.*GeV);
  fParticleGun->SetParticleDefinition(particle);
}

MyPrimaryGenerator::~MyPrimaryGenerator()
{
  delete fParticleGun;
}

// DEFINE WHAT PARTICLES YOU WANT  
void MyPrimaryGenerator::GeneratePrimaries(G4Event *anEvent)
{
  G4ParticleDefinition *particle = fParticleGun->GetParticleDefinition();

  if(particle == G4Geantino::Geantino()) {
// THE FOLLOWING VARIABLES ARE FOR COBALT-60
    // "nucleus contains 27 protons"
    G4int Z = 27;

    // "combined number of neutrons and protons is 60"
    G4int A = 60;

    G4double charge = 0.*eplus;

    // "excitation energy of particle"
    G4double energy = 0.*keV;

    G4ParticleDefinition *ion = G4IonTable::GetIonTable()->GetIon(Z, A, energy);

    fParticleGun->SetParticleDefinition(ion);
    fParticleGun->SetParticleCharge(charge);
  }

  fParticleGun->GeneratePrimaryVertex(anEvent);
}
