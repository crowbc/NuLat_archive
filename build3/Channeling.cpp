using namespace std;
#include <iostream>
#include <iomanip>   // this is required to use "setprecision" below
#include <fstream>
#define _USE_MATH_DEFINES
#include <cmath>
#include <cstdio>     // for the  useful old C-standard stuff
#include <cstdlib>
#include <vector>
using namespace std;
//------------------------------------------------------------------------------------------
vector<double> PositionX, PositionY, PositionZ; //raw data
vector<double> PMTX, PMTY, PMTZ; //raw data
vector<double> Channel;

//double Channel_Count, Channel_Energy;
int main(){
    ifstream file1("PositionX.dat"); //to take data form data file
    if (!file1.good()) {
    	cout << "Unable to find first data file";
    	exit(1);
    }
    while (!file1.eof())
    {
        double temp;
        file1 >> temp;
        PositionX.push_back(temp);
    }

    ifstream file2("PositionY.dat");
    if (!file2.good()) {
    	cout << "Unable to open second data file";
    	exit(1);
    }
    while (!file2.eof())
    {
        double temp;
        file2 >> temp;
        PositionY.push_back(temp);
    }

    ifstream file3("PositionZ.dat");
    if (!file3.good()) {
    	cout << "Unable to open third data file";
    	exit(1);
    }
    while (!file3.eof())
    {
        double temp;
        file3 >> temp;
        PositionZ.push_back(temp);
    }

    for (int i = 0; i < PositionX.size(); i++)
        cout << PositionX[i] << endl;
    for (int j = 0; j < PositionY.size(); j++)
        cout << PositionY[j] << endl;
    for (int k = 0; k < PositionY.size(); k++)
        cout << PositionZ[k] << endl;
    //check the arrays' alement

    PMTX = PositionX; PMTY = PositionX; PMTZ = PositionX; Channel = PositionX;

    cout<< "PositionX.size()" << PositionX.size()
    << "PositionY.size()" << PositionY.size()
    << "PositionZ.size()" << PositionZ.size()
    << "PMTX.sizw()" << PMTX.size()
    << "PMTY.sizw()" << PMTX.size()
    << "PMTY.sizw()" << PMTX.size()
    << "Channel.size()" << Channel.size()
    <<endl;
    //check the arrays' size

//==============================================================================

  for (int n = 0; n < PositionX.size(); n++) {
  if (PositionX[n] < -158.6865) { PMTX[n] = 0; }
  else if (PositionX[n] > -158.6865 && PositionX[n] < -95.1865) { PMTX[n] = 1; }
  else if (PositionX[n] > -95.1865 && PositionX[n] < -31.6865) { PMTX[n] = 2; }
  else if (PositionX[n] > -31.6865 && PositionX[n] < 31.6865) { PMTX[n] = 3; }
  else if (PositionX[n] > 31.6865 && PositionX[n] < 95.1865) { PMTX[n] = 4; }
  else if (PositionX[n] > 95.1865 && PositionX[n] < 158.6865) { PMTX[n] = 5; }
  else if (PositionX[n] > 158.6865) { PMTX[n] = 6; }
  else { PMTX[n] = 999; }

  if (PositionY[n] < -158.6865) { PMTY[n] = 0; }
  else if (PositionY[n] > -158.6865 && PositionY[n] < -95.1865) { PMTY[n] = 1; }
  else if (PositionY[n] > -95.1865 && PositionY[n] < -31.6865) { PMTY[n] = 2; }
  else if (PositionY[n] > -31.6865 && PositionY[n] < 31.6865) { PMTY[n] = 3; }
  else if (PositionY[n] > 31.6865 && PositionY[n] < 95.1865) { PMTY[n] = 4; }
  else if (PositionY[n] > 95.1865 && PositionY[n] < 158.6865) { PMTY[n] = 5; }
  else if (PositionY[n] > 158.6865) { PMTY[n] = 6; }
  else { PMTY[n] = 999; }

  if (PositionZ[n] < -158.6865) { PMTZ[n] = 0; }
  else if (PositionZ[n] > -158.6865 && PositionZ[n] < -95.1865) { PMTZ[n] = 1; }
  else if (PositionZ[n] > -95.1865 && PositionZ[n] < -31.6865) { PMTZ[n] = 2; }
  else if (PositionZ[n] > -31.6865 && PositionZ[n] < 31.6865) { PMTZ[n] = 3; }
  else if (PositionZ[n] > 31.6865 && PositionZ[n] < 95.1865) { PMTZ[n] = 4; }
  else if (PositionZ[n] > 95.1865 && PositionZ[n] < 158.6865) { PMTZ[n] = 5; }
  else if (PositionZ[n] > 158.6865) { PMTZ[n] = 6; }
  else { PMTZ[n] = 999; }
  }

  for (int m = 0; m < PositionX.size(); m++) {
  if (PMTX[m] == 0 && PMTY[m] == 1 && PMTZ[m] == 1) { Channel[m] = 0; }
  else if (PMTX[m] == 0 && PMTY[m] == 2 && PMTZ[m] == 1) { Channel[m] = 1; }
  else if (PMTX[m] == 0 && PMTY[m] == 3 && PMTZ[m] == 1) { Channel[m] = 2; }
  else if (PMTX[m] == 0 && PMTY[m] == 4 && PMTZ[m] == 1) { Channel[m] = 3; }
  else if (PMTX[m] == 0 && PMTY[m] == 5 && PMTZ[m] == 1) { Channel[m] = 4; }
  else if (PMTX[m] == 0 && PMTY[m] == 1 && PMTZ[m] == 2) { Channel[m] = 5; }
  else if (PMTX[m] == 0 && PMTY[m] == 2 && PMTZ[m] == 2) { Channel[m] = 6; }
  else if (PMTX[m] == 0 && PMTY[m] == 3 && PMTZ[m] == 2) { Channel[m] = 7; }
  else if (PMTX[m] == 0 && PMTY[m] == 4 && PMTZ[m] == 2) { Channel[m] = 8; }
  else if (PMTX[m] == 0 && PMTY[m] == 5 && PMTZ[m] == 2) { Channel[m] = 9; }
  else if (PMTX[m] == 0 && PMTY[m] == 1 && PMTZ[m] == 3) { Channel[m] = 10; }
  else if (PMTX[m] == 0 && PMTY[m] == 2 && PMTZ[m] == 3) { Channel[m] = 11; }
  else if (PMTX[m] == 0 && PMTY[m] == 3 && PMTZ[m] == 3) { Channel[m] = 12; }
  else if (PMTX[m] == 0 && PMTY[m] == 4 && PMTZ[m] == 3) { Channel[m] = 13; }
  else if (PMTX[m] == 0 && PMTY[m] == 5 && PMTZ[m] == 3) { Channel[m] = 14; }
  else if (PMTX[m] == 0 && PMTY[m] == 1 && PMTZ[m] == 4) { Channel[m] = 15; }
  else if (PMTX[m] == 0 && PMTY[m] == 2 && PMTZ[m] == 4) { Channel[m] = 16; }
  else if (PMTX[m] == 0 && PMTY[m] == 3 && PMTZ[m] == 4) { Channel[m] = 17; }
  else if (PMTX[m] == 0 && PMTY[m] == 4 && PMTZ[m] == 4) { Channel[m] = 18; }
  else if (PMTX[m] == 0 && PMTY[m] == 5 && PMTZ[m] == 4) { Channel[m] = 19; }
  else if (PMTX[m] == 0 && PMTY[m] == 1 && PMTZ[m] == 5) { Channel[m] = 20; }
  else if (PMTX[m] == 0 && PMTY[m] == 2 && PMTZ[m] == 5) { Channel[m] = 21; }
  else if (PMTX[m] == 0 && PMTY[m] == 3 && PMTZ[m] == 5) { Channel[m] = 22; }
  else if (PMTX[m] == 0 && PMTY[m] == 4 && PMTZ[m] == 5) { Channel[m] = 23; }
  else if (PMTX[m] == 0 && PMTY[m] == 5 && PMTZ[m] == 5) { Channel[m] = 24; }

  else if (PMTX[m] == 6 && PMTY[m] == 1 && PMTZ[m] == 1) { Channel[m] = 25; }
  else if (PMTX[m] == 6 && PMTY[m] == 2 && PMTZ[m] == 1) { Channel[m] = 26; }
  else if (PMTX[m] == 6 && PMTY[m] == 3 && PMTZ[m] == 1) { Channel[m] = 27; }
  else if (PMTX[m] == 6 && PMTY[m] == 4 && PMTZ[m] == 1) { Channel[m] = 28; }
  else if (PMTX[m] == 6 && PMTY[m] == 5 && PMTZ[m] == 1) { Channel[m] = 29; }
  else if (PMTX[m] == 6 && PMTY[m] == 1 && PMTZ[m] == 2) { Channel[m] = 30; }
  else if (PMTX[m] == 6 && PMTY[m] == 2 && PMTZ[m] == 2) { Channel[m] = 31; }
  else if (PMTX[m] == 6 && PMTY[m] == 3 && PMTZ[m] == 2) { Channel[m] = 32; }
  else if (PMTX[m] == 6 && PMTY[m] == 4 && PMTZ[m] == 2) { Channel[m] = 33; }
  else if (PMTX[m] == 6 && PMTY[m] == 5 && PMTZ[m] == 2) { Channel[m] = 34; }
  else if (PMTX[m] == 6 && PMTY[m] == 1 && PMTZ[m] == 3) { Channel[m] = 35; }
  else if (PMTX[m] == 6 && PMTY[m] == 2 && PMTZ[m] == 3) { Channel[m] = 36; }
  else if (PMTX[m] == 6 && PMTY[m] == 3 && PMTZ[m] == 3) { Channel[m] = 37; }
  else if (PMTX[m] == 6 && PMTY[m] == 4 && PMTZ[m] == 3) { Channel[m] = 38; }
  else if (PMTX[m] == 6 && PMTY[m] == 5 && PMTZ[m] == 3) { Channel[m] = 39; }
  else if (PMTX[m] == 6 && PMTY[m] == 1 && PMTZ[m] == 4) { Channel[m] = 40; }
  else if (PMTX[m] == 6 && PMTY[m] == 2 && PMTZ[m] == 4) { Channel[m] = 41; }
  else if (PMTX[m] == 6 && PMTY[m] == 3 && PMTZ[m] == 4) { Channel[m] = 42; }
  else if (PMTX[m] == 6 && PMTY[m] == 4 && PMTZ[m] == 4) { Channel[m] = 43; }
  else if (PMTX[m] == 6 && PMTY[m] == 5 && PMTZ[m] == 4) { Channel[m] = 44; }
  else if (PMTX[m] == 6 && PMTY[m] == 1 && PMTZ[m] == 5) { Channel[m] = 45; }
  else if (PMTX[m] == 6 && PMTY[m] == 2 && PMTZ[m] == 5) { Channel[m] = 46; }
  else if (PMTX[m] == 6 && PMTY[m] == 3 && PMTZ[m] == 5) { Channel[m] = 47; }
  else if (PMTX[m] == 6 && PMTY[m] == 4 && PMTZ[m] == 5) { Channel[m] = 48; }
  else if (PMTX[m] == 6 && PMTY[m] == 5 && PMTZ[m] == 5) { Channel[m] = 49; }

  else if (PMTX[m] == 1 && PMTY[m] == 0 && PMTZ[m] == 1) { Channel[m] = 50; }
  else if (PMTX[m] == 2 && PMTY[m] == 0 && PMTZ[m] == 1) { Channel[m] = 51; }
  else if (PMTX[m] == 3 && PMTY[m] == 0 && PMTZ[m] == 1) { Channel[m] = 52; }
  else if (PMTX[m] == 4 && PMTY[m] == 0 && PMTZ[m] == 1) { Channel[m] = 53; }
  else if (PMTX[m] == 5 && PMTY[m] == 0 && PMTZ[m] == 1) { Channel[m] = 54; }
  else if (PMTX[m] == 1 && PMTY[m] == 0 && PMTZ[m] == 2) { Channel[m] = 55; }
  else if (PMTX[m] == 2 && PMTY[m] == 0 && PMTZ[m] == 2) { Channel[m] = 56; }
  else if (PMTX[m] == 3 && PMTY[m] == 0 && PMTZ[m] == 2) { Channel[m] = 57; }
  else if (PMTX[m] == 4 && PMTY[m] == 0 && PMTZ[m] == 2) { Channel[m] = 58; }
  else if (PMTX[m] == 5 && PMTY[m] == 0 && PMTZ[m] == 2) { Channel[m] = 59; }
  else if (PMTX[m] == 1 && PMTY[m] == 0 && PMTZ[m] == 3) { Channel[m] = 60; }
  else if (PMTX[m] == 2 && PMTY[m] == 0 && PMTZ[m] == 3) { Channel[m] = 61; }
  else if (PMTX[m] == 3 && PMTY[m] == 0 && PMTZ[m] == 3) { Channel[m] = 62; }
  else if (PMTX[m] == 4 && PMTY[m] == 0 && PMTZ[m] == 3) { Channel[m] = 63; }
  else if (PMTX[m] == 5 && PMTY[m] == 0 && PMTZ[m] == 3) { Channel[m] = 64; }
  else if (PMTX[m] == 1 && PMTY[m] == 0 && PMTZ[m] == 4) { Channel[m] = 65; }
  else if (PMTX[m] == 2 && PMTY[m] == 0 && PMTZ[m] == 4) { Channel[m] = 66; }
  else if (PMTX[m] == 3 && PMTY[m] == 0 && PMTZ[m] == 4) { Channel[m] = 67; }
  else if (PMTX[m] == 4 && PMTY[m] == 0 && PMTZ[m] == 4) { Channel[m] = 68; }
  else if (PMTX[m] == 5 && PMTY[m] == 0 && PMTZ[m] == 4) { Channel[m] = 69; }
  else if (PMTX[m] == 1 && PMTY[m] == 0 && PMTZ[m] == 5) { Channel[m] = 70; }
  else if (PMTX[m] == 2 && PMTY[m] == 0 && PMTZ[m] == 5) { Channel[m] = 71; }
  else if (PMTX[m] == 3 && PMTY[m] == 0 && PMTZ[m] == 5) { Channel[m] = 72; }
  else if (PMTX[m] == 4 && PMTY[m] == 0 && PMTZ[m] == 5) { Channel[m] = 73; }
  else if (PMTX[m] == 5 && PMTY[m] == 0 && PMTZ[m] == 5) { Channel[m] = 74; }

  else if (PMTX[m] == 1 && PMTY[m] == 6 && PMTZ[m] == 1) { Channel[m] = 75; }
  else if (PMTX[m] == 2 && PMTY[m] == 6 && PMTZ[m] == 1) { Channel[m] = 76; }
  else if (PMTX[m] == 3 && PMTY[m] == 6 && PMTZ[m] == 1) { Channel[m] = 77; }
  else if (PMTX[m] == 4 && PMTY[m] == 6 && PMTZ[m] == 1) { Channel[m] = 78; }
  else if (PMTX[m] == 5 && PMTY[m] == 6 && PMTZ[m] == 1) { Channel[m] = 79; }
  else if (PMTX[m] == 1 && PMTY[m] == 6 && PMTZ[m] == 2) { Channel[m] = 80; }
  else if (PMTX[m] == 2 && PMTY[m] == 6 && PMTZ[m] == 2) { Channel[m] = 81; }
  else if (PMTX[m] == 3 && PMTY[m] == 6 && PMTZ[m] == 2) { Channel[m] = 82; }
  else if (PMTX[m] == 4 && PMTY[m] == 6 && PMTZ[m] == 2) { Channel[m] = 83; }
  else if (PMTX[m] == 5 && PMTY[m] == 6 && PMTZ[m] == 2) { Channel[m] = 84; }
  else if (PMTX[m] == 1 && PMTY[m] == 6 && PMTZ[m] == 3) { Channel[m] = 85; }
  else if (PMTX[m] == 2 && PMTY[m] == 6 && PMTZ[m] == 3) { Channel[m] = 86; }
  else if (PMTX[m] == 3 && PMTY[m] == 6 && PMTZ[m] == 3) { Channel[m] = 87; }
  else if (PMTX[m] == 4 && PMTY[m] == 6 && PMTZ[m] == 3) { Channel[m] = 88; }
  else if (PMTX[m] == 5 && PMTY[m] == 6 && PMTZ[m] == 3) { Channel[m] = 89; }
  else if (PMTX[m] == 1 && PMTY[m] == 6 && PMTZ[m] == 4) { Channel[m] = 90; }
  else if (PMTX[m] == 2 && PMTY[m] == 6 && PMTZ[m] == 4) { Channel[m] = 91; }
  else if (PMTX[m] == 3 && PMTY[m] == 6 && PMTZ[m] == 4) { Channel[m] = 92; }
  else if (PMTX[m] == 4 && PMTY[m] == 6 && PMTZ[m] == 4) { Channel[m] = 93; }
  else if (PMTX[m] == 5 && PMTY[m] == 6 && PMTZ[m] == 4) { Channel[m] = 94; }
  else if (PMTX[m] == 1 && PMTY[m] == 6 && PMTZ[m] == 5) { Channel[m] = 95; }
  else if (PMTX[m] == 3 && PMTY[m] == 6 && PMTZ[m] == 5) { Channel[m] = 97; }
  else if (PMTX[m] == 2 && PMTY[m] == 6 && PMTZ[m] == 5) { Channel[m] = 96; }
  else if (PMTX[m] == 4 && PMTY[m] == 6 && PMTZ[m] == 5) { Channel[m] = 98; }
  else if (PMTX[m] == 5 && PMTY[m] == 6 && PMTZ[m] == 5) { Channel[m] = 99; }

  else if (PMTX[m] == 1 && PMTY[m] == 1 && PMTZ[m] == 0) { Channel[m] = 100; }
  else if (PMTX[m] == 1 && PMTY[m] == 2 && PMTZ[m] == 0) { Channel[m] = 101; }
  else if (PMTX[m] == 1 && PMTY[m] == 3 && PMTZ[m] == 0) { Channel[m] = 102; }
  else if (PMTX[m] == 1 && PMTY[m] == 4 && PMTZ[m] == 0) { Channel[m] = 103; }
  else if (PMTX[m] == 1 && PMTY[m] == 5 && PMTZ[m] == 0) { Channel[m] = 104; }
  else if (PMTX[m] == 2 && PMTY[m] == 1 && PMTZ[m] == 0) { Channel[m] = 105; }
  else if (PMTX[m] == 2 && PMTY[m] == 2 && PMTZ[m] == 0) { Channel[m] = 106; }
  else if (PMTX[m] == 2 && PMTY[m] == 3 && PMTZ[m] == 0) { Channel[m] = 107; }
  else if (PMTX[m] == 2 && PMTY[m] == 4 && PMTZ[m] == 0) { Channel[m] = 108; }
  else if (PMTX[m] == 2 && PMTY[m] == 5 && PMTZ[m] == 0) { Channel[m] = 109; }
  else if (PMTX[m] == 3 && PMTY[m] == 1 && PMTZ[m] == 0) { Channel[m] = 110; }
  else if (PMTX[m] == 3 && PMTY[m] == 2 && PMTZ[m] == 0) { Channel[m] = 111; }
  else if (PMTX[m] == 3 && PMTY[m] == 3 && PMTZ[m] == 0) { Channel[m] = 112; }
  else if (PMTX[m] == 3 && PMTY[m] == 4 && PMTZ[m] == 0) { Channel[m] = 113; }
  else if (PMTX[m] == 3 && PMTY[m] == 5 && PMTZ[m] == 0) { Channel[m] = 114; }
  else if (PMTX[m] == 4 && PMTY[m] == 1 && PMTZ[m] == 0) { Channel[m] = 115; }
  else if (PMTX[m] == 4 && PMTY[m] == 2 && PMTZ[m] == 0) { Channel[m] = 116; }
  else if (PMTX[m] == 4 && PMTY[m] == 3 && PMTZ[m] == 0) { Channel[m] = 117; }
  else if (PMTX[m] == 4 && PMTY[m] == 4 && PMTZ[m] == 0) { Channel[m] = 118; }
  else if (PMTX[m] == 4 && PMTY[m] == 5 && PMTZ[m] == 0) { Channel[m] = 119; }
  else if (PMTX[m] == 5 && PMTY[m] == 1 && PMTZ[m] == 0) { Channel[m] = 120; }
  else if (PMTX[m] == 5 && PMTY[m] == 2 && PMTZ[m] == 0) { Channel[m] = 121; }
  else if (PMTX[m] == 5 && PMTY[m] == 3 && PMTZ[m] == 0) { Channel[m] = 122; }
  else if (PMTX[m] == 5 && PMTY[m] == 4 && PMTZ[m] == 0) { Channel[m] = 123; }
  else if (PMTX[m] == 5 && PMTY[m] == 5 && PMTZ[m] == 0) { Channel[m] = 124; }

  else if (PMTX[m] == 1 && PMTY[m] == 1 && PMTZ[m] == 6) { Channel[m] = 125; }
  else if (PMTX[m] == 1 && PMTY[m] == 2 && PMTZ[m] == 6) { Channel[m] = 126; }
  else if (PMTX[m] == 1 && PMTY[m] == 3 && PMTZ[m] == 6) { Channel[m] = 127; }
  else if (PMTX[m] == 1 && PMTY[m] == 4 && PMTZ[m] == 6) { Channel[m] = 128; }
  else if (PMTX[m] == 1 && PMTY[m] == 5 && PMTZ[m] == 6) { Channel[m] = 129; }
  else if (PMTX[m] == 2 && PMTY[m] == 1 && PMTZ[m] == 6) { Channel[m] = 130; }
  else if (PMTX[m] == 2 && PMTY[m] == 2 && PMTZ[m] == 6) { Channel[m] = 131; }
  else if (PMTX[m] == 2 && PMTY[m] == 3 && PMTZ[m] == 6) { Channel[m] = 132; }
  else if (PMTX[m] == 2 && PMTY[m] == 4 && PMTZ[m] == 6) { Channel[m] = 133; }
  else if (PMTX[m] == 2 && PMTY[m] == 5 && PMTZ[m] == 6) { Channel[m] = 134; }
  else if (PMTX[m] == 3 && PMTY[m] == 1 && PMTZ[m] == 6) { Channel[m] = 135; }
  else if (PMTX[m] == 3 && PMTY[m] == 2 && PMTZ[m] == 6) { Channel[m] = 136; }
  else if (PMTX[m] == 3 && PMTY[m] == 3 && PMTZ[m] == 6) { Channel[m] = 137; }
  else if (PMTX[m] == 3 && PMTY[m] == 4 && PMTZ[m] == 6) { Channel[m] = 138; }
  else if (PMTX[m] == 3 && PMTY[m] == 5 && PMTZ[m] == 6) { Channel[m] = 139; }
  else if (PMTX[m] == 4 && PMTY[m] == 1 && PMTZ[m] == 6) { Channel[m] = 140; }
  else if (PMTX[m] == 4 && PMTY[m] == 2 && PMTZ[m] == 6) { Channel[m] = 141; }
  else if (PMTX[m] == 4 && PMTY[m] == 3 && PMTZ[m] == 6) { Channel[m] = 142; }
  else if (PMTX[m] == 4 && PMTY[m] == 4 && PMTZ[m] == 6) { Channel[m] = 143; }
  else if (PMTX[m] == 4 && PMTY[m] == 5 && PMTZ[m] == 6) { Channel[m] = 144; }
  else if (PMTX[m] == 5 && PMTY[m] == 1 && PMTZ[m] == 6) { Channel[m] = 145; }
  else if (PMTX[m] == 5 && PMTY[m] == 2 && PMTZ[m] == 6) { Channel[m] = 146; }
  else if (PMTX[m] == 5 && PMTY[m] == 3 && PMTZ[m] == 6) { Channel[m] = 147; }
  else if (PMTX[m] == 5 && PMTY[m] == 4 && PMTZ[m] == 6) { Channel[m] = 148; }
  else if (PMTX[m] == 5 && PMTY[m] == 5 && PMTZ[m] == 6) { Channel[m] = 149; }

  else { Channel[m] = 999; }
  }



  ofstream outfile;
	outfile.open("Channel.dat");

	for (int l = 0; l < Channel.size()-1; l++){
		 	outfile << l << "   " << Channel[l] << endl;
	}

}
