# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/jack/Documents/geant4/NuLat

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/jack/Documents/geant4/NuLat/build4

# Include any dependencies generated for this target.
include CMakeFiles/NuLat.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/NuLat.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/NuLat.dir/flags.make

CMakeFiles/NuLat.dir/NuLat.cc.o: CMakeFiles/NuLat.dir/flags.make
CMakeFiles/NuLat.dir/NuLat.cc.o: ../NuLat.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jack/Documents/geant4/NuLat/build4/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/NuLat.dir/NuLat.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/NuLat.dir/NuLat.cc.o -c /home/jack/Documents/geant4/NuLat/NuLat.cc

CMakeFiles/NuLat.dir/NuLat.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/NuLat.dir/NuLat.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jack/Documents/geant4/NuLat/NuLat.cc > CMakeFiles/NuLat.dir/NuLat.cc.i

CMakeFiles/NuLat.dir/NuLat.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/NuLat.dir/NuLat.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jack/Documents/geant4/NuLat/NuLat.cc -o CMakeFiles/NuLat.dir/NuLat.cc.s

CMakeFiles/NuLat.dir/src/NuLatActionInitialization.cc.o: CMakeFiles/NuLat.dir/flags.make
CMakeFiles/NuLat.dir/src/NuLatActionInitialization.cc.o: ../src/NuLatActionInitialization.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jack/Documents/geant4/NuLat/build4/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/NuLat.dir/src/NuLatActionInitialization.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/NuLat.dir/src/NuLatActionInitialization.cc.o -c /home/jack/Documents/geant4/NuLat/src/NuLatActionInitialization.cc

CMakeFiles/NuLat.dir/src/NuLatActionInitialization.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/NuLat.dir/src/NuLatActionInitialization.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jack/Documents/geant4/NuLat/src/NuLatActionInitialization.cc > CMakeFiles/NuLat.dir/src/NuLatActionInitialization.cc.i

CMakeFiles/NuLat.dir/src/NuLatActionInitialization.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/NuLat.dir/src/NuLatActionInitialization.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jack/Documents/geant4/NuLat/src/NuLatActionInitialization.cc -o CMakeFiles/NuLat.dir/src/NuLatActionInitialization.cc.s

CMakeFiles/NuLat.dir/src/NuLatDetectorConstruction.cc.o: CMakeFiles/NuLat.dir/flags.make
CMakeFiles/NuLat.dir/src/NuLatDetectorConstruction.cc.o: ../src/NuLatDetectorConstruction.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jack/Documents/geant4/NuLat/build4/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/NuLat.dir/src/NuLatDetectorConstruction.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/NuLat.dir/src/NuLatDetectorConstruction.cc.o -c /home/jack/Documents/geant4/NuLat/src/NuLatDetectorConstruction.cc

CMakeFiles/NuLat.dir/src/NuLatDetectorConstruction.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/NuLat.dir/src/NuLatDetectorConstruction.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jack/Documents/geant4/NuLat/src/NuLatDetectorConstruction.cc > CMakeFiles/NuLat.dir/src/NuLatDetectorConstruction.cc.i

CMakeFiles/NuLat.dir/src/NuLatDetectorConstruction.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/NuLat.dir/src/NuLatDetectorConstruction.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jack/Documents/geant4/NuLat/src/NuLatDetectorConstruction.cc -o CMakeFiles/NuLat.dir/src/NuLatDetectorConstruction.cc.s

CMakeFiles/NuLat.dir/src/NuLatEventAction.cc.o: CMakeFiles/NuLat.dir/flags.make
CMakeFiles/NuLat.dir/src/NuLatEventAction.cc.o: ../src/NuLatEventAction.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jack/Documents/geant4/NuLat/build4/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/NuLat.dir/src/NuLatEventAction.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/NuLat.dir/src/NuLatEventAction.cc.o -c /home/jack/Documents/geant4/NuLat/src/NuLatEventAction.cc

CMakeFiles/NuLat.dir/src/NuLatEventAction.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/NuLat.dir/src/NuLatEventAction.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jack/Documents/geant4/NuLat/src/NuLatEventAction.cc > CMakeFiles/NuLat.dir/src/NuLatEventAction.cc.i

CMakeFiles/NuLat.dir/src/NuLatEventAction.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/NuLat.dir/src/NuLatEventAction.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jack/Documents/geant4/NuLat/src/NuLatEventAction.cc -o CMakeFiles/NuLat.dir/src/NuLatEventAction.cc.s

