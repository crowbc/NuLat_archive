//Clean up fECHCID, ecHC variables.  These are relics from SLAC tutorial
#include "math.h"

#include "NuLatEventAction.hh"
#include "NuLatRunAction.hh"

#include "NuLatVoxelHit.hh"
#include "NuLatPhotoCathodeHit.hh"

#include "Analysis.hh"

#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4EventManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4VHitsCollection.hh"
#include "G4SDManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4ios.hh"


#include <iostream>
#include <fstream>
using namespace std;
using namespace CLHEP;


#include "Randomize.hh"

#include "globals.hh"

#include "G4RandomDirection.hh"




/*


*/


//Constructor
NuLatEventAction::NuLatEventAction(int xVoxels, int yVoxels, int zVoxels)
: G4UserEventAction(), 
  fECHCID(-1), fPCHCID(-1)
{
  // set printing per each event
  G4RunManager::GetRunManager()->SetPrintProgress(1);
  localNOfVoxelsInX = xVoxels;
  localNOfVoxelsInY = yVoxels;
  localNOfVoxelsInZ = zVoxels;
  NuLatRunActionLocal = NULL;
  outputFile = NULL;
}



//Destructor
NuLatEventAction::~NuLatEventAction()
{}


//
//
//
//Actions to be run at beggining of event
//Prints "Begin of event" before the first event
//Get hits collections IDs (only once)
void NuLatEventAction::BeginOfEventAction(const G4Event* event)
{
  int eventNumber = event->GetEventID();

  if(eventNumber%1000 == 0)
  {
    if (eventNumber == 0) G4cout << G4endl << G4endl << G4endl << G4endl << G4endl << G4endl;
    G4cout << "Begin of event " << eventNumber << G4endl;
  }
  if (fECHCID==-1) {
    G4SDManager* sdManager = G4SDManager::GetSDMpointer();
    fECHCID = sdManager->GetCollectionID("NuLatVoxel/NuLatVoxelColl"); //
  }
  if (fPCHCID==-1) {
    G4SDManager* sdManager = G4SDManager::GetSDMpointer();
    fPCHCID = sdManager->GetCollectionID("nuLatPhotoCathode/NuLatPhotoCathodeColl"); //
  }
}






