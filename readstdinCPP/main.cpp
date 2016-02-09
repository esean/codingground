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

const string our_csv_headers = "avg,delta,integrate";


bool is_header_line(string str) {
    // if first char in line is '#', this is header line
    return (str.at(0) == '#');
}

void read_3_columns_from_csv_line(string str, double* sample, double* utc, double* data)
{
    if (!sample || !utc || !data) {
        cerr << "ERROR: read_3_columns_from_csv_line NULLs!" << endl;
        return;
    }

    stringstream ss(str);
    string ssample,sutc,sdata;
    getline(ss,ssample,',');
    getline(ss,sutc,',');
    getline(ss,sdata,',');

    *sample = atof(ssample.c_str());
    *utc = atof(sutc.c_str());
    *data = atof(sdata.c_str()); 
}

double maintain_avg(double in_data) {
    static long double sum = 0.0f;
    static long long count = 0;
    sum += in_data;
    ++count;
    return sum/count;
}

double maintain_integrate(double in_data) {
    static long double sum = 0.0f;
    sum += in_data;
    return sum;
}

int main()
{
    //  Don't sync C++ and C I/O
    // http://www.manticmoo.com/articles/jeff/programming/c++/making-io-streams-efficient-in-c++.php
    ios_base::sync_with_stdio(false);

    // get a line
    string str;
    while ( getline(cin,str)) {

        // print and continue if a header row, augment with our stuff
        if (is_header_line(str))
        {
            cout << str << "," << our_csv_headers << endl;
            continue;
        }

        // now break line into csv components
        double sample,utc,data;
        read_3_columns_from_csv_line(str,&sample,&utc,&data);

        // compute our stuff
        double avg = maintain_avg(data);
        double delta = data - avg;
        double integrate = maintain_integrate(delta);

        cout << sample << "," << utc << "," << data << "," << avg << "," << delta << "," << integrate << endl;
    }

	return 0;
}
