//VOXEL PARAMETERIZATION FILE
//Used in building detector with many copied Voxel setups



//Required files to include
#include "NuLatVoxelParameterisation.hh"            //Header for this file

#include "G4VPhysicalVolume.hh"                     //Header to place volumes in the world
#include "G4ThreeVector.hh"                         //Header so you can use vectors
#include "G4SystemOfUnits.hh"                       //Header for system of units
#include "stdlib.h"                                 //Header for Standard Library

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


//Defining the Parameterization function to be used in Detector Construction
NuLatVoxelParameterisation::NuLatVoxelParameterisation(
    G4int    nOfVoxelsInX,   G4int    nOfVoxelsInY,   G4int    nOfVoxelsInZ,
    G4double voxelXDim,      G4double voxelYDim,      G4double voxelZDim,
    G4double voxSpacingXDim, G4double voxSpacingYDim, G4double voxSpacingZDim)
          : G4VPVParameterisation()
{
  G4double totalNumberOfVoxels = nOfVoxelsInX*nOfVoxelsInY*nOfVoxelsInZ;           //Defines total number of Cubes to be created
  xVoxel = (G4double*) malloc(totalNumberOfVoxels*sizeof(G4double));               //Alocates enough space in bytes for an array of [totalNumberOfVoxels] intergers
  yVoxel = (G4double*) malloc(totalNumberOfVoxels*sizeof(G4double));               //Alocates enough space in bytes for an array of [totalNumberOfVoxels] intergers
  zVoxel = (G4double*) malloc(totalNumberOfVoxels*sizeof(G4double));               //Alocates enough space in bytes for an array of [totalNumberOfVoxels] intergers


//Defining the X, Y, and Z voxel number for each copied cube, to be used for properly placing it
  for (G4int copyNo=0;copyNo<totalNumberOfVoxels;copyNo++)
  {                                                                                //ForCopy#:0,1,2,3,4,5,6,7,8,9,10,etc.
    G4int xCellIndex = 1+(copyNo % (nOfVoxelsInX*nOfVoxelsInY))/ nOfVoxelsInY;     //X Index: 1,1,1,1,1,2,2,2,2,2,3,3,3,3,3,4,4,4,4,4,5,5,5,5,5,1,1,1,1,1,2,2,2,2,2,etc.
    G4int yCellIndex = 1+copyNo % nOfVoxelsInY;                                    //Y Index: 1,2,3,4,5,1,2,3,4,5,1,2,3,4,5,1,2,3,4,5,etc.
    G4int zCellIndex = 1+copyNo / (nOfVoxelsInX*nOfVoxelsInY);                     //Z Index: 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,etc.

    G4double voxSpacingX = voxelXDim+voxSpacingXDim;                               //Defining spacing between center of each cube in the X Dimension
    G4double voxSpacingY = voxelYDim+voxSpacingYDim;                               //Defining spacing between center of each cube in the Y Dimension
    G4double voxSpacingZ = voxelZDim+voxSpacingZDim;                               //Defining spacing between center of each cube in the Z Dimension

//Creating array holding the X position for each copy
    if(nOfVoxelsInX%2 == 0)
      xVoxel[copyNo] = (((xCellIndex) - (nOfVoxelsInX/2+0.5)) * voxSpacingX)*2;
    else
     xVoxel[copyNo] = ((xCellIndex-1 - nOfVoxelsInX/2) * voxSpacingX)*2;
     
//Creating array holding the Y position for each copy
    if(nOfVoxelsInY%2 == 0)
      yVoxel[copyNo] = (((yCellIndex) - (nOfVoxelsInY/2+0.5)) * voxSpacingY)*2;
    else
      yVoxel[copyNo] = ((yCellIndex-1 - nOfVoxelsInY/2) * voxSpacingY)*2; //Note nOfVoxelsInY/2 truncates the division
      
//Creating array holding the Z position for each copy      
    if(nOfVoxelsInZ%2 == 0)
      zVoxel[copyNo] = (((zCellIndex) - (nOfVoxelsInZ/2+0.5)) * voxSpacingZ)*2;
    else
      zVoxel[copyNo] = ((zCellIndex-1 - nOfVoxelsInZ/2) * voxSpacingZ)*2; //Note nOfVoxelsInZ/2 truncates the division
    
  }
}


//Destructor
NuLatVoxelParameterisation::~NuLatVoxelParameterisation()
{}


//Geant native transform function setting the position of each copy to be built and labeling its CopyNumber
void NuLatVoxelParameterisation::ComputeTransformation(const G4int copyNo,G4VPhysicalVolume *physVol) const
{
  physVol->SetTranslation(G4ThreeVector(xVoxel[copyNo],yVoxel[copyNo],zVoxel[copyNo]));   //Sets position
  physVol->SetCopyNo(copyNo);                                                             //Sets label of which copy number
}


