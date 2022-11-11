#include "physics.hh"

MyPhysicsList::MyPhysicsList(){

    RegisterPhysics(new G4EmStandardPhysics());
    RegisterPhysics(new G4OpticalPhysics());
    RegisterPhysics(new G4DecayPhysics());
    RegisterPhysics(new G4RadioactiveDecayPhysics());


    // G4VModularPhysicsList* physics = new QGSP_BERT();
    // physics->RegisterPhysics(new G4DecayPhysics());
}

MyPhysicsList::~MyPhysicsList()
{}
