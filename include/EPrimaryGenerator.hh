#ifndef EPRIMARYGENERATOR_HH
#define EPRIMARYGENERATOR_HH

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4ChargedGeantino.hh"
#include "G4IonTable.hh"
#include "Randomize.hh"

class EPrimaryGenerator : public G4VUserPrimaryGeneratorAction
{
public:
    EPrimaryGenerator();
    ~EPrimaryGenerator();

    virtual void GeneratePrimaries(G4Event *);

private:
    G4ParticleGun *fParticleGun;
};

#endif