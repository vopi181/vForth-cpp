// CalcInterp.cpp : Defines the entry point for the console application.
//


#include <iostream>
#include "Forth.hpp"


int main()
{
    
	Forth f(true);

	if (true) {
		
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

