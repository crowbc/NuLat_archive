//EVENT ACTION FILE
//Controls what happens before/during/after an event
//Sets up data collection schemes and organizes collected data
//(Highly related files: EventAction.hh, VoxelHit.hh, PhotoCathodeHit.hh, RunAction.cc)

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

//Getting hit collection of the event
    G4HCofThisEvent* hce = event->GetHCofThisEvent();
//Warning message if no hit collection is created
    if (!hce) 
    {
        G4ExceptionDescription msg;
        msg << "No hits collection of this event found.\n"; 
        G4Exception("NuLatEventAction::EndOfEventAction()",
                    "Code001", JustWarning, msg);
        return;
    }   


//Create hits collection for Voxels
    NuLatVoxelHitsCollection* ecHC 
      = static_cast<NuLatVoxelHitsCollection*>(hce->GetHC(fECHCID));

//Create hits collection for PMTs
    NuLatPhotoCathodeHitsCollection* pcHC 
      = static_cast<NuLatPhotoCathodeHitsCollection*>(hce->GetHC(fPCHCID));
      
//Warning message if Voxel hit collection not found
    if ((!ecHC))
    {
        G4ExceptionDescription msg;
        msg << "Some of hits collections of this event not found.\n";
        G4Exception("NuLatEventAction::EndOfEventAction()",
                    "Code001", JustWarning, msg);
        return;
    }

//Warning message if PMT hit collection not found
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
    
//Get event seed
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




//Sets hit counters to zero
    G4int totalNuLatVoxelHit = 0;
    G4double totalNuLatVoxelEnergy = 0.;
    
    
    for (G4int i=0;i<localNOfVoxelsInX*localNOfVoxelsInY*localNOfVoxelsInY;i++)
    {
//Creates hit container for each voxel    
        NuLatVoxelHit* hit = (*ecHC)[i];
//Gets the energy deposited in the hit        
        G4double eDep = hit->GetEdep();
        
//If hit deposited energy...        
 //       if (eDep>0.)
//        {
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
   //     }
    }

//Sets hit counters to zero    
    G4int totalPMTHit=0;
    G4int totalPE=0;
    