CMakeFiles/NuLat.dir/src/NuLatLightGuideParameterisation.cc.o: CMakeFiles/NuLat.dir/flags.make
CMakeFiles/NuLat.dir/src/NuLatLightGuideParameterisation.cc.o: ../src/NuLatLightGuideParameterisation.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jack/Documents/geant4/NuLat/build4/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/NuLat.dir/src/NuLatLightGuideParameterisation.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/NuLat.dir/src/NuLatLightGuideParameterisation.cc.o -c /home/jack/Documents/geant4/NuLat/src/NuLatLightGuideParameterisation.cc

CMakeFiles/NuLat.dir/src/NuLatLightGuideParameterisation.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/NuLat.dir/src/NuLatLightGuideParameterisation.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jack/Documents/geant4/NuLat/src/NuLatLightGuideParameterisation.cc > CMakeFiles/NuLat.dir/src/NuLatLightGuideParameterisation.cc.i

CMakeFiles/NuLat.dir/src/NuLatLightGuideParameterisation.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/NuLat.dir/src/NuLatLightGuideParameterisation.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jack/Documents/geant4/NuLat/src/NuLatLightGuideParameterisation.cc -o CMakeFiles/NuLat.dir/src/NuLatLightGuideParameterisation.cc.s

CMakeFiles/NuLat.dir/src/NuLatPhotoCathodeHit.cc.o: CMakeFiles/NuLat.dir/flags.make
CMakeFiles/NuLat.dir/src/NuLatPhotoCathodeHit.cc.o: ../src/NuLatPhotoCathodeHit.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jack/Documents/geant4/NuLat/build4/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/NuLat.dir/src/NuLatPhotoCathodeHit.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/NuLat.dir/src/NuLatPhotoCathodeHit.cc.o -c /home/jack/Documents/geant4/NuLat/src/NuLatPhotoCathodeHit.cc

CMakeFiles/NuLat.dir/src/NuLatPhotoCathodeHit.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/NuLat.dir/src/NuLatPhotoCathodeHit.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jack/Documents/geant4/NuLat/src/NuLatPhotoCathodeHit.cc > CMakeFiles/NuLat.dir/src/NuLatPhotoCathodeHit.cc.i

CMakeFiles/NuLat.dir/src/NuLatPhotoCathodeHit.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/NuLat.dir/src/NuLatPhotoCathodeHit.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jack/Documents/geant4/NuLat/src/NuLatPhotoCathodeHit.cc -o CMakeFiles/NuLat.dir/src/NuLatPhotoCathodeHit.cc.s

CMakeFiles/NuLat.dir/src/NuLatPhotoCathodeSensitiveDetector.cc.o: CMakeFiles/NuLat.dir/flags.make
CMakeFiles/NuLat.dir/src/NuLatPhotoCathodeSensitiveDetector.cc.o: ../src/NuLatPhotoCathodeSensitiveDetector.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jack/Documents/geant4/NuLat/build4/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/NuLat.dir/src/NuLatPhotoCathodeSensitiveDetector.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/NuLat.dir/src/NuLatPhotoCathodeSensitiveDetector.cc.o -c /home/jack/Documents/geant4/NuLat/src/NuLatPhotoCathodeSensitiveDetector.cc

CMakeFiles/NuLat.dir/src/NuLatPhotoCathodeSensitiveDetector.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/NuLat.dir/src/NuLatPhotoCathodeSensitiveDetector.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jack/Documents/geant4/NuLat/src/NuLatPhotoCathodeSensitiveDetector.cc > CMakeFiles/NuLat.dir/src/NuLatPhotoCathodeSensitiveDetector.cc.i

CMakeFiles/NuLat.dir/src/NuLatPhotoCathodeSensitiveDetector.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/NuLat.dir/src/NuLatPhotoCathodeSensitiveDetector.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jack/Documents/geant4/NuLat/src/NuLatPhotoCathodeSensitiveDetector.cc -o CMakeFiles/NuLat.dir/src/NuLatPhotoCathodeSensitiveDetector.cc.s

