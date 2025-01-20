#ifndef EDETECTORCONSTRUCTION_HH
#define EDETECTORCONSTRUCTION_HH

#include "G4VUserDetectorConstruction.hh"

#include "G4Box.hh"
#include "G4Tubs.hh"

#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4Material.hh"

#include "G4NistManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"

#include "G4VisAttributes.hh"
#include "G4Color.hh"
#include "G4SDManager.hh"

#include "ESensitiveDetector.hh"

class EDetectorConstruction : public G4VUserDetectorConstruction
{
public:
    EDetectorConstruction();
    virtual ~EDetectorConstruction();

    virtual G4VPhysicalVolume *Construct();

private:
    G4LogicalVolume *logicDetector;

    virtual void ConstructSDandField();
};

#endif