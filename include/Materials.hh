//MATERIALS HEADER
//Contains information on all materials to be used in simulations


#ifndef Materials_H

#define Materials_H 1

#include "G4Material.hh"
#include "G4MaterialTable.hh"
#include "G4Element.hh"
#include "G4ElementTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4ios.hh"

class Materials
{

  public:
    G4Element* elH;
    G4Element* elBe;
    G4Element* elB;
    G4Element* elC;
    G4Element* elO;
    G4Element* elN;
    G4Element* elF;
    G4Element* elSi;
    G4Element* elCa;
    G4Element* elFe;
    G4Element* elNi;
    G4Element* elCu;
    G4Element* elMo;
    G4Element* elIn;
    G4Element* elPb;
    G4Element* elenriched6Li;
    G4Element* elAl;

    G4Isotope* isoLi6;


    G4Material* pseudocumene;
    G4Material* teflonFEP;
    G4Material* acrylic;
    G4Material* LENSscint;
    G4Material* LENSbufferScint;
    G4Material* air;
    G4Material* lead;
    G4Material* limestone;
    G4Material* borosilicateGlass;
    G4Material* BoronPVT_1percent;
    G4Material* Li6PVT_1TenthsOfAPercent;
    G4Material* Li6PVT_2TenthsOfAPercent;
    G4Material* Li6PVT_5TenthsOfAPercent;
    G4Material* Li6PVT_10TenthsOfAPercent;
    G4Material* Li6PVT_15TenthsOfAPercent;
    G4Material* muMetal;
    G4Material* vacuum;
    G4Material* BeCuPhotoCathode;
    G4Material* Aluminium;
    