CMakeFiles/NuLat.dir/src/NuLatPrimaryGeneratorMessenger.cc.o: CMakeFiles/NuLat.dir/flags.make
CMakeFiles/NuLat.dir/src/NuLatPrimaryGeneratorMessenger.cc.o: ../src/NuLatPrimaryGeneratorMessenger.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jack/Documents/geant4/NuLat/build4/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/NuLat.dir/src/NuLatPrimaryGeneratorMessenger.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/NuLat.dir/src/NuLatPrimaryGeneratorMessenger.cc.o -c /home/jack/Documents/geant4/NuLat/src/NuLatPrimaryGeneratorMessenger.cc

CMakeFiles/NuLat.dir/src/NuLatPrimaryGeneratorMessenger.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/NuLat.dir/src/NuLatPrimaryGeneratorMessenger.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jack/Documents/geant4/NuLat/src/NuLatPrimaryGeneratorMessenger.cc > CMakeFiles/NuLat.dir/src/NuLatPrimaryGeneratorMessenger.cc.i

CMakeFiles/NuLat.dir/src/NuLatPrimaryGeneratorMessenger.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/NuLat.dir/src/NuLatPrimaryGeneratorMessenger.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jack/Documents/geant4/NuLat/src/NuLatPrimaryGeneratorMessenger.cc -o CMakeFiles/NuLat.dir/src/NuLatPrimaryGeneratorMessenger.cc.s

CMakeFiles/NuLat.dir/src/NuLatPrimaryParticleGenerator.cc.o: CMakeFiles/NuLat.dir/flags.make
CMakeFiles/NuLat.dir/src/NuLatPrimaryParticleGenerator.cc.o: ../src/NuLatPrimaryParticleGenerator.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jack/Documents/geant4/NuLat/build4/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/NuLat.dir/src/NuLatPrimaryParticleGenerator.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/NuLat.dir/src/NuLatPrimaryParticleGenerator.cc.o -c /home/jack/Documents/geant4/NuLat/src/NuLatPrimaryParticleGenerator.cc

CMakeFiles/NuLat.dir/src/NuLatPrimaryParticleGenerator.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/NuLat.dir/src/NuLatPrimaryParticleGenerator.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jack/Documents/geant4/NuLat/src/NuLatPrimaryParticleGenerator.cc > CMakeFiles/NuLat.dir/src/NuLatPrimaryParticleGenerator.cc.i

CMakeFiles/NuLat.dir/src/NuLatPrimaryParticleGenerator.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/NuLat.dir/src/NuLatPrimaryParticleGenerator.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jack/Documents/geant4/NuLat/src/NuLatPrimaryParticleGenerator.cc -o CMakeFiles/NuLat.dir/src/NuLatPrimaryParticleGenerator.cc.s

CMakeFiles/NuLat.dir/src/NuLatRun.cc.o: CMakeFiles/NuLat.dir/flags.make
CMakeFiles/NuLat.dir/src/NuLatRun.cc.o: ../src/NuLatRun.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jack/Documents/geant4/NuLat/build4/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/NuLat.dir/src/NuLatRun.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/NuLat.dir/src/NuLatRun.cc.o -c /home/jack/Documents/geant4/NuLat/src/NuLatRun.cc

CMakeFiles/NuLat.dir/src/NuLatRun.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/NuLat.dir/src/NuLatRun.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jack/Documents/geant4/NuLat/src/NuLatRun.cc > CMakeFiles/NuLat.dir/src/NuLatRun.cc.i

CMakeFiles/NuLat.dir/src/NuLatRun.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/NuLat.dir/src/NuLatRun.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jack/Documents/geant4/NuLat/src/NuLatRun.cc -o CMakeFiles/NuLat.dir/src/NuLatRun.cc.s

CMakeFiles/NuLat.dir/src/NuLatRunAction.cc.o: CMakeFiles/NuLat.dir/flags.make
CMakeFiles/NuLat.dir/src/NuLatRunAction.cc.o: ../src/NuLatRunAction.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jack/Documents/geant4/NuLat/build4/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object CMakeFiles/NuLat.dir/src/NuLatRunAction.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/NuLat.dir/src/NuLatRunAction.cc.o -c /home/jack/Documents/geant4/NuLat/src/NuLatRunAction.cc

CMakeFiles/NuLat.dir/src/NuLatRunAction.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/NuLat.dir/src/NuLatRunAction.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jack/Documents/geant4/NuLat/src/NuLatRunAction.cc > CMakeFiles/NuLat.dir/src/NuLatRunAction.cc.i

