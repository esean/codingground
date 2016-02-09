#include <iostream>
#include <string>
#include <sstream>
#include <stdbool.h>

using namespace std;

// Input format:
//
// # sample,utc,data
// 0,  0.000000,   0.187138
// 1,  0.000586,   0.187171
// 2,  0.001172,   0.187205
//

bool is_header_line(string str) {
    // if first char in line is '#', this is header line
    return (str.at(0) == '#');
}

int main()
{
    string str;

    //  Don't sync C++ and C I/O
    // http://www.manticmoo.com/articles/jeff/programming/c++/making-io-streams-efficient-in-c++.php
    ios_base::sync_with_stdio(false);

    // get a line
    while ( getline(cin,str)) {

        // print and continue if a header row
        if (is_header_line(str))
        {
            cout << str << endl;
            continue;
        }

        // now break line into csv components
        string sample,utc,data;
        stringstream ss(str);
        getline(ss,sample,',');
        getline(ss,utc,',');
        getline(ss,data,',');

        double utcf,dataf;
        utcf = atof(utc.c_str());
        dataf = atof(data.c_str());

        cout << sample << "," << utcf << "," << dataf << endl;
    }

	return 0;
}
