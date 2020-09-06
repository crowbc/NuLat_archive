#ifndef NuLatRUN_HH
#define NuLatRUN_HH

#include "G4Run.hh"

class G4Event;

class NuLatRun : public G4Run {
public:
    NuLatRun();
  virtual ~NuLatRun() {};

  virtual void RecordEvent(const G4Event*);
  virtual void Merge(const G4Run*);
    G4double GetNuLatEnergy() const { return NuLat_ene; }
private:
    G4double NuLat_ene;
    G4int NuLatHCID;
};
#endif
