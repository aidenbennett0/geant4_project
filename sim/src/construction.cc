#include "construction.hh"

MyDetectorConstruction::MyDetectorConstruction()
{
     
    nCols = 10;
    nRows = 10;

    isCherenkov = false;
    isScintillator = true;
    
    fMessenger = new G4GenericMessenger(this, "/detector/", "Detector Construction");

    fMessenger->DeclareProperty("nCols", nCols, "Number of Columns");
    fMessenger->DeclareProperty("nRows", nRows, "Number of Rows");
    fMessenger->DeclareProperty("isCherenkov", isCherenkov, "Toggle Cherenkov setup");
    fMessenger->DeclareProperty("isScintillator", isScintillator, "Toggle Scintillator setup");

    DefineMaterials();

    xWorld = 0.5*m;
    yWorld = 0.5*m;
    zWorld = 0.5*m;
}

MyDetectorConstruction::~MyDetectorConstruction()
{}

void MyDetectorConstruction::DefineMaterials()
{
    G4NistManager *nist = G4NistManager::Instance();
    
    //CREATE AEROGEL MATERIAL
    
    // G4MATERIAL(MATERIAL, DENSITY, # OF COMPONENTS)
    SiO2 = new G4Material("SiO2", 2.201*g/cm3, 2);
    SiO2->AddElement(nist->FindOrBuildElement("Si"), 1);
    SiO2->AddElement(nist->FindOrBuildElement("O"), 2);

    H2O = new G4Material("H2O", 1.000*g/cm3, 2);
    H2O->AddElement(nist->FindOrBuildElement("H"), 2);
    H2O->AddElement(nist->FindOrBuildElement("O"), 1);

    C = nist->FindOrBuildElement("C");

    Aerogel = new G4Material("Aerogel", 0.200*g/cm3, 3);
    // ADDMATERIAL(MATERIAL, %COMPOSITION);
    Aerogel->AddMaterial(SiO2, 62.5*perCent);
    Aerogel->AddMaterial(H2O, 37.4*perCent);
    Aerogel->AddElement(C, 0.1*perCent);

    worldMat = nist->FindOrBuildMaterial("G4_AIR");

    // WTF THIS IS @ 15:50 OF PHYSICS MATTERS TUTORIAL 6
    G4double energy[2] = {1.239841939*eV/0.2, 1.239841939*eV/0.9};
    G4double rindexAerogel[2] = {1.1, 1.1};
    G4double rindexWorld[2] = {1.0, 1.0};
    G4double rindexNaI[2] = {1.78, 1.78};

    G4MaterialPropertiesTable *mptAerogel = new G4MaterialPropertiesTable();
    mptAerogel->AddProperty("RINDEX", energy, rindexAerogel, 2);

    Aerogel->SetMaterialPropertiesTable(mptAerogel);

    G4MaterialPropertiesTable *mptWorld = new G4MaterialPropertiesTable();
    mptWorld->AddProperty("RINDEX", energy, rindexWorld, 2);

    Na = nist->FindOrBuildElement("Na");
    I = nist->FindOrBuildElement("I");
    NaI = new G4Material("NaI", 3.67*g/cm3, 2);
    NaI->AddElement(Na, 1);
    NaI->AddElement(I, 1);

    //{numRedPhotons, numBluePhotons}
    G4double fraction[2] = {1.0, 1.0};

    G4double abslength[2] = {1.5*m, 1.5*m};

    // All parameters in quotes below are built into Geant4
    G4MaterialPropertiesTable *mptNaI = new G4MaterialPropertiesTable();
    mptNaI->AddProperty("RINDEX", energy, rindexNaI, 2);
    mptNaI->AddProperty("FASTCOMPONENT", energy, fraction, 2);
    mptNaI->AddProperty("ABSLENGTH", energy, abslength, 2);
    // You use AddConstProperty for the following because they take no arrays as argument
    mptNaI->AddConstProperty("SCINTILLATIONYIELD", 38./keV);
    mptNaI->AddConstProperty("RESOLUTIONSCALE", 1.0);
    mptNaI->AddConstProperty("FASTTIMECONSTANT", 250*ns);
    mptNaI->AddConstProperty("YIELDRATIO", 1);

    NaI->SetMaterialPropertiesTable(mptNaI);

    worldMat->SetMaterialPropertiesTable(mptWorld);

    // Adds the reflectivity of the scintillator
    mirrorSurface = new G4OpticalSurface("mirrorSurface");

    mirrorSurface->SetType(dielectric_metal);
    mirrorSurface->SetFinish(ground);
    mirrorSurface->SetModel(unified);

    G4double reflectivity[2] = {1.0, 1.0};

    G4MaterialPropertiesTable *mptMirror = new G4MaterialPropertiesTable();
    mptMirror->AddProperty("REFLECTIVITY", energy, reflectivity, 2);

    mirrorSurface->SetMaterialPropertiesTable(mptMirror);
}

