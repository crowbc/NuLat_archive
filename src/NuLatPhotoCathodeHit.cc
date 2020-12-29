//PHOTOCATHODE HIT FILE
//Records data on hit (not fully understood)

// needs work, this is were to record cell hits when we implement individual cells with optical tracking
#include "NuLatPhotoCathodeHit.hh"

#include "G4VVisManager.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "G4AttDefStore.hh"
#include "G4AttDef.hh"
#include "G4AttValue.hh"
#include "G4UIcommand.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4ios.hh"




G4ThreadLocal G4Allocator<NuLatPhotoCathodeHit>* NuLatPhotoCathodeHitAllocator=0;




NuLatPhotoCathodeHit::NuLatPhotoCathodeHit():
G4VHit(),
fPMTID(-1),
peHits(0),
fPos(0),
fPLogV(0)
{

}




vector<G4int>     NuLatPhotoCathodeHit::PhotonPMTHitParticleTypeIDNumber;
vector<G4int>     NuLatPhotoCathodeHit::PMTPE;
vector<G4int>     NuLatPhotoCathodeHit::PMTXPE;
vector<G4int>     NuLatPhotoCathodeHit::PMTYPE;
vector<G4int>     NuLatPhotoCathodeHit::PMTZPE;
vector<G4double>  NuLatPhotoCathodeHit::PhotonPMTHitEnergy;
vector<G4double>  NuLatPhotoCathodeHit::PhotonPMTHitWavelength;
vector<G4int>     NuLatPhotoCathodeHit::PhotonPMTXHit;
vector<G4int>     NuLatPhotoCathodeHit::PhotonPMTYHit;
vector<G4int>     NuLatPhotoCathodeHit::PhotonPMTZHit;
vector<G4double>  NuLatPhotoCathodeHit::PhotonPMTHitTime;







NuLatPhotoCathodeHit::NuLatPhotoCathodeHit(G4int z): 
G4VHit(),
fPMTID(z),
peHits(0),
fPos(0),
fPLogV(0)
{

}






NuLatPhotoCathodeHit::NuLatPhotoCathodeHit(const NuLatPhotoCathodeHit &right):
G4VHit()
{
    fPMTID = right.fPMTID;
    peHits    = right.peHits;
    fPos    = right.fPos;
    fRot    = right.fRot;
    fPLogV  = right.fPLogV;
}




NuLatPhotoCathodeHit::~NuLatPhotoCathodeHit()
{

}




const NuLatPhotoCathodeHit& NuLatPhotoCathodeHit::operator= (const NuLatPhotoCathodeHit &right)
{
    fPMTID  = right.fPMTID;
    peHits     = right.peHits;
    fPos     = right.fPos;
    fRot     = right.fRot;
    fPLogV   = right.fPLogV;
    return *this;
}




int NuLatPhotoCathodeHit::operator==(const NuLatPhotoCathodeHit &right) const
{
    return (fPMTID==right.fPMTID);
}




void NuLatPhotoCathodeHit::Draw()
{
    G4VVisManager* pVVisManager = G4VVisManager::GetConcreteInstance();
    if (pVVisManager&&(peHits>0.))
    {
        // Draw a calorimeter cell with a color corresponding to its peHits deposit
        G4Transform3D trans(fRot.inverse(),fPos);
        G4VisAttributes attribs;
        const G4VisAttributes* pVA = fPLogV->GetVisAttributes();
        if (pVA) attribs = *pVA;
        G4double rcol = 2;
        if (rcol>1.) rcol = 1.;
        if (rcol<0.4) rcol = 0.4;
        G4Colour colour(rcol,0.,0.);
        attribs.SetColour(colour);
        attribs.SetForceSolid(true);
        pVVisManager->Draw(*fPLogV,attribs,trans);
    }
}




const std::map<G4String,G4AttDef>* NuLatPhotoCathodeHit::GetAttDefs() const
{
    G4bool isNew;
    std::map<G4String,G4AttDef>* store
    = G4AttDefStore::GetInstance("NuLatPhotoCathodeHit",isNew);

    if (isNew) {
        (*store)["HitType"] 
          = G4AttDef("HitType","Hit Type","Physics","","G4String");
        
        (*store)["peHits"] 
          = G4AttDef("peHits", "peHits Deposited", "Physics", "G4BestUnit", 
                     "G4double");
        
        (*store)["Pos"] 
          = G4AttDef("Pos", "Position", "Physics","G4BestUnit", 
                     "G4ThreeVector");
        
        (*store)["LVol"] 
          = G4AttDef("LVol","Logical Volume","Physics","","G4String");
    }
    return store;
}




std::vector<G4AttValue>* NuLatPhotoCathodeHit::CreateAttValues() const
{
    std::vector<G4AttValue>* values = new std::vector<G4AttValue>;
    
    values
      ->push_back(G4AttValue("HitType","NuLatPhotoCathodeHit",""));
    values
      ->push_back(G4AttValue("ID",G4UIcommand::ConvertToString(fPMTID),""));   
    values
      ->push_back(G4AttValue("peHits",G4BestUnit(peHits,"peHits"),""));
    values
      ->push_back(G4AttValue("Pos",G4BestUnit(fPos,"Length"),""));
    
    if (fPLogV)
        values->push_back(G4AttValue("LVol",fPLogV->GetName(),""));
    else
        values->push_back(G4AttValue("LVol"," ",""));
    
    return values;
}




void NuLatPhotoCathodeHit::Print()
{
    G4cout << "  PMT[" << fPMTID << "] " << peHits << G4endl;
}
