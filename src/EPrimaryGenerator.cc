#include "EPrimaryGenerator.hh"

EPrimaryGenerator::EPrimaryGenerator()
{
    fParticleGun = new G4ParticleGun(1);

    // Particle position
    G4double x = 0. * m;
    G4double y = 0. * m;
    G4double z = 0. * m;
    G4ThreeVector pos(x, y, z);

    // Particle direction
    G4double px = 0.;
    G4double py = 0.;
    G4double pz = 1.;
    G4ThreeVector mom(px, py, pz);

    // Particle type
    G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
    // G4ParticleDefinition *particle = particleTable->FindParticle("gamma");
    G4ParticleDefinition *particle = particleTable->FindParticle("chargedgeantino");

    fParticleGun->SetParticlePosition(pos);
    fParticleGun->SetParticleMomentumDirection(mom);
    fParticleGun->SetParticleEnergy(0. * MeV);
    fParticleGun->SetParticleDefinition(particle);
}

EPrimaryGenerator::~EPrimaryGenerator()
{
    delete fParticleGun;
}

void EPrimaryGenerator::GeneratePrimaries(G4Event *anEvent)
{
    G4ParticleDefinition* particle = fParticleGun->GetParticleDefinition();
    if (particle == G4ChargedGeantino::ChargedGeantino())
    {
        // Co-60 source at rest
        G4int Z = 27;
        G4int A = 60;
        G4double charge = 0.*eplus;
        G4double energy = 0.*keV;

        G4ParticleDefinition *ion = G4IonTable::GetIonTable()->GetIon(Z, A, energy);

        fParticleGun->SetParticleDefinition(ion);
        fParticleGun->SetParticleCharge(charge);
    }

    // randomized position
    ///G4double x0  = 0*cm, y0  = 0*cm, z0  = 0*cm;
    ///G4double dx0 = 0*cm, dy0 = 0*cm, dz0 = 0*cm;
    G4double x0  = 0*cm, y0  = 0*cm, z0  = 0*cm;
    G4double dx0 = 1*cm, dy0 = 1*cm, dz0 = 1*cm;
    x0 += dx0*(G4UniformRand()-0.5);
    y0 += dy0*(G4UniformRand()-0.5);
    z0 += dz0*(G4UniformRand()-0.5);
    fParticleGun->SetParticlePosition(G4ThreeVector(x0,y0,z0));

    // Create vertex
    fParticleGun->GeneratePrimaryVertex(anEvent);
}