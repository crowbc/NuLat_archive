//DETECTOR CONSTRUCTION FILE
//File for building the detector geometry
//(highly related files: Materials.hh, DetectorConstruction.hh, VoxelParameterisation.cc/.hh, LightGuideParameterization.cc/.hh)



//Header files we made
#include "NuLatDetectorConstruction.hh"
#include "NuLatVoxelParameterisation.hh"
#include "NuLatLightGuideParameterisation.hh"

//Geant4 header files for making shapes
#include "G4VUserDetectorConstruction.hh"
#include "G4Box.hh"
#include "G4Trd.hh"
#include "G4Cons.hh"
#include "G4Tubs.hh"
#include "G4Sphere.hh"

//Geant4 header file for cutting chunks out of a shape
#include "G4SubtractionSolid.hh"

#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SDManager.hh"
#include "G4IntersectionSolid.hh"
#include "NuLatVoxelSensitiveDetector.hh"
#include "NuLatPhotoCathodeSensitiveDetector.hh"

//Header file to create many copied volumes
#include "G4PVParameterised.hh"

//Header file for creating region that collects data
#include "G4VSensitiveDetector.hh"

//Header files for setting attributes in visualization
#include "G4VisAttributes.hh"
#include "G4Colour.hh"

//New Materail Properties (added 2/7/22)
#include "G4LogicalBorderSurface.hh"
#include "G4LogicalSkinSurface.hh"
#include "G4OpticalSurface.hh"



using namespace std;                                            //Using standard C++ namespace so things like endl and cout are understood

G4VPhysicalVolume* NuLatDetectorConstruction::Construct()       //Enacts the code that will construct the detector
{
  NuLatMaterials = new Materials();                             //Sets the materials

  buildExperimentalHall();                                      //Builds the detector

  return physWorld;                                             //Returns the built detector at the end of function
}



//Defining  Experimental Hall (Volume that everything resides within)
void NuLatDetectorConstruction::buildExperimentalHall()
{
  G4bool checkOverlaps = true;                                                           //sets variable checkOverlaps to true; used in placement functions
  G4int copyNumber;                                                                      //creates variable copyNumber; used to make copies of voxels and lightguides

//Places the world volume with everything inside it
  physWorld = new G4PVPlacement(0,                                                       //no rotation
                                G4ThreeVector( 0.0, 0.0, 0.0 ),                          //at (0,0,0)
                                WorldVolume(),                                           //its logical volume
                                "AirWorld",                                              //its name
                                0,                                                       //its mother  volume
                                false,                                                   //no boolean operation
                                copyNumber=0,                                            //copy number
                                checkOverlaps );                                         //overlaps checking

}

