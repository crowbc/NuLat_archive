#include "NuLatRunAction.hh"
#include "Analysis.hh"
#include "NuLatRun.hh"

#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4RunManager.hh"

#include <iostream>
#include <fstream>
using namespace std;


NuLatRunAction::NuLatRunAction()
 : G4UserRunAction()
{

  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

  G4cout << G4endl << G4endl
    << "Using " << analysisManager->GetType() 
    << G4endl << G4endl;



  // Default settings
  analysisManager->SetVerboseLevel(1);
  analysisManager->SetFileName("NuLatOutput");

  // Creating 1D histograms
  analysisManager
    ->CreateH1("InitialEnergy","InitialEnergy", 100, 0., 10000);                            // h1 Id = 0

  analysisManager->CreateNtuple("NuLatEvent", "NuLatEvent");
  analysisManager->CreateNtupleIColumn(0, "EventID");                                       // column Id = 0
  analysisManager->CreateNtupleIColumn(0, "EventSeed");                                     // column Id = 1
  analysisManager->CreateNtupleIColumn(0, "PrimaryParticleIDNumber");                       // column Id = 2
  analysisManager->CreateNtupleDColumn(0, "PrimaryParticleKEnergy");                        // column Id = 3
  analysisManager->CreateNtupleDColumn(0, "PrimaryParticleVertexX");                        // column Id = 4
  analysisManager->CreateNtupleDColumn(0, "PrimaryParticleVertexY");                        // column Id = 5
  analysisManager->CreateNtupleDColumn(0, "PrimaryParticleVertexZ");                        // column Id = 6
  analysisManager->CreateNtupleDColumn(0, "PrimaryParticleVertexT");                        // column Id = 7
  analysisManager->CreateNtupleDColumn(0, "PrimaryParticleMomentumMagnitude");              // column Id = 8
  analysisManager->CreateNtupleDColumn(0, "PrimaryParticleMomentumX");                      // column Id = 9
  analysisManager->CreateNtupleDColumn(0, "PrimaryParticleMomentumY");                      // column Id = 10
  analysisManager->CreateNtupleDColumn(0, "PrimaryParticleMomentumZ");                      // column Id = 11
  
  
  analysisManager->CreateNtupleDColumn(0, "TotalEnergyDeposited");                          // column Id = 12
  analysisManager->CreateNtupleIColumn(0, "NumberOfCellsHit");                              // column Id = 13
  analysisManager->CreateNtupleIColumn(0, "NumberOfEnergyDepositions");                     // column Id = 14
  analysisManager->CreateNtupleIColumn(0, "NumberOfPhotonHits");                            // column Id = 15
  analysisManager->CreateNtupleIColumn(0, "NumberOfPMTHits");                               // column Id = 16
  
  


  // Cell Vectors of length column Id = 13
  analysisManager->CreateNtupleDColumn(0, "CellEdep", CellEnergyVector);                       // column Id = 17
  analysisManager->CreateNtupleIColumn(0, "CellXHitVector", CellXHitVector);                   // column Id = 18
  analysisManager->CreateNtupleIColumn(0, "CellYHitVector", CellYHitVector);                   // column Id = 19
  analysisManager->CreateNtupleIColumn(0, "CellZHitVector", CellZHitVector);                   // column Id = 20

  // Individual Energy Vectors of length column Id = 14
  analysisManager->CreateNtupleIColumn(0, "ParticleIDNumber", EDepParticleTypeIDNumberVector); // column Id = 21
  analysisManager->CreateNtupleDColumn(0, "ParticleEDep", EDepParticleEDepVector);             // column Id = 22
  analysisManager->CreateNtupleDColumn(0, "XPosition", EDepPositionXVector);                   // column Id = 23
  analysisManager->CreateNtupleDColumn(0, "YPosition", EDepPositionYVector);                   // column Id = 24
  analysisManager->CreateNtupleDColumn(0, "ZPosition", EDepPositionZVector);                   // column Id = 25
  analysisManager->CreateNtupleDColumn(0, "TimeFromEventStart", EDepTimeVector);               // column Id = 26

  //
  analysisManager->CreateNtupleIColumn(0, "PMTPE", PMTPEVector);                               // column Id = 27
  analysisManager->CreateNtupleIColumn(0, "PMTXPEVector", PMTXPEVector);                       // column Id = 28
  analysisManager->CreateNtupleIColumn(0, "PMTYPEVector", PMTYPEVector);                       // column Id = 29
  analysisManager->CreateNtupleIColumn(0, "PMTZPEVector", PMTZPEVector);                       // column Id = 30

  analysisManager->CreateNtupleDColumn(0, "PhotonWavelength", PhotonPMTHitWavelengthVector);   // column Id = 31
  analysisManager->CreateNtupleIColumn(0, "PMTXPosition", PhotonPMTXHitVector);                // column Id = 32
  analysisManager->CreateNtupleIColumn(0, "PMTYPosition", PhotonPMTYHitVector);                // column Id = 33
  analysisManager->CreateNtupleIColumn(0, "PMTZPosition", PhotonPMTZHitVector);                // column Id = 34
  analysisManager->CreateNtupleDColumn(0, "PhotonTimeFromEventStart", PhotonPMTHitTimeVector); // column Id = 35


  analysisManager->FinishNtuple(0);


}



