#include "scintillator.hh"

ScintillatorConstruction::ScintillatorConstruction(){

    nCols = 10;
    nRows = 10;

    wavelenghts      = {Scintillator_Wavelenght_Min, Scintillator_Wavelenght_Max};
    energy           = {hc_constant_eV/wavelenghts[0], hc_constant_eV/wavelenghts[1]};
    rindex_PlasticSC = {1.58, 1.58};
    rindexWorld      = {1.0, 1.0};
    reflectivity     = {1.0, 1.0};


    std::cout << " ---------- Generic Messenger ---------- " << std::endl;
    fMessenger = new G4GenericMessenger(this, "/detector/", "Detector Construction");


    std::cout << " ---------- Declare Properties ---------- " << std::endl;
    fMessenger->DeclareProperty("nCols", nCols, "Number of cols");
    fMessenger->DeclareProperty("nRows", nRows, "Number of rows");

    
    std::cout << " ---------- Construct ---------- " << std::endl;
    nIst = G4NistManager::Instance();
    Construct();
}


ScintillatorConstruction::~ScintillatorConstruction()
{}


G4VPhysicalVolume *ScintillatorConstruction::Construct(){

    World();

    Scintillator();

    Detector();

    MirrorSurface();

    return physWorld;
}


void ScintillatorConstruction::MirrorSurface(){
    // Mirror Surface
    std::cout << " ---------- Mirror Surface ---------- " << std::endl;
    mirrorSurface = new G4OpticalSurface("mirrorSurface");
    mirrorSurface->SetType(dielectric_metal);
    mirrorSurface->SetFinish(ground);
    mirrorSurface->SetModel(unified);

    G4MaterialPropertiesTable *mptMirror = new G4MaterialPropertiesTable();
    mptMirror->AddProperty("REFLECTIVITY", energy, reflectivity, 2);
    mirrorSurface->SetMaterialPropertiesTable(mptMirror);

    skin = new G4LogicalSkinSurface("skin", logicScintillator, mirrorSurface);
}


void ScintillatorConstruction::Scintillator(){
    // Plastic Scitillator

    std::cout << " ---------- Plastic Scitillator ---------- " << std::endl;

    plastic_SC_material = new G4Material("plasticScint", 1.096*g/cm3, 1, kStateSolid);
    plastic_SC_material->AddMaterial( nIst->FindOrBuildMaterial("G4_PLASTIC_SC_VINYLTOLUENE"), 1.0 );

    G4MaterialPropertiesTable* MPT_plastic_SC = new G4MaterialPropertiesTable();
    MPT_plastic_SC->AddProperty("RINDEX", energy, rindex_PlasticSC, 2);
    MPT_plastic_SC->AddConstProperty("SCINTILLATIONYIELD", Scintillator_Scintillation_Yeld);
    MPT_plastic_SC->AddConstProperty("RESOLUTIONSCALE" , 1.0);

    plastic_SC_material->SetMaterialPropertiesTable(MPT_plastic_SC);

    solidScintillator = new G4Tubs(
        "solidScintillator", 
        0.*cm,                 // inner radius
        Scintillator_Radius,   // outer radius
        Scintillator_Height/2, // height
        0.0*deg,  360.0*deg);  // segment angles

    logicScintillator = new G4LogicalVolume(solidScintillator, plastic_SC_material, "logicalScintillator");

    physDetector = new G4PVPlacement(0, G4ThreeVector(0.*cm, 0.*cm, 0.*cm), logicScintillator, "physScintillator", logicWorld, false, 0, true);

    fScoringVolume = logicScintillator;
}


void ScintillatorConstruction::Detector(){

    solidDetector = new G4Box("solidDetector", Solid_Detector_X, Solid_Detector_Y, Solid_Detector_Z);

    logicDetector = new G4LogicalVolume(solidDetector, world_material, "logicDetector");

    physDetector = new G4PVPlacement(0, G4ThreeVector(0.*cm, 0.*cm, Scintillator_Height/2 + 1.1*cm), logicDetector, "physDetector", logicWorld, false, 0, true);

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
    // World Volume

    std::cout << " ---------- World Volume ---------- " << std::endl;

    world_material = nIst->FindOrBuildMaterial("G4_AIR");

    G4MaterialPropertiesTable *MPT_world = new G4MaterialPropertiesTable();

    MPT_world->AddProperty("RINDEX", energy, rindexWorld, 2);

    world_material->SetMaterialPropertiesTable(MPT_world);

    solidWorld = new G4Box("solidWorld", World_X, World_Y, World_Z);

    logicWorld = new G4LogicalVolume(solidWorld, world_material, "logicWorld");

    physWorld  = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicWorld, "physWorld", 0, false, 0, true);

    return physWorld;
}


void ScintillatorConstruction::ConstructSDandField(){

    MySensitiveDetector *sensDet = new MySensitiveDetector("SensitiveDetector");

    if(logicDetector != NULL)
        logicDetector->SetSensitiveDetector(sensDet);
}


G4LogicalVolume* ScintillatorConstruction::GetScoringVolume() const{ 
    return fScoringVolume; 
}
