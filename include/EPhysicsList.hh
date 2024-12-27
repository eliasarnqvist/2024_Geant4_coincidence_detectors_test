#ifndef EPHYSICSLIST_HH
#define EPHYSICSLIST_HH

#include "G4VModularPhysicsList.hh"
#include "G4EmStandardPhysics.hh"
#include "G4DecayPhysics.hh"
#include "G4RadioactiveDecayPhysics.hh"

class EPhysicsList : public G4VModularPhysicsList
{
public:
    EPhysicsList();
    ~EPhysicsList();
};

#endif