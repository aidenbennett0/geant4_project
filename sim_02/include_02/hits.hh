/**
 * @brief This program tells the file what to do when a particle interacts with a sensitive detector
 * 
 * @brief Used to store hit information. Hit class to store energy deposition, primary/secondary particle 
 * information, and detector ID (copy number)
 */

#ifndef HITS_HH
#define HITS_HH

#include "G4VHit.hh"
#include "G4ThreeVector.hh"
#include "G4Allocator.hh"

class MyHit : public G4VHit {
    public:
        MyHit();

        /**
         * @todo Figure out why this one in particular is a virtual
         */
        virtual ~MyHit();
        
        /**
         * @brief Sets the energy deposition for the single hit
         * 
         * @param edep the energy deposition
         */
        void SetEdep(G4double edep) { fEdep = edep; }

        /**
         * @brief Get the energy deposition from the single hit
         */
        G4double GetEdep() const { return fEdep; }

        /**
         * @brief Set if hit is primary particle for event
         * 
         * @param isPrimary
         */
        void SetPrimaryParticle(G4bool isPrimary) { fIsPrimary = isPrimary; }

        /**
         * @brief Set the detector ID object
         * 
         * @param detectorID
         */
        void SetDetectorID(G4double DetectorID) { fDetectorID = DetectorID; }

        /**
         * @brief Get the detector ID of volume energy deposition occured
         * 
         * @return G4int
         */
        G4int GetDetectorID() { return fDetectorID; }

        /**
         * @brief Return true/false depending on if the hit is from a primary particle or a secondary one
         * 
         * @return G4bool
         */
        G4bool IsPrimaryParticle() const { return fIsPrimary; }

        /**
         * @brief Used for hit visualization and not currently used, but required by G4
         */
        virtual void Draw() {}

        /**
         * @brief Print hit information to command line. Similar to Draw(), this is not currently used but is required by G4
         * 
         */
        virtual void Print() {}

    private:
        G4double fEdep;
        G4int fDetectorID;
        G4bool fIsPrimary;

};

/**
 * @brief Setup of MyHit heap
 * 
 * @attention
 */
typedef G4Allocator<MyHit> MyHitAllocator;

#endif