CMakeFiles/NuLat.dir/src/NuLatRunAction.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/NuLat.dir/src/NuLatRunAction.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jack/Documents/geant4/NuLat/src/NuLatRunAction.cc -o CMakeFiles/NuLat.dir/src/NuLatRunAction.cc.s

CMakeFiles/NuLat.dir/src/NuLatVoxelHit.cc.o: CMakeFiles/NuLat.dir/flags.make
CMakeFiles/NuLat.dir/src/NuLatVoxelHit.cc.o: ../src/NuLatVoxelHit.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jack/Documents/geant4/NuLat/build4/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building CXX object CMakeFiles/NuLat.dir/src/NuLatVoxelHit.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/NuLat.dir/src/NuLatVoxelHit.cc.o -c /home/jack/Documents/geant4/NuLat/src/NuLatVoxelHit.cc

CMakeFiles/NuLat.dir/src/NuLatVoxelHit.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/NuLat.dir/src/NuLatVoxelHit.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jack/Documents/geant4/NuLat/src/NuLatVoxelHit.cc > CMakeFiles/NuLat.dir/src/NuLatVoxelHit.cc.i

CMakeFiles/NuLat.dir/src/NuLatVoxelHit.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/NuLat.dir/src/NuLatVoxelHit.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jack/Documents/geant4/NuLat/src/NuLatVoxelHit.cc -o CMakeFiles/NuLat.dir/src/NuLatVoxelHit.cc.s

CMakeFiles/NuLat.dir/src/NuLatVoxelParameterisation.cc.o: CMakeFiles/NuLat.dir/flags.make
CMakeFiles/NuLat.dir/src/NuLatVoxelParameterisation.cc.o: ../src/NuLatVoxelParameterisation.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jack/Documents/geant4/NuLat/build4/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Building CXX object CMakeFiles/NuLat.dir/src/NuLatVoxelParameterisation.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/NuLat.dir/src/NuLatVoxelParameterisation.cc.o -c /home/jack/Documents/geant4/NuLat/src/NuLatVoxelParameterisation.cc

CMakeFiles/NuLat.dir/src/NuLatVoxelParameterisation.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/NuLat.dir/src/NuLatVoxelParameterisation.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jack/Documents/geant4/NuLat/src/NuLatVoxelParameterisation.cc > CMakeFiles/NuLat.dir/src/NuLatVoxelParameterisation.cc.i

CMakeFiles/NuLat.dir/src/NuLatVoxelParameterisation.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/NuLat.dir/src/NuLatVoxelParameterisation.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jack/Documents/geant4/NuLat/src/NuLatVoxelParameterisation.cc -o CMakeFiles/NuLat.dir/src/NuLatVoxelParameterisation.cc.s

CMakeFiles/NuLat.dir/src/NuLatVoxelSensitiveDetector.cc.o: CMakeFiles/NuLat.dir/flags.make
CMakeFiles/NuLat.dir/src/NuLatVoxelSensitiveDetector.cc.o: ../src/NuLatVoxelSensitiveDetector.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jack/Documents/geant4/NuLat/build4/CMakeFiles --progress-num=$(CMAKE_PROGRESS_14) "Building CXX object CMakeFiles/NuLat.dir/src/NuLatVoxelSensitiveDetector.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/NuLat.dir/src/NuLatVoxelSensitiveDetector.cc.o -c /home/jack/Documents/geant4/NuLat/src/NuLatVoxelSensitiveDetector.cc

CMakeFiles/NuLat.dir/src/NuLatVoxelSensitiveDetector.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/NuLat.dir/src/NuLatVoxelSensitiveDetector.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jack/Documents/geant4/NuLat/src/NuLatVoxelSensitiveDetector.cc > CMakeFiles/NuLat.dir/src/NuLatVoxelSensitiveDetector.cc.i

CMakeFiles/NuLat.dir/src/NuLatVoxelSensitiveDetector.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/NuLat.dir/src/NuLatVoxelSensitiveDetector.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jack/Documents/geant4/NuLat/src/NuLatVoxelSensitiveDetector.cc -o CMakeFiles/NuLat.dir/src/NuLatVoxelSensitiveDetector.cc.s

