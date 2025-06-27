#include "generator.hh"

Generator::Generator() {

    // Create a new particle source
    fParticle = new G4GeneralParticleSource();

}

/**
 * @brief Cleans up the Generator::Generator object
 */
Generator::~Generator() {

    delete fParticle;

}

/**
 * @brief Creates the primary vertex for the event
 * 
 * @param anEvent used by geant to create a single event
 */
void Generator::GeneratePrimaries(G4Event *anEvent) {

    fParticle->GeneratePrimaryVertex(anEvent);

}