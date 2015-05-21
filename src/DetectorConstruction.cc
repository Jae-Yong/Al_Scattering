#include "DetectorConstruction.hh"

#include "G4SystemOfUnits.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"

#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"

#include "G4Box.hh"
#include "G4Hype.hh"

#include "AlSD.hh"
#include "WallSD.hh"

#include "G4VisAttributes.hh"

DetectorConstruction::DetectorConstruction()
: G4VUserDetectorConstruction()
{ }

DetectorConstruction::~DetectorConstruction()
{ }

G4VPhysicalVolume* DetectorConstruction::Construct()
{  
  // Get nist material manager
  G4NistManager* nist = G4NistManager::Instance();
   
  // Option to switch on/off checking of volumes overlaps
  //
  G4bool checkOverlaps = true;

  //     
  // World
  //
  G4double world_sizeXY = 100*cm;
  G4double world_sizeZ  = 350*cm;
  G4Material* world_mat = nist->FindOrBuildMaterial("G4_Galactic");
  
  G4VSolid* solidWorld =
    new G4Box("World",                          //its name
    world_sizeXY, world_sizeXY, world_sizeZ);   //its size
    
  G4LogicalVolume* logicWorld =                         
  new G4LogicalVolume(solidWorld,     //its solid
            world_mat,                //its material
            "World");                 //its name

  G4VPhysicalVolume* physWorld = 
  new G4PVPlacement(0,                    //no rotation
            G4ThreeVector(),              //at (0,0,0)
            logicWorld,                   //its logical volume
            "World",                      //its name
            0,                            //its mother  volume
            false,                        //no boolean operation
            0,                            //copy number
            checkOverlaps);               //overlaps checking

  //
  // Al degrader
  //

  G4Material* Al_mat = nist->FindOrBuildMaterial("G4_Al");

  G4double Al_xy = 20 / 2 * cm;
  G4double Al_z = 0.2 / 2 * mm;
  G4VSolid* Al_box = new G4Box("Al_box", Al_xy, Al_xy, Al_z);
  G4LogicalVolume* Al_LV = new G4LogicalVolume(Al_box, Al_mat, "Al_LV");

  new G4PVPlacement(0,
                                      G4ThreeVector(0, 0, - Al_z),
                                      Al_LV,
                                      "Al_PV",
                                      logicWorld,
                                      false,
                                      0,
                                      checkOverlaps);

  //
  // iron wall
  //

  G4double gap = 250 * cm;

  G4Material* Fe_mat = nist->FindOrBuildMaterial("G4_Fe");

  G4double Fe_xy = 100 / 2 * cm;
  G4double Fe_z = 1 * cm;
  G4VSolid* Fe_box = new G4Box("Fe_box", Fe_xy, Fe_xy, Fe_z);
  G4LogicalVolume* Fe_LV = new G4LogicalVolume(Fe_box, Fe_mat, "Fe_LV");

  new G4PVPlacement(0,
                                      G4ThreeVector(0, 0, Fe_z + gap),
                                      Fe_LV,
                                      "Fe_PV",
                                      logicWorld,
                                      false,
                                      0,
                                      checkOverlaps);

  //
  //always return the physical World
  //
  return physWorld;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::ConstructSDandField()
{
  AlSD* Al_sd = AlSD::GetInstance();
  SetSensitiveDetector("Al_LV", Al_sd);

  WallSD* wall_sd = WallSD::GetInstance();
  SetSensitiveDetector("Fe_LV", wall_sd);
}