NuLatRunAction::~NuLatRunAction()
{

  delete G4AnalysisManager::Instance();  
}



void NuLatRunAction::BeginOfRunAction(const G4Run* /*run*/)
{

  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

  analysisManager->OpenFile();

}



void NuLatRunAction::EndOfRunAction(const G4Run* run)
{
	const NuLatRun* myrun = dynamic_cast<const NuLatRun*>(run);
	if ( myrun )
	{
		G4int nEvets = myrun->GetNumberOfEvent();
		if ( nEvets < 1 )
		{
			G4ExceptionDescription msg;
			msg << "Run consists of 0 events";
			G4Exception("NuLatRunAction::EndOfRunAction()",
					"Code001", JustWarning, msg);
			nEvets=1;
		}

		G4double NuLat_energy = myrun->GetNuLatEnergy();
		G4cout<<G4endl<<G4endl
		      <<"End of Run Action" << G4endl
		      <<"  Run["<<myrun->GetRunID()<<"] With: "<<nEvets<<" Events" << G4endl
		      <<"  <E_em> = "<<G4BestUnit(NuLat_energy/nEvets,"Energy")<<G4endl
		      <<G4endl<<G4endl;
	}
	else
	{
		G4ExceptionDescription msg;
		msg << "Run is not of correct type, skipping analysis via RunAction";
		G4Exception("NuLatRunAction::EndOfRunAction()",
			"Code001", JustWarning, msg);
	}
	G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  analysisManager->Write();
  analysisManager->CloseFile();
}


G4Run* NuLatRunAction::GenerateRun() {
    return new NuLatRun;
}

/*

  // Default settings
  analysisManager->SetVerboseLevel(1);
  analysisManager->SetFileName("NuLatOutput");



  analysisManager->CreateNtuple("NuLatEvent", "NuLatEvent");
  analysisManager->CreateNtupleIColumn(0, "Event ID");                                         // column Id = 0
  analysisManager->CreateNtupleIColumn(0, "Event Seed");                                       // column Id = 1
  analysisManager->CreateNtupleIColumn(0, "Primary Particle ID Number");                       // column Id = 2
  analysisManager->CreateNtupleDColumn(0, "Primary Particle K Energy");                        // column Id = 3
  analysisManager->CreateNtupleDColumn(0, "Primary Particle Vertex X");                        // column Id = 4
  analysisManager->CreateNtupleDColumn(0, "Primary Particle Vertex Y");                        // column Id = 5
  analysisManager->CreateNtupleDColumn(0, "Primary Particle Vertex Z");                        // column Id = 6
  analysisManager->CreateNtupleDColumn(0, "Primary Particle Vertex T");                        // column Id = 7
  analysisManager->CreateNtupleDColumn(0, "Primary Particle Momentum Magnitude");              // column Id = 8
  analysisManager->CreateNtupleDColumn(0, "Primary Particle Momentum X");                      // column Id = 9
  analysisManager->CreateNtupleDColumn(0, "Primary Particle Momentum Y");                      // column Id = 10
  analysisManager->CreateNtupleDColumn(0, "Primary Particle Momentum Z");                      // column Id = 11
  
  
  analysisManager->CreateNtupleDColumn(0, "Total Energy");                                     // column Id = 12
  analysisManager->CreateNtupleIColumn(0, "Number Of Cells Hit");                              // column Id = 13
  analysisManager->CreateNtupleIColumn(0, "Number Of Energy Depositions");                     // column Id = 14


  // Cell Vectors of length column Id = 13
  analysisManager->CreateNtupleDColumn(0, "CellEdep", CellEnergyVector);                       // column Id = 15
  analysisManager->CreateNtupleIColumn(0, "CellXHitVector", CellXHitVector);                   // column Id = 16
  analysisManager->CreateNtupleIColumn(0, "CellYHitVector", CellYHitVector);                   // column Id = 17
  analysisManager->CreateNtupleIColumn(0, "CellZHitVector", CellZHitVector);                   // column Id = 18

  // Individual Energy Vectors of length column Id = 14
  analysisManager->CreateNtupleIColumn(0, "ParticleIDNumber", EDepParticleTypeIDNumberVector); // column Id = 19
  analysisManager->CreateNtupleDColumn(0, "ParticleEDep", EDepParticleEDepVector);             // column Id = 20
  analysisManager->CreateNtupleDColumn(0, "X Position", EDepPositionXVector);                  // column Id = 21
  analysisManager->CreateNtupleDColumn(0, "Y Position", EDepPositionYVector);                  // column Id = 22
  analysisManager->CreateNtupleDColumn(0, "Z Position", EDepPositionZVector);                  // column Id = 23
  analysisManager->CreateNtupleDColumn(0, "Time From Event Start", EDepTimeVector);            // column Id = 24


  analysisManager->FinishNtuple(0);
*/
