#include "EPhysicsList.hh"

EPhysicsList::EPhysicsList()
{
    // EM physics
    RegisterPhysics(new G4EmStandardPhysics());

    // decay physics
	RegisterPhysics (new G4DecayPhysics());
	
    // radioactive decay
    RegisterPhysics (new G4RadioactiveDecayPhysics());
}

EPhysicsList::~EPhysicsList()
{
    
}