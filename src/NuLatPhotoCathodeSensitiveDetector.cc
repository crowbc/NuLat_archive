//PHOTOCATHODE SENSITIVE DETECTOR FILE
//Decribes Sensitive Region of Detection and what to do when hit

//file needs work
// hit proccessing / energy deposit processing
#include <iostream>
#include <fstream>

#include "NuLatPhotoCathodeSensitiveDetector.hh"
#include "NuLatPhotoCathodeHit.hh"

#include "Analysis.hh"

#include "G4Event.hh"
#include "G4HCofThisEvent.hh"
#include "G4TouchableHistory.hh"
#include "G4Track.hh"
#include "G4Step.hh"
#include "G4SDManager.hh" //SD = SensitiveDetector
#include "G4TrackingManager.hh"
#include "G4ios.hh"
#include "G4EventManager.hh"
#include "G4SystemOfUnits.hh"



using namespace std;




/* ---------------------------------------------- */
/*                   Constructor                  */
/* ---------------------------------------------- */
NuLatPhotoCathodeSensitiveDetector::NuLatPhotoCathodeSensitiveDetector(G4String name,
    G4int    nOfVoxelsInX,   G4int    nOfVoxelsInY,   G4int    nOfVoxelsInZ,
    G4double voxelXDim,      G4double voxelYDim,      G4double voxelZDim,
    G4double voxSpacingXDim, G4double voxSpacingYDim, G4double voxSpacingZDim)
: G4VSensitiveDetector(name), PhotoCathodeHitCollection(0), PhotoCathodeHitCollectionID(-1)
{
    collectionName.insert("NuLatPhotoCathodeColl");
    localNOfVoxelsInX = nOfVoxelsInX;
    localNOfVoxelsInY = nOfVoxelsInY;
    localNOfVoxelsInZ = nOfVoxelsInZ;
    localVoxelXDim = voxelXDim;
    localVoxelYDim = voxelYDim;
    localVoxelZDim = voxelZDim;
    localVoxSpacingXDim = voxSpacingXDim;
    localVoxSpacingYDim = voxSpacingYDim;
    localVoxSpacingZDim = voxSpacingZDim;
}



//Destructor
NuLatPhotoCathodeSensitiveDetector::~NuLatPhotoCathodeSensitiveDetector()
{}




/* ---------------------------------------------- */
/*       Initialze the sensitive detector         */
/* ---------------------------------------------- */
//Called for each new event and gets the HCofThisEVent for the event
void NuLatPhotoCathodeSensitiveDetector::Initialize(G4HCofThisEvent* hce)
{
//Creating a hits collection for the current event with ID: 0 and name: collectionName[0]
  PhotoCathodeHitCollection
    = new NuLatPhotoCathodeHitsCollection(SensitiveDetectorName,collectionName[0]);
    
//Retreive the ID of the hits collection named collectionName[0]
//If it has not been done already, this ID is stored in the variable PhotoCathodeHitCollectionID    
  if (PhotoCathodeHitCollectionID<0)
  {
    PhotoCathodeHitCollectionID = G4SDManager::GetSDMpointer()->GetCollectionID(PhotoCathodeHitCollection);
  }

//The hits collection just defined is now registered to the HCOfThisEvent of the current event    
  hce->AddHitsCollection(PhotoCathodeHitCollectionID,PhotoCathodeHitCollection);
  
//CHECK, DOESN'T SEEM RIGHT  
  // fill NuLatPhotoCathodeHits with zero energy deposition
  G4int numberOfPhotoCathodes = (localNOfVoxelsInX*localNOfVoxelsInY+
                                 localNOfVoxelsInY*localNOfVoxelsInZ+
                                 localNOfVoxelsInZ*localNOfVoxelsInX)*2;
  for (G4int i=0;i<numberOfPhotoCathodes;i++)
  {
    NuLatPhotoCathodeHit* hit = new NuLatPhotoCathodeHit(i);
    PhotoCathodeHitCollection->insert(hit);
  }
}




