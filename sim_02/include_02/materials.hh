#ifndef MATERIALS_HH
#define MATERIALS_HH

#include "G4NistManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"

class materials {
    public:
        /**
         * @brief World air. From G4_AIR
         * 
         * @return G4Material*
         */
        G4Material* WorldAir();

        /**
         * @brief Sodium. From G4_Na
         * 
         * @return G4Material*
         */
        G4Material* Na();

        /**
         * @brief Iodide. From G4_I
         * 
         * @return G4Material*
         */
        G4Material* I();

        /**
         * @brief Aluminum. From G4_Al
         * 
         * @return G4Material*
         */
        G4Material* Al();

    private:
    /**
     * @brief Creates an instance of the NIST database which is used to get material properties
     */
        G4NistManager *nist = G4NistManager::Instance();
}
#endif