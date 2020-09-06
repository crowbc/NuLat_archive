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
vector<double> Channel, Energy; //raw data
double Channel_Count, Channel_Energy;

main(){
    ifstream file1("channel.txt2"); //to take data form data file
    if (!file1.good()) {
    	cout << "Unable to find first data file";
    	exit(1);
    }
    while (!file1.eof())
    {
        double temp;
        file1 >> temp;
        Channel.push_back(temp);
    }

    ifstream file2("energy.txt2");
    if (!file2.good()) {
    	cout << "Unable to open second data file";
    	exit(1);
    }
    while (!file2.eof())
    {
        double temp;
        file2 >> temp;
        Energy.push_back(temp);
    }

    for (int i = 0; i < Channel.size(); i++)
        cout << Channel[i] << endl;
    for (int j = 0; j < Energy.size(); j++)
        cout << Energy[j] << endl;
    //check the arrays' alement
    cout<< "Channel.size()" << Channel.size() << "Energy.size()" << Energy.size() <<endl;
    //check the arrays' size


	ofstream outfile;
	outfile.open("result.txt");
	outfile << "Channel" << " " << "Count" << " " << "Energy" <<  endl;
	int n,m;
	int number_of_Channel = 150;
	for(n=0; n<number_of_Channel; n++){
		Channel_Count = 0;
		Channel_Energy = 0;
		for(m=0; m<Channel.size(); m++){
			if(Channel[m]==n){
			Channel_Count++;
			Channel_Energy+=Energy[m];
			}
		}
		outfile << n << "   " << Channel_Count << "   " << Channel_Energy <<  endl;
	}

}