//Get number of PMTs    
    G4int totalNumberOfPMTs = 2*(localNOfVoxelsInX*localNOfVoxelsInY 
                               + localNOfVoxelsInY*localNOfVoxelsInZ 
                               + localNOfVoxelsInZ*localNOfVoxelsInX);
    for (G4int i=0;i<totalNumberOfPMTs;i++)
    {
//Creates a hit container for each PMT    
        NuLatPhotoCathodeHit* hit = (*pcHC)[i];
//Gets the energy deposited in the hit        
        G4int peHits = hit->GetPEHits();
        
//If hit deposits energy...        
 //       if (peHits>0.)
 //       {
            G4int xID = -1;                                            //Resetting xID
            G4int yID = -1;                                            //Resetting yID
            G4int zID = -1;                                            //Resetting zID
            
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
  //      }
    }
    {
    
//Creates Voxel hitVector for sum-of-voxels data
    NuLatVoxelHit* hitVectors = (*ecHC)[0];
//Creates PMT hitVector for sum-of-PMT data    
    NuLatPhotoCathodeHit* NuLatPhotoCathodeHitHitVectors = (*pcHC)[0];
    
    
    
//FOR VOXELS   
    NuLatRunActionLocal->EDepParticleTypeIDNumberVector = hitVectors->GetEDepParticleTypeIDNumberVector();                    //Save Particle ID number from hitVector to NuLatRunAcionLocal 
    hitVectors->ClearEDepParticleTypeIDNumberVector();                                                                        //Clearing hitVector of transfered data    
    
    NuLatRunActionLocal->EDepParticleEDepVector = hitVectors->GetEDepVector();                                                //Save Energy Deposit from hitVector to NuLatRunAcionLocal 
    hitVectors->ClearEDepVector();                                                                                            //Clearing hitVector of transfered data    
    
    NuLatRunActionLocal->EDepPositionXVector = hitVectors->GetEDepPositionXVector();                                          //Save X position from hitVector to NuLatRunAcionLocal 
    hitVectors->ClearEDepPositionXVector();                                                                                   //Clearing hitVector of transfered data    
    
    NuLatRunActionLocal->EDepPositionYVector = hitVectors->GetEDepPositionYVector();                                          //Save Y position value from hitVector to NuLatRunAcionLocal 
    hitVectors->ClearEDepPositionYVector();                                                                                   //Clearing hitVector of transfered data    
    
    NuLatRunActionLocal->EDepPositionZVector = hitVectors->GetEDepPositionZVector();                                          //Save Z position value from hitVector to NuLatRunAcionLocal 
    hitVectors->ClearEDepPositionZVector();                                                                                   //Clearing hitVector of transfered data    
    
    NuLatRunActionLocal->EDepTimeVector = hitVectors->GetEDepTimeVector();                                                    //Save Time value from hitVector to NuLatRunAcionLocal 
    hitVectors->ClearEDepTimeVector();                                                                                        //Clearing hitVector of transfered data    

    NuLatRunActionLocal->InitialMomentumXVector = hitVectors->GetInitialMomentumXVector();                                          //Save X position from hitVector to NuLatRunAcionLocal 
    hitVectors->ClearInitialMomentumXVector();                                                                                   //Clearing hitVector of transfered data    
    NuLatRunActionLocal->InitialMomentumYVector = hitVectors->GetInitialMomentumYVector();                                          //Save X position from hitVector to NuLatRunAcionLocal 
    hitVectors->ClearInitialMomentumYVector();                                                                                   //Clearing hitVector of transfered data    
    NuLatRunActionLocal->InitialMomentumZVector = hitVectors->GetInitialMomentumZVector();                                          //Save X position from hitVector to NuLatRunAcionLocal 
    hitVectors->ClearInitialMomentumZVector();                                                                                   //Clearing hitVector of transfered data    

//FOR PMTs (Data collected in Sensitive Detector File)
//CHECK WHY NO LINE OF CODE HERE
    NuLatPhotoCathodeHitHitVectors->ClearPhotonPMTHitParticleTypeIDNumberVector();

//Set to always 0 in Sensitive Detector File
    NuLatRunActionLocal->PhotonPMTHitWavelengthVector =  NuLatPhotoCathodeHitHitVectors->GetPhotonPMTHitWavelengthVector();   //Save Wavelength value from NuLatPhotoCathodeHitVector to NuLatRunAcionLocal 
    NuLatPhotoCathodeHitHitVectors->ClearPhotonPMTHitWavelengthVector();                                                      //Clearing NuLatPhotoCathodeHitVector of transfered data   
    
     NuLatRunActionLocal->PhotonPMTHitEnergyVector =  NuLatPhotoCathodeHitHitVectors->GetPhotonPMTHitEnergyVector();   //Save Energy value from NuLatPhotoCathodeHitVector to NuLatRunAcionLocal 
    NuLatPhotoCathodeHitHitVectors->ClearPhotonPMTHitEnergyVector();                                                      //Clearing NuLatPhotoCathodeHitVector of transfered data       

    NuLatRunActionLocal->PhotonPMTXHitVector =  NuLatPhotoCathodeHitHitVectors->GetPhotonPMTXHitVector();                     //Save X PMT location from NuLatPhotoCathodeHitVector to NuLatRunAcionLocal 
    NuLatPhotoCathodeHitHitVectors->ClearPhotonPMTXHitVector();                                                               //Clearing NuLatPhotoCathodeHitVector of transfered data    

    NuLatRunActionLocal->PhotonPMTYHitVector =  NuLatPhotoCathodeHitHitVectors->GetPhotonPMTYHitVector();                     //Save Y PMT location from NuLatPhotoCathodeHitVector to NuLatRunAcionLocal 
    NuLatPhotoCathodeHitHitVectors->ClearPhotonPMTYHitVector();                                                               //Clearing NuLatPhotoCathodeHitVector of transfered data    

    NuLatRunActionLocal->PhotonPMTZHitVector =  NuLatPhotoCathodeHitHitVectors->GetPhotonPMTZHitVector();                     //Save Z PMT location from NuLatPhotoCathodeHitVector to NuLatRunAcionLocal 
    NuLatPhotoCathodeHitHitVectors->ClearPhotonPMTZHitVector();                                                               //Clearing NuLatPhotoCathodeHitVector of transfered data    

    NuLatRunActionLocal->PhotonPMTHitTimeVector =  NuLatPhotoCathodeHitHitVectors->GetPhotonPMTHitTimeVector();               //Save Time value from NuLatPhotoCathodeHitVector to NuLatRunAcionLocal 
    NuLatPhotoCathodeHitHitVectors->ClearPhotonPMTHitTimeVector();                                                            //Clearing NuLatPhotoCathodeHitVector of transfered data    

    }


    //General Run Information Results
    // Fill Ntuple with primary particle information
    analysisManager->FillNtupleIColumn(0, 0, eventNumber);                                          // column Id = 0     Event Number
    analysisManager->FillNtupleIColumn(0, 1, eventSeed);                                            // column Id = 1     Event Seed
    analysisManager->FillNtupleIColumn(0, 2, primaryParticleIDNumber);                              // column Id = 2     Primary Particle's ID Number (particle type ID)
    analysisManager->FillNtupleDColumn(0, 3, primaryParticleInitialKE);                             // column Id = 3     Primary Particle's Initial Kinetic Energy
    analysisManager->FillNtupleDColumn(0, 4, primaryParticlePosX);                                  // column Id = 4     Primary Particle's Initial X Position
    analysisManager->FillNtupleDColumn(0, 5, primaryParticlePosY);                                  // column Id = 5     Primary Particle's Initial Y Position
    analysisManager->FillNtupleDColumn(0, 6, primaryParticlePosZ);                                  // column Id = 6     Primary Particle's Initial Z Position
    analysisManager->FillNtupleDColumn(0, 7, primaryParticleTime);                                  // column Id = 7     Primary Particle's Initial Time
    analysisManager->FillNtupleDColumn(0, 8, primaryParticleMomentum);                              // column Id = 8     Primary Particle's Initial Momentum
    analysisManager->FillNtupleDColumn(0, 9, primaryParticleMomentumX);                             // column Id = 9     Primary Particle's Initial X Momentum
    analysisManager->FillNtupleDColumn(0, 10, primaryParticleMomentumY);                            // column Id = 10    Primary Particle's Initial Y Momentum
    analysisManager->FillNtupleDColumn(0, 11, primaryParticleMomentumZ);                            // column Id = 11    Primary Particle's Initial Z Momentum
    
    // Fill Ntuple with event summary information:
    //               Total energy in the detector,
    //               Number of cells hit in the detector, and 
    //               Number of individual energy depositions in the detector
    analysisManager->FillNtupleDColumn(0, 12, totalNuLatVoxelEnergy);                               // column Id = 12    Total Energy Collected in Voxels
    analysisManager->FillNtupleIColumn(0, 13, NuLatRunActionLocal->CellEnergyVector.size());        // column Id = 13    Total Number of Particles Collected in Voxels
    analysisManager->FillNtupleIColumn(0, 14, NuLatRunActionLocal->EDepParticleEDepVector.size());  // column Id = 14    Total Number of Hits in Voxels and PMTs
    analysisManager->FillNtupleIColumn(0, 15, NuLatRunActionLocal->PhotonPMTHitTimeVector.size());  // column Id = 15    Total Number of Photon Hits
    analysisManager->FillNtupleIColumn(0, 16, totalPMTHit);                                         // column Id = 16    Total Number of PMT Hits


	//FULL PMT DATA Results
	for (int i=0; i<NuLatRunActionLocal->PhotonPMTXHitVector.size(); i++)
	{
	
	    analysisManager->FillNtupleDColumn(4, 0, NuLatRunActionLocal->PhotonPMTHitEnergyVector[i]);
	    analysisManager->FillNtupleDColumn(4, 1, NuLatRunActionLocal->PhotonPMTHitWavelengthVector[i]);
	    analysisManager->FillNtupleIColumn(4, 2, NuLatRunActionLocal->PhotonPMTXHitVector[i]);     
	    analysisManager->FillNtupleIColumn(4, 3, NuLatRunActionLocal->PhotonPMTYHitVector[i]);
	    analysisManager->FillNtupleIColumn(4, 4, NuLatRunActionLocal->PhotonPMTZHitVector[i]);
	    analysisManager->FillNtupleDColumn(4, 5, NuLatRunActionLocal->PhotonPMTHitTimeVector[i]);      
	    analysisManager->AddNtupleRow(4);
	    
	    }
	    analysisManager->FillNtupleDColumn(4, 0, eventNumber+1);
	    analysisManager->FillNtupleDColumn(4, 1, 0);
	    analysisManager->FillNtupleIColumn(4, 2, 0);     
	    analysisManager->FillNtupleIColumn(4, 3, 0);
	    analysisManager->FillNtupleIColumn(4, 4, 0);
	    analysisManager->FillNtupleDColumn(4, 5, 0);      
	    analysisManager->AddNtupleRow(4);
	    
	    
	    
	    
	    	    
	    

	//ORGANIZED PMT DATA Results (sorted by PMT)
	G4double CenterCounts;
	for (int i=0; i<NuLatRunActionLocal->PMTPEVector.size(); i++)
	{
	
	    analysisManager->FillNtupleIColumn(3, 0, NuLatRunActionLocal->PMTPEVector[i]);
	    analysisManager->FillNtupleIColumn(3, 1, NuLatRunActionLocal->PMTXPEVector[i]);     
	    analysisManager->FillNtupleIColumn(3, 2, NuLatRunActionLocal->PMTYPEVector[i]);
	    analysisManager->FillNtupleIColumn(3, 3, NuLatRunActionLocal->PMTZPEVector[i]);
	    analysisManager->AddNtupleRow(3);
	    
	    if (NuLatRunActionLocal->PMTXPEVector[i] == 3 && NuLatRunActionLocal->PMTYPEVector[i] == 3 || 
	        NuLatRunActionLocal->PMTXPEVector[i] == 3 && NuLatRunActionLocal->PMTZPEVector[i] == 3 || 
	        NuLatRunActionLocal->PMTZPEVector[i] == 3 && NuLatRunActionLocal->PMTYPEVector[i] == 3)
	        {CenterCounts += NuLatRunActionLocal->PMTPEVector[i];
	        analysisManager->FillNtupleIColumn(0, 17, CenterCounts); 
	        }
	    }
	    analysisManager->FillNtupleIColumn(3, 0, eventNumber+1);
	    analysisManager->FillNtupleIColumn(3, 1, 0);     
	    analysisManager->FillNtupleIColumn(3, 2, 0);
	    analysisManager->FillNtupleIColumn(3, 3, 0);
	    analysisManager->AddNtupleRow(3);	    
	    
	    
	    
	    
	    
	    
	//FULL VOXEL HIT DATA Results
	for (int i=0; i<NuLatRunActionLocal->EDepParticleTypeIDNumberVector.size(); i++)
	{
	
	    analysisManager->FillNtupleIColumn(2, 0, NuLatRunActionLocal->EDepParticleTypeIDNumberVector[i]);
	    analysisManager->FillNtupleDColumn(2, 1, NuLatRunActionLocal->EDepParticleEDepVector[i]);     
	    analysisManager->FillNtupleDColumn(2, 2, NuLatRunActionLocal->EDepPositionXVector[i]);
	    analysisManager->FillNtupleDColumn(2, 3, NuLatRunActionLocal->EDepPositionYVector[i]);
	    analysisManager->FillNtupleDColumn(2, 4, NuLatRunActionLocal->EDepPositionZVector[i]);     
	    analysisManager->FillNtupleDColumn(2, 5, NuLatRunActionLocal->EDepTimeVector[i]);  
   	    analysisManager->FillNtupleDColumn(2, 6, NuLatRunActionLocal->InitialMomentumXVector[i]);
    	    analysisManager->FillNtupleDColumn(2, 7, NuLatRunActionLocal->InitialMomentumYVector[i]);
    	    analysisManager->FillNtupleDColumn(2, 8, NuLatRunActionLocal->InitialMomentumZVector[i]);	                 
	    analysisManager->AddNtupleRow(2);
	    
	    }
	    analysisManager->FillNtupleIColumn(2, 0, eventNumber+1);
	    analysisManager->FillNtupleDColumn(2, 1, 0);     
	    analysisManager->FillNtupleDColumn(2, 2, 0);
	    analysisManager->FillNtupleDColumn(2, 3, 0);
	    analysisManager->FillNtupleDColumn(2, 4, 0);     
	    analysisManager->FillNtupleDColumn(2, 5, 0);  
   	    analysisManager->FillNtupleDColumn(2, 6, 0);
    	    analysisManager->FillNtupleDColumn(2, 7, 0);
    	    analysisManager->FillNtupleDColumn(2, 8, 0);	                 
	    analysisManager->AddNtupleRow(2);	    
	   
	   
	   
	   
	   
	   
	//ORGANIZED VOXEL HIT Results (Sorted by Voxel)
	for (int i=0; i<NuLatRunActionLocal->CellEnergyVector.size(); i++)
	{

	    analysisManager->FillNtupleDColumn(1, 0, NuLatRunActionLocal->CellEnergyVector[i]);
	    analysisManager->FillNtupleIColumn(1, 1, NuLatRunActionLocal->CellXHitVector[i]);     
	    analysisManager->FillNtupleIColumn(1, 2, NuLatRunActionLocal->CellYHitVector[i]);
	    analysisManager->FillNtupleIColumn(1, 3, NuLatRunActionLocal->CellZHitVector[i]);
	    analysisManager->AddNtupleRow(1);
	    
	    if (NuLatRunActionLocal->CellXHitVector[i] == 3 && NuLatRunActionLocal->CellYHitVector[i] == 3 && NuLatRunActionLocal->CellZHitVector[i] == 3)
	    {analysisManager->FillNtupleDColumn(0, 18, NuLatRunActionLocal->CellEnergyVector[i]); 
	    }
	    
	    }
	    analysisManager->FillNtupleDColumn(1, 0, eventNumber+1);
	    analysisManager->FillNtupleIColumn(1, 1, 0);     
	    analysisManager->FillNtupleIColumn(1, 2, 0);
	    analysisManager->FillNtupleIColumn(1, 3, 0);
	    analysisManager->AddNtupleRow(1);
	    






