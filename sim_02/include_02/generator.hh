#ifndef GENERATOR_HH
#define GENERATOR_HH

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4GeneralParticleSource.hh"

class Generator : public G4VUserPrimaryGeneratorAction 
{
    public:
        Generator();
        ~Generator();

        /**
         * @brief Generates the primary vertexes for each event
         */
        virtual void GeneratePrimaries(G4Event*);

    private:
        G4GeneralParticleSource* fparticle;

};

#endif