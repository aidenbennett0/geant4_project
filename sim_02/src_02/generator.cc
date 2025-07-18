#include "generator.hh"

Generator::Generator() {
    // Create a new particle source
    fparticle = new G4GeneralParticleSource();
}


/**
 * @brief Cleans up the Generator::Generator object
 */
Generator::~Generator() {

    delete fparticle;
}

/**
 * @brief Creates the primary vertex for the event
 * 
 * @param anEvent used by geant to create a single event
 */
void Generator::GeneratePrimaries(G4Event *anEvent) {
    
    fparticle->GeneratePrimaryVertex(anEvent);
}