//Verifying that Vectors are of the correct size    
    G4int dataQualityFlag = -1;
    
//Number of hits in Voxels    
    if(NuLatRunActionLocal->CellEnergyVector.size() == NuLatRunActionLocal->CellXHitVector.size() &&
       NuLatRunActionLocal->CellEnergyVector.size() == NuLatRunActionLocal->CellYHitVector.size() &&
       NuLatRunActionLocal->CellEnergyVector.size() == NuLatRunActionLocal->CellZHitVector.size())
    {
//Number of hits everywhere (Total)    
      if(NuLatRunActionLocal->EDepParticleEDepVector.size() == NuLatRunActionLocal->EDepParticleTypeIDNumberVector.size() &&
         NuLatRunActionLocal->EDepParticleEDepVector.size() == NuLatRunActionLocal->EDepPositionXVector.size() &&
         NuLatRunActionLocal->EDepParticleEDepVector.size() == NuLatRunActionLocal->EDepPositionXVector.size() &&
         NuLatRunActionLocal->EDepParticleEDepVector.size() == NuLatRunActionLocal->EDepPositionXVector.size() &&
         NuLatRunActionLocal->EDepParticleEDepVector.size() == NuLatRunActionLocal->EDepTimeVector.size())
        {
//Total is bigger than just voxel hits        
          if (NuLatRunActionLocal->CellEnergyVector.size() <= NuLatRunActionLocal->EDepParticleEDepVector.size())
          {
            dataQualityFlag = 1;
          }
        }
    }

