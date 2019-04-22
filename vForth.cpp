// CalcInterp.cpp : Defines the entry point for the console application.
//


#include <iostream>
#include "Forth.hpp"


int main()
{
    
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
	return 0;
}

