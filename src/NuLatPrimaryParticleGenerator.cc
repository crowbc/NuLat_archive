#include "Randomize.hh"
#include "G4ios.hh"
#include "math.h"

#include "NuLatPrimaryParticleGenerator.hh"


#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4PrimaryVertex.hh"

#include "G4ParticleTypes.hh"
#include "G4SystemOfUnits.hh"

#include <iostream>
#include <fstream>
using namespace std;


//Defining general particle creating function
NuLatPrimaryParticleGenerator::NuLatPrimaryParticleGenerator()
{
  G4int n_particle = 1;                                                              //Standard, generating 1 particle event

  fParticleGun  = new G4ParticleGun(n_particle);                                     //Using Geant defined particle gun as our generator (as opposed to GeneralParticleSource)

//Defing the types of particles used
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4String particleName;
  fGeantino = particleTable->FindParticle(particleName="geantino");
  fPositron = particleTable->FindParticle(particleName="e+");
  fMuon = particleTable->FindParticle(particleName="mu+");
  fPion = particleTable->FindParticle(particleName="pi+");
  fKaon = particleTable->FindParticle(particleName="kaon+");
  fProton = particleTable->FindParticle(particleName="proton");
  fElectron = particleTable->FindParticle(particleName="e-");
  fGamma = particleTable->FindParticle(particleName="gamma");
  fNeutron = particleTable->FindParticle(particleName="neutron");
}

//Destructor
NuLatPrimaryParticleGenerator::~NuLatPrimaryParticleGenerator()
{
//Deleting Particle Gun at end of program (required to do)
  delete fParticleGun;
}

//Function Controlling what type of particle Generator we want to use for a run, option set in Macro 
void NuLatPrimaryParticleGenerator::GeneratePrimaries( G4Event* event )
{

  GenerateIBDEvent( event );
  
// this function is called at the beginning of event
  fParticleGun->GeneratePrimaryVertex(event);

}







//Function to generate an Inverse Beta Decay Event
void NuLatPrimaryParticleGenerator::GenerateIBDEvent( G4Event* event )
{
//Defining Variables
  G4double Ekin;
 
  G4double Detector_length = 15.86865*2;//cm
  G4double one_voxel_length = 6.3373;//cm
  G4double gap_length = 0.0126;//cm


//Random PositionGenerator for each voxel (cube) index
   G4double pos1 = (-12.7+(one_voxel_length*G4UniformRand()-one_voxel_length/2))*cm; //-15.86865 ~ -9.53135
   G4double pos2 = (-12.7+(one_voxel_length*G4UniformRand()-one_voxel_length/2)+one_voxel_length+gap_length)*cm; //-9.51865 ~ -3.18135
   G4double pos3 = (-12.7+(one_voxel_length*G4UniformRand()-one_voxel_length/2)+one_voxel_length+gap_length+one_voxel_length+gap_length)*cm; //-3.16865 ~ 3.16865
   G4double pos4 = (-12.7+(one_voxel_length*G4UniformRand()-one_voxel_length/2)+one_voxel_length+gap_length+one_voxel_length+gap_length+one_voxel_length+gap_length)*cm; //3.18135 ~ 9.52865
   G4double pos5 = (-12.7+(one_voxel_length*G4UniformRand()-one_voxel_length/2)+one_voxel_length+gap_length+one_voxel_length+gap_length+one_voxel_length+gap_length+one_voxel_length+gap_length)*cm; //9.52865 ~ 15.86865


//Defining Position for our IBD event
    G4double posX = pos3;
    G4double posY = pos3;
    G4double posZ = pos3;



//Defining Time Particles are produced    
    G4double particleTime=0.0*ns;
    
//Creating Vertex Variables for each particle 
    G4PrimaryVertex* fvertex1= new G4PrimaryVertex();                  //Creating Positron Vertex
    G4PrimaryVertex* fvertex2= new G4PrimaryVertex();                  //Creating Neutron  Vertex
    
//Creating Particle Variable for each particle
    G4PrimaryParticle* pp = new G4PrimaryParticle();                   //Creating Positron Particle Description
    G4PrimaryParticle* pp2 = new G4PrimaryParticle();                  //Creating Neutron  Particle Description



//Defining Positron to create
    G4double costheta = 2.*G4UniformRand()-1.0;                       //Setting random momentum direction for Positron
    G4double sintheta = sqrt( 1. - costheta*costheta );
    G4double phi      = (360.*deg)*G4UniformRand();
    
    Ekin=2*MeV;                                                        //Defining Positron Energy
    pp->SetParticleDefinition(fPositron);                              //Setting pp particle type: Positron
    pp->SetMomentumDirection(G4ThreeVector(sintheta*cos(phi), sintheta*sin(phi), costheta));
                                                                       //Setting pp Momentum Direction
    pp->SetKineticEnergy(Ekin);                                        //Setting pp Kinetic Energy (2MeV)

    fvertex1->SetPosition(posX,posY,posZ);                             //Setting Positron Creation Position
    fvertex1->SetT0(0.0);                                              //Setting Positron Creation Time
    fvertex1->SetPrimary(pp);                                          //Connecting particle info (pp) and vertex info (fvertex1) for Positron
    fvertex1->SetT0(particleTime);                                     //Setting Positron creation time

    event->AddPrimaryVertex(fvertex1);                                 //Telling Program to Create Particle (Positron) with specifications we gave it




//Defining Neutron to create
    costheta = 2.*G4UniformRand()-1.0;                                //Setting random momentum directions for Neutron
    sintheta = sqrt( 1. - costheta*costheta );
    phi      = (360.*deg)*G4UniformRand();
    
    Ekin=400*keV;;                                                     //Defining Neutron Energy
    pp2->SetParticleDefinition(fNeutron);                              //Setting pp2 particle type: Neutron
    pp2->SetMomentumDirection(G4ThreeVector(sintheta*cos(phi), sintheta*sin(phi), costheta));
                                                                       //Setting pp2 Momentum Direction
    pp2->SetKineticEnergy(Ekin);                                       //Setting pp2 Kinetic Energy (4keV)

    fvertex2->SetPosition(posY,posX,posZ);                             //Setting Neutron Creation Position
    fvertex2->SetT0(0.0);                                              //Setting Neutron Creation Time
    fvertex2->SetPrimary(pp2);                                         //Connecting particle info (pp2) and vertex info (fvertex2) for Neutron
    fvertex2->SetT0(particleTime);                                     //Setting Neutron creation time

    event->AddPrimaryVertex(fvertex2);                                 //Telling Program to Create Particle (Neutron) with specifications we gave it
}



