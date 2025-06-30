#ifndef SENSITIVEDETECTOR_HH
#define SENSITIVEDETECTOR_HH

/**
 * @brief This class contains the hit data collected in sensitive detector
 */

#include "G4VSensitiveDetector.hh"
#include "G4RunManager.hh"
#include "g4root.hh"
#include "G4TouchableHistory.hh"
#include "G4HCofThisEvent.hh"
#include "G4THitsCollection.hh"
#include "G4SDManager.hh"
#include "G4SystemOfUnits.hh"

#include "hits.hh"

/**
 * @brief Class for sensitive detector construction
 */
class SensitiveDetector : public G4VSensitiveDetector {

    public:
        /**
         * @brief Construct a new Sensitive Detector object
         * 
         * @param name name of sensitive detector
         * @param hitsCollectionName name of sensitive detector hits collection
         */
        SensitiveDetector(const G4String& name, const G4String& hitsCollectionName);

        ~SensitiveDetector();

        // Methods required by G4VSensitiveDetector
        /**
         * @brief Initialize the sensitive detector
         * 
         * @param hce hits collection storing event
         */
        virtual void Initialize(G4HCofThisEvent *hce) override;

        /**
         * @brief Processing of hit collection
         * 
         * @param step event step
         * @param history event history
         * 
         * @return G4bool
         */
        virtual G4bool ProcessHits(G4Step* step, G4TouchableHistory* history) override;

        /**
         * @brief Process all event data collected through hits.
         * 
         *        This is where the results will be written to a ROOT tree. Gaussian energy broadening will also take place here.
         * 
         * @param hce
         */
        virtual void EndOfEvent(G4HCofThisEvent* hce) override;

        /**
         * @brief Sets the Gaussian Energy Broadening parameters
         * 
         * @param paramGEB;
         */
        void SetGEBParameters(G4ThreeVector paramGEB);
        
        private:
            G4double fEventEnergyDeposited;
            G4double fTotalEnergyDeposited;

            G4THitsCollection<MyHit>* fHitsCollection;
            G4int fHCID;

            /**
             * @brief Sets the gaussian energy broadening. To be set by detector implemented from sensitive detector construction.
             */
            G4double a = 0;
            G4double b = 0;
            G4double c = 0;
};

#endif