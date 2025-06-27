#ifndef GENERATOR_HH
#define GENERATOR_HH

#include "G4UserPrimaryGeneratorAction.hh"
#include "G4GeneralParticleSource.hh"

class Generator : public G4UserPrimaryGeneratorAction 
{
    public:
        Generator();
        ~Generator();

        /**
         * @brief Generates the primary vertexes for each event
         */
        virtual void GeneratePrimaries(G4Event*);

    private:
        G4GeneralParticleSource *fParticle;

};

#endif