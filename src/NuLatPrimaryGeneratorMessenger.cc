//PRIMARY GENREATOR MESSENGER FILE
//Not fully understood and may be obsolete at this point

//  NuLatPrimaryGeneratorMessenger.cc 
 
#include "NuLatPrimaryGeneratorMessenger.hh"
#include "NuLatPrimaryParticleGenerator.hh"

#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4UIcmdWithoutParameter.hh"
#include "G4UIcmdWith3Vector.hh"

//  NuLatPrimaryGeneratorMessenger::NuLatPrimaryGeneratorMessenger(
//	NuLatPrimaryParticleGenerator* NuLatGun):NuLatGenerator(NuLatGun){

//	gunDir = new G4UIdirectory("/NuLat/gun/");
//	gunDir->SetGuidance("PrimaryGenerator control");

//	EventTypeCmd = new G4UIcmdWithAString("/NuLat/gun/eventType",this);
//	EventTypeCmd->SetGuidance("Controls the inital event type.");
//	EventTypeCmd->SetGuidance(" Choice: electronTest positronTest IBDTest");
//	EventTypeCmd->SetParameterName("choice",true);
//	EventTypeCmd->SetDefaultValue("electronTest");
//	EventTypeCmd->SetCandidates("electronTest positronTest IBDTest");

//	MessInput = new std::string;

//}

 NuLatPrimaryGeneratorMessenger::NuLatPrimaryGeneratorMessenger(
	NuLatPrimaryParticleGenerator* NuLatGun):NuLatGenerator(NuLatGun){
	
	mydetDir = new G4UIdirectory("/NuLat/gun/");
	mydetDir->SetGuidance("Set Up Commands");
	
	InitialVoxelCMD = new G4UIcmdWith3Vector("/NuLat/gun/initialVoxel", this);
	InitialVoxelCMD->SetGuidance("Controls wich voxel primary particles spawn from");
	InitialVoxelCMD->SetGuidance("Input three intergers for X, Y, and Z");
	InitialVoxelCMD->SetParameterName("X","Y","Z",true,false);
//	InitialVoxelCMD->SetRange("0 < X < 6 || 0 < Y < 6 || 0 < Z < 6");
	InitialVoxelCMD->SetRange("-40 < X < 40 || -40 < Y < 40 || -40 < Z < 40");
	InitialVoxelCMD->SetDefaultValue(G4ThreeVector (3, 3, 3));
	
	
	

}


NuLatPrimaryGeneratorMessenger::~NuLatPrimaryGeneratorMessenger(){
	//delete gunDir;
	//delete EventTypeCmd;
	//delete InputCmd;
	//delete UpdateCmd;
	
	delete mydetDir;
	delete InitialVoxelCMD;
}


void NuLatPrimaryGeneratorMessenger::SetNewValue(G4UIcommand* command, G4String newValue){ 
//	if( command == EventTypeCmd) {
//		NuLatGenerator->SetEventTypeFlag(newValue);
//	}
	
	if( command ==InitialVoxelCMD) {
		NuLatGenerator->SetPrimaryEventVoxel(InitialVoxelCMD->GetNew3VectorValue(newValue));
	}
	
	
}


