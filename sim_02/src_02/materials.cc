#include "materials.hh"

G4Material *materials::WorldAir() {
    G4Material *material;
    material = nist->FindOrBuildMaterial("G4_AIR");
    return material;
}

G4Material *materials::Al() {
    G4Material *material;
    material = nist->FindOrBuildElement("G4_Al");
    return material;
}

G4Material *materials::NaI() {
    G4material *material;
    material->AddElement(nist->FindOrBuildElement("Na"), 1);
    material->AddElement(nist->FindOrBuildElement("I"), 1);
    return material;
}