# NuLat

1. How to use
-Create a build directory in the NuLat directory. (Current build is build3 - starting with build4 for Co-60 source)
-In the build directory, type the command "cmake .."
-Enter the command "make" in the build directory
-To run in visual mode, enter the command "./NuLat" in the build directory. You may simulate events from the ui and can run macros from the ui.
-To run in batch mode, enter the command "./NuLat <macroName>.mac" in the build directory. The macro file should be in the build directory. NuLatOutput.root will be generated in the build directory and will contain simulation results.

2. Result File
-NuLatOutput.root shows the cumulative results of the entire run, showing how many optical photons have entered and how much energy (MeV) has accumulated per channel.