/* ---------------------------------------------- */
/*                 Process Hits                   */
/* ---------------------------------------------- */
//Called when the particle goes through the sensitive detector
//Potentially creates a new hit and adds it to the collection
//Returns a boolean value
//CHECK if TouchableHistory needs a variable and if we need a space before step
G4bool NuLatPhotoCathodeSensitiveDetector::ProcessHits(G4Step*step, G4TouchableHistory*)
{


  //G4double edep = step->GetTotalEnergyDeposit();
  G4double wLength = 0.0; //0.00000124*eV*m/edep;

//  if (edep==0.)
//    return true;

  G4TouchableHistory* touchable = (G4TouchableHistory*)(step->GetPreStepPoint()->GetTouchable());           //CHECK if this is required or touchable is an input above
  G4VPhysicalVolume*  physical  = touchable->GetVolume();
  G4int               grandMotherCopyNo    = touchable->GetCopyNumber(2);
  G4int xID = -1;
  G4int yID = -1;
  G4int zID = -1;
  G4int copyNo;



//For each LightGuide bank, locates the hit PMT and records its placement and copynumber
  if(touchable->GetVolume(3)->GetLogicalVolume()->GetName() == "NuLatLightGuideXBankMinusLogical")
	{
	  xID = 0;
	  yID = grandMotherCopyNo%localNOfVoxelsInY + 1;
	  zID = grandMotherCopyNo/localNOfVoxelsInY + 1;
	  copyNo = 0
	           +(yID-1)+(zID-1)*localNOfVoxelsInY;
	}
	else if(touchable->GetVolume(3)->GetLogicalVolume()->GetName() == "NuLatLightGuideXBankPlusLogical")
	{
	  xID = localNOfVoxelsInX+1;
	  yID = grandMotherCopyNo%localNOfVoxelsInY + 1;
	  zID = grandMotherCopyNo/localNOfVoxelsInY + 1;
	  copyNo = 1*localNOfVoxelsInY*localNOfVoxelsInZ
	           +(yID-1)+(zID-1)*localNOfVoxelsInY;
	}
	else if(touchable->GetVolume(3)->GetLogicalVolume()->GetName() == "NuLatLightGuideYBankMinusLogical")
	{
	  xID = grandMotherCopyNo/localNOfVoxelsInZ + 1;
	  yID = 0;
	  zID = grandMotherCopyNo%localNOfVoxelsInZ + 1;
	  copyNo = 2*localNOfVoxelsInY*localNOfVoxelsInZ
	           +(zID-1)+(xID-1)*localNOfVoxelsInZ;
	}
	else if(touchable->GetVolume(3)->GetLogicalVolume()->GetName() == "NuLatLightGuideYBankPlusLogical")
	{
	  xID = grandMotherCopyNo/localNOfVoxelsInZ + 1;
	  yID = localNOfVoxelsInY+1;
	  zID = grandMotherCopyNo%localNOfVoxelsInZ + 1;
	  copyNo = 2*localNOfVoxelsInY*localNOfVoxelsInZ
	           +1*localNOfVoxelsInX*localNOfVoxelsInZ
	           +(zID-1)+(xID-1)*localNOfVoxelsInZ;
	}
	else if(touchable->GetVolume(3)->GetLogicalVolume()->GetName() == "NuLatLightGuideZBankMinusLogical")
	{
	  xID = grandMotherCopyNo/localNOfVoxelsInY + 1;
	  yID = grandMotherCopyNo%localNOfVoxelsInY + 1;
	  zID = 0;
	  copyNo = 2*localNOfVoxelsInY*localNOfVoxelsInZ
	           +2*localNOfVoxelsInX*localNOfVoxelsInZ
	           +(yID-1)+(xID-1)*localNOfVoxelsInY;
	}
	else if(touchable->GetVolume(3)->GetLogicalVolume()->GetName() == "NuLatLightGuideZBankPlusLogical")
	{
	  xID = grandMotherCopyNo/localNOfVoxelsInY + 1;
	  yID = grandMotherCopyNo%localNOfVoxelsInY + 1;
	  zID = localNOfVoxelsInZ+1;
	  copyNo = 2*localNOfVoxelsInY*localNOfVoxelsInZ
	           +2*localNOfVoxelsInX*localNOfVoxelsInZ
	           +1*localNOfVoxelsInX*localNOfVoxelsInY
	           +(yID-1)+(xID-1)*localNOfVoxelsInY;
	}

//Create a new hit object and get hit accounting data for this cell
  NuLatPhotoCathodeHit* hit = (*PhotoCathodeHitCollection)[copyNo];
  // add pe deposit to this PMT
  hit->AddPEHits(1);

  // check if it is first touch           //CHECK: None of these are used after saving
  if (!(hit->GetLogV()))
  {
    // fill volume information
    hit->SetLogV(physical->GetLogicalVolume());
    G4AffineTransform transform = touchable->GetHistory()->GetTopTransform();
    transform.Invert();
    hit->SetRot(transform.NetRotation());
    hit->SetPos(transform.NetTranslation());
  }
  
//If interaction is an optical absorption, pushes results to hit
  if (step->GetTrack()->GetDefinition()->GetParticleName()=="opticalphoton" &&
      step->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName() == "OpAbsorption")
		{
      hit->PushPhotonPMTHitParticleTypeIDNumber(ParticleNameToIDNumber(step));
      hit->PushPhotonPMTHitEnergy(step->GetTotalEnergyDeposit());
      hit->PushWavelength(wLength);
      hit->PushPhotonPMTXHit(xID);
      hit->PushPhotonPMTYHit(yID);
      hit->PushPhotonPMTZHit(zID);
      hit->PushPhotonPMTHitTime(step->GetTrack()->GetGlobalTime());
		}


  return true;
}




/* ---------------------------------------------- */
/*  Convert a steps particle name to an ID number */
/*  specific to the NuLat analysis                */
/* ---------------------------------------------- */
//CHECK: Change to something other than string comparison as it is very slow and this code is used a lot
G4int NuLatPhotoCathodeSensitiveDetector::ParticleNameToIDNumber(G4Step*step)
{
  G4int particleIDNumber;
  if(step->GetTrack()->GetDefinition()->GetParticleName()=="gamma") 		      		particleIDNumber=1;
  else if(step->GetTrack()->GetDefinition()->GetParticleName()=="e-") 		      	particleIDNumber=2;
  else if(step->GetTrack()->GetDefinition()->GetParticleName()=="e+") 		      	particleIDNumber=3;
  else if(step->GetTrack()->GetDefinition()->GetParticleName()=="neutron")       	particleIDNumber=4;
  else if(step->GetTrack()->GetDefinition()->GetParticleName()=="proton")       	particleIDNumber=5;
  else if(step->GetTrack()->GetDefinition()->GetParticleName()=="mu+") 		      	particleIDNumber=6;
  else if(step->GetTrack()->GetDefinition()->GetParticleName()=="mu-") 		      	particleIDNumber=7;
  else if(step->GetTrack()->GetDefinition()->GetParticleName()=="alpha") 	      	particleIDNumber=8;
  else if(step->GetTrack()->GetDefinition()->GetParticleName()=="Li7") 			      particleIDNumber=9;
  else if(step->GetTrack()->GetDefinition()->GetParticleName()=="opticalphoton") 	particleIDNumber=100;
  else particleIDNumber=0;
  return (particleIDNumber);
}
