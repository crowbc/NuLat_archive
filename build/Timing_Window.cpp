using namespace std;
#include <iostream>
#include <iomanip>   // this is required to use "setprecision" below
#include <fstream>
#define _USE_MATH_DEFINES
#include <cmath>
#include <cstdio>     // for the  useful old C-standard stuff
#include <cstdlib>
#include <vector>
#include <algorithm>
using namespace std;
//------------------------------------------------------------------------------------------
vector<double> Time, Window; //raw data
//double Channel_Count, Channel_Energy;

main(){
    ifstream file1("t.dat"); //to take data form data file
    if (!file1.good()) {
    	cout << "Unable to find first data file";
    	exit(1);
    }
    while (!file1.eof())
    {
        double temp;
        file1 >> temp;
        Time.push_back(temp);
    }

    Window = Time;

    for (int i = 0; i < Time.size(); i++)
        cout << Time[i] << "  " << Window[i] << endl;
    //check the arrays' alement
    cout<< "Time.size() " << Time.size() <<endl;//102623
    //check the arrays' size

	int maxTime = *max_element(Time.begin(), Time.end());
	cout<< "maxTime " << maxTime <<endl;//34731
	int maxWindow = ceil(maxTime/47.17);
	cout<< "maxWindow " << maxWindow <<endl;//737

	ofstream outfile;
	outfile.open("Window.dat");

	int n,m;
	for(n=0; n<maxWindow; n++){//0 //1
	 	for(m=0; m<Time.size(); m++){
			if((Time[m]>47.17*n) && (Time[m]<47.17*(n+1))){
				Window[m]=n+1;//[1, , ,1,1,1, , ,1,1,1,1] //[1,2,2,1,1,1, , ,1,1,1,1]
	 		}
	 	}
	 }

	for(m=0; m<Time.size()-1; m++){
	 	outfile << m << "   " << Time[m] << "   " << Window[m] << endl;
	}

}
