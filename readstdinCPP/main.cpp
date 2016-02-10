#include <iostream>
#include <string>
#include <sstream>
#include <stdbool.h>
#include <unordered_map>

using namespace std;

// Input format:
//
// # sample,utc,data
// 0,  0.000000,   0.187138
// 1,  0.000586,   0.187171
// 2,  0.001172,   0.187205
//

const string input_csv_headers = "sample,utc,data";
const string output_csv_headers = "sample,utc,data,avg,delta,integrate";


bool is_header_line(string str) {
    // if first char in line is '#', this is header line
    return (str.at(0) == '#');
}

// loop thru the provided headers while reading from csv line
unordered_map<string,string> read_csv_line_with_headers(string header, string csv_line, char delim = ',') {
    unordered_map<string,string> ret;
    stringstream ss(csv_line), hdrss(header);
    string str;
    while (getline(hdrss,str,delim)) {
        string stmp;
        getline(ss,stmp,delim);
        ret[str] = stmp;
    }
    return ret;
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

    cout << "# " << output_csv_headers << endl;
    
    // get a line
    string str;
    while ( getline(cin,str)) {

        // make sure to strip any \r from windows systems
        if (!str.empty() && str[str.size() - 1] == '\r')
            str.erase(str.size() - 1);
        
        // print and continue if a header row, augment with our stuff
        if (is_header_line(str)) continue;
        
        // now break line into csv components
        unordered_map<string,string> csv_cols = read_csv_line_with_headers(input_csv_headers,str);
        double sample = atof(csv_cols["sample"].c_str());
        double utc = atof(csv_cols["utc"].c_str());
        double data = atof(csv_cols["data"].c_str());

        // compute our stuff
        double avg = maintain_avg(data);
        double delta = data - avg;
        double integrate = maintain_integrate(delta);

        cout << sample << "," << utc << "," << data << "," << avg << "," << delta << "," << integrate << endl;
    }

	return 0;
}
