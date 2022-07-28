// using namespace std;
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
vector<double> Channel; //raw data
double Ch0, Ch1, Ch2, Ch3, Ch4, Ch5, Ch6, Ch7, Ch8, Ch9, Ch10,
Ch11, Ch12, Ch13, Ch14, Ch15, Ch16, Ch17, Ch18, Ch19, Ch20,
Ch21, Ch22, Ch23, Ch24, Ch25, Ch26, Ch27, Ch28, Ch29, Ch30,
Ch31, Ch32, Ch33, Ch34, Ch35, Ch36, Ch37, Ch38, Ch39, Ch40,
Ch41, Ch42, Ch43, Ch44, Ch45, Ch46, Ch47, Ch48, Ch49, Ch50,
Ch51, Ch52, Ch53, Ch54, Ch55, Ch56, Ch57, Ch58, Ch59, Ch60,
Ch61, Ch62, Ch63, Ch64, Ch65, Ch66, Ch67, Ch68, Ch69, Ch70,
Ch71, Ch72, Ch73, Ch74, Ch75, Ch76, Ch77, Ch78, Ch79, Ch80,
Ch81, Ch82, Ch83, Ch84, Ch85, Ch86, Ch87, Ch88, Ch89, Ch90,
Ch91, Ch92, Ch93, Ch94, Ch95, Ch96, Ch97, Ch98, Ch99, Ch100,
Ch101, Ch102, Ch103, Ch104, Ch105, Ch106, Ch107, Ch108, Ch109, Ch110,
Ch111, Ch112, Ch113, Ch114, Ch115, Ch116, Ch117, Ch118, Ch119, Ch120,
Ch121, Ch122, Ch123, Ch124, Ch125, Ch126, Ch127, Ch128, Ch129, Ch130,
Ch131, Ch132, Ch133, Ch134, Ch135, Ch136, Ch137, Ch138, Ch139, Ch140,
Ch141, Ch142, Ch143, Ch144, Ch145, Ch146, Ch147, Ch148, Ch149 = 0;