//If data is good, finishes row of Ntuple and starts next one    
    if (dataQualityFlag == 1)
    {
      analysisManager->AddNtupleRow();  //Note: vectors being cleared below are added at this point as well
    }
    
    
//If data is not good gives error, produces error file, and still finishes Ntuple row    
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

//Clearing Vectors    
    // clear cell vectors
    NuLatRunActionLocal->CellEnergyVector.clear();                   // column Id = 0
    NuLatRunActionLocal->CellXHitVector.clear();                     // column Id = 1
    NuLatRunActionLocal->CellYHitVector.clear();                     // column Id = 2
    NuLatRunActionLocal->CellZHitVector.clear();                     // column Id = 3
    
    // clear individual energy deposition vectors
    NuLatRunActionLocal->EDepParticleTypeIDNumberVector.clear();     // column Id = 0
    NuLatRunActionLocal->EDepParticleEDepVector.clear();             // column Id = 1
    NuLatRunActionLocal->EDepPositionXVector.clear();                // column Id = 2
    NuLatRunActionLocal->EDepPositionYVector.clear();                // column Id = 3
    NuLatRunActionLocal->EDepPositionZVector.clear();                // column Id = 4
    NuLatRunActionLocal->EDepTimeVector.clear();                     // column Id = 5
    
    NuLatRunActionLocal->PMTPEVector.clear();                        // column Id = 0
    NuLatRunActionLocal->PMTXPEVector.clear();                       // column Id = 1
    NuLatRunActionLocal->PMTYPEVector.clear();                       // column Id = 2
    NuLatRunActionLocal->PMTZPEVector.clear();                       // column Id = 3
    
    NuLatRunActionLocal->PhotonPMTHitEnergyVector.clear();           // column Id = 0
    NuLatRunActionLocal->PhotonPMTHitWavelengthVector.clear();       // column Id = 1
    NuLatRunActionLocal->PhotonPMTXHitVector.clear();                // column Id = 2
    NuLatRunActionLocal->PhotonPMTYHitVector.clear();                // column Id = 3
    NuLatRunActionLocal->PhotonPMTZHitVector.clear();                // column Id = 4
    NuLatRunActionLocal->PhotonPMTHitTimeVector.clear();             // column Id = 5
    
    NuLatRunActionLocal->InitialMomentumXVector.clear();   
    NuLatRunActionLocal->InitialMomentumYVector.clear();    
    NuLatRunActionLocal->InitialMomentumZVector.clear();     
    
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
