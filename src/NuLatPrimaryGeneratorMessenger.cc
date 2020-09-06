//  NuLatPrimaryGeneratorMessenger.cc 
 
#include "NuLatPrimaryGeneratorMessenger.hh"
#include "NuLatPrimaryParticleGenerator.hh"

#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4UIcmdWithoutParameter.hh"

  NuLatPrimaryGeneratorMessenger::NuLatPrimaryGeneratorMessenger(
	NuLatPrimaryParticleGenerator* NuLatGun):NuLatGenerator(NuLatGun){

	gunDir = new G4UIdirectory("/NuLat/gun/");
	gunDir->SetGuidance("PrimaryGenerator control");

	EventTypeCmd = new G4UIcmdWithAString("/NuLat/gun/eventType",this);
	EventTypeCmd->SetGuidance("Controls the inital event type.");
	EventTypeCmd->SetGuidance(" Choice: electronTest positronTest IBDTest");
	EventTypeCmd->SetParameterName("choice",true);
	EventTypeCmd->SetDefaultValue("electronTest");
	EventTypeCmd->SetCandidates("electronTest positronTest IBDTest");

	MessInput = new std::string;

}


NuLatPrimaryGeneratorMessenger::~NuLatPrimaryGeneratorMessenger(){
	delete gunDir;
	delete EventTypeCmd;
	delete InputCmd;
	delete UpdateCmd;
}


void NuLatPrimaryGeneratorMessenger::SetNewValue(G4UIcommand* command, G4String newValue){ 
	if( command == EventTypeCmd) {
		NuLatGenerator->SetEventTypeFlag(newValue);
	}
}