void MyDetectorConstruction::ConstructCherenkov()
{
    solidRadiator = new G4Box("solidRadiator", 0.4*m, 0.4*m, 0.01*m);

    logicRadiator = new G4LogicalVolume(solidRadiator, Aerogel, "logicRadiator");

    fScoringVolume = logicRadiator; 

    physRadiator = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.25*m), logicRadiator, "physRadiator", logicWorld, false, 0, true);

    // DEFINE ARRAY FOR PHOTOSENSOR DETECTORS
    solidDetector = new G4Box("solidDetector", xWorld/nRows, yWorld/nCols, 0.01*m);

    logicDetector = new G4LogicalVolume(solidDetector, worldMat, "logicDetector");

    int iteration = 0;

    for (G4int i = 0; i < nRows; i++) 
    {
        for (G4int j = 0; j < nCols; j++)
        {
            physDetector = new G4PVPlacement(0, G4ThreeVector(-0.5*m+(i+0.5)*m/nRows,-0.5*m +(j+0.5)*m/nCols, 0.49*m), logicDetector, "physDetector", logicWorld, false, i+j*nCols, false);
            
            iteration++;
            if (iteration % 100 == 0) {
                std::cout << "---\n\n\nPlaced and checked " << iteration << " detectors\n\n\n---\n";
            }

        }
    }
    std::cout << "Total detector count: " << iteration;
}

void MyDetectorConstruction::ConstructScintillator()
{
    solidScintillator = new G4Box("solidScintillator", 5*cm, 5*cm, 6*cm);

    logicScintillator = new G4LogicalVolume(solidScintillator, NaI, "logicalScintillator");

    // Essentially adds a reflective coating to the world volume to keep photons in scintillator
    G4LogicalSkinSurface *skin = new G4LogicalSkinSurface("skin", logicWorld, mirrorSurface);

    fScoringVolume = logicScintillator;

    solidDetector = new G4Box("solidDetector", 1.*cm, 5.*cm, 6.*cm);

    logicDetector = new G4LogicalVolume(solidDetector, worldMat, "logicDetector");


    for(G4int i = 0; i < 6; i++) {
        for(G4int j = 0; j < 16; j++) {

            G4Rotate3D rotZ(j*22.5*deg, G4ThreeVector(0.,0.,1.));

            G4Translate3D transXScint(G4ThreeVector(5./tan(22.5/2*deg)*cm + 5.*cm, 0*cm, -40*cm + i*15*cm));
            G4Translate3D transXDet(G4ThreeVector(5./tan(22.5/2*deg)*cm + 6.*cm + 5.*cm, 0*cm, -40*cm + i*15*cm));

            G4Transform3D transformScint = (rotZ) * (transXScint);
            G4Transform3D transformDet = (rotZ) * (transXDet);

            physScintillator = new G4PVPlacement(transformScint, logicScintillator, "physScintillator", logicWorld, false, 0, true);
            physDetector = new G4PVPlacement(transformDet, logicDetector, "physDetector", logicWorld, false, 0, true);
        }
    }

}

G4VPhysicalVolume *MyDetectorConstruction::Construct()
{
    //G4Box("name", 0.5 * length, 0.5 * height, 0.5 * depth) ('*m' tells G4 to use meters (mm is default))
    solidWorld = new G4Box("solidWorld", xWorld, yWorld, zWorld);

    logicWorld = new G4LogicalVolume(solidWorld, worldMat, "logicWorld");

    // G4PVPlacement(rotation, G4ThreeVector(x, y, x), logicVolume, "name", place in mother volume?, boolean?, copy number, check for overlaps?)
    physWorld = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicWorld, "physWorld", 0, false, 0, true);

    if(isCherenkov) {
        ConstructCherenkov(); 
    }

    if(isScintillator) {
        ConstructScintillator();
    }
    return physWorld;
}

void MyDetectorConstruction::ConstructSDandField()
{
    MySensitiveDetector *sensDet = new MySensitiveDetector("SensitiveDetector");

    if(isCherenkov) {
        logicDetector->SetSensitiveDetector(sensDet); 
    }
}