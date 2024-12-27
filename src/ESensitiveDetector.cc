#include "ESensitiveDetector.hh"

ESensitiveDetector::ESensitiveDetector(G4String name) : G4VSensitiveDetector(name)
{
    fTotalEnergyDeposited_0 = 0.;
    fTotalEnergyDeposited_1 = 0.;
}

ESensitiveDetector::~ESensitiveDetector()
{
    
}

void ESensitiveDetector::Initialize(G4HCofThisEvent *)
{
    fTotalEnergyDeposited_0 = 0.;
    fTotalEnergyDeposited_1 = 0.;
}

void ESensitiveDetector::EndOfEvent(G4HCofThisEvent *)
{
    G4AnalysisManager *analysisManager = G4AnalysisManager::Instance();

    G4int eventID = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();

    // Check if enough energy was deposited to pass the threshold
    G4double thresholdEnergy = 30 * keV;
    if(fTotalEnergyDeposited_0 < thresholdEnergy)
    {
        fTotalEnergyDeposited_0 = 0;
    }
    if(fTotalEnergyDeposited_1 < thresholdEnergy)
    {
        fTotalEnergyDeposited_1 = 0;
    }

    analysisManager->FillNtupleIColumn(0, 0, eventID);
    analysisManager->FillNtupleDColumn(0, 1, fTotalEnergyDeposited_0);
    analysisManager->FillNtupleDColumn(0, 2, fTotalEnergyDeposited_1);
    analysisManager->AddNtupleRow(0);
    
    // G4cout << "Deposited energy: " << fTotalEnergyDeposited << G4endl;
}

G4bool ESensitiveDetector::ProcessHits(G4Step *aStep, G4TouchableHistory *)
{
    G4int eventID = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();

    G4AnalysisManager *analysisManager = G4AnalysisManager::Instance();

    G4StepPoint *preStepPoint = aStep->GetPreStepPoint();

    // G4double fGlobalTime = preStepPoint->GetGlobalTime();
    // G4ThreeVector posPhoton = preStepPoint->GetPosition();
    // G4ThreeVector momPhoton = preStepPoint->GetMomentum();
    // G4double fMomPhotonMag = momPhoton.mag();

    const G4VTouchable *touchable = aStep->GetPreStepPoint()->GetTouchable();
    G4int copyNo = touchable->GetCopyNumber(1);
    // G4int replicaNo = touchable->GetReplicaNumber(1);
    // G4VPhysicalVolume *physVol = touchable->GetVolume(1);
	// G4ThreeVector posDetector = physVol->GetTranslation();

    // G4cout << "Copy number: " << copyNo << G4endl;
    // G4cout << "Replica number: " << replicaNo << G4endl;
    // G4cout << "Detector position: " << posDetector << G4endl;

    // analysisManager->FillNtupleIColumn(0, 0, eventID);
    // analysisManager->FillNtupleDColumn(0, 1, posPhoton[0]);
    // analysisManager->FillNtupleDColumn(0, 2, posPhoton[1]);
    // analysisManager->FillNtupleDColumn(0, 3, posPhoton[2]);
    // analysisManager->FillNtupleDColumn(0, 4, fGlobalTime);
    // analysisManager->AddNtupleRow(0);

    G4double fEnergyDeposited = aStep->GetTotalEnergyDeposit();

    if (fEnergyDeposited > 0)
    {
        if (copyNo == 0)
        {
            fTotalEnergyDeposited_0 += fEnergyDeposited;
        }
        if (copyNo == 1)
        {
            fTotalEnergyDeposited_1 += fEnergyDeposited;
        }
    }

    return true;
}