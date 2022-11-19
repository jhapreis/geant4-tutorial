#include "scintillator.hh"

ScintillatorConstruction::ScintillatorConstruction()
{
    nCols = 10;
    nRows = 10;

    std::cout << " ---------- Generic Messenger ---------- " << std::endl;
    fMessenger = new G4GenericMessenger(this, "/detector/", "Detector Construction");


    std::cout << " ---------- Declare Properties ---------- " << std::endl;
    fMessenger->DeclareProperty("nCols", nCols, "Number of cols");
    fMessenger->DeclareProperty("nRows", nRows, "Number of rows");


    std::cout << " ---------- Define Materials ---------- " << std::endl;
    DefineMaterials();
    

    std::cout << " ---------- Construct ---------- " << std::endl;
    Construct();
}


ScintillatorConstruction::~ScintillatorConstruction()
{}


void ScintillatorConstruction::DefineMaterials(){

    G4double energy[2] = {1.239841939*eV/0.2, 1.239841939*eV/0.9};
    G4double rindex_PlasticSC[2] = {1.58, 1.58};
    G4double rindexWorld[2] = {1.0, 1.0};
    G4double reflectivity[2] = {1.0, 1.0};


    std::cout << " ---------- NIST Instance ---------- " << std::endl;
    G4NistManager *nIst = G4NistManager::Instance();


    // Plastic Scitillator
    std::cout << " ---------- Plastic Scitillator ---------- " << std::endl;

    std::cout << " ---------- Build Scintillator Material ---------- " << std::endl;
    plastic_SC_material = nIst->FindOrBuildMaterial("G4_PLASTIC_SC_VINYLTOLUENE");

    std::cout << " ---------- Assign Material Properties Table ---------- " << std::endl;
    G4MaterialPropertiesTable *MPT_plastic_SC = new G4MaterialPropertiesTable();
    MPT_plastic_SC->AddProperty("RINDEX", energy, rindex_PlasticSC, 2);
    plastic_SC_material->SetMaterialPropertiesTable(MPT_plastic_SC);


    // World Volume
    std::cout << " ---------- World Volume ---------- " << std::endl;

    std::cout << " ---------- Build Air Material ---------- " << std::endl;
    world_material = nIst->FindOrBuildMaterial("G4_AIR");

    std::cout << " ---------- Assign Material Properties Table ---------- " << std::endl;
    G4MaterialPropertiesTable *MPT_world = new G4MaterialPropertiesTable();
    MPT_world->AddProperty("RINDEX", energy, rindexWorld, 2);
    world_material->SetMaterialPropertiesTable(MPT_world);


    // Mirror Surface
    std::cout << " ---------- Mirror Surface ---------- " << std::endl;
    mirrorSurface = new G4OpticalSurface("mirrorSurface");

    std::cout << " ---------- Set Type ---------- " << std::endl;
    mirrorSurface->SetType(dielectric_metal);

    std::cout << " ---------- Set Finish ---------- " << std::endl;
    mirrorSurface->SetFinish(ground);

    std::cout << " ---------- Set Model ---------- " << std::endl;
    mirrorSurface->SetModel(unified);

    std::cout << " ---------- Assign Material Properties Table ---------- " << std::endl;
    G4MaterialPropertiesTable *mptMirror = new G4MaterialPropertiesTable();
    mptMirror->AddProperty("REFLECTIVITY", energy, reflectivity, 2);
    mirrorSurface->SetMaterialPropertiesTable(mptMirror);
}


void ScintillatorConstruction::Scintillator(){

    solidScintillator = new G4Tubs(
        "solidScintillator", 
        0.*cm,                     // inner radius
        Solid_Scintillator_Radius, // outer radius
        Solid_Scintillator_Height, // height
        0.0*deg,  360.0*deg);      // segment angles

    logicScintillator = new G4LogicalVolume(solidScintillator, plastic_SC_material, "logicalScintillator");

    physDetector = new G4PVPlacement(0, G4ThreeVector(0.*cm, 0.*cm, 0.*cm), logicScintillator, "physScintillator", logicWorld, false, 0, true);

    fScoringVolume = logicScintillator;
}


void ScintillatorConstruction::Detector(){

    solidDetector = new G4Box("solidDetector", Solid_Detector_X, Solid_Detector_Y, Solid_Detector_Z);

    logicDetector = new G4LogicalVolume(solidDetector, world_material, "logicDetector");

    physDetector = new G4PVPlacement(0, G4ThreeVector(0.1*cm, 0.1*cm, 4.*cm), logicDetector, "physDetector", logicWorld, false, 0, true);


    skin = new G4LogicalSkinSurface("skin", logicWorld, mirrorSurface);

    // physScintillator = new G4PVPlacement(0, logicScintillator, "physScintillator", logicWorld, false, 0, true);

    // physDetector = new G4PVPlacement(0, logicDetector, "physDetector", logicWorld, false, 0, true);


    // physDetector = new G4PVPlacement(0, G4ThreeVector(0.15*cm, 0.15*cm, 0.5*cm), logicDetector, "physDetector", logicWorld, false, 1, true);

    // for(G4int i = 0; i < 6; i++)
    // {
    //     for(G4int j = 0; j < 16; j++)
    //     {
    //         G4Rotate3D rotZ(j*22.5*deg, G4ThreeVector(0,0,1));
    //         G4Translate3D transXScint(G4ThreeVector(5./tan(22.5/2*deg)*cm+5.*cm, 0.*cm, -40.*cm + i*15*cm));
    //         G4Transform3D transformScint = (rotZ)*(transXScint);

    //         G4Translate3D transXDet(G4ThreeVector(5./tan(22.5/2*deg)*cm+5.*cm+6.*cm, 0.*cm, -40.*cm + i*15*cm));
    //         G4Transform3D transformDet = (rotZ)*(transXDet);

    //         physScintillator = new G4PVPlacement(transformScint, logicScintillator, "physScintillator", logicWorld, false, 0, true);

    //         physDetector = new G4PVPlacement(transformDet, logicDetector, "physDetector", logicWorld, false, 0, true);
    //     }
    // }
}

G4VPhysicalVolume *ScintillatorConstruction::World(){

    solidWorld = new G4Box("solidWorld", World_X, World_Y, World_Z);

    logicWorld = new G4LogicalVolume(solidWorld, world_material, "logicWorld");

    physWorld  = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicWorld, "physWorld", 0, false, 0, true);

    return physWorld;
}

G4VPhysicalVolume *ScintillatorConstruction::Construct(){

    World();

    Scintillator();

    Detector();

    return physWorld;
}

void ScintillatorConstruction::Construct_SensitiveDetector_and_Field(){

    MySensitiveDetector *sensDet = new MySensitiveDetector("SensitiveDetector");

    if(logicDetector != NULL)
        logicDetector->SetSensitiveDetector(sensDet);
}


G4LogicalVolume* ScintillatorConstruction::GetScoringVolume() const{ 
    return fScoringVolume; 
}