/*Create a world logical volume*/
G4LogicalVolume* NuLatDetectorConstruction::WorldVolume()
{
  G4bool checkOverlaps = true;
  photoCathodeIDNum=0;


//Total number of cubes (voxels)
  G4double totalNumberOfVoxels = nOfVoxelsInX*nOfVoxelsInY*nOfVoxelsInZ;

//Dimensions of Raghaven Optical Lattice of cubes (voxels)
  G4double NuLatVoxelatedCalorimeterBoxXDimension =
    nOfVoxelsInX * (voxelXDimension+voxelSpacingXDimension)+voxelSpacingXDimension;

  G4double NuLatVoxelatedCalorimeterBoxYDimension =
    nOfVoxelsInY * (voxelYDimension+voxelSpacingYDimension)+voxelSpacingYDimension;

  G4double NuLatVoxelatedCalorimeterBoxZDimension =
    nOfVoxelsInZ * (voxelZDimension+voxelSpacingZDimension)+voxelSpacingZDimension;

//WORLD
//Creating shape for world, going from -VoxelatedCalorimeterBoxDimension to +VoxelatedCalorimeterBoxDimension in each direction  //IMPROVE
  G4Box* solidWorld = new G4Box( "World",
                  NuLatVoxelatedCalorimeterBoxXDimension+lightGuideWithPMTLength*2, //Currently larger than it needs to be as it was getting overlap with lighguide boxes
                  NuLatVoxelatedCalorimeterBoxYDimension+lightGuideWithPMTLength*2,
                  NuLatVoxelatedCalorimeterBoxZDimension+lightGuideWithPMTLength*2);
              
//Creating logical volume world, giving it a material                
  G4LogicalVolume* logicWorld = new G4LogicalVolume( solidWorld,               //Its solid
                                                     NuLatMaterials->air,      //Its material: Air
                                                     "World");                 //Its name
                            
//Style Dictates this is used elsewhere and not here in this program                            
//Creating physical volume world, placing the logical volume in a location                                                    
//  G4VPhysicalVolume* physWorld = new G4PVPlacement(0,                         //no rotation
//                      G4ThreeVector(),                                        //at (0,0,0)
//                      logicWorld,                                             //its logical volume
//                      "World",                                                //its name
//                      0,                                                      //its mother  volume
//                      false,                                                  //no boolean operation
//                      0,                                                      //copy number
//                      checkOverlaps);                                         //overlaps checking

//VOXELATED CALORIMETER
//Creating NuLat Voxelated Calorimeter shape
    G4VSolid* NuLatVoxelatedCalorimeterSolid
      = new G4Box("NuLatVoxelatedCalorimeterBox",
                  NuLatVoxelatedCalorimeterBoxXDimension/2,
                  NuLatVoxelatedCalorimeterBoxYDimension/2,
                  NuLatVoxelatedCalorimeterBoxZDimension/2);

//Creating NuLat Voxelated Calorimeter logical, giving it material: air
    G4LogicalVolume* NuLatVoxelatedCalorimeterLogical
      = new G4LogicalVolume(NuLatVoxelatedCalorimeterSolid,
                            NuLatMaterials->air,
                            "NuLatVoxelatedCalorimeterLogical");

//Placing NuLat Voxelated Calorimeter logical into world                       
    new G4PVPlacement(0,                                                      //no rotation
                      G4ThreeVector(0.,0.,0.),                                //at (0,0,0)
                      NuLatVoxelatedCalorimeterLogical,                       //its logical volume
                      "NuLatVoxelatedCalorimeterPhysical",                    //its name
                      logicWorld,                                             //its mother volume
                      false,                                                  //no boolean operation
                      0,                                                      //copy number
                      checkOverlaps);                                         //overlaps checking
    
//VOXEL
//Creating Voxel Shape
    G4VSolid* VoxelSolid
      = new G4Box("Voxel",voxelXDimension/2, voxelYDimension/2, voxelZDimension/2);

//Creating Voxel logical, giving it material: 0.5% Lithiated PVT
    VoxelLogical
      = new G4LogicalVolume(VoxelSolid,NuLatMaterials->Li6PVT_5TenthsOfAPercent,"VoxelLogical");
      
//Placing many repeated volumes, following unknown pattern?  
//References NuLatVoxelParameterization in src
    G4VPVParameterisation* voxelParam =
      new NuLatVoxelParameterisation(nOfVoxelsInX,                            //number of voxels (cubes) in x-direction
                                     nOfVoxelsInY,                            //number of voxels in y-direction
                                     nOfVoxelsInZ,                            //number of voxels in z-direction
                                     voxelXDimension/2,
                                     voxelYDimension/2,
                                     voxelZDimension/2,
                                     voxelSpacingXDimension/2,
                                     voxelSpacingYDimension/2, 
                                     voxelSpacingZDimension/2);
//    G4VPhysicalVolume* physVoxel =     
      new G4PVParameterised("voxelPhysical",                                  //its name
                            VoxelLogical,                                     //its logical volume
                            NuLatVoxelatedCalorimeterLogical,                 //its mother volume
                            kXAxis,                                           //are places along this axis
                            totalNumberOfVoxels,                              //its number of copies
                            voxelParam,                                       //its paramaterization
                            checkOverlaps);                                  //checking overlaps);



//NuLat Light Guides

////Defining LightGuideAndPMT logical volume (assuming based on lightguideparamaterization file)
//    LightGuideAndPMTLog = LightGuideAndPMT((voxelXDimension+voxelSpacingXDimension-0.127*cm), 4.6*cm,
//                                           (voxelYDimension+voxelSpacingYDimension-0.127*cm), 4.6*cm,
//                                            LightGuideTaperLength,
//                                            true);
//    LightGuideAndPMTLog_noPMTs = LightGuideAndPMT((voxelXDimension+voxelSpacingXDimension-0.127*cm), 4.6*cm,
//                                           (voxelYDimension+voxelSpacingYDimension-0.127*cm), 4.6*cm,
//                                            LightGuideTaperLength,
//                                            false);
//Defining LightGuideAndPMT logical volume (assuming based on lightguideparamaterization file)
    LightGuideAndPMTLog = LightGuideAndPMT((voxelXDimension+voxelSpacingXDimension-0.127*cm), 4.6*cm,			//EDIT TO add metal dividers
                                           (voxelYDimension+voxelSpacingYDimension-0.127*cm), 4.6*cm,
                                            LightGuideTaperLength,
                                            true);
    LightGuideAndPMTLog_noPMTs = LightGuideAndPMT((voxelXDimension+voxelSpacingXDimension-0.127*cm), 4.6*cm,
                                           (voxelYDimension+voxelSpacingYDimension-0.127*cm), 4.6*cm,
                                            LightGuideTaperLength,
                                            false);
    
//NuLat LightGuide z+ Bank (Zone on the Z+ side of Cube)
//Creating Lightguide Bank Shape
    G4VSolid* NuLatLightGuideZBankPlusSolid
      = new G4Box("NuLatLightGuideZBankPlusBox",
                  NuLatVoxelatedCalorimeterBoxXDimension/2,
                  NuLatVoxelatedCalorimeterBoxYDimension/2,
                  (lightGuideWithPMTLength)/2);

//Creating LightGuide z+ Logical Volume, giving it material: Air    
    NuLatLightGuideZBankPlusLogical
      = new G4LogicalVolume(NuLatLightGuideZBankPlusSolid,
                            NuLatMaterials->air,
                            "NuLatLightGuideZBankPlusLogical");

//Placing Lightguide z+ Logical Volume into world                            
    new G4PVPlacement(0,G4ThreeVector(0.,0.,NuLatVoxelatedCalorimeterBoxZDimension/2+(lightGuideWithPMTLength)/2 +.010*2.54*cm),NuLatLightGuideZBankPlusLogical,
                      "NuLatLightGuideZBankPlusPhysical",logicWorld,
                      false,0,checkOverlaps);

//Placing LightGuide and PMT setup into Z+ Bank
//    G4VPVParameterisation* lightGuideParamZBankPlus =
//      new NuLatLightGuideParameterisation(nOfVoxelsInX, nOfVoxelsInY, nOfVoxelsInZ,
//        voxelXDimension/2, voxelYDimension/2, voxelZDimension/2,
//        voxelSpacingXDimension/2, voxelSpacingYDimension/2, voxelSpacingZDimension/2, 0, 0, 1);
//      
    G4VPVParameterisation* lightGuideParamZBankPlus =
      new NuLatLightGuideParameterisation(nOfVoxelsInX, nOfVoxelsInY, nOfVoxelsInZ,					//EDIT TO add metal dividers
        voxelXDimension/2+voxelSpacingXDimension/2, voxelYDimension/2+voxelSpacingYDimension/2, voxelZDimension/2+voxelSpacingZDimension/2,
        0/2, 0/2, 0/2, 0, 0, 1);
      
    new G4PVParameterised("LightGuidePhysicalZPlus",LightGuideAndPMTLog,NuLatLightGuideZBankPlusLogical,
                          kZAxis,nOfVoxelsInX*nOfVoxelsInY,lightGuideParamZBankPlus);



    // NuLat LightGuide z- Bank
    G4VSolid* NuLatLightGuideZBankMinusSolid
      = new G4Box("NuLatLightGuideZBankMinusBox",
                  NuLatVoxelatedCalorimeterBoxXDimension/2,
                  NuLatVoxelatedCalorimeterBoxYDimension/2,
                  (lightGuideWithPMTLength)/2);
      
    NuLatLightGuideZBankMinusLogical
      = new G4LogicalVolume(NuLatLightGuideZBankMinusSolid,
                            NuLatMaterials->air,
                            "NuLatLightGuideZBankMinusLogical");
                            
    new G4PVPlacement(0,G4ThreeVector(0.,0.,-1*(NuLatVoxelatedCalorimeterBoxZDimension/2+(lightGuideWithPMTLength)/2 +.010*2.54*cm)),NuLatLightGuideZBankMinusLogical,
                      "NuLatLightGuideZBankMinusPhysical",logicWorld,
                      false,0,checkOverlaps);



//  G4VPVParameterisation* lightGuideParamZBankMinus =
//      new NuLatLightGuideParameterisation(nOfVoxelsInX, nOfVoxelsInY, nOfVoxelsInZ,
//        voxelXDimension/2, voxelYDimension/2, voxelZDimension/2,
//        voxelSpacingXDimension/2, voxelSpacingYDimension/2, voxelSpacingZDimension/2, 0, 0, -1);
  G4VPVParameterisation* lightGuideParamZBankMinus =									//EDIT TO add metal dividers
      new NuLatLightGuideParameterisation(nOfVoxelsInX, nOfVoxelsInY, nOfVoxelsInZ,
        voxelXDimension/2+voxelSpacingXDimension/2, voxelYDimension/2+voxelSpacingYDimension/2, voxelZDimension/2+voxelSpacingZDimension/2,
        0/2, 0/2, 0/2, 0, 0, -1);
      
    new G4PVParameterised("LightGuidePhysicalZMinus",LightGuideAndPMTLog_noPMTs,NuLatLightGuideZBankMinusLogical,
                          kZAxis,nOfVoxelsInX*nOfVoxelsInY,lightGuideParamZBankMinus);
                          
                          
                          
                          
                          
                          

    // NuLat LightGuide y+ Bank
    G4VSolid* NuLatLightGuideYBankPlusSolid 
      = new G4Box("NuLatLightGuideYBankPlusBox",
                  NuLatVoxelatedCalorimeterBoxXDimension/2,
                  (lightGuideWithPMTLength)/2,
                  NuLatVoxelatedCalorimeterBoxZDimension/2);
      
    NuLatLightGuideYBankPlusLogical
      = new G4LogicalVolume(NuLatLightGuideYBankPlusSolid,
                            NuLatMaterials->air,
                            "NuLatLightGuideYBankPlusLogical");
                            
    new G4PVPlacement(0,G4ThreeVector(0.,NuLatVoxelatedCalorimeterBoxYDimension/2+(lightGuideWithPMTLength)/2 +.010*2.54*cm,0.),NuLatLightGuideYBankPlusLogical,
                      "NuLatLightGuideYBankPlusPhysical",logicWorld,
                      false,0,checkOverlaps);

// EDIT FOR HALF INSTRUMENTED

//  G4VPVParameterisation* lightGuideParamYBankPlus =
//      new NuLatLightGuideParameterisation(nOfVoxelsInX, nOfVoxelsInY, nOfVoxelsInZ,
//        voxelXDimension/2, voxelYDimension/2, voxelZDimension/2,
//        voxelSpacingXDimension/2, voxelSpacingYDimension/2, voxelSpacingZDimension/2, 0, 1, 0);
//      
  G4VPVParameterisation* lightGuideParamYBankPlus =
      new NuLatLightGuideParameterisation(nOfVoxelsInX, nOfVoxelsInY, nOfVoxelsInZ,
        voxelXDimension/2+voxelSpacingXDimension/2, voxelYDimension/2+voxelSpacingYDimension/2, voxelZDimension/2+voxelSpacingZDimension/2,
        0/2, 0/2, 0/2, 0, 1, 0);
      
    new G4PVParameterised("LightGuidePhysicalZPlus",LightGuideAndPMTLog_noPMTs,NuLatLightGuideYBankPlusLogical,
                          kZAxis,nOfVoxelsInX*nOfVoxelsInZ,lightGuideParamYBankPlus);


    // NuLat LightGuide y- Bank
    G4VSolid* NuLatLightGuideYBankMinusSolid 
      = new G4Box("NuLatLightGuideYBankPlusBox",
                  NuLatVoxelatedCalorimeterBoxXDimension/2,
                  (lightGuideWithPMTLength)/2,
                  NuLatVoxelatedCalorimeterBoxZDimension/2);
      
    NuLatLightGuideYBankMinusLogical
      = new G4LogicalVolume(NuLatLightGuideYBankMinusSolid,
                            NuLatMaterials->air,
                            "NuLatLightGuideYBankMinusLogical");

    new G4PVPlacement(0,G4ThreeVector(0.,-1*(NuLatVoxelatedCalorimeterBoxYDimension/2+(lightGuideWithPMTLength)/2 +.010*2.54*cm),0.),NuLatLightGuideYBankMinusLogical,
                      "NuLatLightGuideYBankMinusPhysical",logicWorld,
                      false,0,checkOverlaps);


//  G4VPVParameterisation* lightGuideParamYBankMinus =
//      new NuLatLightGuideParameterisation(nOfVoxelsInX, nOfVoxelsInY, nOfVoxelsInZ,
//        voxelXDimension/2, voxelYDimension/2, voxelZDimension/2,
//        voxelSpacingXDimension/2, voxelSpacingYDimension/2, voxelSpacingZDimension/2, 0, -1, 0);
//      
  G4VPVParameterisation* lightGuideParamYBankMinus =
      new NuLatLightGuideParameterisation(nOfVoxelsInX, nOfVoxelsInY, nOfVoxelsInZ,
        voxelXDimension/2+voxelSpacingXDimension/2, voxelYDimension/2+voxelSpacingYDimension/2, voxelZDimension/2+voxelSpacingZDimension/2,
        0/2, 0/2, 0/2, 0, -1, 0);
      
    new G4PVParameterised("LightGuidePhysicalZMinus",LightGuideAndPMTLog,NuLatLightGuideYBankMinusLogical,
                          kZAxis,nOfVoxelsInX*nOfVoxelsInZ,lightGuideParamYBankMinus);
                          
                          
                          
                          
                          
                          
                          
                          
                          
                          
                          
    // NuLat LightGuide x+ Bank
    G4VSolid* NuLatLightGuideXBankPlusSolid 
      = new G4Box("NuLatLightGuideXBankPlusBox",
                  (lightGuideWithPMTLength)/2,
                  NuLatVoxelatedCalorimeterBoxYDimension/2,
                  NuLatVoxelatedCalorimeterBoxZDimension/2);
      
    NuLatLightGuideXBankPlusLogical
      = new G4LogicalVolume(NuLatLightGuideXBankPlusSolid,
                            NuLatMaterials->air,
                            "NuLatLightGuideXBankPlusLogical");
                            
    new G4PVPlacement(0,G4ThreeVector(NuLatVoxelatedCalorimeterBoxXDimension/2+(lightGuideWithPMTLength)/2 +.010*2.54*cm,0.,0.),NuLatLightGuideXBankPlusLogical,
                      "NuLatLightGuideXBankPlusPhysical",logicWorld,
                      false,0,checkOverlaps);


// EDIT FOR HALF INSTRUMENTED

//  G4VPVParameterisation* lightGuideParamXBankPlus =
//      new NuLatLightGuideParameterisation(nOfVoxelsInX, nOfVoxelsInY, nOfVoxelsInZ,
//        voxelXDimension/2, voxelYDimension/2, voxelZDimension/2,
//        voxelSpacingXDimension/2, voxelSpacingYDimension/2, voxelSpacingZDimension/2, 1, 0, 0);
//      
  G4VPVParameterisation* lightGuideParamXBankPlus =
      new NuLatLightGuideParameterisation(nOfVoxelsInX, nOfVoxelsInY, nOfVoxelsInZ,
        voxelXDimension/2+voxelSpacingXDimension/2, voxelYDimension/2+voxelSpacingYDimension/2, voxelZDimension/2+voxelSpacingZDimension/2,
        0/2, 0/2, 0/2, 1, 0, 0);
      
    new G4PVParameterised("LightGuidePhysicalZPlus",LightGuideAndPMTLog_noPMTs,NuLatLightGuideXBankPlusLogical,
                          kZAxis,nOfVoxelsInZ*nOfVoxelsInY,lightGuideParamXBankPlus);


    // NuLat LightGuide x- Bank
    G4VSolid* NuLatLightGuideXBankMinusSolid 
      = new G4Box("NuLatLightGuideXBankPlusBox",
                  (lightGuideWithPMTLength)/2,
                  NuLatVoxelatedCalorimeterBoxYDimension/2,
                  NuLatVoxelatedCalorimeterBoxZDimension/2);
      
    NuLatLightGuideXBankMinusLogical
      = new G4LogicalVolume(NuLatLightGuideXBankMinusSolid,
                            NuLatMaterials->air,
                            "NuLatLightGuideXBankMinusLogical");
                            
    new G4PVPlacement(0,G4ThreeVector(-1*(NuLatVoxelatedCalorimeterBoxXDimension/2+(lightGuideWithPMTLength)/2 +.010*2.54*cm),0.,0.),NuLatLightGuideXBankMinusLogical,
                      "NuLatLightGuideXBankMinusPhysical",logicWorld,
                      false,0,checkOverlaps);


//  G4VPVParameterisation* lightGuideParamXBankMinus =
//      new NuLatLightGuideParameterisation(nOfVoxelsInX, nOfVoxelsInY, nOfVoxelsInZ,
//        voxelXDimension/2, voxelYDimension/2, voxelZDimension/2,
//        voxelSpacingXDimension/2, voxelSpacingYDimension/2, voxelSpacingZDimension/2, -1, 0, 0);
//      
  G4VPVParameterisation* lightGuideParamXBankMinus =
      new NuLatLightGuideParameterisation(nOfVoxelsInX, nOfVoxelsInY, nOfVoxelsInZ,
        voxelXDimension/2+voxelSpacingXDimension/2, voxelYDimension/2+voxelSpacingYDimension/2, voxelZDimension/2+voxelSpacingZDimension/2,
        0/2, 0/2, 0/2, -1, 0, 0);
      
    new G4PVParameterised("LightGuidePhysicalZMinus",LightGuideAndPMTLog,NuLatLightGuideXBankMinusLogical,
                          kZAxis,nOfVoxelsInZ*nOfVoxelsInY,lightGuideParamXBankMinus);






//Setting visualization attributes

//Making Voxels Yellowish
    G4VisAttributes* visAttributes = new G4VisAttributes(G4Colour(0.9,0.9,0.0));
    VoxelLogical->SetVisAttributes(visAttributes);
    NuLatVisAttributes.push_back(visAttributes);
  
//Making VoxelatedCalorimeter Redish
    visAttributes = new G4VisAttributes(G4Colour(0.9,0.0,0.0));
    NuLatVoxelatedCalorimeterLogical->SetVisAttributes(visAttributes);
    NuLatVisAttributes.push_back(visAttributes);

//Making the World Volume Invisible
  visAttributes = new G4VisAttributes(false);
    logicWorld->SetVisAttributes(visAttributes);
    NuLatVisAttributes.push_back(visAttributes);


  return(logicWorld);

}




