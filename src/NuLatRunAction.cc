//RUN ACTION FILE
//Actions to do at Beginning/During/After Run
//Sets up Data structures and saves results

#include "NuLatRunAction.hh"
#include "Analysis.hh"
#include "NuLatRun.hh"

#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4RunManager.hh"

#include <iostream>
#include <fstream>
using namespace std;


//Constructor
NuLatRunAction::NuLatRunAction()
 : G4UserRunAction()
{
  //Gets analysis manager
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

  G4cout << G4endl << G4endl
    << "Using " << analysisManager->GetType() 
    << G4endl << G4endl;



  //Setting FileName and verbose level
  analysisManager->SetVerboseLevel(1);
  analysisManager->SetFileName("NuLatOutput.root");




//Collection of run values (what we start with and total counts in each file)
  analysisManager->CreateNtuple("NuLatEvent", "NuLatEvent");     
  analysisManager->CreateNtupleIColumn(0, "EventID");                                      // column Id = 0 
  analysisManager->CreateNtupleIColumn(0, "EventSeed");                                        // column Id = 1
  analysisManager->CreateNtupleIColumn(0, "PrimaryParticleIDNumber");                       // column Id = 2
  analysisManager->CreateNtupleDColumn(0, "PrimaryParticleKEnergy");                            // column Id = 3
  analysisManager->CreateNtupleDColumn(0, "PrimaryParticleVertexX");                          // column Id = 4
  analysisManager->CreateNtupleDColumn(0, "PrimaryParticleVertexY");                          // column Id = 5
  analysisManager->CreateNtupleDColumn(0, "PrimaryParticleVertexZ");                            // column Id = 6
  analysisManager->CreateNtupleDColumn(0, "PrimaryParticleVertexT");                           // column Id = 7
  analysisManager->CreateNtupleDColumn(0, "PrimaryParticleMomentumMagnitude");                    // column Id = 8
  analysisManager->CreateNtupleDColumn(0, "PrimaryParticleMomentumX");                         // column Id = 9
  analysisManager->CreateNtupleDColumn(0, "PrimaryParticleMomentumY");                         // column Id = 10
  analysisManager->CreateNtupleDColumn(0, "PrimaryParticleMomentumZ");                          // column Id = 11
  
  
  analysisManager->CreateNtupleDColumn(0, "TotalEnergyDeposited");                              // column Id = 12
  analysisManager->CreateNtupleIColumn(0, "NumberOfCellsHit");                                    // column Id = 13
  analysisManager->CreateNtupleIColumn(0, "NumberOfEnergyDepositions");                        // column Id = 14
  analysisManager->CreateNtupleIColumn(0, "NumberOfPhotonHits");                           // column Id = 15
  analysisManager->CreateNtupleIColumn(0, "NumberOfPMTHits");                                  // column Id = 16
  analysisManager->CreateNtupleIColumn(0, "CenterCubePMTHits");    
  analysisManager->CreateNtupleDColumn(0, "CenterCubeDirectHits");      
  
  analysisManager->FinishNtuple(0);  


//Collection of each Voxel's total counts
//CellEdep originally collected in Voxel Sensitive Detector then pushed through EventAction, Rest created in EventAction  
  analysisManager->CreateNtuple("VoxelHits", "VoxelHits");     
  analysisManager->CreateNtupleDColumn(1, "CellEdep");                            // column Id = 17
  analysisManager->CreateNtupleIColumn(1, "CellXHitVector");                       // column Id = 18
  analysisManager->CreateNtupleIColumn(1, "CellYHitVector");                       // column Id = 19
  analysisManager->CreateNtupleIColumn(1, "CellZHitVector");                         // column Id = 20
  analysisManager->FinishNtuple(1);
  
  
//Collection of each particle in Voxels
//Oringally collected in Voxel Sensitive Detector, then pushed through EventAction
  analysisManager->CreateNtuple("ParticlesInVoxel", "ParticlesInVoxel");     
  analysisManager->CreateNtupleIColumn(2, "ParticleIDNumber");      // column Id = 21
  analysisManager->CreateNtupleDColumn(2, "ParticleEDep");                   // column Id = 22
  analysisManager->CreateNtupleDColumn(2, "XPosition");                      // column Id = 23
  analysisManager->CreateNtupleDColumn(2, "YPosition");                      // column Id = 24
  analysisManager->CreateNtupleDColumn(2, "ZPosition");                        // column Id = 25
  analysisManager->CreateNtupleDColumn(2, "TimeFromEventStart");                     // column Id = 26
  analysisManager->CreateNtupleDColumn(2, "XMomentum"); 
  analysisManager->CreateNtupleDColumn(2, "YMomentum"); 
  analysisManager->CreateNtupleDColumn(2, "ZMomentum");   
  analysisManager->FinishNtuple(2);
  

//Collection for each PMT's total counts  
//PMTPE originally collected in PMT Sensitive Detector then pushed through EventAction, Rest created in EventAction
  analysisManager->CreateNtuple("PMThits", "PMThits");     
  analysisManager->CreateNtupleIColumn(3, "PMTPE");                                   //Number of Hits in a PMT
  analysisManager->CreateNtupleIColumn(3, "PMTXPEVector");                            //X Position of PMT
  analysisManager->CreateNtupleIColumn(3, "PMTYPEVector");                            //Y Position of PMT
  analysisManager->CreateNtupleIColumn(3, "PMTZPEVector");                            //Z Position of PMT
  analysisManager->FinishNtuple(3);


//Collection of each photon event in PMTs
//Collected lists saved in PMT Sensitive Detector
  analysisManager->CreateNtuple("PhotonsInPMT", "PhotonsInPMT");     
  analysisManager->CreateNtupleDColumn(4, "PhotonEnergy");
  analysisManager->CreateNtupleDColumn(4, "PhotonWavelength");        // column Id = 31
  analysisManager->CreateNtupleIColumn(4, "PMTXPosition");                   // column Id = 32
  analysisManager->CreateNtupleIColumn(4, "PMTYPosition");                      // column Id = 33
  analysisManager->CreateNtupleIColumn(4, "PMTZPosition");                     // column Id = 34
  analysisManager->CreateNtupleDColumn(4, "PhotonTimeFromEventStart");      // column Id = 35
  analysisManager->FinishNtuple(4);


}


//Destructor
NuLatRunAction::~NuLatRunAction()
{

  delete G4AnalysisManager::Instance();  
}


//Beginning of Run Actions (opens data file)
void NuLatRunAction::BeginOfRunAction(const G4Run* /*run*/)
{

  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

  analysisManager->OpenFile();

}


//End of Run Actions (check for errors, write results, and close data file
void NuLatRunAction::EndOfRunAction(const G4Run* run)
{
// Get analysis manager
    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();














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
//	G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  analysisManager->Write();
  analysisManager->CloseFile();
}

//Starts Run
G4Run* NuLatRunAction::GenerateRun() {
    return new NuLatRun;
}


