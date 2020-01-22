// CalcInterp.cpp : Defines the entry point for the console application.
//


#include <iostream>
#include <fstream>
#include "Forth.hpp"


int main(int argc, char** argv)
{
    
	if (argc > 1) {
		ifstream source(argv[1]);
		string inp;
		vector<string> lines;
		while (!source.eof()) {
			std::getline(source, inp);
			lines.push_back(inp);
		}
		Forth finterp(false);
		for (auto line : lines) {
			finterp.interp(line);
		}
		
		

	}
	else {
  		Forth f(true);

		if (true) {


			cout << "vForth-cpp by Dominic Pace\n";
			cout << "Compiled on " << __DATE__ << " at " << __TIME__ << "\n";
			while (true) {
				cout << ">";
				string inp;
				std::getline(std::cin, inp);
				f.interp(inp);
				cout << endl << "ok" << endl;


			}
		}
	}
	return 0;
}