//Creating PMT
G4LogicalVolume* NuLatDetectorConstruction::HamamatsuR10533()
{


  G4bool checkOverlaps = true;
	//	The PMTs are semi spherical quartz with vacuum inside, 
	//	with a cylindrical mu-metal shield
	
//Defing Material Sizes	
        G4double pmtRadius=23*mm;
        G4double pmtGlassThickness = 4*mm;
        G4double pmtGlassMinimumThickness = 0.8*mm;
        G4double pmtPhotoCathodeRadius=529.25*mm;
        G4double pmtPhotoCathodeThickness = 1*mm;

        G4double muMetalRadius = 3.05*cm;
        G4double muMetalHeight = 19.863*cm;
        G4double muMetalThickness = 0.05*cm;

//Defining MuMetal cylinder
	G4Tubs* muMetal_solid = new G4Tubs("muMetal_solid",                        //its name
	                                    muMetalRadius-muMetalThickness,        //its inner radius
	                                    muMetalRadius,                         //its outer radius
	                                    muMetalHeight/2.,                      //its height
	                                    0., 360*deg);                          //its segment angles (from 0 to 360 degrees here)

//Creating MuMetal Logical Volume, giving it material: muMetal                                    
       muMetal_Log = new G4LogicalVolume(muMetal_solid,
                                         NuLatMaterials->muMetal,
                                         "muMetal_Log");


//Defining PMT lens cylinder
	G4Tubs* pmtGlass_solid = new G4Tubs("pmtGlass_solid",                      //its name
	                                     0,                                    //its inner radius (0 because it is solid
	                                     pmtRadius,                            //its outer radius
	                                     pmtGlassThickness/2.,                 //its height (thickness)
	                                     0., 360*deg);                         //its segment angles 

//Defining PMT Convex Surface	                                     
       G4Sphere* pmtConvexSurface_solid = new G4Sphere("pmtConvexSurface_solid",  //its name
                                                        0.,                       //its inner radius
                                                        pmtPhotoCathodeRadius,    //its outer radius
                                                        0.*deg, 360.*deg,         //its segment angles phi
                                                        0.*deg, 360.*deg);        //its segment angles theta


//Subtracting a chunk out of pmtGlass_solid to produce a concave lense                                            
  G4SubtractionSolid* pmtLens_solid = new G4SubtractionSolid("pmtLens_solid",          //its name (name of solid after subtraction)
                                                             pmtGlass_solid,           //starting solid
                                                             pmtConvexSurface_solid,   //solid to be subtracted out
                                                             0,                        //rotations (zero in this case)
                                                             G4ThreeVector(0, 0, pmtPhotoCathodeRadius-pmtGlassThickness/2+pmtGlassMinimumThickness));  //translation before subtraction

//Creating pmtLens Logical Volume, giving it material: Borosilicate Glass	                                                
  pmtLens_Log = new G4LogicalVolume(pmtLens_solid,
                                              NuLatMaterials->borosilicateGlass,
                                              "pmtLens_Log");


//Defining photocathode
  G4Sphere* pmtPhotoCathode_solid = new G4Sphere("pmtPhotoCathode_solid",
                                                 pmtPhotoCathodeRadius-pmtPhotoCathodeThickness,
                                                 pmtPhotoCathodeRadius,
                                                 0.*deg, 360.*deg,
                                                 177.51*deg, 180*deg);                                 

//Creating PMT PhotoCathode, giving it material: BeCu
  pmtPhotoCathode_Log = new G4LogicalVolume(pmtPhotoCathode_solid,
                                            NuLatMaterials->BeCuPhotoCathode,
                                            "pmtPhotoCathode_Log");




//Assembling Full PMT

//Defining shape it will be build in
  G4Tubs* pmt_solid = new G4Tubs("pmt_solid",
	                                    0,
	                                    muMetalRadius, 
	                                    muMetalHeight/2., 
	                                    0., 
	                                    360*deg);

//Creating Logical Volume for the shape, giving it material: vacuum
  G4LogicalVolume * pmt_Log
      = new G4LogicalVolume(pmt_solid,
                            NuLatMaterials->vacuum,
                            "pmt_log");

//Placing muMetal shell in PMT
  new G4PVPlacement(0,G4ThreeVector(0.,0.,0),muMetal_Log,
                      "muMetal",pmt_Log,
                      false,0,checkOverlaps);

//Placing Lens in PMT
  new G4PVPlacement(0,G4ThreeVector(0.,0.,-1*(muMetalHeight/2.- pmtGlassThickness/2)),pmtLens_Log,
                      "pmtLens",pmt_Log,
                      false,0,checkOverlaps);

//Placing PhotoCathode in PMT
  new G4PVPlacement(0,
                    G4ThreeVector(0.,0.,pmtPhotoCathodeRadius-muMetalHeight/2+pmtGlassMinimumThickness),//-1*(.- pmtGlassThickness/2)-)
                    pmtPhotoCathode_Log,
                      "pmtPhotoCathode",pmt_Log,
                      false,0,checkOverlaps);


//Setting Visualization Attributes

//Making MuMetal Green and partly transparent
  G4VisAttributes* visAttributes = new G4VisAttributes(G4Colour(0,255,0,.3));
  visAttributes->SetForceWireframe(true);
//  visAttributes->SetForceSolid(true);
  muMetal_Log->SetVisAttributes(visAttributes);
  NuLatVisAttributes.push_back(visAttributes);

//Making Lens Red and partly transparent  
  visAttributes = new G4VisAttributes(G4Colour(255,0,0,.3));
//  visAttributes->SetForceWireframe(true);
  visAttributes->SetForceSolid(true);
  pmtLens_Log->SetVisAttributes(visAttributes);
  NuLatVisAttributes.push_back(visAttributes);
  
//  visAttributes = new G4VisAttributes(G4Colour(0,0,255,.3));
//  visAttributes->SetForceWireframe(true);
//  visAttributes->SetForceSolid(true);
//  pmtFace_Log->SetVisAttributes(visAttributes);
//  NuLatVisAttributes.push_back(visAttributes);


//Making Photocathode Green and partly transparent  
  visAttributes = new G4VisAttributes(G4Colour(0,255,0,.3));
  visAttributes->SetForceSolid(true);
  pmtPhotoCathode_Log->SetVisAttributes(visAttributes);
  NuLatVisAttributes.push_back(visAttributes);

  
  
  
  return (pmt_Log);
}



