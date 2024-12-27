#include "ERunAction.hh"

ERunAction::ERunAction()
{
    G4AnalysisManager *analysisManager = G4AnalysisManager::Instance();

    // analysisManager->CreateNtuple("Photons", "Photons");
    // analysisManager->CreateNtupleIColumn("iEvent");
    // analysisManager->CreateNtupleDColumn("fX");
    // analysisManager->CreateNtupleDColumn("fY");
    // analysisManager->CreateNtupleDColumn("fZ");
    // analysisManager->CreateNtupleDColumn("fGlobalTime");
    // analysisManager->FinishNtuple(0);

    analysisManager->CreateNtuple("Scoring", "Scoring");
    analysisManager->CreateNtupleIColumn("iEvent");
    analysisManager->CreateNtupleDColumn("energy1");
    analysisManager->CreateNtupleDColumn("energy2");
    analysisManager->FinishNtuple(0);
}

ERunAction::~ERunAction()
{
    
}

void ERunAction::BeginOfRunAction(const G4Run *run)
{
    G4AnalysisManager *analysisManager = G4AnalysisManager::Instance();

    G4int runID = run->GetRunID();

    std::stringstream strRunID;
    strRunID << runID;

    analysisManager->OpenFile("output" + strRunID.str() + ".root");
}

void ERunAction::EndOfRunAction(const G4Run *run)
{
    G4AnalysisManager *analysisManager = G4AnalysisManager::Instance();

    analysisManager->Write();

    analysisManager->CloseFile();

    G4int runID = run->GetRunID();

    G4cout << "Finishing run " << runID << G4endl;
}