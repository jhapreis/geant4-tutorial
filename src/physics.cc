#include "physics.hh"

MyPhysicsList::MyPhysicsList(){
    PhysicsList();
}


MyPhysicsList::~MyPhysicsList()
{}


void MyPhysicsList::PhysicsList(){

    physicsList = new QGSP_BERT();

    physicsList->RegisterPhysics(new G4DecayPhysics());
    physicsList->RegisterPhysics(new G4EmStandardPhysics());
    physicsList->RegisterPhysics(new G4OpticalPhysics());
    physicsList->RegisterPhysics(new G4DecayPhysics());
    physicsList->RegisterPhysics(new G4RadioactiveDecayPhysics());
}


G4VModularPhysicsList* MyPhysicsList::Get_PhysicsList(){
    return physicsList;
}