//Creating Lightguide
G4LogicalVolume* NuLatDetectorConstruction::LightGuideAndPMT(G4double dx1, G4double dx2, G4double dy1, G4double dy2, G4double dz, G4bool instrumented)
{
//Defining Box that lightguide will be constructed in
    G4VSolid* lightGuideBox 
      = new G4Box("lightGuideBox",
                  dx1/2+0.0635*cm, 		//Edit to add in metal dividers. Increasing size of box and adding divier, removing spacing between PMTs
                  dy1/2+0.0635*cm, 
                  (dz+0.5*cm+19.863*cm)/2);

//Creating Lightguide Logical to build within, giving it material: air
    G4LogicalVolume* lightGuide
      = new G4LogicalVolume(lightGuideBox,
                            NuLatMaterials->air,
                            "lightGuide");


if (instrumented == true) {

//Defining Light Guide Trapezoid
  G4VSolid* lightGuideTrd = new G4Trd("LightGuideTrd",     //its name
                                      dx1/2,               //half length along x at the -z surface
                                      dx2/2,               //half length along x at the +z surface
                                      dy1/2,               //half length along y at the -z surface
                                      dy2/2,               //half length along y at the +z surface
                                      dz/2);               //half length along the z axis
  
  G4double r1max = 3.465*2.54/2*cm;
  G4double r1min = 0.0*cm;
  G4double r2max = 1.811*2.54/2*cm;
  G4double r2min = 0.0*cm;
  
//Defining Light Guide Cone  
  G4VSolid* lightGuideCone = new G4Cons("LightGuideCone",   //its name
                                        r1min,              //inside radius at -z surface
                                        r1max,              //outside radius at -z surface
                                        r2min,              //inside radius at +z surface
                                        r2max,              //ouside radius at +z surface
                                        dz/2,               //half length along the z axis
                                        0, 360*deg);        //its segment angles
  G4bool checkOverlaps = true;


//Defining Light Guide Square  
  G4Box* lightGuideSquare = new G4Box("LightGuideSquare",   //its name
                                      dx1/2,                //half length along x axis
                                      dy1/2,                //half length along y axis
                                      0.5*cm/2);            //half length along z axis

//Creating interesecting solid between Trapezoid and Cone, where only material in both zones simultaneously is saved
  G4IntersectionSolid* lightGuideTrdIntersLightGuideCone = new G4IntersectionSolid("Trd Intersect Cone",       //its name
                                                                                    lightGuideTrd,             //solid 1 to interesect
                                                                                    lightGuideCone);           //solid 2 to intersect





                            
//Creating Logical Volume for LightGuide cone/trapezoid intersection, giving it material acrylic                            
    lightGuideTrdIntersLightGuideConeLog
      = new G4LogicalVolume(lightGuideTrdIntersLightGuideCone,
                            NuLatMaterials->acrylic,
                            "lightGuideTrdIntersLightGuideConeLog");

//Creating Logical Volume for Square part of LightGuide, giving it material acrylic
    lightGuideSquareLog
      = new G4LogicalVolume(lightGuideSquare,
                            NuLatMaterials->acrylic,
                            "lightGuideSquareLog");

//Placing cone/trapezoid intersection into lightguide box
    new G4PVPlacement(0,G4ThreeVector(0.,0.,0.5*cm/2 - 19.863*cm/2),lightGuideTrdIntersLightGuideConeLog,
                      "guide001",lightGuide,
                      false,0,checkOverlaps);
//Placing square into lightguide box                      
    new G4PVPlacement(0,G4ThreeVector(0.,0.,-1.0*dz/2 - 19.863*cm/2),lightGuideSquareLog,
                      "guide002",lightGuide,
                      false,0,checkOverlaps);


             
    

//Placing Full PMT Structure into lightguide box
   PMTLog = HamamatsuR10533();
   new G4PVPlacement(0,G4ThreeVector(0.,0.,(dz+0.5*cm)/2),PMTLog,
                      "PMT",lightGuide,
                      false,0,checkOverlaps);
}



     G4VSolid* dividers_outer
      = new G4Box("dividers_outer",
                  dx1/2 + 0.0635*cm, 	
                  dy1/2 + 0.0635*cm, 
                  (6.5*2.54*cm)/2);
      G4VSolid* dividers_inner
      = new G4Box("dividers_inner",
                  dx1/2 , 
                  dy1/2 , 
                  (6.5*2.54*cm)/2);      

  	G4SubtractionSolid* dividers_solid = new G4SubtractionSolid("dividers_solid",          //its name (name of solid after subtraction)
                                                             dividers_outer,           //starting solid
                                                             dividers_inner,   //solid to be subtracted out
                                                             0,                        //rotations (zero in this case)
                                                             G4ThreeVector(0, 0, 0));  //translation before subtraction              
 	dividers_Log = new G4LogicalVolume(dividers_solid,
                                              NuLatMaterials->Aluminium,
                                              "dividers_Log");
    	new G4PVPlacement(0,G4ThreeVector(0.,0.,-(dz+0.5*cm+19.863*cm)/2+(6.5*2.54*cm)/2),dividers_Log,
                      "dividers",lightGuide,
                      false,0,true);


        const G4int numEntries = 182;
        G4double photonEnergy[numEntries] = {
          2.034*eV, 2.068*eV, 2.103*eV, 2.139*eV, 2.177*eV, 2.216*eV, 2.256*eV, 2.298*eV, 2.341*eV, 2.386*eV, //10
          2.433*eV, 2.481*eV, 2.487*eV, 2.496*eV, 2.506*eV, 2.516*eV, 2.524*eV, 2.531*eV, 2.539*eV, 2.547*eV, //20
          2.554*eV, 2.561*eV, 2.569*eV, 2.577*eV, 2.586*eV, 2.595*eV, 2.605*eV, 2.614*eV, 2.622*eV, 2.630*eV, //30
          2.638*eV, 2.646*eV, 2.653*eV, 2.660*eV, 2.669*eV, 2.676*eV, 2.681*eV, 2.688*eV, 2.693*eV, 2.698*eV, //40
          2.703*eV, 2.706*eV, 2.711*eV, 2.718*eV, 2.723*eV, 2.731*eV, 2.742*eV, 2.755*eV, 2.768*eV, 2.782*eV, //50
          2.793*eV, 2.803*eV, 2.811*eV, 2.819*eV, 2.829*eV, 2.837*eV, 2.845*eV, 2.853*eV, 2.860*eV, 2.867*eV, //60
          2.875*eV, 2.882*eV, 2.888*eV, 2.894*eV, 2.900*eV, 2.907*eV, 2.913*eV, 2.919*eV, 2.924*eV, 2.930*eV, //70
          2.937*eV, 2.942*eV, 2.948*eV, 2.954*eV, 2.960*eV, 2.968*eV, 2.976*eV, 2.983*eV, 2.991*eV, 3.001*eV, //80
          3.008*eV, 3.017*eV, 3.028*eV, 3.038*eV, 3.048*eV, 3.055*eV, 3.070*eV, 3.087*eV, 3.103*eV, 3.121*eV, //90
          3.138*eV, 3.155*eV, 3.173*eV, 3.191*eV, 3.220*eV, 3.250*eV, 3.281*eV, 3.313*eV, 3.344*eV, 3.375*eV, //100
          3.403*eV, 3.439*eV, 3.479*eV, 3.522*eV, 3.566*eV, 3.611*eV, 3.644*eV, 3.684*eV, 3.731*eV, 3.780*eV, //110
          3.831*eV, 3.868*eV, 3.892*eV, 3.910*eV, 3.921*eV, 3.934*eV, 3.946*eV, 3.957*eV, 3.970*eV, 3.994*eV, //120
          4.044*eV, 4.102*eV, 4.160*eV, 4.202*eV, 4.236*eV, 4.267*eV, 4.298*eV, 4.328*eV, 4.357*eV, 4.387*eV, //130
          4.422*eV, 4.455*eV, 4.494*eV, 4.563*eV, 4.607*eV, 4.616*eV, 4.624*eV, 4.627*eV, 4.628*eV, 4.633*eV, //140
          4.640*eV, 4.642*eV, 4.649*eV, 4.656*eV, 4.661*eV, 4.666*eV, 4.678*eV, 4.685*eV, 4.692*eV, 4.699*eV, //150
          4.706*eV, 4.713*eV, 4.720*eV, 4.727*eV, 4.740*eV, 4.751*eV, 4.763*eV, 4.775*eV, 4.788*eV, 4.798*eV, //160
          4.813*eV, 4.828*eV, 4.840*eV, 4.853*eV, 4.869*eV, 4.886*eV, 4.905*eV, 4.928*eV, 4.953*eV, 5.015*eV, //170
          5.099*eV, 5.143*eV, 5.174*eV, 5.202*eV, 5.235*eV, 5.265*eV, 5.294*eV, 5.330*eV, 5.413*eV, 5.493*eV, //180
          5.556*eV, 5.611*eV}; //182

                  
	G4double reflectivityAlMetal[numEntries];
	G4double efficiencyAlMetal[numEntries];	
          for(int i=0; i<numEntries; i++){
          reflectivityAlMetal[i] = 0.95;
          efficiencyAlMetal[i] = 1.;

       

          }                  
        
        G4OpticalSurface* OpSurface = new G4OpticalSurface("Al_surface");
	G4LogicalSkinSurface* Al_surface = new G4LogicalSkinSurface("Al_surface",dividers_Log,OpSurface);
	OpSurface -> SetType(dielectric_metal);
	OpSurface -> SetFinish(ground);
	OpSurface -> SetModel(glisur);
	G4double polish = 0.8;
	G4MaterialPropertiesTable *OpSurfaceProperty = new G4MaterialPropertiesTable();
	OpSurfaceProperty -> AddProperty("REFLECTIVITY", photonEnergy, reflectivityAlMetal, numEntries);
	OpSurfaceProperty -> AddProperty("EFFICIENCY",photonEnergy,efficiencyAlMetal,numEntries);
	OpSurface -> SetMaterialPropertiesTable(OpSurfaceProperty);     
	

   

//Visualization Attributes

//Making Box holding Light Guide parts invisible
  G4VisAttributes* visAttributes = new G4VisAttributes(false);
    lightGuide->SetVisAttributes(visAttributes);
    NuLatVisAttributes.push_back(visAttributes);

if (instrumented == true) {
//Making Acrylic Light Guide parts Yellow and partly transparent
  visAttributes = new G4VisAttributes(G4Colour(255,0,255,.3));
    lightGuideTrdIntersLightGuideConeLog->SetVisAttributes(visAttributes);

    lightGuideSquareLog->SetVisAttributes(visAttributes);
    NuLatVisAttributes.push_back(visAttributes);
}

   visAttributes = new G4VisAttributes(G4Colour(255,0,0,.3));
  visAttributes->SetForceWireframe(true);
//  visAttributes->SetForceSolid(true);
  dividers_Log->SetVisAttributes(visAttributes);
  NuLatVisAttributes.push_back(visAttributes);                 
                      
                      
                      
                      
    return(lightGuide);
}



