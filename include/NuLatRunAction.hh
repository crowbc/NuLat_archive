//RUN ACTION HEADER FILE

#ifndef RunAction_h
#define RunAction_h 1

#include <vector>

#include "G4UserRunAction.hh"
#include "globals.hh"

using namespace std;

class G4Run;

/// Run action class

class NuLatRunAction : public G4UserRunAction
{
  public:
    NuLatRunAction();
    virtual ~NuLatRunAction();
    std::vector<G4double> CellEnergyVector;
    std::vector<G4int> CellXHitVector;
    std::vector<G4int> CellYHitVector;
    std::vector<G4int> CellZHitVector;
    
    std::vector<G4int> EDepParticleTypeIDNumberVector;
    std::vector<G4double> EDepParticleEDepVector;
    std::vector<G4double> EDepPositionXVector;
    std::vector<G4double> EDepPositionYVector;
    std::vector<G4double> EDepPositionZVector;
    std::vector<G4double> EDepTimeVector;
    
    std::vector<G4int> PhotonPMTHitParticleTypeIDNumberVector;
    
    std::vector<G4int> PMTPEVector;
    std::vector<G4int> PMTXPEVector;
    std::vector<G4int> PMTYPEVector;
    std::vector<G4int> PMTZPEVector;
    
    std::vector<G4double> PhotonPMTHitWavelengthVector;
    std::vector<G4double> PhotonPMTHitEnergyVector;    
    std::vector<G4int> PhotonPMTXHitVector;
    std::vector<G4int> PhotonPMTYHitVector;
    std::vector<G4int> PhotonPMTZHitVector;
    std::vector<G4double> PhotonPMTHitTimeVector;
    std::vector<G4double> InitialMomentumXVector;
    std::vector<G4double> InitialMomentumYVector;
    std::vector<G4double> InitialMomentumZVector;      

    virtual void BeginOfRunAction(const G4Run*);
    virtual void   EndOfRunAction(const G4Run*);
    virtual G4Run* GenerateRun();
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