//Actions to be run at end of event
void NuLatEventAction::EndOfEventAction(const G4Event* event)
{

    G4HCofThisEvent* hce = event->GetHCofThisEvent();
    if (!hce) 
    {
        G4ExceptionDescription msg;
        msg << "No hits collection of this event found.\n"; 
        G4Exception("NuLatEventAction::EndOfEventAction()",
                    "Code001", JustWarning, msg);
        return;
    }   


    // Get hits collections 

      
    NuLatVoxelHitsCollection* ecHC 
      = static_cast<NuLatVoxelHitsCollection*>(hce->GetHC(fECHCID));


    NuLatPhotoCathodeHitsCollection* pcHC 
      = static_cast<NuLatPhotoCathodeHitsCollection*>(hce->GetHC(fPCHCID));
      

    if ((!ecHC))
    {
        G4ExceptionDescription msg;
        msg << "Some of hits collections of this event not found.\n";
        G4Exception("NuLatEventAction::EndOfEventAction()",
                    "Code001", JustWarning, msg);
        return;
    }

    if ((!pcHC))
    {
        G4ExceptionDescription msg;
        msg << "Some of hits collections of this event not found.\n";
        G4Exception("NuLatEventAction::EndOfEventAction()",
                    "Code001", JustWarning, msg);
        return;
    }


    // Get analysis manager
    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

//Get event ID
    G4int eventNumber=event->GetEventID();
//Get primary particle name (particle created at beginning of simulation)
    G4PrimaryParticle* primaryParticle = event->GetPrimaryVertex(0)->GetPrimary(0);
    

    G4long eventSeed;
    eventSeed = G4Random::getTheSeed();

//Changes value of primary particle to numerical value (Check how much this slows program)
    G4int primaryParticleIDNumber;
    if(primaryParticle->GetG4code()->GetParticleName()=="gamma")          primaryParticleIDNumber=1;
    else if(primaryParticle->GetG4code()->GetParticleName()=="e-")        primaryParticleIDNumber=2;
    else if(primaryParticle->GetG4code()->GetParticleName()=="e+")        primaryParticleIDNumber=3;
    else if(primaryParticle->GetG4code()->GetParticleName()=="neutron")   primaryParticleIDNumber=4;
    else if(primaryParticle->GetG4code()->GetParticleName()=="proton")    primaryParticleIDNumber=5;
    else if(primaryParticle->GetG4code()->GetParticleName()=="mu+")       primaryParticleIDNumber=6;
    else if(primaryParticle->GetG4code()->GetParticleName()=="mu-")       primaryParticleIDNumber=7;
    else if(primaryParticle->GetG4code()->GetParticleName()=="alpha")     primaryParticleIDNumber=8;
    else if(primaryParticle->GetG4code()->GetParticleName()=="Li7")       primaryParticleIDNumber=9;
    else primaryParticleIDNumber=0;

//Gets kinetic energy value of primary particle    
    G4double primaryParticleInitialKE = primaryParticle->GetKineticEnergy();

//Gets position and time values of primary particle
    G4double primaryParticlePosX = event->GetPrimaryVertex(0)->GetX0();
    G4double primaryParticlePosY = event->GetPrimaryVertex(0)->GetY0();
    G4double primaryParticlePosZ = event->GetPrimaryVertex(0)->GetZ0();
    G4double primaryParticleTime = event->GetPrimaryVertex(0)->GetT0();

//Gets momentum values of primary particle
    G4double primaryParticleMomentum = primaryParticle->GetMomentum().mag();    
    G4double primaryParticleMomentumX = primaryParticle->GetMomentum().getX();
    G4double primaryParticleMomentumY = primaryParticle->GetMomentum().getY();
    G4double primaryParticleMomentumZ = primaryParticle->GetMomentum().getZ();





    G4int totalNuLatVoxelHit = 0;
    G4double totalNuLatVoxelEnergy = 0.;
    for (G4int i=0;i<localNOfVoxelsInX*localNOfVoxelsInY*localNOfVoxelsInY;i++)
    {
//Creates hit container for each voxel    
        NuLatVoxelHit* hit = (*ecHC)[i];
//Gets the energy deposited in the hit        
        G4double eDep = hit->GetEdep();
        if (eDep>0.)
        {
            totalNuLatVoxelHit++;                                                                       //Adds 1 tally to Voxel hit counter
            totalNuLatVoxelEnergy += eDep;                                                              //Adds current energy deposit to total Voxel energy counter
            
            G4int cellID = hit->GetCellID();                                                            //Gets cell ID value from hit
            G4int column = 1+(cellID % (localNOfVoxelsInX*localNOfVoxelsInY))/ localNOfVoxelsInY;       //assigns cell colunm location from ID
            G4int row = 1+cellID % localNOfVoxelsInY;                                                   //assigns cell row location from ID
            G4int plane = 1+cellID / (localNOfVoxelsInX*localNOfVoxelsInY);                             //assigns cell plane location from ID

//Pushes saved values of energy deposit, colunm, row, and plane to a local vector for later use
            NuLatRunActionLocal->CellEnergyVector.push_back(eDep);
            NuLatRunActionLocal->CellXHitVector.push_back(column);
            NuLatRunActionLocal->CellYHitVector.push_back(row);
            NuLatRunActionLocal->CellZHitVector.push_back(plane);
        }
    }
    
    G4int totalPMTHit=0;
    G4int totalPE=0;
    G4int totalNumberOfPMTs = 2*(localNOfVoxelsInX*localNOfVoxelsInY 
                               + localNOfVoxelsInY*localNOfVoxelsInZ 
                               + localNOfVoxelsInZ*localNOfVoxelsInX);
    for (G4int i=0;i<totalNumberOfPMTs;i++)
    {
//Creates a hit container for each PMT    
        NuLatPhotoCathodeHit* hit = (*pcHC)[i];
//Gets the energy deposited in the hit        
        G4int peHits = hit->GetPEHits();
        if (peHits>0.)
        {
            G4int xID = -1;
            G4int yID = -1;
            G4int zID = -1;
            totalPMTHit++;                                             //Add 1 tally to PMT hit counter
            totalPE += peHits;                                         //Adds current energy deposit to total PMT energy counter
      
//Assigns x, y, and z location values for each created hit container            
            if (i< 1*localNOfVoxelsInY*localNOfVoxelsInZ)
            {
               xID = 0;
               yID = (i-0*localNOfVoxelsInY*localNOfVoxelsInZ)
                     %localNOfVoxelsInY + 1;
               zID = (i-0*localNOfVoxelsInY*localNOfVoxelsInZ)
                     /localNOfVoxelsInY + 1;
            }
            else if (i< 2*localNOfVoxelsInY*localNOfVoxelsInZ)
            {
               xID = localNOfVoxelsInX+1;
               yID = (i-1*localNOfVoxelsInY*localNOfVoxelsInZ)
                     %localNOfVoxelsInY + 1;
               zID = (i-1*localNOfVoxelsInY*localNOfVoxelsInZ)
                     /localNOfVoxelsInY + 1;
                           }
            else if (i< 2*localNOfVoxelsInY*localNOfVoxelsInZ
                      + 1*localNOfVoxelsInZ*localNOfVoxelsInX)
            {
               xID = (i-2*localNOfVoxelsInY*localNOfVoxelsInZ)
                     /localNOfVoxelsInZ + 1;
               yID = 0;
               zID = (i-2*localNOfVoxelsInY*localNOfVoxelsInZ)
                     %localNOfVoxelsInZ + 1;
            }
            else if (i< 2*localNOfVoxelsInY*localNOfVoxelsInZ
                      + 2*localNOfVoxelsInZ*localNOfVoxelsInX)
            {
               xID = (i - (2*localNOfVoxelsInY*localNOfVoxelsInZ 
                        + 1*localNOfVoxelsInZ*localNOfVoxelsInX))
                      /localNOfVoxelsInZ + 1;
               yID = localNOfVoxelsInY+1;
               zID = (i - (2*localNOfVoxelsInY*localNOfVoxelsInZ 
                        + 1*localNOfVoxelsInZ*localNOfVoxelsInX))
                      %localNOfVoxelsInZ + 1;
            }
            else if (i< 2*localNOfVoxelsInY*localNOfVoxelsInZ
                      + 2*localNOfVoxelsInZ*localNOfVoxelsInX
                      + 1*localNOfVoxelsInX*localNOfVoxelsInY)
            {
               xID = (i - (2*localNOfVoxelsInY*localNOfVoxelsInZ 
                      + 2*localNOfVoxelsInZ*localNOfVoxelsInX))
                      / localNOfVoxelsInY + 1;
               yID = (i - (2*localNOfVoxelsInY*localNOfVoxelsInZ 
                        + 2*localNOfVoxelsInZ*localNOfVoxelsInX))
                      % localNOfVoxelsInY + 1;
               zID = 0;

            }
            else if (i< 2*localNOfVoxelsInY*localNOfVoxelsInZ
                      + 2*localNOfVoxelsInZ*localNOfVoxelsInX
                      + 2*localNOfVoxelsInX*localNOfVoxelsInY)
            {
               xID = (i - (2*localNOfVoxelsInY*localNOfVoxelsInZ 
                        + 2*localNOfVoxelsInZ*localNOfVoxelsInX
                        + 1*localNOfVoxelsInX*localNOfVoxelsInY))
                      / localNOfVoxelsInY + 1;
               yID = (i - (2*localNOfVoxelsInY*localNOfVoxelsInZ 
                        + 2*localNOfVoxelsInZ*localNOfVoxelsInX
                        + 1*localNOfVoxelsInX*localNOfVoxelsInY))
                      % localNOfVoxelsInY + 1;
	             zID = localNOfVoxelsInZ+1;

            }
            else
            {
              G4cout   << G4endl <<  G4endl <<  G4endl << "ERROR" << G4endl <<  G4endl <<  G4endl;
            }
//Pushes saved values of energy deposit, x position, y position, and z position to a local vector for later use            
            NuLatRunActionLocal->PMTPEVector.push_back(peHits);
            NuLatRunActionLocal->PMTXPEVector.push_back(xID);
            NuLatRunActionLocal->PMTYPEVector.push_back(yID);
            NuLatRunActionLocal->PMTZPEVector.push_back(zID);

//            G4int cellID = hit->GetCellID();
//            G4int column = 1+(cellID % 225)/ 15;
//            G4int row = 1+cellID % 15;
//            G4int plane = 1+cellID / 225;

//            NuLatRunActionLocal->CellEnergyVector.push_back(eDep);
//            NuLatRunActionLocal->CellXHitVector.push_back(column);
//            NuLatRunActionLocal->CellYHitVector.push_back(row);
//            NuLatRunActionLocal->CellZHitVector.push_back(plane);
        }
    }
    {
    NuLatVoxelHit* hitVectors = (*ecHC)[0];
    NuLatPhotoCathodeHit* NuLatPhotoCathodeHitHitVectors = (*pcHC)[0];
    
    NuLatRunActionLocal->EDepParticleTypeIDNumberVector = hitVectors->GetEDepParticleTypeIDNumberVector();
    hitVectors->ClearEDepParticleTypeIDNumberVector();
    
    NuLatRunActionLocal->EDepParticleEDepVector = hitVectors->GetEDepVector();
    hitVectors->ClearEDepVector();
    
    NuLatRunActionLocal->EDepPositionXVector = hitVectors->GetEDepPositionXVector();
    hitVectors->ClearEDepPositionXVector();
    
    NuLatRunActionLocal->EDepPositionYVector = hitVectors->GetEDepPositionYVector();
    hitVectors->ClearEDepPositionYVector();
    
    NuLatRunActionLocal->EDepPositionZVector = hitVectors->GetEDepPositionZVector();
    hitVectors->ClearEDepPositionZVector();
    
    NuLatRunActionLocal->EDepTimeVector = hitVectors->GetEDepTimeVector();
    hitVectors->ClearEDepTimeVector();

    NuLatPhotoCathodeHitHitVectors->ClearPhotonPMTHitParticleTypeIDNumberVector();

    NuLatRunActionLocal->PhotonPMTHitWavelengthVector =  NuLatPhotoCathodeHitHitVectors->GetPhotonPMTHitWavelengthVector();
    NuLatPhotoCathodeHitHitVectors->ClearPhotonPMTHitWavelengthVector();

    NuLatRunActionLocal->PhotonPMTXHitVector =  NuLatPhotoCathodeHitHitVectors->GetPhotonPMTXHitVector();
    NuLatPhotoCathodeHitHitVectors->ClearPhotonPMTXHitVector();

    NuLatRunActionLocal->PhotonPMTYHitVector =  NuLatPhotoCathodeHitHitVectors->GetPhotonPMTYHitVector();
    NuLatPhotoCathodeHitHitVectors->ClearPhotonPMTYHitVector();

    NuLatRunActionLocal->PhotonPMTZHitVector =  NuLatPhotoCathodeHitHitVectors->GetPhotonPMTZHitVector();
    NuLatPhotoCathodeHitHitVectors->ClearPhotonPMTZHitVector();

    NuLatRunActionLocal->PhotonPMTHitTimeVector =  NuLatPhotoCathodeHitHitVectors->GetPhotonPMTHitTimeVector();
    NuLatPhotoCathodeHitHitVectors->ClearPhotonPMTHitTimeVector();  

    }

    if (event->GetNumberOfPrimaryVertex()==1)
    {
    	analysisManager->FillH1(0, primaryParticleInitialKE/keV);
    }
    else
    {
   		G4PrimaryParticle* primary = event->GetPrimaryVertex(0)->GetPrimary(0);
   		G4double initialKE = primary->GetKineticEnergy();
   		analysisManager->FillH1(0, initialKE/keV);
    }
    
    // Fill Ntuple with primary particle information
    analysisManager->FillNtupleIColumn(0, 0, eventNumber);                                          // column Id = 0
    analysisManager->FillNtupleIColumn(0, 1, eventSeed);                                            // column Id = 1
    analysisManager->FillNtupleIColumn(0, 2, primaryParticleIDNumber);                              // column Id = 2
    analysisManager->FillNtupleDColumn(0, 3, primaryParticleInitialKE);                             // column Id = 3
    analysisManager->FillNtupleDColumn(0, 4, primaryParticlePosX);                                  // column Id = 4
    analysisManager->FillNtupleDColumn(0, 5, primaryParticlePosY);                                  // column Id = 5
    analysisManager->FillNtupleDColumn(0, 6, primaryParticlePosZ);                                  // column Id = 6
    analysisManager->FillNtupleDColumn(0, 7, primaryParticleTime);                                  // column Id = 7
    analysisManager->FillNtupleDColumn(0, 8, primaryParticleMomentum);                              // column Id = 8
    analysisManager->FillNtupleDColumn(0, 9, primaryParticleMomentumX);                             // column Id = 9
    analysisManager->FillNtupleDColumn(0, 10, primaryParticleMomentumY);                            // column Id = 10
    analysisManager->FillNtupleDColumn(0, 11, primaryParticleMomentumZ);                            // column Id = 11
    
    // Fill Ntuple with event summary information:
    //               Total energy in the detector,
    //               Number of cells hit in the detector, and 
    //               Number of individual energy depositions in the detector
    analysisManager->FillNtupleDColumn(0, 12, totalNuLatVoxelEnergy);                               // column Id = 12
    analysisManager->FillNtupleIColumn(0, 13, NuLatRunActionLocal->CellEnergyVector.size());        // column Id = 13
    analysisManager->FillNtupleIColumn(0, 14, NuLatRunActionLocal->EDepParticleEDepVector.size());  // column Id = 14
    analysisManager->FillNtupleIColumn(0, 15, NuLatRunActionLocal->PhotonPMTHitTimeVector.size());  // column Id = 15
    analysisManager->FillNtupleIColumn(0, 16, totalPMTHit);                                         // column Id = 16
    
    G4int dataQualityFlag = -1;
    if(NuLatRunActionLocal->CellEnergyVector.size() == NuLatRunActionLocal->CellXHitVector.size() &&
       NuLatRunActionLocal->CellEnergyVector.size() == NuLatRunActionLocal->CellYHitVector.size() &&
       NuLatRunActionLocal->CellEnergyVector.size() == NuLatRunActionLocal->CellZHitVector.size())
    {
      if(NuLatRunActionLocal->EDepParticleEDepVector.size() == NuLatRunActionLocal->EDepParticleTypeIDNumberVector.size() &&
         NuLatRunActionLocal->EDepParticleEDepVector.size() == NuLatRunActionLocal->EDepPositionXVector.size() &&
         NuLatRunActionLocal->EDepParticleEDepVector.size() == NuLatRunActionLocal->EDepPositionXVector.size() &&
         NuLatRunActionLocal->EDepParticleEDepVector.size() == NuLatRunActionLocal->EDepPositionXVector.size() &&
         NuLatRunActionLocal->EDepParticleEDepVector.size() == NuLatRunActionLocal->EDepTimeVector.size())
        {
          if (NuLatRunActionLocal->CellEnergyVector.size() <= NuLatRunActionLocal->EDepParticleEDepVector.size())
          {
            dataQualityFlag = 1;
          }
        }
    }
    
    if (dataQualityFlag == 1)
    {
      analysisManager->AddNtupleRow();  //Note: vectors being cleared below are added at this point as well
    }
    else // implement better error later
    {
      ofstream errorFile;
      errorFile.open ("NuLatSimErrorLog.txt", ios::out | ios::app);
      errorFile << G4endl
        <<"*****************************************" << G4endl
        <<"*       DATA QUALITY CHECK FAILED       *" << G4endl
        <<"*  Event "  << event->GetEventID() // print Event ID
        <<"                            *"             << G4endl
        <<"*****************************************" << G4endl
        << G4endl;
      if(NuLatRunActionLocal->CellEnergyVector.size() != NuLatRunActionLocal->CellXHitVector.size() ||
         NuLatRunActionLocal->CellEnergyVector.size() != NuLatRunActionLocal->CellYHitVector.size() ||
         NuLatRunActionLocal->CellEnergyVector.size() != NuLatRunActionLocal->CellZHitVector.size())
      {
        errorFile << G4endl
          <<"    *************************************" << G4endl
          <<"    *     Failed Cell Vector Test       *" << G4endl 
          <<"    *************************************" << G4endl
          << G4endl;
      }
      
      if(NuLatRunActionLocal->EDepParticleEDepVector.size() != NuLatRunActionLocal->EDepParticleTypeIDNumberVector.size() ||
         NuLatRunActionLocal->EDepParticleEDepVector.size() != NuLatRunActionLocal->EDepPositionXVector.size() ||
         NuLatRunActionLocal->EDepParticleEDepVector.size() != NuLatRunActionLocal->EDepPositionXVector.size() ||
         NuLatRunActionLocal->EDepParticleEDepVector.size() != NuLatRunActionLocal->EDepPositionXVector.size() ||
         NuLatRunActionLocal->EDepParticleEDepVector.size() != NuLatRunActionLocal->EDepTimeVector.size())
      {
        errorFile << G4endl
          <<"    *************************************" << G4endl
          <<"    * Failed Inividual Edep Vector Test *" << G4endl 
          <<"    *************************************" << G4endl
          << G4endl;
      }
      
      if (NuLatRunActionLocal->CellEnergyVector.size() > NuLatRunActionLocal->EDepParticleEDepVector.size())
      {
        errorFile << G4endl
          <<"    *************************************" << G4endl
          <<"    *          Cell <= EDep test        *" << G4endl 
          <<"    *************************************" << G4endl
          << G4endl;
      }
      errorFile.close();
      
      analysisManager->AddNtupleRow();  //Note: vectors being cleared below are added at this point as well
    }
    
    // clear cell vectors
    NuLatRunActionLocal->CellEnergyVector.clear();                   // column Id = 17
    NuLatRunActionLocal->CellXHitVector.clear();                     // column Id = 18
    NuLatRunActionLocal->CellYHitVector.clear();                     // column Id = 19
    NuLatRunActionLocal->CellZHitVector.clear();                     // column Id = 20
    
    // clear individual energy deposition vectors
    NuLatRunActionLocal->EDepParticleTypeIDNumberVector.clear();     // column Id = 21
    NuLatRunActionLocal->EDepParticleEDepVector.clear();             // column Id = 22
    NuLatRunActionLocal->EDepPositionXVector.clear();                // column Id = 23
    NuLatRunActionLocal->EDepPositionYVector.clear();                // column Id = 24
    NuLatRunActionLocal->EDepPositionZVector.clear();                // column Id = 25
    NuLatRunActionLocal->EDepTimeVector.clear();                     // column Id = 26
    
    NuLatRunActionLocal->PMTPEVector.clear();                        // column Id = 27
    NuLatRunActionLocal->PMTXPEVector.clear();                       // column Id = 28
    NuLatRunActionLocal->PMTYPEVector.clear();                       // column Id = 29
    NuLatRunActionLocal->PMTZPEVector.clear();                       // column Id = 30
    
    NuLatRunActionLocal->PhotonPMTHitWavelengthVector.clear();       // column Id = 31
    NuLatRunActionLocal->PhotonPMTXHitVector.clear();                // column Id = 32
    NuLatRunActionLocal->PhotonPMTYHitVector.clear();                // column Id = 33
    NuLatRunActionLocal->PhotonPMTZHitVector.clear();                // column Id = 34
    NuLatRunActionLocal->PhotonPMTHitTimeVector.clear();             // column Id = 35
    
    NuLatRunActionLocal->PhotonPMTHitParticleTypeIDNumberVector.clear();  // not a column?

    //
    // Print diagnostics: UI command /run/printProgress can be used
    // to set frequency of how often info should be dumped
    // 
    if (event->GetEventID() % 1000 == 0)
    {
    	for(int i = 0; i<event->GetNumberOfPrimaryVertex()-1; i++)
    	{
    		G4int printModulo = G4RunManager::GetRunManager()->GetPrintProgress();
    		if ( printModulo==0 || event->GetEventID() % printModulo != 0) return;

    		G4PrimaryParticle* primary = event->GetPrimaryVertex(i)->GetPrimary(0);
    		G4double initialKE = primary->GetKineticEnergy();

    		G4cout   << G4endl
    				<<"***********************************************************" << G4endl
					<<"*  NuLatEventAction::EndOfEventAction     "                                       <<"                " <<"*"<< G4endl
					<<"*  Event "  << event->GetEventID() << "                                "         <<"                "  <<"*"<< G4endl // print Event ID
					<<"*  >>> Simulation truth :                 "                                        <<"                "<<"*"<< G4endl
					<<"*    Particle                        =    "<<primary->GetG4code()->GetParticleName()<<"              "    <<"*"<< G4endl // print name of particle
					<<"*    Primary Particle Momentum       =    "<<primary->GetMomentum()                 <<"  "          <<"*"<< G4endl // print momentum
					<<"*    Primary Particle Kinetic Energy =    "<<initialKE/MeV                          <<" (MeV)       "    <<"*"<< G4endl // print primary particle Energy
					<<"*    NuLat Total Energy Deposited:        "<<totalNuLatVoxelEnergy/MeV              <<" (MeV)   "    <<"*"<< G4endl // print total energy detected
					<<"*    NuLat Number of Voxels Hit:          "<<totalNuLatVoxelHit                     <<"              " <<"*"<< G4endl // Print number of voxels hit
					<<"***********************************************************" << G4endl
					<< G4endl;
    	}
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
