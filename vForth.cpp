// CalcInterp.cpp : Defines the entry point for the console application.
//


#include <iostream>
#include "Forth.hpp"


int main()
{

	Forth f;
	if (true) {
		while (true) {
			cout << "> ";
			string inp;
			cin >> inp;
			f.interp(inp);
			
		}
	}
	return 0;
}