main(){
    ifstream file1("Channel++.dat"); //to take data form data file
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



	ofstream outfile;
	outfile.open("result3.txt");
  outfile << " Ch0 " << " Ch1 " << " Ch2 " << " Ch3 " << " Ch4 " << " Ch5 " << " Ch6 " << " Ch7 " << " Ch8 " << " Ch9 " << " Ch10 " << " Ch11 " << " Ch12 " << " Ch13 " << " Ch14 " << " Ch15 " << " Ch16 " << " Ch17 " << " Ch18 " << " Ch19 " << " Ch20 "
  << " Ch21 " << " Ch22 " << " Ch23 " << " Ch24 " << " Ch25 " << " Ch26 " << " Ch27 " << " Ch28 " << " Ch29 " << " Ch30 " << " Ch31 " << " Ch32 " << " Ch33 " << " Ch34 " << " Ch35 " << " Ch36 " << " Ch37 " << " Ch38 " << " Ch39 " << " Ch40 "
  << " Ch41 " << " Ch42 " << " Ch43 " << " Ch44 " << " Ch45 " << " Ch46 " << " Ch47 " << " Ch48 " << " Ch49 " << " Ch50 " << " Ch51 " << " Ch52 " << " Ch53 " << " Ch54 " << " Ch55 " << " Ch56 " << " Ch57 " << " Ch58 " << " Ch59 " << " Ch60 "
  << " Ch61 " << " Ch62 " << " Ch63 " << " Ch64 " << " Ch65 " << " Ch66 " << " Ch67 " << " Ch68 " << " Ch69 " << " Ch70 " << " Ch71 " << " Ch72 " << " Ch73 " << " Ch74 " << " Ch75 " << " Ch76 " << " Ch77 " << " Ch78 " << " Ch79 " << " Ch80 "
  << " Ch81 " << " Ch82 " << " Ch83 " << " Ch84 " << " Ch85 " << " Ch86 " << " Ch87 " << " Ch88 " << " Ch89 " << " Ch90 " << " Ch91 " << " Ch92 " << " Ch93 " << " Ch94 " << " Ch95 " << " Ch96 " << " Ch97 " << " Ch98 " << " Ch99 " << " Ch100 "
  << " Ch101 " << " Ch102 " << " Ch103 " << " Ch104 " << " Ch105 " << " Ch106 " << " Ch107 " << " Ch108 " << " Ch109 " << " Ch110 " << " Ch111 " << " Ch112 " << " Ch113 " << " Ch114 " << " Ch115 " << " Ch116 " << " Ch117 " << " Ch118 " << " Ch119 " << " Ch120 "
  << " Ch121 " << " Ch122 " << " Ch123 " << " Ch124 " << " Ch125 " << " Ch126 " << " Ch127 " << " Ch128 " << " Ch129 " << " Ch130 " << " Ch131 " << " Ch132 " << " Ch133 " << " Ch134 " << " Ch135 " << " Ch136 " << " Ch137 " << " Ch138 " << " Ch139 " << " Ch140 "
  << " Ch141 " << " Ch142 " << " Ch143 " << " Ch144 " << " Ch145 " << " Ch146 " << " Ch147 " << " Ch148 " << " Ch149 " << endl;

	// int number_of_Channel = 150;

      for (int i = 0; i < Channel.size(); i++)
      cout << Channel[i] << endl;

		  for (int m = 0; m < Channel.size(); m++){
          if(Channel[m]==0)
          { Ch0++; }
          else if(Channel[m]==1)
          { Ch1++; }
          else if(Channel[m]==2)
          { Ch2++; }
          else if(Channel[m]==3)
          { Ch3++; }
          else if(Channel[m]==4)
          { Ch4++; }
          else if(Channel[m]==5)
          { Ch5++; }
          else if(Channel[m]==6)
          { Ch6++; }
          else if(Channel[m]==7)
          { Ch7++; }
          else if(Channel[m]==8)
          { Ch8++; }
          else if(Channel[m]==9)
          { Ch9++; }
          else if(Channel[m]==10)
          { Ch10++; }
          else if(Channel[m]==11)
          { Ch11++; }
          else if(Channel[m]==12)
          { Ch12++; }
          else if(Channel[m]==13)
          { Ch13++; }
          else if(Channel[m]==14)
          { Ch14++; }
          else if(Channel[m]==15)
          { Ch15++; }
          else if(Channel[m]==16)
          { Ch16++; }
          else if(Channel[m]==17)
          { Ch17++; }
          else if(Channel[m]==18)
          { Ch18++; }
          else if(Channel[m]==19)
          { Ch19++; }
          else if(Channel[m]==20)
          { Ch20++; }
          else if(Channel[m]==21)
          { Ch21++; }
          else if(Channel[m]==22)
          { Ch22++; }
          else if(Channel[m]==23)
          { Ch23++; }
          else if(Channel[m]==24)
          { Ch24++; }
          else if(Channel[m]==25)
          { Ch25++; }
          else if(Channel[m]==26)
          { Ch26++; }
          else if(Channel[m]==27)
          { Ch27++; }
          else if(Channel[m]==28)
          { Ch28++; }
          else if(Channel[m]==29)
          { Ch29++; }
          else if(Channel[m]==30)
          { Ch30++; }
          else if(Channel[m]==31)
          { Ch31++; }
          else if(Channel[m]==32)
          { Ch32++; }
          else if(Channel[m]==33)
          { Ch33++; }
          else if(Channel[m]==34)
          { Ch34++; }
          else if(Channel[m]==35)
          { Ch35++; }
          else if(Channel[m]==36)
          { Ch36++; }
          else if(Channel[m]==37)
          { Ch37++; }
          else if(Channel[m]==38)
          { Ch38++; }
          else if(Channel[m]==39)
          { Ch39++; }
          else if(Channel[m]==40)
          { Ch40++; }
          else if(Channel[m]==41)
          { Ch41++; }
          else if(Channel[m]==42)
          { Ch42++; }
          else if(Channel[m]==43)
          { Ch43++; }
          else if(Channel[m]==44)
          { Ch44++; }
          else if(Channel[m]==45)
          { Ch45++; }
          else if(Channel[m]==46)
          { Ch46++; }
          else if(Channel[m]==47)
          { Ch47++; }
          else if(Channel[m]==48)
          { Ch48++; }
          else if(Channel[m]==49)
          { Ch49++; }
          else if(Channel[m]==50)
          { Ch50++; }
          else if(Channel[m]==51)
          { Ch51++; }
          else if(Channel[m]==52)
          { Ch52++; }
          else if(Channel[m]==53)
          { Ch53++; }
          else if(Channel[m]==54)
          { Ch54++; }
          else if(Channel[m]==55)
          { Ch55++; }
          else if(Channel[m]==56)
          { Ch56++; }
          else if(Channel[m]==57)
          { Ch57++; }
          else if(Channel[m]==58)
          { Ch58++; }
          else if(Channel[m]==59)
          { Ch59++; }
          else if(Channel[m]==60)
          { Ch60++; }
          else if(Channel[m]==61)
          { Ch61++; }
          else if(Channel[m]==62)
          { Ch62++; }
          else if(Channel[m]==63)
          { Ch63++; }
          else if(Channel[m]==64)
          { Ch64++; }
          else if(Channel[m]==65)
          { Ch65++; }
          else if(Channel[m]==66)
          { Ch66++; }
          else if(Channel[m]==67)
          { Ch67++; }
          else if(Channel[m]==68)
          { Ch68++; }
          else if(Channel[m]==69)
          { Ch69++; }
          else if(Channel[m]==70)
          { Ch70++; }
          else if(Channel[m]==71)
          { Ch71++; }
          else if(Channel[m]==72)
          { Ch72++; }
          else if(Channel[m]==73)
          { Ch73++; }
          else if(Channel[m]==74)
          { Ch74++; }
          else if(Channel[m]==75)
          { Ch75++; }
          else if(Channel[m]==76)
          { Ch76++; }
          else if(Channel[m]==77)
          { Ch77++; }
          else if(Channel[m]==78)
          { Ch78++; }
          else if(Channel[m]==79)
          { Ch79++; }
          else if(Channel[m]==80)
          { Ch80++; }
          else if(Channel[m]==81)
          { Ch81++; }
          else if(Channel[m]==82)
          { Ch82++; }
          else if(Channel[m]==83)
          { Ch83++; }
          else if(Channel[m]==84)
          { Ch84++; }
          else if(Channel[m]==85)
          { Ch85++; }
          else if(Channel[m]==86)
          { Ch86++; }
          else if(Channel[m]==87)
          { Ch87++; }
          else if(Channel[m]==88)
          { Ch88++; }
          else if(Channel[m]==89)
          { Ch89++; }
          else if(Channel[m]==90)
          { Ch90++; }
          else if(Channel[m]==91)
          { Ch91++; }
          else if(Channel[m]==92)
          { Ch92++; }
          else if(Channel[m]==93)
          { Ch93++; }
          else if(Channel[m]==94)
          { Ch94++; }
          else if(Channel[m]==95)
          { Ch95++; }
          else if(Channel[m]==96)
          { Ch96++; }
          else if(Channel[m]==97)
          { Ch97++; }
          else if(Channel[m]==98)
          { Ch98++; }
          else if(Channel[m]==99)
          { Ch99++; }
          else if(Channel[m]==100)
          { Ch100++; }
          else if(Channel[m]==101)
          { Ch101++; }
          else if(Channel[m]==102)
          { Ch102++; }
          else if(Channel[m]==103)
          { Ch103++; }
          else if(Channel[m]==104)
          { Ch104++; }
          else if(Channel[m]==105)
          { Ch105++; }
          else if(Channel[m]==106)
          { Ch106++; }
          else if(Channel[m]==107)
          { Ch107++; }
          else if(Channel[m]==108)
          { Ch108++; }
          else if(Channel[m]==109)
          { Ch109++; }
          else if(Channel[m]==110)
          { Ch110++; }
          else if(Channel[m]==111)
          { Ch111++; }
          else if(Channel[m]==112)
          { Ch112++; }
          else if(Channel[m]==113)
          { Ch113++; }
          else if(Channel[m]==114)
          { Ch114++; }
          else if(Channel[m]==115)
          { Ch115++; }
          else if(Channel[m]==116)
          { Ch116++; }
          else if(Channel[m]==117)
          { Ch117++; }
          else if(Channel[m]==118)
          { Ch118++; }
          else if(Channel[m]==119)
          { Ch119++; }
          else if(Channel[m]==120)
          { Ch120++; }
          else if(Channel[m]==121)
          { Ch121++; }
          else if(Channel[m]==122)
          { Ch122++; }
          else if(Channel[m]==123)
          { Ch123++; }
          else if(Channel[m]==124)
          { Ch124++; }
          else if(Channel[m]==125)
          { Ch125++; }
          else if(Channel[m]==126)
          { Ch126++; }
          else if(Channel[m]==127)
          { Ch127++; }
          else if(Channel[m]==128)
          { Ch128++; }
          else if(Channel[m]==129)
          { Ch129++; }
          else if(Channel[m]==130)
          { Ch130++; }
          else if(Channel[m]==131)
          { Ch131++; }
          else if(Channel[m]==132)
          { Ch132++; }
          else if(Channel[m]==133)
          { Ch133++; }
          else if(Channel[m]==134)
          { Ch134++; }
          else if(Channel[m]==135)
          { Ch135++; }
          else if(Channel[m]==136)
          { Ch136++; }
          else if(Channel[m]==137)
          { Ch137++; }
          else if(Channel[m]==138)
          { Ch138++; }
          else if(Channel[m]==139)
          { Ch139++; }
          else if(Channel[m]==140)
          { Ch140++; }
          else if(Channel[m]==141)
          { Ch141++; }
          else if(Channel[m]==142)
          { Ch142++; }
          else if(Channel[m]==143)
          { Ch143++; }
          else if(Channel[m]==144)
          { Ch144++; }
          else if(Channel[m]==145)
          { Ch145++; }
          else if(Channel[m]==146)
          { Ch146++; }
          else if(Channel[m]==147)
          { Ch147++; }
          else if(Channel[m]==148)
          { Ch148++; }
          else if(Channel[m]==149)
          { Ch149++; }
          else
          { outfile << "  " << Ch0 << "  " << Ch1 << "  " << Ch2 << "  " << Ch3 << "  " << Ch4 << "  " << Ch5 << "  " << Ch6 << "  " << Ch7 << "  " << Ch8 << "  " << Ch9 << "  " << Ch10 << "  " << Ch11 << "  " << Ch12 << "  " << Ch13 << "  " << Ch14 << "  " << Ch15 << "  " << Ch16 << "  " << Ch17 << "  " << Ch18 << "  " << Ch19 << "  " << Ch20
          << "  " << Ch21 << "  " << Ch22 << "  " << Ch23 << "  " << Ch24 << "  " << Ch25 << "  " << Ch26 << "  " << Ch27 << "  " << Ch28 << "  " << Ch29 << "  " << Ch30 << "  " << Ch31 << "  " << Ch32 << "  " << Ch33 << "  " << Ch34 << "  " << Ch35 << "  " << Ch36 << "  " << Ch37 << "  " << Ch38 << "  " << Ch39 << "  " << Ch40
          << "  " << Ch41 << "  " << Ch42 << "  " << Ch43 << "  " << Ch44 << "  " << Ch45 << "  " << Ch46 << "  " << Ch47 << "  " << Ch48 << "  " << Ch49 << "  " << Ch50 << "  " << Ch51 << "  " << Ch52 << "  " << Ch53 << "  " << Ch54 << "  " << Ch55 << "  " << Ch56 << "  " << Ch57 << "  " << Ch58 << "  " << Ch59 << "  " << Ch60
          << "  " << Ch61 << "  " << Ch62 << "  " << Ch63 << "  " << Ch64 << "  " << Ch65 << "  " << Ch66 << "  " << Ch67 << "  " << Ch68 << "  " << Ch69 << "  " << Ch70 << "  " << Ch71 << "  " << Ch72 << "  " << Ch73 << "  " << Ch74 << "  " << Ch75 << "  " << Ch76 << "  " << Ch77 << "  " << Ch78 << "  " << Ch79 << "  " << Ch80
          << "  " << Ch81 << "  " << Ch82 << "  " << Ch83 << "  " << Ch84 << "  " << Ch85 << "  " << Ch86 << "  " << Ch87 << "  " << Ch88 << "  " << Ch89 << "  " << Ch90 << "  " << Ch91 << "  " << Ch92 << "  " << Ch93 << "  " << Ch94 << "  " << Ch95 << "  " << Ch96 << "  " << Ch97 << "  " << Ch98 << "  " << Ch99 << "  " << Ch100
          << "  " << Ch101 << "  " << Ch102 << "  " << Ch103 << "  " << Ch104 << "  " << Ch105 << "  " << Ch106 << "  " << Ch107 << "  " << Ch108 << "  " << Ch109 << "  " << Ch110 << "  " << Ch111 << "  " << Ch112 << "  " << Ch113 << "  " << Ch114 << "  " << Ch115 << "  " << Ch116 << "  " << Ch117 << "  " << Ch118 << "  " << Ch119 << "  " << Ch120
          << "  " << Ch121 << "  " << Ch122 << "  " << Ch123 << "  " << Ch124 << "  " << Ch125 << "  " << Ch126 << "  " << Ch127 << "  " << Ch128 << "  " << Ch129 << "  " << Ch130 << "  " << Ch131 << "  " << Ch132 << "  " << Ch133 << "  " << Ch134 << "  " << Ch135 << "  " << Ch136 << "  " << Ch137 << "  " << Ch138 << "  " << Ch139 << "  " << Ch140
          << "  " << Ch141 << "  " << Ch142 << "  " << Ch143 << "  " << Ch144 << "  " << Ch145 << "  " << Ch146 << "  " << Ch147 << "  " << Ch148 << "  " << Ch149 << endl;
          // cout<< "run change" << endl;
          Ch0 = 0; Ch1 = 0; Ch2 = 0; Ch3 = 0; Ch4 = 0; Ch5 = 0; Ch6 = 0; Ch7 = 0; Ch8 = 0; Ch9 = 0; Ch10 = 0; Ch11 = 0; Ch12 = 0; Ch13 = 0; Ch14 = 0; Ch15 = 0; Ch16 = 0; Ch17 = 0; Ch18 = 0; Ch19 = 0; Ch20 = 0;
          Ch21 = 0; Ch22 = 0; Ch23 = 0; Ch24 = 0; Ch25 = 0; Ch26 = 0; Ch27 = 0; Ch28 = 0; Ch29 = 0; Ch30 = 0; Ch31 = 0; Ch32 = 0; Ch33 = 0; Ch34 = 0; Ch35 = 0; Ch36 = 0; Ch37 = 0; Ch38 = 0; Ch39 = 0; Ch40 = 0;
          Ch41 = 0; Ch42 = 0; Ch43 = 0; Ch44 = 0; Ch45 = 0; Ch46 = 0; Ch47 = 0; Ch48 = 0; Ch49 = 0; Ch50 = 0; Ch51 = 0; Ch52 = 0; Ch53 = 0; Ch54 = 0; Ch55 = 0; Ch56 = 0; Ch57 = 0; Ch58 = 0; Ch59 = 0; Ch60 = 0;
          Ch61 = 0; Ch62 = 0; Ch63 = 0; Ch64 = 0; Ch65 = 0; Ch66 = 0; Ch67 = 0; Ch68 = 0; Ch69 = 0; Ch70 = 0; Ch71 = 0; Ch72 = 0; Ch73 = 0; Ch74 = 0; Ch75 = 0; Ch76 = 0; Ch77 = 0; Ch78 = 0; Ch79 = 0; Ch80 = 0;
          Ch81 = 0; Ch82 = 0; Ch83 = 0; Ch84 = 0; Ch85 = 0; Ch86 = 0; Ch87 = 0; Ch88 = 0; Ch89 = 0; Ch90 = 0; Ch91 = 0; Ch92 = 0; Ch93 = 0; Ch94 = 0; Ch95 = 0; Ch96 = 0; Ch97 = 0; Ch98 = 0; Ch99 = 0; Ch100 = 0;
          Ch101 = 0; Ch102 = 0; Ch103 = 0; Ch104 = 0; Ch105 = 0; Ch106 = 0; Ch107 = 0; Ch108 = 0; Ch109 = 0; Ch110 = 0; Ch111 = 0; Ch112 = 0; Ch113 = 0; Ch114 = 0; Ch115 = 0; Ch116 = 0; Ch117 = 0; Ch118 = 0; Ch119 = 0; Ch120 = 0;
          Ch121 = 0; Ch122 = 0; Ch123 = 0; Ch124 = 0; Ch125 = 0; Ch126 = 0; Ch127 = 0; Ch128 = 0; Ch129 = 0; Ch130 = 0; Ch131 = 0; Ch132 = 0; Ch133 = 0; Ch134 = 0; Ch135 = 0; Ch136 = 0; Ch137 = 0; Ch138 = 0; Ch139 = 0; Ch140 = 0;
          Ch141 = 0; Ch142 = 0; Ch143 = 0; Ch144 = 0; Ch145 = 0; Ch146 = 0; Ch147 = 0; Ch148 = 0; Ch149 = 0;
          }
        }
}
