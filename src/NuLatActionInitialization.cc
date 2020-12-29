//ACTION INITIALIZATION FILE
//Sets up actions, putting together parts of simulation
//(Highly related files: RunAction.cc/.hh, EventAction.cc/.hh, PrimaryParticleGenerator.cc/.hh)

#include "NuLatActionInitialization.hh"
#include "NuLatPrimaryParticleGenerator.hh"
#include "NuLatRunAction.hh"
#include "NuLatEventAction.hh"

//Constructor
NuLatActionInitialization::NuLatActionInitialization(int xVoxels, int yVoxels, int zVoxels)
 : G4VUserActionInitialization()
{
  localNOfVoxelsInX = xVoxels;
  localNOfVoxelsInY = yVoxels;
  localNOfVoxelsInZ = zVoxels;
}


//Destructor
NuLatActionInitialization::~NuLatActionInitialization()
{}


//BuildForMaster orgainizes multithreading and is done sequentially
//Should only contain RunAction
void NuLatActionInitialization::BuildForMaster() const
{
  SetUserAction(new NuLatRunAction);
}


//Build is what is used for each thread and can run parallel
void NuLatActionInitialization::Build() const
{

//Setting Primary Particle Generator (controls initial particle creation), RunAction (Actions at beggining and end of run), and Event Action (Actions at beggining and end of each event) programs
//RunAction and Event Action mainly used for data collecting and filling tables
  NuLatPrimaryParticleGenerator* NuLatPrimaryParticleGenerator001 = new NuLatPrimaryParticleGenerator();
  NuLatRunAction* NuLatRunAction001 = new NuLatRunAction();
  NuLatEventAction* NuLatEventAction001 = new NuLatEventAction(localNOfVoxelsInX, localNOfVoxelsInY, localNOfVoxelsInZ);
  
  SetUserAction(NuLatPrimaryParticleGenerator001);
  SetUserAction(NuLatRunAction001);
  SetUserAction(NuLatEventAction001);
  
  NuLatEventAction001->NuLatRunActionLocal=NuLatRunAction001;   //CHECK: UNKNOWN
}  

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
