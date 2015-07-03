#include "parser.hpp"
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

void Parser::readfile(string input) // this is horrible messy code that i need to redo sometime, but it works for now
{
    ifstream ifstreamer;
    ifstreamer.open((string("./") + input).c_str());
    ostringstream strstm;
    strstm << ifstreamer.rdbuf();
    ifstreamer.close();
    string instring = strstm.str();
    vector<string> lines;
    int lastpos=0;
    int foundpos=0;
    int i=0;
    while (foundpos!=string::npos)
    {
        foundpos=instring.find("\n",lastpos);
        lines.push_back(instring.substr(lastpos,foundpos-lastpos));
        lastpos=foundpos+1;
        cout << lines[i] << endl;
        i++;
    }
}
