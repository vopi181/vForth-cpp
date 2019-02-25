// CalcInterp.cpp : Defines the entry point for the console application.
//


#include <iostream>
#include <tuple>
#include <vector>
#include <string>
#include <regex>
#include <numeric>
using namespace std;






enum AST_TYPE {
	LITERAL_NUMBER,
	OP_ADD,
	WHITESPACE,
};

typedef tuple<AST_TYPE, char> AST_NODE;
typedef vector<AST_NODE> AST;
vector<int> data_stack;
vector<AST_TYPE> op_stack;


bool is_digit(char c) {
	if (c >= '0' && c <= '9') {
		return true;
	}
	return false;
}





int ascii_num_to_val(char c) {
	return c - '0';
}





//A simple util function to dump the AST
void dump_AST(AST ast) {
	for (AST_NODE a : ast) {
		if (get<0>(a) == AST_TYPE::LITERAL_NUMBER) {
			cout << "AST_NODE<AST_TYPE::LITERAL_NUMBER," << get<1>(a) << ">\n";
		}
		else if (get<0>(a) == AST_TYPE::OP_ADD) {
			cout << "AST_NODE<AST_TYPE::OP_ADD," << get<1>(a) << ">\n";
		}
	}
}
void dump_stack() {
	for (int i = 0; i < data_stack.size(); i++) {
		cout << i << ": " << data_stack.at(i) << ", ";
	}
}




AST lex(const string& inp) {
	AST ret;


	for (int i = 0; i < inp.size(); i++) {
		char c = inp.at(i);
		if (is_digit(c)) {
			dump_stack();
			int t = 0;
			int val = 0;
			while ((i < inp.size()) && is_digit(inp.at(t + i))) {
				val += ascii_num_to_val(c);
				t++;
			}
			ret.push_back(make_tuple(AST_TYPE::LITERAL_NUMBER, val));
			i = i + t;
		}
		else if (c == '+') {
			ret.push_back(make_tuple(AST_TYPE::OP_ADD, NULL));
		}
		else if (c == ' ') {
			ret.push_back(make_tuple(AST_TYPE::WHITESPACE, NULL));
		}

	}


	return ret;

}


void interp_AST(AST ast) {
	for (int i = 0; i < ast.size(); i++) {
		AST_NODE curr = ast.at(i);


		switch (get<0>(curr)) {

		case AST_TYPE::LITERAL_NUMBER:
			data_stack.push_back(ascii_num_to_val(get<1>(curr)));
			break;
		case AST_TYPE::OP_ADD:
			if (data_stack.size() >= 2) {
				cout << (data_stack.back() + data_stack.back());
			}
			break;
		case AST_TYPE::WHITESPACE:
			break;

		}
	}
}


void interp(const string& inp) {
	interp_AST(lex(inp));
}


int main()
{
	dump_AST(lex("2 2 +"));
	interp("2 2 +");
	cin.get();
	if (true) {
		while (true) {
			cout << "> ";
			string inp;
			cin >> inp;
			interp(inp);
			cout << endl;
		}
	}
	return 0;
}
