#ifndef SCINTILLATOR_HH
#define SCINTILLATOR_HH

#include "G4VUserDetectorConstruction.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4PVPlacement.hh"
#include "G4NistManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4GenericMessenger.hh"
#include "G4OpticalSurface.hh"
#include "G4LogicalBorderSurface.hh"
#include "G4LogicalSkinSurface.hh"

#include "detector.hh"
#include "cfg.hh"

class ScintillatorConstruction : public G4VUserDetectorConstruction{
    
public:
    /**
     * @brief Class Constructor...
     * 
     * @return * Class 
     */
    ScintillatorConstruction();

    /**
     * @brief Destroy the Scintillator Construction object
     * 
     */
    ~ScintillatorConstruction();

    /**
     * @brief Get the Scoring Volume object
     * 
     * @return G4LogicalVolume* 
     */
    virtual G4LogicalVolume* GetScoringVolume() const;

    /**
     * @brief Construct All
     * 
     * @return G4VPhysicalVolume* 
     */
    virtual G4VPhysicalVolume* Construct();

private:
    std::vector<G4double> 
        wavelenghts,
        energy,
        rindex_PlasticSC,
        rindexWorld,
        reflectivity;

    G4NistManager* nIst;

    G4Tubs* solidScintillator;

    G4Box 
        *solidWorld, 
        *solidRadiator, 
        *solidDetector;

    G4LogicalVolume 
        *logicWorld, 
        *logicRadiator, 
        *logicDetector, 
        *logicScintillator, 
        *fScoringVolume;

    G4VPhysicalVolume 
        *physWorld, 
        *physDetector, 
        *physRadiator, 
        *physScintillator;

    G4OpticalSurface* mirrorSurface;

    G4LogicalSkinSurface* skin;

    G4Material 
        *plastic_SC_material,
        *world_material;

    G4GenericMessenger *fMessenger;

    G4int nRows, nCols;

    /**
     * @brief 
     * 
     */
    virtual void ConstructSDandField();
    
    /**
     * @brief 
     * 
     * @return G4VPhysicalVolume* 
     */
    virtual G4VPhysicalVolume* World();

    /**
     * @brief Construct the Solids and Logical Volumes 
     * for the scintillator and detector
     * 
     */
    void Detector();

    /**
     * @brief 
     * 
     */
    void Scintillator();

    /**
     * 
    */
    void MirrorSurface();
};

#endif
