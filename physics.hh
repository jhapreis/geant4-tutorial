#ifndef PHYSICS_HH
#define PHYSICS_HH

#include "G4VModularPhysicsList.hh"
#include "G4EmStandardPhysics.hh"
#include "G4OpticalPhysics.hh"
#include "G4RadioactiveDecayPhysics.hh"
#include "G4DecayPhysics.hh"
#include "QGSP_BERT.hh"

class MyPhysicsList : public G4VModularPhysicsList{
    
public:
    MyPhysicsList();
    ~MyPhysicsList();

    G4VModularPhysicsList* Get_PhysicsList();

private:
    void PhysicsList();

    G4VModularPhysicsList* physicsList;
};

#endif
