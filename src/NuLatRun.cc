//this file needs work
//this is where to implNuLatent post event output
#include "NuLatRun.hh"
#include "NuLatVoxelHit.hh"

#include "G4Event.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"




NuLatRun::NuLatRun() :
    G4Run(),
    NuLat_ene(0),
    NuLatHCID(-1)
{ }


void NuLatRun::RecordEvent(const G4Event* evt)
{




    //Forward call to base class
    G4Run::RecordEvent(evt);

    if ( NuLatHCID == -1 ) {

        G4SDManager* sdManager = G4SDManager::GetSDMpointer();
        NuLatHCID = sdManager->GetCollectionID("NuLatVoxel/NuLatVoxelColl");


    }
    //
    //
    G4HCofThisEvent* hce = evt->GetHCofThisEvent();
    //
    //
    //
    if (!hce) {
        G4ExceptionDescription msg;
        msg << "No hits collection of this event found.\n";
        G4Exception("Run::RecordEvent()",
                    "Code001", JustWarning, msg);
        return;
  
    }
    //
    //
    const NuLatVoxelHitsCollection* NuLatHC =
        static_cast<const NuLatVoxelHitsCollection*>(hce->GetHC(NuLatHCID));
    //
    //
    if ( !NuLatHC)
    {
        G4ExceptionDescription msg;
        msg << "Some of hits collections of this event not found.\n";
        G4Exception("Run::RecordEvent()",
                    "Code001", JustWarning, msg);
        return;

    }
    //
    //
    G4double NuLatSum = 0;
    G4int    NuLatNumVoxelsHit = 0;
    //
    //
    for (size_t i=0;i<NuLatHC->GetSize();i++)
    {
        NuLatVoxelHit* hit = (*NuLatHC)[i];
        NuLatSum += hit->GetEdep();
        if (hit->GetEdep()>0.0)
          NuLatNumVoxelsHit++;
    }

    NuLat_ene += NuLatSum;

    if (evt->GetEventID() % 1000 == 0)
    {    
    		G4cout<<G4endl<<G4endl
		      << "End of Run" << G4endl
		      << "   Event" << evt->GetEventID() <<G4endl
		      << "   Energy = " << NuLatSum << G4endl
		      << "   # of Cells Hit = "<< NuLatNumVoxelsHit
		      <<G4endl <<G4endl;
		}

}


void NuLatRun::Merge(const G4Run* aRun)
{
    const NuLatRun* localRun = static_cast<const NuLatRun*>(aRun);
    NuLat_ene += localRun->GetNuLatEnergy();
    //Forward call to base-class
    G4Run::Merge(localRun);
}
