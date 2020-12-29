//VOXEL SENSITIVE DETECTOR HEADER FILE

// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
// $Id: NuLatVoxelSensitiveDetector.hh 76474 2013-11-11 10:36:34Z gcosmo $
//
/// \file NuLatVoxelSensitiveDetector.hh
/// \brief Definition of the NuLatVoxelSensitiveDetector class

#ifndef NuLatVoxelSensitiveDetector_h
#define NuLatVoxelSensitiveDetector_h 1

#include "NuLatVoxelHit.hh"

#include "G4VSensitiveDetector.hh"

class G4Step;
class G4HCofThisEvent;
class G4TouchableHistory;

/// EM calorimeter sensitive detector

class NuLatVoxelSensitiveDetector : public G4VSensitiveDetector
{
    
public:
    NuLatVoxelSensitiveDetector(G4String name,
      G4int    nOfVoxelsInX,   G4int    nOfVoxelsInY,   G4int    nOfVoxelsInZ,
      G4double voxelXDim,      G4double voxelYDim,      G4double voxelZDim,
      G4double voxSpacingXDim, G4double voxSpacingYDim, G4double voxSpacingZDim);
    virtual ~NuLatVoxelSensitiveDetector();



    virtual void Initialize(G4HCofThisEvent*HCE);
    virtual G4bool ProcessHits(G4Step*aStep,G4TouchableHistory*ROhist);
    virtual G4int ParticleNameToIDNumber(G4Step*step);


private:
    NuLatVoxelHitsCollection* voxelHitCollection;
    G4int voxelHitCollectionID;
    G4int    localNOfVoxelsInX;
    G4int    localNOfVoxelsInY;
    G4int    localNOfVoxelsInZ;
    G4double localVoxelXDim;   
    G4double localVoxelYDim;   
    G4double localVoxelZDim;
    G4double localVoxSpacingXDim;
    G4double localVoxSpacingYDim;
    G4double localVoxSpacingZDim;

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
