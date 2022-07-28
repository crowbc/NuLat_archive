//PRIMARY PARTICLE GENERATOR FILE
//Produces initial particle(s) to be input into detector
//(Choose setup in Generate Primaries function and Edit specific values in Generate[            ] function

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
  NuLatGenerator = new NuLatPrimaryGeneratorMessenger(this);

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
  fOpticalphoton = particleTable->FindParticle(particleName="opticalphoton");  
}

//Destructor
NuLatPrimaryParticleGenerator::~NuLatPrimaryParticleGenerator()
{
//Deleting Particle Gun at end of program (required to do)
  delete fParticleGun;
}

//Function Controlling what type of particle Generator we want to use for a run, option set by comment/uncomment
void NuLatPrimaryParticleGenerator::GeneratePrimaries( G4Event* event )
{

  G4int initialXVoxel = PrimaryEventVoxel.getX();				//Getting the 3 values from PrimaryEventVoxel ThreeVector
  G4int initialYVoxel = PrimaryEventVoxel.getY();				//PrimaryEventVoxel values set in messenger file with a Macro
  G4int initialZVoxel = PrimaryEventVoxel.getZ();
//  initialXVoxel = initialYVoxel = initialZVoxel = 4;

  //GenerateIBDEvent( event );                    				//Inverse Beta Decay Run
  //GenerateTestParticle( event, fElectron );       				//Test Particle Run (edit specifics of particle in Function, choose partilce type here)
  //GeneratePhotonEvent(event, initialXVoxel, initialYVoxel, initialZVoxel);	//Photon Bomb Run (inputs are X_voxel, Y_voxel, and Z_voxel of primary particle (random within voxel))
  GeneratePhotonBeamEvent(event, initialXVoxel, initialYVoxel, initialZVoxel);	//Photon Bomb Run (inputs are X_voxel, Y_voxel, and Z_voxel of primary particle (random within voxel))
  

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




void NuLatPrimaryParticleGenerator::GenerateTestParticle( G4Event* event, G4ParticleDefinition* particle )
{
  //Geometry of Detector
  G4double Detector_length = 15.86865*2;//cm
  G4double one_voxel_length = 6.3373;//cm
  G4double gap_length = 0.0126;//cm

    //Setting Energy
    G4double Ekin=1*MeV;
    
    //Setting Position and Momentum
    G4double posX = (15.86865*2*G4UniformRand()-15.86865)*cm,  posY = (15.86865*2*G4UniformRand()-15.86865)*cm,    posZ = (15.86865*2*G4UniformRand()-15.86865)*cm; //position
    G4double phi = acos(1-G4UniformRand()*2);
    G4double theta = 6.283185*G4UniformRand();

    //Setting Particle creation time
    G4double particleTime=0.0*ns;
    
    //Creating Primary Particle and Primary Vertex
    G4PrimaryVertex* fvertex= new G4PrimaryVertex();
    G4PrimaryParticle* pp = new G4PrimaryParticle();

    //Setting Primary Paricle values (Partile_type, Momentum_direction, and Kinetic_energy)
    pp->SetParticleDefinition(particle);
    pp->SetMomentumDirection(G4ThreeVector(sin(phi)*cos(theta), sin(phi)*sin(theta), cos(phi)));
    pp->SetKineticEnergy(Ekin);

    //Setting Primary Vertex values (Primary_particle used, Position, Time)
    fvertex->SetPrimary(pp);
    fvertex->SetPosition((2*3.16865*0.5-3.16865 + (5-3)*6.3499)*cm, (2*3.16865*0.5-3.16865 + (5-3)*6.3499)*cm, (2*3.16865*0.5-3.16865 + (5-3)*6.3499)*cm);
    fvertex->SetT0(0.0);
    fvertex->SetT0(particleTime);

    //Add primary vertex to event (Generates Particle into simulation)
    event->AddPrimaryVertex(fvertex);
}




//Used to make photon bombs
void NuLatPrimaryParticleGenerator::GeneratePhotonEvent( G4Event* event, G4int Xpos, G4int Ypos, G4int Zpos)
{
   
   
   
   //number of photon bombs (currently:1)
   for (G4int j=0; j<1; j++)
   {
   G4PrimaryVertex* fvertex= new G4PrimaryVertex();
   
   //Setting Position and Time
//   fvertex->SetPosition((2*3.16865*G4UniformRand()-3.16865 + (Xpos-3)*6.3499)*cm,			//setting position from Macro file
//                        (2*3.16865*G4UniformRand()-3.16865 + (Ypos-3)*6.3499)*cm,
//                        (2*3.16865*G4UniformRand()-3.16865 + (Zpos-3)*6.3499)*cm);


   fvertex->SetPosition(  (2*3.16865*0.5            -3.16865 + (1   -3)*6.3499)*cm, 		//setting position manually (0,0,0) is center of detector
                          (2*3.16865*0.5            -3.16865 + (1   -3)*6.3499)*cm, 
                         ((0.5-3)*6.3499-17.78)*cm);	
   fvertex->SetT0(0.0);
   
   
   
               
   //number of photons in a bomb (currently:10,000), with energy 4 eV and random momentum direction (photon bomb)
   for (G4int i=0; i<10000; i++)
   {
      G4PrimaryParticle* pp = new G4PrimaryParticle();
      pp->SetKineticEnergy(4*eV);
      //pp->SetMass(0);
      pp->SetParticleDefinition(fOpticalphoton);     
      G4double cosphi = 1-G4UniformRand()*2;				//using phi and theta to produce randomized  momentum vector
      G4double phi = acos(cosphi);
      G4double theta = 6.283185*G4UniformRand();
      pp->SetMomentumDirection(G4ThreeVector(sin(phi)*cos(theta), sin(phi)*sin(theta), cos(phi)));  
      
      //pp->SetCharge(0);

     
      //pp->SetPolarization(G4ThreeVector(1.,1.,0.));
      
      
      fvertex->SetPrimary(pp);
 
      }

      event->AddPrimaryVertex(fvertex);				//launches the photon bomb
   
   
   }}
   
   
   
   
   
   
   
   
   
   
   
   
//Used to make pencil beams
void NuLatPrimaryParticleGenerator::GeneratePhotonBeamEvent( G4Event* event, G4int Xpos, G4int Ypos, G4int Zpos)
{
   
   G4double phi;
   G4double theta;
   G4double momX, momY, momZ;
   G4bool six_axis = false;				//option to make a unidirectional beam or splits the photons to go in 6 cardinal directions
      
   
   //number of photons used is k*j*i (currently:600)
for (G4int k=0; k<2; k++)
{
   for (G4int j=0; j<3; j++)
   {
      for (G4int i=0; i<100; i++)
   	{
   G4PrimaryVertex* fvertex= new G4PrimaryVertex();

   

   fvertex->SetT0(0.0);
   
   
   
               


      G4PrimaryParticle* pp = new G4PrimaryParticle();
      pp->SetKineticEnergy(4*eV);					//energy set to 4 eV for every photon
      //pp->SetMass(0);
      pp->SetParticleDefinition(fOpticalphoton);    
      
      
      
       {G4double angle = G4UniformRand() * 360.0*deg;		//forcibly defines polarization (found in someone elses code, may not be neccisary)
       G4ThreeVector normal (1., 0., 0.);
	G4ThreeVector kphoton = fParticleGun->GetParticleMomentumDirection();
 	G4ThreeVector product = normal.cross(kphoton);
 	G4double modul2       = product*product;
 
 	G4ThreeVector e_perpend (0., 0., 1.);
 	if (modul2 > 0.) {e_perpend = (1./std::sqrt(modul2))*product;}
 	G4ThreeVector e_paralle    = e_perpend.cross(kphoton);
 
 	G4ThreeVector polar = std::cos(angle)*e_paralle + std::sin(angle)*e_perpend;
 	pp->SetPolarization(polar); 
 	}
 	
//      G4double cosphi = 1-G4UniformRand()*2;
//      G4double phi = acos(cosphi);
//      G4double theta = 6.283185*G4UniformRand();
//      pp->SetMomentumDirection(G4ThreeVector(sin(phi)*cos(theta), sin(phi)*sin(theta), cos(phi))); 
	
	//Code to define pecil beam direction and spread
	G4double angularDispersion = 4;										//4 degree dispersion
	G4double min_primaryP = cos(angularDispersion / 180 * 3.1415);						//minimum value of primary axis momentum vector
	G4double primaryP = (1-min_primaryP)* G4UniformRand() + min_primaryP;					//Possible values of main momentum direction
	G4double r = sqrt(1-primaryP*primaryP);								//Momentum off axis
	G4double Angle = 2*3.1415 * G4UniformRand();								//Random angle along plane perpendicular to main momentum
	G4double offAxisP1 = r * cos(Angle);									//Momentum along secondary axis
	G4double offAxisP2 = r * sin(Angle);									//Momentum along tertiary axis
	
	
	//Either splits photons to go in 6 directions (not currently including beam spread) or makes them along one axis (using beam spread
	if (six_axis == true) {
	if (j == 0) { momX = primaryP;  momY = offAxisP1;  momZ = offAxisP2;};
	if (j == 1) { momX = offAxisP1;  momY = primaryP;  momZ = offAxisP2;};
	if (j == 2) { momX = offAxisP2;  momY = offAxisP1;  momZ = primaryP;};
	if (k == 0) {pp->SetMomentumDirection(G4ThreeVector(momX,momY,momZ));};
	if (k == 1) {pp->SetMomentumDirection(G4ThreeVector(-momX,-momY,-momZ));};
	};
//	if (six_axis == false) { momX = offAxisP2;  momY = offAxisP1;  momZ = primaryP; pp->SetMomentumDirection(G4ThreeVector(momX,momY,momZ));};
	if (six_axis == false) { 	G4double angle1 = (45.0/180.0*3.14159); G4double angle2 = (0.0/180.0*3.14159);
					G4double x1 = offAxisP2*cos(angle1) - offAxisP1*sin(angle1); G4double y1 = offAxisP2*sin(angle1) + offAxisP1*cos(angle1); G4double z1 = primaryP;
                                	G4double x2 = x1; G4double y2 = y1*cos(angle2) - z1*sin(angle2); G4double z2 = y1*sin(angle2) + z1*cos(angle2);
                                 	x1 = x2*cos(-angle1) - y2*sin(-angle1); y1 = x2*sin(-angle1) + y2*cos(-angle1); z1 = z2; 
	                         	momX = x1;  momY = y1;  momZ = z1; pp->SetMomentumDirection(G4ThreeVector(momX,momY,momZ));};
	
	
	

   
 //     	G4double max_radius = 0.03969*cm; 		// 1/64 in in cm (for 1/32 in hole)
 
 	//Pencil beam aperture definition (constant density circle, currently with radius set to 0: point source) and starting location
      	G4double max_radius = 0.0*cm;
      	G4double a_circle =  G4UniformRand() * 2 * 3.1415;
      	G4double r_circle = max_radius * sqrt(G4UniformRand());
   	fvertex->SetPosition(	(r_circle*cos(a_circle)) + ((1-3)*6.3499- 3.175+4*6.3499/8)*cm,			
                        	(r_circle*sin(a_circle)) + ((1-3)*6.3499- 3.175+4*6.3499/8)*cm,	
                        	((0.5-3)*6.3499-17.78)*cm);		//set at 7in from lattice
           

 	
      	
      	fvertex->SetPrimary(pp);
	event->AddPrimaryVertex(fvertex);			//creates the photon
      
   
   
   }}}}
   