void NuLatDetectorConstruction::ConstructSDandField()
{
    G4SDManager* SDman = G4SDManager::GetSDMpointer();                                      //gets the pointer to the Manager so it can be accessed
    G4String SDname;
    
    G4VSensitiveDetector* nuLatVoxel                                                        //defining Voxel Sensitive Detector
      = new NuLatVoxelSensitiveDetector(SDname="/NuLatVoxel",                               //Name of Detector
        nOfVoxelsInX, nOfVoxelsInY, nOfVoxelsInZ,                                           //Number of Voxels (cubes) in X, Y, Z Directions
        voxelXDimension/2, voxelYDimension/2, voxelZDimension/2,                            //Size of Voxels (cubes) in X, Y, Z Directions
        voxelSpacingXDimension/2, voxelSpacingYDimension/2, voxelSpacingZDimension/2);      //Spacing between Voxels (cubes) in X, Y, Z Direction
        
    SDman->AddNewDetector(nuLatVoxel);                                                      //Adds Voxel Detector to SD Manager
    VoxelLogical->SetSensitiveDetector(nuLatVoxel);                                         //Links the Voxel Detector to the Voxel Logical Volume used in Construction

    G4VSensitiveDetector* nuLatPhotoCathode                                                 //defining PhotoCathode Sensitive Detector
      = new NuLatPhotoCathodeSensitiveDetector(SDname="/nuLatPhotoCathode",                 //Name of Detector
        nOfVoxelsInX, nOfVoxelsInY, nOfVoxelsInZ,                                           //Number of Voxels (cubes) in X, Y, Z Directions: linked to number of lightguide/PMTs
        voxelXDimension/2, voxelYDimension/2, voxelZDimension/2,                            //Size of Voxels (cubes) in X, Y, Z Directions: linked to location/size of lightguide/PMTS
        voxelSpacingXDimension/2, voxelSpacingYDimension/2, voxelSpacingZDimension/2);      //Spacing between Voxels (cubes) in X, Y, Z Direction: linked to location of lightguide/PMTs
        
    SDman->AddNewDetector(nuLatPhotoCathode);                                               //Adds PhotoCathode Detector to SD Manager
    pmtPhotoCathode_Log->SetSensitiveDetector(nuLatPhotoCathode);                           //Links the PhotoCathode Detector to the PMT/PhotoCahode Logical Volume used in Construction
}





