//VOXEL SENSITIVE DETECTOR FILE
//Decribes Sensitive Region of Detection and what to do when hit


//file needs work
// hit proccessing / energy deposit processing
#include <iostream>
#include <fstream>

#include "NuLatVoxelSensitiveDetector.hh"
#include "NuLatVoxelHit.hh"

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
NuLatVoxelSensitiveDetector::NuLatVoxelSensitiveDetector(G4String name,
    G4int    nOfVoxelsInX,   G4int    nOfVoxelsInY,   G4int    nOfVoxelsInZ,
    G4double voxelXDim,      G4double voxelYDim,      G4double voxelZDim,
    G4double voxSpacingXDim, G4double voxSpacingYDim, G4double voxSpacingZDim)
: G4VSensitiveDetector(name), voxelHitCollection(0), voxelHitCollectionID(-1)
{
    collectionName.insert("NuLatVoxelColl");
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




NuLatVoxelSensitiveDetector::~NuLatVoxelSensitiveDetector()
{}




/* ---------------------------------------------- */
/*       Initialze the sensitive detector         */
/* ---------------------------------------------- */
void NuLatVoxelSensitiveDetector::Initialize(G4HCofThisEvent* hce)
{
  voxelHitCollection
    = new NuLatVoxelHitsCollection(SensitiveDetectorName,collectionName[0]);
  if (voxelHitCollectionID<0)
  {
    voxelHitCollectionID = G4SDManager::GetSDMpointer()->GetCollectionID(voxelHitCollection);
  }
  hce->AddHitsCollection(voxelHitCollectionID,voxelHitCollection);
  // fill NuLatVoxelHits with zero energy deposition
  for (G4int i=0;i<localNOfVoxelsInX*localNOfVoxelsInY*localNOfVoxelsInZ;i++)
  {
    NuLatVoxelHit* hit = new NuLatVoxelHit(i);
    voxelHitCollection->insert(hit);
  }
}




/* ---------------------------------------------- */
/*                 Process Hits                   */
/* ---------------------------------------------- */
G4bool NuLatVoxelSensitiveDetector::ProcessHits(G4Step*step, G4TouchableHistory*)
{

  G4double edep = step->GetTotalEnergyDeposit();

  if (edep==0.)
    return true;

  G4TouchableHistory* touchable = (G4TouchableHistory*)(step->GetPreStepPoint()->GetTouchable());
  G4VPhysicalVolume*  physical  = touchable->GetVolume();
  G4int               copyNo    = physical->GetCopyNo();

  NuLatVoxelHit* hit = (*voxelHitCollection)[copyNo];

  // check if it is first touch
  if (!(hit->GetLogV()))
  {
    // fill volume information
    hit->SetLogV(physical->GetLogicalVolume());
    G4AffineTransform transform = touchable->GetHistory()->GetTopTransform();
    transform.Invert();
    hit->SetRot(transform.NetRotation());
    hit->SetPos(transform.NetTranslation());
  }


  // add energy deposit to this voxel


//  if (step->GetTrack()->GetDefinition()->GetParticleName()=="opticalphoton" &&
//      step->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName() == "OpAbsorption")
//      {
  if (step->GetTrack()->GetDefinition()->GetParticleName()!="opticalphoton"  )
  {
    hit->AddEdep(edep);  
  // push onto the appropriate vectors the
  // values associated with the energy deposit (EDep)
  hit->PushEDepParticleTypeIDNumber(ParticleNameToIDNumber(step));
  hit->PushEDep(edep);
  hit->PushEDepPositionX(step->GetTrack()->GetPosition().x());
  hit->PushEDepPositionY(step->GetTrack()->GetPosition().y());
  hit->PushEDepPositionZ(step->GetTrack()->GetPosition().z());
  hit->PushEDepTime(step->GetTrack()->GetGlobalTime());
  hit->PushInitialMomentumX(step->GetTrack()->GetVertexMomentumDirection().theta());
  hit->PushInitialMomentumY(step->GetTrack()->GetVertexMomentumDirection().phi());
  hit->PushInitialMomentumZ(step->GetTrack()->GetVertexMomentumDirection().z());  
}
  return true;

}




/* ---------------------------------------------- */
/*  Convert a steps particle name to an ID number */
/*  specific to the NuLat analysis                */
/* ---------------------------------------------- */
G4int NuLatVoxelSensitiveDetector::ParticleNameToIDNumber(G4Step*step)
{
  G4int particleIDNumber;
  if(step->GetTrack()->GetDefinition()->GetParticleName()=="opticalphoton") 		      		particleIDNumber=100;
  else if(step->GetTrack()->GetDefinition()->GetParticleName()=="e-") 			      	particleIDNumber=2;
  else if(step->GetTrack()->GetDefinition()->GetParticleName()=="e+") 		      		particleIDNumber=3;
  else if(step->GetTrack()->GetDefinition()->GetParticleName()=="neutron")   		    	particleIDNumber=4;
  else if(step->GetTrack()->GetDefinition()->GetParticleName()=="proton")    		   	particleIDNumber=5;
  else if(step->GetTrack()->GetDefinition()->GetParticleName()=="mu+") 			      	particleIDNumber=6;
  else if(step->GetTrack()->GetDefinition()->GetParticleName()=="mu-") 			      	particleIDNumber=7;
  else if(step->GetTrack()->GetDefinition()->GetParticleName()=="alpha") 			      	particleIDNumber=8;
  else if(step->GetTrack()->GetDefinition()->GetParticleName()=="Li7") 			      	particleIDNumber=9;
  else if(step->GetTrack()->GetDefinition()->GetParticleName()=="gamma") 				particleIDNumber=1;
  else particleIDNumber=0;
  return (particleIDNumber);
}