  public: 
    Materials()
    {
        //Photon energy range for energy dependent material responses
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



      //***************************
      //*        Materials        *
      //***************************

      //&&&&&&&&&&&&&&&&&&&&&&&&&
      //&  Element Data Base    &
      //&&&&&&&&&&&&&&&&&&&&&&&&&

      G4double a_elH     =   1.00797 * g/mole;
      G4double a_isoLi6  =   6.015   * g/mole;
      G4double a_elBe    =   9.012   * g/mole;
      G4double a_elB     =  10.81    * g/mole;
      G4double a_elC     =  12.01115 * g/mole;
      G4double a_elO     =  15.9994  * g/mole;
      G4double a_elN     =  14.0067  * g/mole;
      G4double a_elF     =  18.9984  * g/mole;
      G4double a_elSi    =  28.085   * g/mole;
      G4double a_elCa    =  40.078   * g/mole;
      G4double a_elFe    =  55.845   * g/mole;
      G4double a_elNi    =  58.6934  * g/mole;
      G4double a_elCu    =  63.546   * g/mole;
      G4double a_elMo    =  95.95    * g/mole;
      G4double a_elIn    = 114.82    * g/mole;
      G4double a_elPb    = 207.19    * g/mole;
      G4double a_elAl    = 26.98     * g/mole;

      G4double z;  // atomic number

      
      z = 1.0;
      elH  = new G4Element("Hydrogen", "H" , z, a_elH);
      
      z = 4.0;
      elBe  = new G4Element("Beryllium", "Be" , z, a_elBe);
      
      z = 5.0;
      elB  = new G4Element("Boron", "B", z, a_elB);

      z = 6.0;
      elC  = new G4Element("Carbon", "C" , z, a_elC);

      z = 8.0;
      elO  = new G4Element("Oxygen", "O" , z, a_elO);

      z = 7.0;
      elN  = new G4Element("Nitrogen", "N" , z, a_elN);

      z = 9.0;
      elF  = new G4Element("Fluorine", "F" , z, a_elF);
      
      z = 14.0;
      elSi  = new G4Element("Silicon", "Si" , z, a_elSi);

      z = 20;
      elCa = new G4Element( "Calcium", "Ca", z, a_elCa);
      
      z = 26;
      elFe = new G4Element( "Iron", "Fe", z, a_elFe);
      
      z = 28;
      elNi = new G4Element( "Nickel", "Ni", z, a_elNi);
      
      z = 29;
      elCu = new G4Element( "Copper", "Cu", z, a_elCu);
      
      z = 42;
      elMo = new G4Element( "Molybdenum", "Mo", z, a_elMo);
      
      z = 49.0;
      elIn  = new G4Element("Indium", "In" , z, a_elIn);

      z = 82.0;
      elPb = new G4Element( "Lead", "Pb", z, a_elPb);


      z = 3.0;
      isoLi6  = new G4Isotope("Li6", z, 6, a_isoLi6);

      elenriched6Li = new G4Element("enriched Li6", "Li6", 1);
      elenriched6Li->AddIsotope(isoLi6, 100*perCent);
      
      z = 13.0;
      elAl = new G4Element("Aluminium", "Al", z, a_elAl);


      //&&&&&&&&&&&&&&&&&&&&&&&&&
      //&  Molecule Data Base   &
      //&&&&&&&&&&&&&&&&&&&&&&&&&

      G4double density;
      G4int    numberOfElements;

      //Pseudocumene
      density = 0.875*g/cm3;
      numberOfElements = 2;
      pseudocumene = new G4Material("Pseudocumene",density,numberOfElements);
      pseudocumene->AddElement(elC, 9);
      pseudocumene->AddElement(elH, 12);
      
      //TeflonFEP
      density = 2.150*g/cm3;
      teflonFEP = new G4Material("Teflon FEP",density,2);
      teflonFEP->AddElement(elF, 10);
      teflonFEP->AddElement(elC, 5);

//    Acrylic Material properties
      density = 1.180*g/cm3;
      acrylic = new G4Material("Acrylic",density,3);
      acrylic->AddElement(elO, 2);
      acrylic->AddElement(elH, 8);
      acrylic->AddElement(elC, 5);
//    Acrylic Optical properties
//    see 2012 J. Phys.: Conf. Ser. 356 012049
//    Assumes that it is thin film acrylic (idealistic)
      G4double refractiveIndexAcrylic[numEntries];
      G4double absorptionAcrylic[numEntries];
      G4cout << G4endl << G4endl << G4endl << G4endl << G4endl << G4endl << G4endl << G4endl << G4endl << G4endl << G4endl << G4endl << G4endl << G4endl;
      for(int i=0;i<numEntries;i++)
      {
         G4double wavelength = ((1240./photonEnergy[i])*nm)*static_cast<G4double>(pow(10.,-3.));
         refractiveIndexAcrylic[i] = 1.492;
         
//         				      sqrt( 1.866120+
//                                           0.2085454*pow(wavelength,2.)+0.4806770*pow(wavelength,-2.)-
//                                           0.1840693*pow(wavelength,-4.)+0.03424849*pow(wavelength,-6.)-
//                                           0.002340796*pow(wavelength,-8.));
         absorptionAcrylic[i] = 10.0*m;  //absorptions will need to be tuned to data
//         if(refractiveIndexAcrylic[i]<1.49244 || refractiveIndexAcrylic[i]!=refractiveIndexAcrylic[i])
//         //this is removing the nan from Cauchy equation... look for emperical measurments
//         {
//           refractiveIndexAcrylic[i]=1.49244;
//         }
         G4cout << wavelength*1000 << "  " << refractiveIndexAcrylic[i] << G4endl;
      }
      G4cout << G4endl << G4endl << G4endl << G4endl << G4endl << G4endl << G4endl << G4endl << G4endl << G4endl << G4endl << G4endl << G4endl << G4endl;

      G4MaterialPropertiesTable *acrylicMat = new G4MaterialPropertiesTable();
      acrylicMat->AddProperty("RINDEX",photonEnergy,refractiveIndexAcrylic,numEntries);
      acrylicMat->AddProperty("ABSLENGTH", photonEnergy, absorptionAcrylic, numEntries);
      acrylic->SetMaterialPropertiesTable(acrylicMat);


      //Lead
      density = 11.35*g/cm3;
      lead = new G4Material( "Lead", density, 1);
      lead->AddElement(elPb, 1);
      
      //Limestone
      density = 2360*kg/m3;
      limestone = new G4Material("Limestone",density,3);
      limestone->AddElement(elCa, 2);
      limestone->AddElement(elC, 8);
      limestone->AddElement(elO, 5);
      
      //Vacuum
      vacuum = new G4Material( "vacuum", 1., 1.008*g/mole, 1.e-25*g/cm3,kStateGas, 
			273*kelvin, 3.8e-18*pascal );


 //   Artificial Photocathode material density set such that 20nm ->1mm
      BeCuPhotoCathode = new G4Material( "BeCuPhotoCathode", 5.0/50000.0 * g/cm3, 2 );
      BeCuPhotoCathode->AddElement( elBe, 1 );
      BeCuPhotoCathode->AddElement( elCu, 1 );
//    BeCuPhotoCathode Optical Properties
      G4double refractiveIndexBeCuPhotoCathode[numEntries];
      G4double absorptionBeCuPhotoCathode[numEntries];
      for(int i=0; i<numEntries; i++){
        refractiveIndexBeCuPhotoCathode[i] = 2.7;
        absorptionBeCuPhotoCathode[i] = 0.001*mm;
      }
      G4MaterialPropertiesTable *BeCuPhotoCathodeMat = new G4MaterialPropertiesTable();
      BeCuPhotoCathodeMat->AddProperty("RINDEX", photonEnergy, refractiveIndexBeCuPhotoCathode, numEntries);
      BeCuPhotoCathodeMat->AddProperty("ABSLENGTH", photonEnergy, absorptionBeCuPhotoCathode, numEntries);
      BeCuPhotoCathode->SetMaterialPropertiesTable( BeCuPhotoCathodeMat );


      //BorosilicateGlass Material Properties
      borosilicateGlass = new G4Material( "BorosilicateGlass", 2.65*g/cm3, 2 );
      borosilicateGlass->AddElement( elSi, 1 );
      borosilicateGlass->AddElement( elO, 2 );
      //BorosilicateGlass Optical Properties
      G4double refractiveIndexBorosilicateGlass[numEntries];
      G4double absorptionBorosilicateGlass[numEntries];
      for(int i=0; i<numEntries; i++){
        refractiveIndexBorosilicateGlass[i] = 1.55;
        absorptionBorosilicateGlass[i] = 10*m;
      }
      G4MaterialPropertiesTable *borosilicateGlassMat = new G4MaterialPropertiesTable();
      borosilicateGlassMat->AddProperty("RINDEX", photonEnergy, refractiveIndexBorosilicateGlass, numEntries);
      borosilicateGlassMat->AddProperty("ABSLENGTH", photonEnergy, absorptionBorosilicateGlass, numEntries);
      borosilicateGlass->SetMaterialPropertiesTable( borosilicateGlassMat );
      
      
      //Alluminium Material Properties
      Aluminium = new G4Material("Aluminium", 2.7*g/cm3, 1);
      Aluminium->AddElement( elAl, 1);
      
          G4double reflectivityAlMetal[numEntries];
          G4double refractiveIndexAl[numEntries];
          G4double absorptionAlMetal[numEntries];
          G4double imgrefractiveIndexAl[numEntries];          
          for(int i=0; i<numEntries; i++){
          reflectivityAlMetal[i] = 0.95;
          absorptionAlMetal[i] = 0.1*m;
          refractiveIndexAl[i] = 1.5;
          imgrefractiveIndexAl[i] = 4.836;          

          }
          
	  G4MaterialPropertiesTable *Al_SurfaceMPT = new G4MaterialPropertiesTable();
//          Al_SurfaceMPT->AddProperty("REFLECTIVITY", photonEnergy, reflectivityAlMetal, numEntries);   //overall
          Al_SurfaceMPT->AddProperty("ABSLENGTH", photonEnergy, absorptionAlMetal, numEntries );
//          Al_SurfaceMPT->AddProperty("RINDEX", photonEnergy, refractiveIndexAl, numEntries );
//          Al_SurfaceMPT->AddProperty("IMAGINARYRINDEX", photonEnergy, imgrefractiveIndexAl, numEntries );          
          Aluminium->SetMaterialPropertiesTable(Al_SurfaceMPT);


      //&&&&&&&&&&&&&&&&&&&&&&&&&
      //&  Mixture Data Base    &
      //&&&&&&&&&&&&&&&&&&&&&&&&&

      G4int numberOfComponents;

      density = 0.950*g/cm3;
      numberOfComponents = 2;
      LENSscint = new G4Material("LENSscint",density,numberOfComponents);
      LENSscint->AddElement(elIn, 8*perCent);
      LENSscint->AddMaterial(pseudocumene, 92*perCent);


      density = 0.875*g/cm3;
      LENSbufferScint = new G4Material("bufferScint",density,1);
      LENSbufferScint->AddMaterial(pseudocumene, 100*perCent);


   // Air Material Properies
      density = 1.290*mg/cm3;
      air = new G4Material("air",density,2);
      air->AddElement(elN, 70*perCent);
      air->AddElement(elO, 30*perCent);
   // Air Optics
      G4double refractiveIndexAir[numEntries];
      G4double absorptionAir[numEntries];
      for(int i=0; i<numEntries; i++){
            refractiveIndexAir[i] = 1.003;
            absorptionAir[i] = 100*m;
      }
      G4MaterialPropertiesTable *airMat = new G4MaterialPropertiesTable();
      airMat->AddProperty("RINDEX", photonEnergy, refractiveIndexAir, numEntries );
      airMat->AddProperty("ABSLENGTH", photonEnergy, absorptionAir, numEntries );
      air->SetMaterialPropertiesTable(airMat);



      // 1% by wt Boron loaded polyvinyltoluene
      G4double CAtomsPerCC=4.62, HAtomsPerCC=5.16, BAtomsPerCC=1.14/100/.199;
      G4double CMassPerCC=CAtomsPerCC*a_elC, HMassPerCC=HAtomsPerCC*a_elH, BMassPerCC=BAtomsPerCC*a_elB;

      G4double C_fractionmass = CMassPerCC/(CMassPerCC + HMassPerCC + BMassPerCC);
      G4double H_fractionmass = HMassPerCC/(CMassPerCC + HMassPerCC + BMassPerCC);
      G4double B_fractionmass = BMassPerCC/(CMassPerCC + HMassPerCC + BMassPerCC);

      density = 1.021*g/cm3;
      BoronPVT_1percent = new G4Material("BoronPVT_1percent",density, 3);
      BoronPVT_1percent->AddElement(elH, H_fractionmass);
      BoronPVT_1percent->AddElement(elC, C_fractionmass);
      BoronPVT_1percent->AddElement(elB, B_fractionmass);

    G4cout << BoronPVT_1percent << G4endl;

      G4double C_StandardFractionMass = C_fractionmass * 1.01;
      G4double H_StandardFractionMass = H_fractionmass * 1.01;








//    Li 6 Generic optical properties
//    scintillator
//    see Journal of Colloid and Interface Science Volume 118, Issue 2, August 1987, Pages 314–325
//    gives Sellmeier Coefficients
      
      
      G4double refractiveIndexPlastic[numEntries];
      G4double absorptionPlastic[numEntries];
      G4double rayleigh_scattering[numEntries];
  
      for(int i=0; i<numEntries; i++)  {
      //refractive index assumes PVT, absorption is something to be tuned
      G4double wavelength = (1240./photonEnergy[i])*nm;
      refractiveIndexPlastic[i] = 1.58;
      absorptionPlastic[i]=90.*cm;
      rayleigh_scattering[i] =90.0*cm;
      }
  
      //  Fast scintillation properties, no reference and were here with the original file
      G4double fastComponentPlastic[numEntries] = {
        0.000,  0.000,  0.000,  0.000,  0.000,  0.010,  0.020,  0.035,  0.050,  0.060, //10
        0.070,  0.085,  0.090,  0.095,  0.098,  0.100,  0.110,  0.120,  0.130,  0.140, //20
        0.150,  0.160,  0.170,  0.180,  0.200,  0.220,  0.240,  0.250,  0.270,  0.290, //30  
        0.300,  0.320,  0.340,  0.350,  0.360,  0.390,  0.400,  0.420,  0.430,  0.440, //40  
        0.445,  0.450,  0.460,  0.470,  0.480,  0.500,  0.550,  0.600,  0.630,  0.700, //50  
        0.730,  0.750,  0.800,  0.830,  0.850,  0.870,  0.900,  0.920,  0.940,  0.950, //60  
        0.960,  0.970,  0.980,  0.985,  0.990,  0.995,  1.000,  1.000,  1.000,  0.995, //70  
        0.990,  0.985,  0.980,  0.970,  0.960,  0.930,  0.900,  0.870,  0.850,  0.800, //80 
        0.700,  0.600,  0.500,  0.400,  0.300,  0.220,  0.130,  0.070,  0.010,  0.000, //90  
        0.000,  0.000,  0.000,  0.000,  0.000,  0.000,  0.000,  0.000,  0.000,  0.000, //100
        0.000,  0.000,  0.000,  0.000,  0.000,  0.000,  0.000,  0.000,  0.000,  0.000, //110  
        0.000,  0.000,  0.000,  0.000,  0.000,  0.000,  0.000,  0.000,  0.000,  0.000, //120  
        0.000,  0.000,  0.000,  0.000,  0.000,  0.000,  0.000,  0.000,  0.000,  0.000, //130  
        0.000,  0.000,  0.000,  0.000,  0.000,  0.000,  0.000,  0.000,  0.000,  0.000, //140  
        0.000,  0.000,  0.000,  0.000,  0.000,  0.000,  0.000,  0.000,  0.000,  0.000, //150  
        0.000,  0.000,  0.000,  0.000,  0.000,  0.000,  0.000,  0.000,  0.000,  0.000, //160  
        0.000,  0.000,  0.000,  0.000,  0.000,  0.000,  0.000,  0.000,  0.000,  0.000, //170  
        0.000,  0.000,  0.000,  0.000,  0.000,  0.000,  0.000,  0.000,  0.000,  0.000, //180  
        0.000,  0.000}; //182
  

      G4MaterialPropertiesTable *PVT_MPT = new G4MaterialPropertiesTable();      
      PVT_MPT->AddProperty("RINDEX", photonEnergy, refractiveIndexPlastic, numEntries);
      PVT_MPT->AddProperty("ABSLENGTH", photonEnergy, absorptionPlastic, numEntries); 
      PVT_MPT->AddProperty("FASTCOMPONENT",photonEnergy, fastComponentPlastic, numEntries, true);
      //add a slow compontent at some point
      PVT_MPT->AddConstProperty("SCINTILLATIONYIELD",10000./MeV);//10000./MeV);
      PVT_MPT->AddConstProperty("RESOLUTIONSCALE",1.0);    
      PVT_MPT->AddConstProperty("FASTTIMECONSTANT", 2.1*ns, true);    
      PVT_MPT->AddConstProperty("YIELDRATIO",1., true);
      
   //   PVT_MPT->AddProperty("RAYLEIGH",photonEnergy,rayleigh_scattering,numEntries); 



      // 0.1% by wt 6Li loaded polyvinyltoluene  
      G4double Li6_fractionmass = 0.001;
      H_fractionmass = C_StandardFractionMass/(1.0+Li6_fractionmass);
      C_fractionmass = H_StandardFractionMass/(1.0+Li6_fractionmass);
        
      density = 1.021*g/cm3;
      Li6PVT_1TenthsOfAPercent = new G4Material("Li6PVT_1TenthsOfAPercent",density, 3);
      Li6PVT_1TenthsOfAPercent->AddElement(elH, H_fractionmass);
      Li6PVT_1TenthsOfAPercent->AddElement(elC, C_fractionmass);
      Li6PVT_1TenthsOfAPercent->AddElement(elenriched6Li, Li6_fractionmass);
      Li6PVT_1TenthsOfAPercent->SetMaterialPropertiesTable(PVT_MPT);
      Li6PVT_1TenthsOfAPercent->GetIonisation()->SetBirksConstant(0.01045*cm/MeV);
      
    G4cout << Li6PVT_1TenthsOfAPercent << G4endl << G4endl << G4endl;
    
      // 0.2% by wt 6Li loaded polyvinyltoluene  
      Li6_fractionmass = 0.002;
      H_fractionmass = C_StandardFractionMass/(1.0+Li6_fractionmass);
      C_fractionmass = H_StandardFractionMass/(1.0+Li6_fractionmass);
        
    density = 1.021*g/cm3;
      Li6PVT_2TenthsOfAPercent = new G4Material("Li6PVT_1TenthsOfAPercent",density, 3);
      Li6PVT_2TenthsOfAPercent->AddElement(elH, H_fractionmass);
      Li6PVT_2TenthsOfAPercent->AddElement(elC, C_fractionmass);
      Li6PVT_2TenthsOfAPercent->AddElement(elenriched6Li, Li6_fractionmass);
      Li6PVT_2TenthsOfAPercent->SetMaterialPropertiesTable(PVT_MPT);
      Li6PVT_2TenthsOfAPercent->GetIonisation()->SetBirksConstant(0.01045*cm/MeV);

    G4cout << Li6PVT_2TenthsOfAPercent << G4endl << G4endl << G4endl;

      // 0.5% by wt 6Li loaded polyvinyltoluene  
      Li6_fractionmass = 0.005;
      H_fractionmass = C_StandardFractionMass/(1.0+Li6_fractionmass);
      C_fractionmass = H_StandardFractionMass/(1.0+Li6_fractionmass);
        
    density = 1.021*g/cm3;
      Li6PVT_5TenthsOfAPercent = new G4Material("Li6PVT_5TenthsOfAPercent",density, 3);
      Li6PVT_5TenthsOfAPercent->AddElement(elH, H_fractionmass);
      Li6PVT_5TenthsOfAPercent->AddElement(elC, C_fractionmass);
      Li6PVT_5TenthsOfAPercent->AddElement(elenriched6Li, Li6_fractionmass);
      Li6PVT_5TenthsOfAPercent->SetMaterialPropertiesTable(PVT_MPT);
      Li6PVT_5TenthsOfAPercent->GetIonisation()->SetBirksConstant(0.01045*cm/MeV);

    G4cout << Li6PVT_5TenthsOfAPercent << G4endl << G4endl << G4endl;
    
      // 1.0% by wt 6Li loaded polyvinyltoluene  
      Li6_fractionmass = 0.010;
      H_fractionmass = C_StandardFractionMass/(1.0+Li6_fractionmass);
      C_fractionmass = H_StandardFractionMass/(1.0+Li6_fractionmass);
        
    density = 1.021*g/cm3;
      Li6PVT_10TenthsOfAPercent = new G4Material("Li6PVT_10TenthsOfAPercent",density, 3);
      Li6PVT_10TenthsOfAPercent->AddElement(elH, H_fractionmass);
      Li6PVT_10TenthsOfAPercent->AddElement(elC, C_fractionmass);
      Li6PVT_10TenthsOfAPercent->AddElement(elenriched6Li, Li6_fractionmass);
      Li6PVT_10TenthsOfAPercent->SetMaterialPropertiesTable(PVT_MPT);
      Li6PVT_10TenthsOfAPercent->GetIonisation()->SetBirksConstant(0.01045*cm/MeV);

    G4cout << Li6PVT_10TenthsOfAPercent << G4endl << G4endl << G4endl;

      // 1.5% by wt 6Li loaded polyvinyltoluene  
      Li6_fractionmass = 0.015;
      H_fractionmass = C_StandardFractionMass/(1.0+Li6_fractionmass);
      C_fractionmass = H_StandardFractionMass/(1.0+Li6_fractionmass);
        
    density = 1.021*g/cm3;
      Li6PVT_15TenthsOfAPercent = new G4Material("Li6PVT_15TenthsOfAPercent",density, 3);
      Li6PVT_15TenthsOfAPercent->AddElement(elH, H_fractionmass);
      Li6PVT_15TenthsOfAPercent->AddElement(elC, C_fractionmass);
      Li6PVT_15TenthsOfAPercent->AddElement(elenriched6Li, Li6_fractionmass);
      Li6PVT_15TenthsOfAPercent->SetMaterialPropertiesTable(PVT_MPT);
      Li6PVT_15TenthsOfAPercent->GetIonisation()->SetBirksConstant(0.01045*cm/MeV);

    G4cout << Li6PVT_15TenthsOfAPercent << G4endl << G4endl << G4endl;
      //materials
      //Water, Steel, Quartz, Stainless steel (304, 316, etc), tungsten, teflon (all others), polyester, polyethyliene..
      
    //MuMetal  
    muMetal = new G4Material( "muMetal",8.77*g/cm3,4);
    muMetal->AddElement(elNi,77.*perCent);
    muMetal->AddElement(elFe,16.*perCent);
    muMetal->AddElement(elCu,5.*perCent);
    muMetal->AddElement(elMo,2.*perCent);   
    //   Mu-metal Surface Properties
    G4double reflectivityMuMetal[numEntries];
    G4double specularLopeMuMetal[numEntries];
    G4double specularSpikeMuMetal[numEntries];
    G4double backscatterMuMetal[numEntries];
    G4double efficiencyMuMetal[numEntries];
    for(int i=0; i<numEntries; i++){
       specularLopeMuMetal[i] = 0.0;
       specularSpikeMuMetal[i] = 0.;
       backscatterMuMetal[i] = 0.0;
       reflectivityMuMetal[i] = 0.0;
       efficiencyMuMetal[i] = 0.;
    }
    G4MaterialPropertiesTable *muMetal_SurfaceMPT = new G4MaterialPropertiesTable();
    muMetal_SurfaceMPT->AddProperty("REFLECTIVITY", photonEnergy, 
                         reflectivityMuMetal, numEntries);   //overall
    muMetal_SurfaceMPT->AddProperty("SPECULARLOBECONSTANT", photonEnergy, 
                         specularLopeMuMetal, numEntries);   //normal of micro-facet
    muMetal_SurfaceMPT->AddProperty("SPECULARSPIKECONSTANT", photonEnergy, 
                         specularSpikeMuMetal, numEntries);   //mirror
    muMetal_SurfaceMPT->AddProperty("BACKSCATTERCONSTANT", photonEnergy,
                         backscatterMuMetal, numEntries);   //backscatter
    muMetal_SurfaceMPT->AddProperty("EFFICIENCY",photonEnergy,efficiencyMuMetal,
                         numEntries);
    muMetal->SetMaterialPropertiesTable(muMetal_SurfaceMPT);
   

    }
};

#endif

