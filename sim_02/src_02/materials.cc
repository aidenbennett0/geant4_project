#include "materials.hh"

G4Material *materials::WorldAir() {
    G4Material *material;
    material = nist->FindOrBuildMaterial("G4_AIR");
    return material;
}

G4Material *materials::Al() {
    G4Material *material;
    material = nist->FindOrBuildMaterial("G4_Al");
    return material;
}

G4Material *materials::NaI() {
    G4Material *material;
    material = new G4Material("NaI", 3.67*g/cm3,2);
    material->AddElement(nist->FindOrBuildElement("Na"), 1);
    material->AddElement(nist->FindOrBuildElement("I"), 1);
    return material;
}

G4Material *materials::Teflon() {
    G4Material *material;
    material = nist->FindOrBuildMaterial("G4_TEFLON");
    return material;
}