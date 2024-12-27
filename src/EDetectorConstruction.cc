#include "EDetectorConstruction.hh"

EDetectorConstruction::EDetectorConstruction()
{

}

EDetectorConstruction::~EDetectorConstruction()
{
    
}

G4VPhysicalVolume *EDetectorConstruction::Construct()
{
    G4bool checkOverlaps = true;

    G4NistManager *nist = G4NistManager::Instance();
    G4Material *worldMat = nist->FindOrBuildMaterial("G4_AIR");
    // G4Material *leadMat = nist->FindOrBuildMaterial("G4_Pb");
    G4Material *germaniumMat = nist->FindOrBuildMaterial("G4_Ge");
    G4Material *aluminiumMat = nist->FindOrBuildMaterial("G4_Al");

    G4double xWorld = 1. * m;
    G4double yWorld = 1. * m;
    G4double zWorld = 1. * m;
    G4Box *solidWorld = new G4Box("solidWorld", 0.5 * xWorld, 0.5 * yWorld, 0.5 * zWorld);
    G4LogicalVolume *logicWorld = new G4LogicalVolume(solidWorld, worldMat, "logicWorld");
    G4VPhysicalVolume *physWorld = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicWorld, "physWorld", 0, false, 0, checkOverlaps);

    G4double capInnerDiameter = 0 * cm;
    G4double capOuterDiameter = 8.1 * cm;
    G4double capLength = 8.1 * cm;
    G4double capPos = 5 * cm;
    G4Tubs *solidCap = new G4Tubs("solidCap", 0.5 * capInnerDiameter, 0.5 * capOuterDiameter, 0.5 * capLength, 0. * deg, 360. * deg);
    G4LogicalVolume *logicCap = new G4LogicalVolume(solidCap, aluminiumMat, "logicCap");
    G4VPhysicalVolume *physCap1 = new G4PVPlacement(0, G4ThreeVector(0., 0., capPos), logicCap, "physCap", logicWorld, false, 0, checkOverlaps);
    G4VPhysicalVolume *physCap2 = new G4PVPlacement(0, G4ThreeVector(0., 0., -capPos), logicCap, "physCap", logicWorld, false, 1, checkOverlaps);

    G4double detectorInnerDiameter = 0 * cm;
    G4double detectorOuterDiameter = 8 * cm;
    G4double detectorLength = 8 * cm;
    G4Tubs *solidDetector = new G4Tubs("solidDetector", 0.5 * detectorInnerDiameter, 0.5 * detectorOuterDiameter, 0.5 * detectorLength, 0. * deg, 360. * deg);
    logicDetector = new G4LogicalVolume(solidDetector, germaniumMat, "logicDetector");
    G4VPhysicalVolume *physDetector = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicDetector, "physDetector", logicCap, false, 0, checkOverlaps);

    // Colors for display purposes

    G4VisAttributes *capVisAtt = new G4VisAttributes(G4Color(1.0, 0.0, 0.0, 0.5));
    capVisAtt->SetForceSolid(true);
    logicCap->SetVisAttributes(capVisAtt);

    G4VisAttributes *detVisAtt = new G4VisAttributes(G4Color(1.0, 1.0, 0.0, 0.5));
    detVisAtt->SetForceSolid(true);
    logicDetector->SetVisAttributes(detVisAtt);

    return physWorld;
}

void EDetectorConstruction::ConstructSDandField()
{
    ESensitiveDetector *sensDet = new ESensitiveDetector("ESensitiveDetector");
    logicDetector->SetSensitiveDetector(sensDet);
    G4SDManager::GetSDMpointer()->AddNewDetector(sensDet);
}