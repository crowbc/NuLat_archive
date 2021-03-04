//PRIMARY PARTICLE GENERATOR HEADER FILE

#include <time.h>
#ifndef NuLatPrimaryParticleGenerator_H
#define NuLatPrimaryParticleGenerator_H 1


#include "G4VUserPrimaryGeneratorAction.hh"
#include "globals.hh"

#include "NuLatPrimaryGeneratorMessenger.hh"


class G4ParticleGun;
//class G4GenericMessenger;  to be implemented
class G4Event;
class G4ParticleDefinition;

class NuLatPrimaryParticleGenerator : public G4VUserPrimaryGeneratorAction
{

  public:
    NuLatPrimaryParticleGenerator();
    ~NuLatPrimaryParticleGenerator();
    void GeneratePrimaries( G4Event* );
    void SetEventTypeFlag(G4String val) {EventTypeFlag = val;};
    void SetPrimaryEventVoxel(G4ThreeVector val) {PrimaryEventVoxel = val;};

	private:

		void DefineCommands();
		G4double GetRndReactorPositronEnergy();
		G4double GetRndReactorBackgroundGammaEnergyInMiniTimeCubeCaveAtNIST();
		G4double GetRndSpecialNuclearMaterialNeutronFissionEnergy();
		void GenerateTestParticle( G4Event* event, G4ParticleDefinition* particleToRun );
		void GenerateIBDEvent( G4Event* event );
		void GeneratePhotonEvent( G4Event* event, G4int Xpos, G4int Ypos, G4int Zpos );

		G4ParticleGun* fParticleGun;

		G4ParticleDefinition* fGeantino;
		G4ParticleDefinition* fPositron;
		G4ParticleDefinition* fNeutron;
		G4ParticleDefinition* fElectron;
		G4ParticleDefinition* fGamma;
		G4ParticleDefinition* fMuon;
		G4ParticleDefinition* fPion;
		G4ParticleDefinition* fKaon;
		G4ParticleDefinition* fProton;
		G4ParticleDefinition* fOpticalphoton;
		
		
		G4String EventTypeFlag;
		G4ThreeVector PrimaryEventVoxel;
		
		NuLatPrimaryGeneratorMessenger* NuLatGenerator;

};

#endif
