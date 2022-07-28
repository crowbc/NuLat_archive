#!/bin/bash

./NuLat Macros/run1000_xyzE.mac | awk '/pmtPhotoCathode OpAbsorption/ || /geantino/ {print}' > xyzE.txt2

awk '{print $2 " "  $3 " "  $4 " " $5}' xyzE.txt2 > xyzE.dat; awk '{if ($1 == "G4Track") print $1=999 ; else print $1 }' xyzE.dat > PositionX.dat; awk '{if ($2 == "Information:") print $1=999 ; else print $2 }' xyzE.dat > PositionY.dat; awk '{if ($3 == "Particle") print $1=999 ; else print $3 }' xyzE.dat > PositionZ.dat

./Channeling

awk '{print $2}' Channel.dat > Channel++.dat
./Channel_count2

rm *.dat
rm *.txt2
