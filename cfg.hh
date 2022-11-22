#ifndef CFG_HH
#define CFG_HH

#include <nlohmann/json.hpp> // https://json.nlohmann.me/integration/package_managers/#homebrew
#include "G4SystemOfUnits.hh"


#define hc_constant_eV 1.23984198*eV*micrometer

#define World_X 10.*cm
#define World_Y 10.*cm
#define World_Z 10.*cm

#define Solid_Scintillator_X 5.*cm
#define Solid_Scintillator_Y 5.*cm
#define Solid_Scintillator_Z 6.*cm

#define Scintillator_Height 10.*cm
#define Scintillator_Radius 5.*cm
#define Scintillator_Scintillation_Yeld 8000./MeV
#define Scintillator_Wavelenght_MaxEmission 425*nm
#define Scintillator_Wavelenght_Min 400*nm
#define Scintillator_Wavelenght_Max 525*nm

#define Solid_Detector_X 1.*cm
#define Solid_Detector_Y 1.*cm
#define Solid_Detector_Z 1.*cm


#endif
