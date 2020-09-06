#ifndef NuLatPhotoCathodeHit_h
#define NuLatPhotoCathodeHit_h 1

#include "vector"

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "G4LogicalVolume.hh"
#include "G4Transform3D.hh"
#include "G4RotationMatrix.hh"

using namespace std;

class G4AttDef;
class G4AttValue;

/// NuLatPhotoCathodeHit hit
///
/// It should record:
/// - the PMT ID
/// - the energy deposit 
/// - the PMT logical volume, its position and rotation

class NuLatPhotoCathodeHit : public G4VHit
{
public:
  NuLatPhotoCathodeHit();
  NuLatPhotoCathodeHit(G4int z);
  NuLatPhotoCathodeHit(const NuLatPhotoCathodeHit &right);
  
  virtual ~NuLatPhotoCathodeHit();

  const NuLatPhotoCathodeHit& operator=(const NuLatPhotoCathodeHit &right);
  int operator==(const NuLatPhotoCathodeHit &right) const;

  inline void *operator new(size_t);
  inline void operator delete(void *aHit);
    
  virtual void Draw();
  virtual void Print();
    
  virtual const std::map<G4String,G4AttDef>* GetAttDefs() const;
  virtual std::vector<G4AttValue>* CreateAttValues() const;

    
  void SetPMTID(G4int z) { fPMTID = z; }
  G4int GetPMTID() const { return fPMTID; }

  void SetPEHits(G4int de) { peHits = de; }
  void AddPEHits(G4int de) { peHits += de;}
  G4double GetPEHits() const { return peHits; }
  G4double GetWavelength() const { return Wavelength; }

  void SetPos(G4ThreeVector xyz) { fPos = xyz; }
  G4ThreeVector GetPos() const { return fPos; }

  void SetRot(G4RotationMatrix rmat) { fRot = rmat; }
  G4RotationMatrix GetRot() const { return fRot; }

  void SetLogV(G4LogicalVolume* val) { fPLogV = val; }
  const G4LogicalVolume* GetLogV() const { return fPLogV; }

  void PushPhotonPMTHitParticleTypeIDNumber(G4int ID) { PhotonPMTHitParticleTypeIDNumber.push_back(ID); }
  void PushWavelength(G4double de)                  { PhotonPMTHitWavelength.push_back(de); }
  void PushPhotonPMTXHit(G4int X)          { PhotonPMTXHit.push_back(X); }
  void PushPhotonPMTYHit(G4int Y)          { PhotonPMTYHit.push_back(Y); }
  void PushPhotonPMTZHit(G4int Z)          { PhotonPMTZHit.push_back(Z); }
  void PushPhotonPMTHitTime(G4double time)            { PhotonPMTHitTime.push_back(time); }
    
  std::vector<G4int>     GetPhotonPMTHitParticleTypeIDNumberVector() { return  PhotonPMTHitParticleTypeIDNumber; }
  std::vector<G4double>  GetPhotonPMTHitWavelengthVector()                     { return  PhotonPMTHitWavelength; }
  std::vector<G4int>  GetPhotonPMTXHitVector()            { return  PhotonPMTXHit; }
  std::vector<G4int>  GetPhotonPMTYHitVector()            { return  PhotonPMTYHit; }
  std::vector<G4int>  GetPhotonPMTZHitVector()            { return  PhotonPMTZHit; }
  std::vector<G4double>  GetPhotonPMTHitTimeVector()                 { return  PhotonPMTHitTime; }

  void ClearPhotonPMTHitParticleTypeIDNumberVector() { PhotonPMTHitParticleTypeIDNumber.clear(); }
  void ClearPhotonPMTHitWavelengthVector()                      { PhotonPMTHitWavelength.clear(); }
  void ClearPhotonPMTXHitVector()             { PhotonPMTXHit.clear(); }
  void ClearPhotonPMTYHitVector()             { PhotonPMTYHit.clear(); }
  void ClearPhotonPMTZHitVector()             { PhotonPMTZHit.clear(); }
  void ClearPhotonPMTHitTimeVector()                  { PhotonPMTHitTime.clear(); }



private:
  G4int fPMTID;
  G4int peHits;
  G4double Wavelength;

  static std::vector<G4int>  PhotonPMTHitParticleTypeIDNumber;
  static std::vector<G4int> PMTPE;
  static std::vector<G4int> PMTXPE;
  static std::vector<G4int> PMTYPE;
  static std::vector<G4int> PMTZPE;
  static std::vector<G4double>  PhotonPMTHitWavelength;
  static std::vector<G4int>  PhotonPMTXHit;
  static std::vector<G4int>  PhotonPMTYHit;
  static std::vector<G4int>  PhotonPMTZHit;
  static std::vector<G4double>  PhotonPMTHitTime;

  G4ThreeVector fPos;
  G4RotationMatrix fRot;
  const G4LogicalVolume* fPLogV;
    
}; 

typedef G4THitsCollection<NuLatPhotoCathodeHit> NuLatPhotoCathodeHitsCollection;

extern G4ThreadLocal G4Allocator<NuLatPhotoCathodeHit>* NuLatPhotoCathodeHitAllocator;

inline void* NuLatPhotoCathodeHit::operator new(size_t)
{
  if (!NuLatPhotoCathodeHitAllocator)
      NuLatPhotoCathodeHitAllocator = new G4Allocator<NuLatPhotoCathodeHit>;
  return (void*)NuLatPhotoCathodeHitAllocator->MallocSingle();
}

inline void NuLatPhotoCathodeHit::operator delete(void* aHit)
{
  NuLatPhotoCathodeHitAllocator->FreeSingle((NuLatPhotoCathodeHit*) aHit);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
