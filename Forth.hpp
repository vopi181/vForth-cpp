#pragma once


#include <tuple>
#include <regex>
#include <numeric>
#include <cmath>
#include "Common.hpp"
using namespace std;









class Forth {

	vector<string> data_stack;
	vector<string> ret_stack;

public:

	Forth() {
		this->std_repl = false;
	}
	Forth(bool repl) {
		this->std_repl = repl;
	}

	~Forth() {

	}
	
	// REPL helper
	bool std_repl;

	// A simple util function to dump the AST
	void dump_AST(AST ast) {
		for (AST_NODE a : ast) {
			switch (get<0>(a)) {


				SWITCH_AST_TYPE_FORMAT(LITERAL_NUMBER)
					SWITCH_AST_TYPE_FORMAT(LITERAL_STRING)
					SWITCH_AST_TYPE_FORMAT(OP_ADD)
					SWITCH_AST_TYPE_FORMAT(OP_SUB)
					SWITCH_AST_TYPE_FORMAT(OP_MUL)
					SWITCH_AST_TYPE_FORMAT(OP_POW)
					SWITCH_AST_TYPE_FORMAT(POP_STACK)
					SWITCH_AST_TYPE_FORMAT(WHITESPACE)
					SWITCH_AST_TYPE_FORMAT(OP_SWAP)

			}
		}
	}
	//A simple util function to dump the stack
	void dump_stack() {
		cout << endl;
		cout << "=========\n";
		for (int i = data_stack.size() - 1; i >= 0; i--) {
			cout << i << ": " << data_stack.at(i) << "\n";
		}
		cout << "=========\n";
	}
	AST lex(const string& inp) {
		AST ret;


		// Split input string into tokens
		auto tokens = split(inp, " ");

		regex re_d("\\d+");
		regex re_string("\"(.*)\"");
		for (int i = 0; i < tokens.size(); i++) {
			auto old_ret_len = ret.size();
			smatch dm;
			smatch sm;
			const string s = tokens.at(i);


			// Single Char?
			if (s.length() == 1) {
				switch (s.at(0)) {
				case '+': {
					ret.push_back(make_tuple(AST_TYPE::OP_ADD, ""));
					break;
				}
				case  '.': {
					ret.push_back(make_tuple(AST_TYPE::POP_STACK, ""));
					break;
				}
				case '-': {
					ret.push_back(make_tuple(AST_TYPE::OP_SUB, ""));
					break;
				}
				case '*': {
					ret.push_back(make_tuple(AST_TYPE::OP_MUL, ""));
					break;
				}
				}
			}

			// Check if token is a string
			regex_search(s, sm, re_string);
			if (sm.length() > 0) {
				ret.push_back(make_tuple(AST_TYPE::LITERAL_STRING, sm[0].str()));
				cout << dm[0].str();
			}



			// Check if token is a number
			regex_search(s, dm, re_d);
			if (dm.length() > 0) {
				ret.push_back(make_tuple(AST_TYPE::LITERAL_NUMBER, dm[0].str()));
			}

			// Built ins
			// [#] = # in stack, where 0 = bottom

			// pow: [0] raise to [1]
			if (s == "pow") {
				ret.push_back(make_tuple(AST_TYPE::OP_POW, ""));

			}
			// swap  (n1 n2 -- n2 n1 )
			else if (s == "swap") {
				ret.push_back(make_tuple(AST_TYPE::OP_SWAP, ""));

			}
			// Exit
			else if (s == "exit") {
				cout << "Quiting...\n";
				exit(0);
			}
			// Dump Stack
			else if (s == "ds") {
				dump_stack();
			}








		}
		return ret;

	}
	void interp_AST(AST ast) {
		bool should_print = true;
		for (int i = 0; i < ast.size(); i++) {
			should_print = true;

			
			AST_NODE curr = ast.at(i);


			switch (get<0>(curr)) {

			case AST_TYPE::LITERAL_NUMBER: {
				data_stack.push_back(get<1>(curr));
				break; }
			case AST_TYPE::LITERAL_STRING: {
				data_stack.push_back(get<1>(curr));
				break; }
			case AST_TYPE::OP_ADD: {
				if (data_stack.size() >= 2) {
					double v1 = stod(data_stack.back());
					data_stack.pop_back();
					double v2 = stod(data_stack.back());
					data_stack.pop_back();
					auto val = (v1 + v2);
					std::ostringstream strs;
					strs << val;
					std::string str = strs.str();
					data_stack.push_back(str);
				}
				else {
					disp_error(ERRORS::MISSING_STACK_OPERANDS);
				}
				break; }
			case AST_TYPE::WHITESPACE:
				break;
			case AST_TYPE::POP_STACK: {
				if (data_stack.size() >= 1) {
					cout << data_stack.back();
					data_stack.pop_back();
					should_print = false;
				}
				else {
					disp_error(ERRORS::MISSING_STACK_OPERANDS);
				}
				break; }
			case AST_TYPE::OP_SUB: {
				if (data_stack.size() >= 2) {
					double v1 = stod(data_stack.back());
					data_stack.pop_back();
					double v2 = stod(data_stack.back());
					data_stack.pop_back();
					auto val = (v1 - v2);
					std::ostringstream strs;
					strs << val;
					std::string str = strs.str();
					data_stack.push_back(str);
				}
				else {
					disp_error(ERRORS::MISSING_STACK_OPERANDS);
				}
				break;
			}
			case AST_TYPE::OP_MUL: {
				if (data_stack.size() >= 2) {
					double v1 = stod(data_stack.back());
					data_stack.pop_back();
					double v2 = stod(data_stack.back());
					data_stack.pop_back();
					auto val = (v1 * v2);
					std::ostringstream strs;
					strs << val;
					std::string str = strs.str();
					data_stack.push_back(str);
				}
				else {
					disp_error(ERRORS::MISSING_STACK_OPERANDS);
				}
				break;
			}
			case AST_TYPE::OP_POW: {
				if (data_stack.size() >= 2) {
					double v1 = stod(data_stack.back());
					data_stack.pop_back();
					double v2 = stod(data_stack.back());
					data_stack.pop_back();
					auto val = std::pow(v1, v2);
					std::ostringstream strs;
					strs << val;
					std::string str = strs.str();
					data_stack.push_back(str);
				}
				else {
					disp_error(ERRORS::MISSING_STACK_OPERANDS);
				}
				break;
			}
			case AST_TYPE::OP_SWAP: {
				if (data_stack.size() >= 2) {
					double v1 = stod(data_stack.back());
					data_stack.pop_back();
					double v2 = stod(data_stack.back());
					data_stack.pop_back();
					std::ostringstream strs1;
					strs1 << v1;
					std::string str1 = strs1.str();
					std::ostringstream strs2;
					strs2 << v2;
					std::string str2 = strs2.str();
					data_stack.push_back(str1);
					data_stack.push_back(str2);
				}
				else {
					disp_error(ERRORS::MISSING_STACK_OPERANDS);
				}
			}
			}
		}
		if(this->std_repl) {
			if(should_print) {
				cout << data_stack[data_stack.size() - 1];
			}
		}
	}


	void interp(const string& inp) {
		interp_AST(lex(inp));
	}
};



























