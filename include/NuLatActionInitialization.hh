//ACTION INITIALIZATION HEADER FILE

#ifndef ActionInitialization_h
#define ActionInitialization_h 1

#include "G4VUserActionInitialization.hh"
#include "globals.hh"

/// Action initialization class.

class NuLatActionInitialization : public G4VUserActionInitialization
{
  public:
    NuLatActionInitialization(int xVoxels, int yVoxels, int zVoxels);
    virtual ~NuLatActionInitialization();

    virtual void BuildForMaster() const;
    virtual void Build() const;
    G4int localNOfVoxelsInX;
    G4int localNOfVoxelsInY;
    G4int localNOfVoxelsInZ;

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
