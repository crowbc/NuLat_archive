#!/bin/bash

#1 get Time data
./NuLat Macros/run1000_t.mac | awk -v N=26 -v pattern="pmtPhotoCathode OpAbsorption" '{i=(1+(i%N));if (buffer[i]&& $0 ~ pattern || /geantino/ ) print buffer[i]; buffer[i]=$0;}' > t.txt2
#2 get Channel data
./NuLat Macros/run1000_xyzE.mac | awk '/pmtPhotoCathode OpAbsorption/ || /geantino/ {print}' > xyzE.txt2

awk '{if ($1 == "Global") print $6 ; else print $6=471700 }' t.txt2 > t.dat
g++ Timing_Window.cpp -o Timing_Window
./Timing_Window
awk '{if ($3 == "471700") print $3=" "; else print $3 }' Window.dat > Window+.dat
awk '{print $2 " "  $3 " "  $4 " " $5}' xyzE.txt2 > xyzE.dat; awk '{if ($1 == "G4Track") print $1=999 ; else print $1 }' xyzE.dat > PositionX.dat; awk '{if ($2 == "Information:") print $1=999 ; else print $2 }' xyzE.dat > PositionY.dat; awk '{if ($3 == "Particle") print $1=999 ; else print $3 }' xyzE.dat > PositionZ.dat


g++ Channeling.cpp -o Channeling
./Channeling
awk '{if ($2 == "999") print $2=" "; else print $2 }' Channel.dat > Channel+.dat


#3 Energy
awk '{if ($4 == "=") print $1=" "; else print $4 }' xyzE.dat > Energy+.dat


#4 data combinening
paste Channel+.dat Window+.dat Energy+.dat > result2.txt


#5 data eraseing
rm *.dat

#6 getiing channel and energy data
awk '{print $1}' result2.txt > channel.txt2
awk '{print $3}' result2.txt > energy.txt2

Channel_count
./Channel_count

rm *.txt2
