#ifndef ESENSITIVEDETECTOR_HH
#define ESENSITIVEDETECTOR_HH

#include "G4VSensitiveDetector.hh"

#include "G4RunManager.hh"
#include "G4AnalysisManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"

class ESensitiveDetector : public G4VSensitiveDetector
{
public:
    ESensitiveDetector(G4String);
    ~ESensitiveDetector();

private:
    G4double fTotalEnergyDeposited_0;
    G4double fTotalEnergyDeposited_1;

    virtual void Initialize(G4HCofThisEvent *) override;
    virtual void EndOfEvent(G4HCofThisEvent *) override;

    virtual G4bool ProcessHits(G4Step *, G4TouchableHistory *);
};

#endif