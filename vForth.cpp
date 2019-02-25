// CalcInterp.cpp : Defines the entry point for the console application.
//


#include <iostream>
#include <tuple>
#include <vector>
#include <string>
#include <regex>
#include <numeric>
using namespace std;


// Helper funcs


// "Tokenize" a string into a vector of strings
vector<string> split(const string& str, const string& delim)
{
	vector<string> tokens;
	size_t prev = 0, pos = 0;
	do
	{
		pos = str.find(delim, prev);
		if (pos == string::npos) pos = str.length();
		string token = str.substr(prev, pos - prev);
		if (!token.empty()) tokens.push_back(token);
		prev = pos + delim.length();
	} while (pos < str.length() && prev < str.length());
	return tokens;
}

// Old
bool is_digit(char c) {
	if (c >= '0' && c <= '9') {
		return true;
	}
	return false;
}

// Old
int ascii_num_to_val(char c) {
	return c - '0';
}


// Error Types
enum ERRORS {
	MISSING_STACK_OPERANDS,
};

// Display Errors
// @TODO add token or line number or smth to errors
void disp_error(ERRORS e) {
	switch (e)
	{
	case MISSING_STACK_OPERANDS:
		cout << "Interp. Error: MISSING_STACK_OPERANDS\n";
		break;
	default:
		cout << "Interp. Error: UNKNOWN_ERROR";
		break;
	}
}

// Difference Literal AST node types
enum AST_TYPE {
	LITERAL_NUMBER,
	POP_STACK,
	OP_ADD,
	WHITESPACE,
};

typedef tuple<AST_TYPE, char> AST_NODE;
typedef vector<AST_NODE> AST;
vector<int> data_stack;
vector<AST_TYPE> op_stack;


// A simple util function to dump the AST
void dump_AST(AST ast) {
	for (AST_NODE a : ast) {
		switch (get<0>(a)) {
		case AST_TYPE::LITERAL_NUMBER: {
			cout << "AST_NODE<AST_TYPE::LITERAL_NUMBER," << get<1>(a) << ">\n";
			break;
		}
		case AST_TYPE::OP_ADD: {
			cout << "AST_NODE<AST_TYPE::OP_ADD," << get<1>(a) << ">\n";
			break;
		}

		case AST_TYPE::POP_STACK: {
			cout << "AST_NODE<AST_TYPE::POP_STACK," << ">\n";
			break;
		}
		case AST_TYPE::WHITESPACE: {
			cout << "AST_NODE<AST_TYPE::POP_STACK, " << ">\n";
			break;
		}
		}
	}
}

//A simple util function to dump the stack
void dump_stack() {
	for (int i = 0; i < data_stack.size(); i++) {
		cout << i << ": " << data_stack.at(i) << ", ";
	}
}






AST lex(const string& inp) {
	AST ret;


	// Split input string into tokens
	auto tokens = split(inp, " ");

	regex d("\\d+");
	for (int i = 0; i < tokens.size(); i++) {
		smatch m;
		const string s = tokens.at(i);


		// Single Char?
		if (s.length() == 1) {
			switch (s.at(0)) {
			case '+':
				ret.push_back(make_tuple(AST_TYPE::OP_ADD, NULL));
				break;
			case  '.':
				ret.push_back(make_tuple(AST_TYPE::POP_STACK, NULL));
			}
		}



		// Check if token is a number
		regex_search(s, m, d);
		if (m.length() > 0) {
			ret.push_back(make_tuple(AST_TYPE::LITERAL_NUMBER, std::atoi(m[0].str().c_str())));
		}






	}
	return ret;

}


void interp_AST(AST ast) {
	for (int i = 0; i < ast.size(); i++) {
		AST_NODE curr = ast.at(i);


		switch (get<0>(curr)) {

		case AST_TYPE::LITERAL_NUMBER:
			data_stack.push_back(get<1>(curr));
			break;
		case AST_TYPE::OP_ADD:
			if (data_stack.size() >= 2) {
				cout << (data_stack.back() + data_stack.back());
				data_stack.pop_back();
				data_stack.pop_back();
			}
			else {
				disp_error(ERRORS::MISSING_STACK_OPERANDS);
			}
			break;
		case AST_TYPE::WHITESPACE:
			break;

		case AST_TYPE::POP_STACK:
			if (data_stack.size() >= 1) {
				cout << data_stack.back();
				data_stack.pop_back();
			}
			else {
				disp_error(ERRORS::MISSING_STACK_OPERANDS);
			}
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

