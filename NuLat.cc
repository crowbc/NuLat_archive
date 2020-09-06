/*******************************************/
/*            C++ header files             */
/*******************************************/
#include <time.h>
#include <string.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>

#include <iostream>
#include <fstream>

/*******************************************/
/*      Geant4 defined header files        */
/*******************************************/
#include "Randomize.hh"

#ifdef G4MULTITHREADED // Set RunManager according to Multithread status
#include "G4MTRunManager.hh"
#else
#include "G4RunManager.hh"
#endif

#include "G4UImanager.hh"
#include "G4ios.hh"

//Physics Lists
#include "G4HadronicProcessStore.hh"
#include "QGSP_BERT_HP.hh"
#include "G4StepLimiterPhysics.hh"
#include "G4OpticalPhysics.hh"

#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"




/*******************************************/
/*      User/NuLat simulation developer    */
/*          defined header files           */
/*******************************************/
#include "NuLatDetectorConstruction.hh"
#include "NuLatActionInitialization.hh"

using namespace std;


/*******************************************/
/*    int main( int argc, char** argv )    */
/*    This is where the simulation begins.  The random number generator is initialized                 */
/*******************************************/
int main( int argc, char** argv )
{
 G4UIExecutive* ui = 0;
  if ( argc == 1 ) {
    ui = new G4UIExecutive(argc, argv);}

//Simulation parameters-- TODO produce input file
  // Number of voxels in x y and z
  G4int numOfVoxelsInX = 5;
  G4int numOfVoxelsInY = 5;
  G4int numOfVoxelsInZ = 5;
  
  // voxel dimmensions x y and z 
//  G4double voxelXDimension = 2.495*2.54*cm;
//  G4double voxelYDimension = 2.495*2.54*cm;
//  G4double voxelZDimension = 2.495*2.54*cm;
  
  G4double voxelXDimension = 2.495*2.54*cm;
  G4double voxelYDimension = 2.495*2.54*cm;
  G4double voxelZDimension = 2.495*2.54*cm;
  
  // voxel spacing x y and z
  G4double voxelSpacingXDimension = 0.005*2.54*cm;;
  G4double voxelSpacingYDimension = 0.005*2.54*cm;;
  G4double voxelSpacingZDimension = 0.005*2.54*cm;;

 

G4int myseed = 0;//time( NULL );
G4Random::setTheEngine(new CLHEP::RanluxEngine);
G4Random::setTheSeed(myseed);


  /****************************************************/
  /*                                                  */
  /* Construct the default run manager                */
  /* single or multi threaded                         */
  /*                                                  */
  /****************************************************/
#ifdef G4MULTITHREADED

  G4cout << "Multithread is currently disabled." << G4endl;
  G4RunManager* runManager = new G4RunManager;
  
  
  /* Multithread is currently disabled.
  G4MTRunManager* runManager = new G4MTRunManager;
  runManager->SetNumberOfThreads(G4Threading::G4GetNumberOfCores());
  */
  
#else
  G4RunManager* runManager = new G4RunManager;
#endif


  /****************************************************/
  /* Create the detector and point run manager to it  */
  /* To access the code responsible for this geometry */ 
  /* view the following files:                        */
  /* src/NuLatDetectorConstruction.cc                 */
  /* include/NuLatDetectorConstruction.hh             */
  /****************************************************/

  NuLatDetectorConstruction* NuLatDetector = new NuLatDetectorConstruction(
                                                 numOfVoxelsInX, numOfVoxelsInY, numOfVoxelsInZ,
                                                 voxelXDimension, voxelYDimension, voxelZDimension,
                                                 voxelSpacingXDimension, voxelSpacingYDimension, voxelSpacingZDimension);
  runManager->SetUserInitialization(NuLatDetector);


  /****************************************************/
  /* Define physics to use in the detector and point  */
  /* run manager to it                                */
  /* currently using predefined physics lists         */
  /****************************************************/

  G4VModularPhysicsList * physicsList = new QGSP_BERT_HP(0);
  physicsList->SetVerboseLevel(0);
  G4HadronicProcessStore::Instance()->SetVerbose(0);
  physicsList->RegisterPhysics(new G4OpticalPhysics(0));
  runManager->SetUserInitialization(physicsList);
  

  /****************************************************/
  /* User action initialization                       */
  /****************************************************/

  runManager->SetUserInitialization(new NuLatActionInitialization(numOfVoxelsInX, numOfVoxelsInY, numOfVoxelsInZ));


  /*****************************************************/
  /* If Visualization support exists Create visManager */
  /*****************************************************/

    G4VisManager* visManager = new G4VisExecutive;
    visManager->Initialize();




  /*****************************************************/
  /* Get the pointer to the User Interface manager     */
  /*****************************************************/
  G4UImanager * UImanager = G4UImanager::GetUIpointer();  



  if (argc>1)   // batch mode  
  {
    /***********************************************************/
    /* Run in batch mode by having the user interface manager  */
    /* executing the macro file passed via the command line    */
    /***********************************************************/

    UImanager->ApplyCommand((G4String)"/control/execute "+(G4String)argv[1]);
  }
  else         // interactive mode : define UI session
  {
//    runManager->Initialize();



    UImanager->ApplyCommand("/control/execute Macros/init_vis.mac");
    ui->SessionStart();
    delete ui;
  }


  delete visManager;
 

  delete runManager;

  return 0;
}