# Object files for target NuLat
NuLat_OBJECTS = \
"CMakeFiles/NuLat.dir/NuLat.cc.o" \
"CMakeFiles/NuLat.dir/src/NuLatActionInitialization.cc.o" \
"CMakeFiles/NuLat.dir/src/NuLatDetectorConstruction.cc.o" \
"CMakeFiles/NuLat.dir/src/NuLatEventAction.cc.o" \
"CMakeFiles/NuLat.dir/src/NuLatLightGuideParameterisation.cc.o" \
"CMakeFiles/NuLat.dir/src/NuLatPhotoCathodeHit.cc.o" \
"CMakeFiles/NuLat.dir/src/NuLatPhotoCathodeSensitiveDetector.cc.o" \
"CMakeFiles/NuLat.dir/src/NuLatPrimaryGeneratorMessenger.cc.o" \
"CMakeFiles/NuLat.dir/src/NuLatPrimaryParticleGenerator.cc.o" \
"CMakeFiles/NuLat.dir/src/NuLatRun.cc.o" \
"CMakeFiles/NuLat.dir/src/NuLatRunAction.cc.o" \
"CMakeFiles/NuLat.dir/src/NuLatVoxelHit.cc.o" \
"CMakeFiles/NuLat.dir/src/NuLatVoxelParameterisation.cc.o" \
"CMakeFiles/NuLat.dir/src/NuLatVoxelSensitiveDetector.cc.o"

# External object files for target NuLat
NuLat_EXTERNAL_OBJECTS =

