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
#include "aux.hh"


int main(int argc, char** argv){

    bool CUSTOM_MACRO, UI_USAGE;

    if(argc == 1){
        CUSTOM_MACRO = false;
        UI_USAGE     = true;
    }
    else if(argc == 3){
        CUSTOM_MACRO = true;
        UI_USAGE     = *string(argv[2]).str_toupper() == "TRUE";
    }
    else{
        std::cout << "Could not interpret the arguments passed." << std::endl;

        exit(1);
    }

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
    MyPhysicsList* physicsList = new MyPhysicsList();
    runManager->SetUserInitialization(physicsList->Get_PhysicsList());

    std::cout << " ========== Setting MyActionInitialization ========== " << std::endl;
    runManager->SetUserInitialization(new MyActionInitialization());

    std::cout << " ========== Done ========== " << std::endl;


    G4VisManager *visManager = new G4VisExecutive();
    visManager->Initialize();

    std::cout << " \n========== Defining UI ==========\n " << std::endl;
    G4UImanager *UImanager = G4UImanager::GetUIpointer();


    if(!CUSTOM_MACRO){ // no macro files passed as arguments

        ui = new G4UIExecutive(argc, argv);
    
        UImanager->ApplyCommand("/control/execute vis.mac");
        ui->SessionStart();
    }
    else if(CUSTOM_MACRO){ // macro file, but still using UI

        std::string command = "/control/execute ";
        std::string fileName = argv[1];
        
        if(UI_USAGE){
            ui = new G4UIExecutive(argc, argv);
            UImanager->ApplyCommand(command+fileName);
            ui->SessionStart();
        }
        else{
            UImanager->ApplyCommand(command+fileName);
        }    
    }

    return 0;
}
