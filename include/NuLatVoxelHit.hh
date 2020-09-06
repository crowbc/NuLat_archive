// needs work, this is were to record cell hits when we implement individual cells with optical tracking
#ifndef NuLatVoxelHit_h
#define NuLatVoxelHit_h 1

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

/// NuLatVoxelHit hit
///
/// It should record:
/// - the cell ID
/// - the energy deposit
/// - the cell logical volume, its position and rotation

class NuLatVoxelHit : public G4VHit
{
public:
  NuLatVoxelHit();
  NuLatVoxelHit(G4int z);
  NuLatVoxelHit(const NuLatVoxelHit &right);
  
  virtual ~NuLatVoxelHit();

  const NuLatVoxelHit& operator=(const NuLatVoxelHit &right);
  int operator==(const NuLatVoxelHit &right) const;

  inline void *operator new(size_t);
  inline void operator delete(void *aHit);
    
  virtual void Draw();
  virtual void Print();
    
  virtual const std::map<G4String,G4AttDef>* GetAttDefs() const;
  virtual std::vector<G4AttValue>* CreateAttValues() const;

    
  void SetCellID(G4int z) { fCellID = z; }
  G4int GetCellID() const { return fCellID; }

  void SetEdep(G4double de) { eDep = de; }
  void AddEdep(G4double de) { eDep += de;}
  G4double GetEdep() const { return eDep; }

  void SetPos(G4ThreeVector xyz) { fPos = xyz; }
  G4ThreeVector GetPos() const { return fPos; }

  void SetRot(G4RotationMatrix rmat) { fRot = rmat; }
  G4RotationMatrix GetRot() const { return fRot; }

  void SetLogV(G4LogicalVolume* val) { fPLogV = val; }
  const G4LogicalVolume* GetLogV() const { return fPLogV; }

  void PushEDepParticleTypeIDNumber(G4int ID) { eDepParticleTypeIDNumber.push_back(ID); }
  void PushEDep(G4double de)                  { eDepEDep.push_back(de); }
  void PushEDepPositionX(G4double X)          { eDepPositionX.push_back(X); }
  void PushEDepPositionY(G4double Y)          { eDepPositionY.push_back(Y); }
  void PushEDepPositionZ(G4double Z)          { eDepPositionZ.push_back(Z); }
  void PushEDepTime(G4double time)            { eDepTime.push_back(time); }
    
  std::vector<G4int>     GetEDepParticleTypeIDNumberVector() { return  eDepParticleTypeIDNumber; }
  std::vector<G4double>  GetEDepVector()                     { return  eDepEDep; }
  std::vector<G4double>  GetEDepPositionXVector()            { return  eDepPositionX; }
  std::vector<G4double>  GetEDepPositionYVector()            { return  eDepPositionY; }
  std::vector<G4double>  GetEDepPositionZVector()            { return  eDepPositionZ; }
  std::vector<G4double>  GetEDepTimeVector()                 { return  eDepTime; }
    
  void ClearEDepParticleTypeIDNumberVector() { eDepParticleTypeIDNumber.clear(); }
  void ClearEDepVector()                      { eDepEDep.clear(); }
  void ClearEDepPositionXVector()             { eDepPositionX.clear(); }
  void ClearEDepPositionYVector()             { eDepPositionY.clear(); }
  void ClearEDepPositionZVector()             { eDepPositionZ.clear(); }
  void ClearEDepTimeVector()                  { eDepTime.clear(); }
    

    
private:
  G4int fCellID;
  G4double eDep;

  static std::vector<G4int>  eDepParticleTypeIDNumber;
  static std::vector<G4double>  eDepEDep;
  static std::vector<G4double>  eDepPositionX;
  static std::vector<G4double>  eDepPositionY;
  static std::vector<G4double>  eDepPositionZ;
  static std::vector<G4double>  eDepTime;

  G4ThreeVector fPos;
  G4RotationMatrix fRot;
  const G4LogicalVolume* fPLogV;
    
}; 

typedef G4THitsCollection<NuLatVoxelHit> NuLatVoxelHitsCollection;

extern G4ThreadLocal G4Allocator<NuLatVoxelHit>* NuLatVoxelHitAllocator;

inline void* NuLatVoxelHit::operator new(size_t)
{
  if (!NuLatVoxelHitAllocator)
      NuLatVoxelHitAllocator = new G4Allocator<NuLatVoxelHit>;
  return (void*)NuLatVoxelHitAllocator->MallocSingle();
}

inline void NuLatVoxelHit::operator delete(void* aHit)
{
  NuLatVoxelHitAllocator->FreeSingle((NuLatVoxelHit*) aHit);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
