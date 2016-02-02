#include <iostream>
#include <string>
#include <map>
#include <sstream>
#include <vector>

using namespace std;

void split(const string &s, char delim, vector<string> &elems) {
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim)) {
        elems.push_back(item);
    }
}

int main()
{
	string txt = "this is the word cloud and this is the other word";	
	map<string,int> word_map;
	vector<string> words;

	split(txt,' ',words);
	for (vector<string>::iterator it = words.begin(); it != words.end(); ++it)
		if (!word_map[*it])
			word_map[*it] = 1;
		else
			++word_map[*it];

	for (map<string,int>::iterator it = word_map.begin(); it != word_map.end(); ++it)
		cout << "Word = " << it->first << ", count = " << it->second << endl;

	return 0;
}
