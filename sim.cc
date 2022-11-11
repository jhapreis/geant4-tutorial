#include <iostream>

#include "G4RunManager.hh"
#include "G4MTRunManager.hh"
#include "G4UImanager.hh"
#include "G4VisManager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include "QGSP_BERT.hh"

#include "scintillator.hh"
#include "physics.hh"
#include "action.hh"


int main(int argc, char** argv){

  G4UIExecutive* ui = 0;

  std::cout << " ========== Defining runManager ========== " << std::endl;

  #ifdef G4MULTITHREADED
    G4MTRunManager* runManager = new G4MTRunManager;
  #else
    G4RunManager* runManager = new G4RunManager;
  #endif


  std::cout << " ========== Setting ScintillatorConstruction ========== " << std::endl;
  runManager->SetUserInitialization(new ScintillatorConstruction());

  std::cout << " ========== Setting PhysicsList ========== " << std::endl;
  runManager->SetUserInitialization(new MyPhysicsList());

  std::cout << " ========== Setting MyActionInitialization ========== " << std::endl;
  runManager->SetUserInitialization(new MyActionInitialization());

  std::cout << " ========== Done ========== " << std::endl;



  G4VisManager *visManager = new G4VisExecutive();
  visManager->Initialize();

  G4UImanager *UImanager = G4UImanager::GetUIpointer();

  if(argc == 1){ // no macro files passed as arguments
    std::cout << " ========== Defining UI ========== " << std::endl;

    ui = new G4UIExecutive(argc, argv);
    UImanager->ApplyCommand("/control/execute vis.mac");
    ui->SessionStart();
  }
  else{
    G4String command = "/control/execute ";
    G4String fileName = argv[1];
    UImanager->ApplyCommand(command+fileName);
  }

  return 0;
}
