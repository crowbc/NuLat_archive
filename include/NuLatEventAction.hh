//EVENT ACTION HEADER FILE

#ifndef EventAction_h
#define EventAction_h 1


#include "G4UserEventAction.hh"
#include "globals.hh"
#include "NuLatRunAction.hh"

/// Event action

class NuLatEventAction : public G4UserEventAction
{
public:
    NuLatEventAction(int xVoxels, int yVoxels, int zVoxels);
    virtual ~NuLatEventAction();
    
    virtual void BeginOfEventAction(const G4Event*);
    virtual void EndOfEventAction(const G4Event*);
    
    NuLatRunAction* NuLatRunActionLocal;
    
private:
    G4int fECHCID;
    G4int fPCHCID;
    FILE * outputFile;
    G4int localNOfVoxelsInX;
    G4int localNOfVoxelsInY;
    G4int localNOfVoxelsInZ;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