NuLat: CMakeFiles/NuLat.dir/NuLat.cc.o
NuLat: CMakeFiles/NuLat.dir/src/NuLatActionInitialization.cc.o
NuLat: CMakeFiles/NuLat.dir/src/NuLatDetectorConstruction.cc.o
NuLat: CMakeFiles/NuLat.dir/src/NuLatEventAction.cc.o
NuLat: CMakeFiles/NuLat.dir/src/NuLatLightGuideParameterisation.cc.o
NuLat: CMakeFiles/NuLat.dir/src/NuLatPhotoCathodeHit.cc.o
NuLat: CMakeFiles/NuLat.dir/src/NuLatPhotoCathodeSensitiveDetector.cc.o
NuLat: CMakeFiles/NuLat.dir/src/NuLatPrimaryGeneratorMessenger.cc.o
NuLat: CMakeFiles/NuLat.dir/src/NuLatPrimaryParticleGenerator.cc.o
NuLat: CMakeFiles/NuLat.dir/src/NuLatRun.cc.o
NuLat: CMakeFiles/NuLat.dir/src/NuLatRunAction.cc.o
NuLat: CMakeFiles/NuLat.dir/src/NuLatVoxelHit.cc.o
NuLat: CMakeFiles/NuLat.dir/src/NuLatVoxelParameterisation.cc.o
NuLat: CMakeFiles/NuLat.dir/src/NuLatVoxelSensitiveDetector.cc.o
NuLat: CMakeFiles/NuLat.dir/build.make
NuLat: /opt/applications/geant4/geant4-v11.0.2-installMT/lib/libG4Tree.so
NuLat: /opt/applications/geant4/geant4-v11.0.2-installMT/lib/libG4FR.so
NuLat: /opt/applications/geant4/geant4-v11.0.2-installMT/lib/libG4GMocren.so
NuLat: /opt/applications/geant4/geant4-v11.0.2-installMT/lib/libG4visHepRep.so
NuLat: /opt/applications/geant4/geant4-v11.0.2-installMT/lib/libG4RayTracer.so
NuLat: /opt/applications/geant4/geant4-v11.0.2-installMT/lib/libG4VRML.so
NuLat: /opt/applications/geant4/geant4-v11.0.2-installMT/lib/libG4OpenGL.so
NuLat: /opt/applications/geant4/geant4-v11.0.2-installMT/lib/libG4gl2ps.so
NuLat: /opt/applications/geant4/geant4-v11.0.2-installMT/lib/libG4ToolsSG.so
NuLat: /opt/applications/geant4/geant4-v11.0.2-installMT/lib/libG4vis_management.so
NuLat: /opt/applications/geant4/geant4-v11.0.2-installMT/lib/libG4modeling.so
NuLat: /opt/applications/geant4/geant4-v11.0.2-installMT/lib/libG4interfaces.so
NuLat: /opt/applications/geant4/geant4-v11.0.2-installMT/lib/libG4persistency.so
NuLat: /opt/applications/geant4/geant4-v11.0.2-installMT/lib/libG4error_propagation.so
NuLat: /opt/applications/geant4/geant4-v11.0.2-installMT/lib/libG4readout.so
NuLat: /opt/applications/geant4/geant4-v11.0.2-installMT/lib/libG4physicslists.so
NuLat: /opt/applications/geant4/geant4-v11.0.2-installMT/lib/libG4run.so
NuLat: /opt/applications/geant4/geant4-v11.0.2-installMT/lib/libG4event.so
NuLat: /opt/applications/geant4/geant4-v11.0.2-installMT/lib/libG4tracking.so
NuLat: /opt/applications/geant4/geant4-v11.0.2-installMT/lib/libG4parmodels.so
NuLat: /opt/applications/geant4/geant4-v11.0.2-installMT/lib/libG4processes.so
NuLat: /opt/applications/geant4/geant4-v11.0.2-installMT/lib/libG4digits_hits.so
NuLat: /opt/applications/geant4/geant4-v11.0.2-installMT/lib/libG4track.so
NuLat: /opt/applications/geant4/geant4-v11.0.2-installMT/lib/libG4particles.so
NuLat: /opt/applications/geant4/geant4-v11.0.2-installMT/lib/libG4geometry.so
NuLat: /opt/applications/geant4/geant4-v11.0.2-installMT/lib/libG4materials.so
NuLat: /opt/applications/geant4/geant4-v11.0.2-installMT/lib/libG4graphics_reps.so
NuLat: /usr/lib/x86_64-linux-gnu/libXm.so
NuLat: /usr/lib/x86_64-linux-gnu/libGL.so
NuLat: /usr/lib/x86_64-linux-gnu/libQt5OpenGL.so.5.12.8
NuLat: /usr/lib/x86_64-linux-gnu/libQt5PrintSupport.so.5.12.8
NuLat: /usr/lib/x86_64-linux-gnu/libQt5Widgets.so.5.12.8
NuLat: /usr/lib/x86_64-linux-gnu/libQt5Gui.so.5.12.8
NuLat: /usr/lib/x86_64-linux-gnu/libQt5Core.so.5.12.8
NuLat: /usr/lib/x86_64-linux-gnu/libXmu.so
NuLat: /usr/lib/x86_64-linux-gnu/libXext.so
NuLat: /usr/lib/x86_64-linux-gnu/libXt.so
NuLat: /usr/lib/x86_64-linux-gnu/libICE.so
NuLat: /usr/lib/x86_64-linux-gnu/libSM.so
NuLat: /usr/lib/x86_64-linux-gnu/libX11.so
NuLat: /usr/lib/x86_64-linux-gnu/libxerces-c.so
NuLat: /opt/applications/geant4/geant4-v11.0.2-installMT/lib/libG4analysis.so
NuLat: /usr/lib/x86_64-linux-gnu/libexpat.so
NuLat: /opt/applications/geant4/geant4-v11.0.2-installMT/lib/libG4zlib.so
NuLat: /opt/applications/geant4/geant4-v11.0.2-installMT/lib/libG4intercoms.so
NuLat: /opt/applications/geant4/geant4-v11.0.2-installMT/lib/libG4global.so
NuLat: /opt/applications/geant4/geant4-v11.0.2-installMT/lib/libG4clhep.so
NuLat: /opt/applications/geant4/geant4-v11.0.2-installMT/lib/libG4ptl.so.2.3.3
NuLat: CMakeFiles/NuLat.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/jack/Documents/geant4/NuLat/build4/CMakeFiles --progress-num=$(CMAKE_PROGRESS_15) "Linking CXX executable NuLat"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/NuLat.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/NuLat.dir/build: NuLat

.PHONY : CMakeFiles/NuLat.dir/build

CMakeFiles/NuLat.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/NuLat.dir/cmake_clean.cmake
.PHONY : CMakeFiles/NuLat.dir/clean

CMakeFiles/NuLat.dir/depend:
	cd /home/jack/Documents/geant4/NuLat/build4 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jack/Documents/geant4/NuLat /home/jack/Documents/geant4/NuLat /home/jack/Documents/geant4/NuLat/build4 /home/jack/Documents/geant4/NuLat/build4 /home/jack/Documents/geant4/NuLat/build4/CMakeFiles/NuLat.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/NuLat.dir/depend

