#pragma once


#include <tuple>
#include <regex>
#include <numeric>
#include <cmath>
#include <map>
#include <unordered_map>
#include "Common.hpp"
#include "Func.hpp"

using namespace std;


#define PRIM_CASE(str, type) \
	else if (s == #str ) { \
		ret.push_back(make_tuple(type, "")); \
	}






class Forth {

	vector<string> data_stack;
	vector<string> ret_stack;
	std::unordered_map<string, Function> func_map; 
	ParseFlags flags;
	int stack_before_op = 0;
	vector<string> builtins;

public:

	Forth() {
		this->std_repl = false;
		auto builts = { "pop", "df", "swap", "exit", "df", "df_def", "ds" };
		for (auto str : builts) {
			builtins.push_back(str);
		}

		flags.IfTrue = false;
		flags.InIfDef = false;
		
	}
	Forth(bool repl) {
		this->std_repl = repl;
		auto builts = { "pop", "df", "swap", "exit", "df", "df_def", "ds" };
		for (auto str : builts) {
			builtins.push_back(str);
		}
		flags.IfTrue = false;
		flags.InIfDef = false;
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
					SWITCH_AST_TYPE_FORMAT(OP_DUP)
					SWITCH_AST_TYPE_FORMAT(OP_CR)
					SWITCH_AST_TYPE_FORMAT(OP_MOD)
					SWITCH_AST_TYPE_FORMAT(OP_OVER)
					SWITCH_AST_TYPE_FORMAT(OP_ROT)
					SWITCH_AST_TYPE_FORMAT(OP_DROP)
					SWITCH_AST_TYPE_FORMAT(OP_IF)
					SWITCH_AST_TYPE_FORMAT(OP_AND)
					SWITCH_AST_TYPE_FORMAT(OP_OR)
					SWITCH_AST_TYPE_FORMAT(OP_THEN)








			}
		}
	}
	//A simple util function to dump the stack
	void dump_stack() {
		cout << endl;
		cout << "=========\n";
		for (int i = data_stack.size() - 1; i >= 0; i--) {
			cout << i << ": " << data_stack.at(i) << endl;
		}
		cout << "=========\n";
	}
	void dump_functions() {
		cout << endl;
		cout << "=========\n";
		int f_i = 0;
		for (auto it = func_map.begin(); it != func_map.end(); ++it) {
			cout << f_i << ": " << it->first << endl;
			f_i++;
		}
		cout << "=========\n";

	}
	void dump_functions_defs() {
		cout << endl;
		cout << "=========\n";
		int f_i = 0;
		for (auto it = func_map.begin(); it != func_map.end(); ++it) {
			cout << f_i << ": " << it->first << " -> " << it->second.Dump_AST() << endl;
			f_i++;
		}
		cout << "=========\n";

	}
	AST lex(const string& inp) {
		AST ret;


		// Split input string into tokens
		auto tokens = split(inp, " ");

		regex re_d("\\d+");
		regex re_string("\"(.*)\"");

		
		regex re_func("([A-Za-z]*)");
		for (int i = 0; i < tokens.size(); i++) {
			auto old_ret_len = ret.size();
			smatch dm;
			smatch sm;
			smatch fm;
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
			else if (s == "df") {
				dump_functions();
			}
			else if (s == "df_def") {
				dump_functions_defs();
			}
			
			PRIM_CASE(0 < , AST_TYPE::OP_ISNEG)
				PRIM_CASE(0 > , AST_TYPE::OP_ISPOS)
				PRIM_CASE(0=, AST_TYPE::OP_ISZERO)
				PRIM_CASE(< , AST_TYPE::OP_LESSTHAN)
				PRIM_CASE(<>, AST_TYPE::OP_NOTEQ)
				PRIM_CASE(=, AST_TYPE::OP_EQ)
				PRIM_CASE(> , AST_TYPE::OP_GREATERTHAN)
				PRIM_CASE(pow, AST_TYPE::OP_POW)
				PRIM_CASE(swap, AST_TYPE::OP_SWAP)
				PRIM_CASE(:, AST_TYPE::OP_START_SUB)
				PRIM_CASE(;, AST_TYPE::OP_END_SUB)
				PRIM_CASE(dup, AST_TYPE::OP_DUP)
				PRIM_CASE(emit, AST_TYPE::OP_EMIT)
				PRIM_CASE(mod, AST_TYPE::OP_MOD)
				PRIM_CASE(over, AST_TYPE::OP_OVER)
				PRIM_CASE(rot, AST_TYPE::OP_ROT)
				PRIM_CASE(drop, AST_TYPE::OP_DROP)
				PRIM_CASE(if, AST_TYPE::OP_IF)
				PRIM_CASE(and, AST_TYPE::OP_AND)
				PRIM_CASE(or, AST_TYPE::OP_OR)
				PRIM_CASE(then, AST_TYPE::OP_THEN)


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
			// Check if token is a func
			regex_search(s, fm, re_func);
			if (fm.length() > 0) {


				ret.push_back(make_tuple(AST_TYPE::FUNCTION, fm[0].str()));


			}









		}
		return ret;

	}
	void interp_AST(AST ast) {
		bool should_print = true;
		for (int i = 0; i < ast.size(); i++) {
			should_print = true;

			this->stack_before_op = this->data_stack.size();
		

			AST_NODE curr = ast.at(i);

			if(!(flags.IfTrue && flags.InIfDef)) {
				//@CLEAN
				//cout << "Exec. " << get<0>(curr) << "\n";
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
						disp_error(ERRORS::MISSING_STACK_OPERANDS, __LINE__);
					}
					break; }
				case AST_TYPE::WHITESPACE:
					should_print = false;
					break;
				case AST_TYPE::POP_STACK: {
					if (data_stack.size() >= 1) {
						cout << data_stack.back();
						data_stack.pop_back();
						should_print = false;
					}
					else {
						disp_error(ERRORS::MISSING_STACK_OPERANDS, __LINE__);
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
						disp_error(ERRORS::MISSING_STACK_OPERANDS, __LINE__);
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
						disp_error(ERRORS::MISSING_STACK_OPERANDS, __LINE__);
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
						disp_error(ERRORS::MISSING_STACK_OPERANDS, __LINE__);
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
						disp_error(ERRORS::MISSING_STACK_OPERANDS, __LINE__);
					}
					break;
				}
				case AST_TYPE::OP_ISZERO: {
					if (data_stack.size() >= 1) {
						double v1 = stod(data_stack.back());
						data_stack.pop_back();
						auto val = v1 == 0 ? 1 : 0;
						std::ostringstream strs1;
						strs1 << v1;
						std::string str1 = strs1.str();
						data_stack.push_back(str1);


					}
					else {
						disp_error(ERRORS::MISSING_STACK_OPERANDS, __LINE__);
					}
					break;
				}
				case AST_TYPE::OP_ISNEG: {
					if (data_stack.size() >= 1) {
						double v1 = stod(data_stack.back());
						data_stack.pop_back();
						auto val = v1 < 0 ? 1 : 0;
						std::ostringstream strs1;
						strs1 << v1;
						std::string str1 = strs1.str();
						data_stack.push_back(str1);


					}
					else {
						disp_error(ERRORS::MISSING_STACK_OPERANDS, __LINE__);
					}
					break;
				}
				case AST_TYPE::OP_ISPOS: {
					if (data_stack.size() >= 1) {
						double v1 = stod(data_stack.back());
						data_stack.pop_back();
						auto val = v1 > 0 ? 1 : 0;
						std::ostringstream strs1;
						strs1 << v1;
						std::string str1 = strs1.str();
						data_stack.push_back(str1);


					}
					else {
						disp_error(ERRORS::MISSING_STACK_OPERANDS, __LINE__);
					}
					break;
				}
				case AST_TYPE::OP_EQ: {
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
						int val = v1 == v2 ? 1 : 0;
						std::ostringstream strs3;
						strs3 << val;
						std::string str3 = strs3.str();
						data_stack.push_back(str3);
					}
					else {
						disp_error(ERRORS::MISSING_STACK_OPERANDS, __LINE__);
					}
					break;
				}
				case AST_TYPE::OP_LESSTHAN: {
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
						int val = v1 < v2 ? 1 : 0;
						std::ostringstream strs3;
						strs3 << val;
						std::string str3 = strs3.str();
						if (val > 0) {
							data_stack.push_back("1");
						}
						else {
							data_stack.push_back("0");
						}
					}
					else {
						disp_error(ERRORS::MISSING_STACK_OPERANDS, __LINE__);
					}
					break;
				}
				case AST_TYPE::OP_GREATERTHAN: {
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
						int val = v1 > v2 ? 1 : 0;
						std::ostringstream strs3;
						strs3 << val;
						std::string str3 = strs3.str();
						if (val > 0) {
							data_stack.push_back("1");
						}
						else {
							data_stack.push_back("0");
						}
					}
					else {
						disp_error(ERRORS::MISSING_STACK_OPERANDS, __LINE__);
					}
					break;
				}
				case AST_TYPE::OP_NOTEQ: {
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
						int val = v1 != v2 ? 1 : 0;
						std::ostringstream strs3;
						strs3 << val;
						std::string str3 = strs3.str();
						data_stack.push_back(str3);
					}
					else {
						disp_error(ERRORS::MISSING_STACK_OPERANDS, __LINE__);
					}
					break;
				}
				case AST_TYPE::OP_START_SUB: {
					should_print = false;
					flags.InFuncDef = true;
					int first = i;
					AST temp;
					string func_name = "";
					int t = first;
					while ((get<0>(ast.at(t)) != AST_TYPE::OP_END_SUB || get<0>(ast.at(t)) != AST_TYPE::OP_START_SUB) && t < ast.size() - 1) {
						if (t == first + 1) {
							func_name = get<1>(ast.at(t));
						}
						if (t > 1)
							temp.push_back(ast.at(t));
						t++;
					}
					int end = t;
					i = t;

					func_map[func_name] = Function(temp);

					break;
				}
				case AST_TYPE::OP_END_SUB: {
					flags.InFuncDef = false;
					should_print = false;
					break;
				}
				case AST_TYPE::FUNCTION: {
					should_print = false;
					auto temp = func_map.find(get<1>(curr));
					
					if (temp != func_map.end()) {
						this->exec_func_string(temp->first);
					}
					else {
						bool found = false;
						for (auto built : builtins) {
							if (built == get<1>(curr)) {
								found = true;
								break;
							}
						}
						if (!found) {
							disp_error(ERRORS::UNKNOWN_FUNC, __LINE__);
						}
					}
					break;
				}
				case AST_TYPE::OP_DUP: {
					if (data_stack.size() >= 1) {
						string v1 = data_stack.back();
						data_stack.pop_back();

						data_stack.push_back(v1);
						data_stack.push_back(v1);



					}
					else {
						disp_error(ERRORS::MISSING_STACK_OPERANDS, __LINE__);
					}
					break;
				}
				case AST_TYPE::OP_EMIT: {
					if (data_stack.size() >= 1) {
						char v1 = stoi(data_stack.back());
						data_stack.pop_back();
						std::cout << v1;


					}
					else {
						disp_error(ERRORS::MISSING_STACK_OPERANDS, __LINE__);
					}
					break;
				}
				case AST_TYPE::OP_CR: {
					cout << endl;
					break;
				}
				case AST_TYPE::OP_MOD: {
					if (data_stack.size() >= 2) {
						double v2 = stod(data_stack.back());
						data_stack.pop_back();
						double v1 = stod(data_stack.back());
						data_stack.pop_back();
						std::ostringstream strs1;
						strs1 << v1;
						std::string str1 = strs1.str();
						std::ostringstream strs2;
						strs2 << v2;
						std::string str2 = strs2.str();
						double val = (int)v1 % (int)v2;
						std::ostringstream strs3;
						strs3 << val;
						std::string str3 = strs3.str();
						data_stack.push_back(str3);
					}
					else {
						disp_error(ERRORS::MISSING_STACK_OPERANDS, __LINE__);
					}
					break;
				}
				case AST_TYPE::OP_OVER: {
					if (data_stack.size() >= 2) {
						auto v2 = data_stack.back();
						data_stack.pop_back();
						auto v1 = data_stack.back();

						data_stack.push_back(v2);
						data_stack.push_back(v1);


					}
					else {
						disp_error(ERRORS::MISSING_STACK_OPERANDS, __LINE__);
					}
					break;
				}
				case AST_TYPE::OP_ROT: {
					if (data_stack.size() >= 3) {
						auto v3 = data_stack.back();
						data_stack.pop_back();
						auto v2 = data_stack.back();
						data_stack.pop_back();
						auto v1 = data_stack.back();
						data_stack.pop_back();


						data_stack.push_back(v2);
						data_stack.push_back(v1);
						data_stack.push_back(v3);



					}
					else {
						disp_error(ERRORS::MISSING_STACK_OPERANDS, __LINE__);
					}
					break;
				}
				case AST_TYPE::OP_DROP: {
					if (data_stack.size() >= 1) {
						data_stack.pop_back();
					}
					else {
						disp_error(ERRORS::MISSING_STACK_OPERANDS, __LINE__);
					}
					break;
				}
				case AST_TYPE::OP_IF: {
					if (flags.InFuncDef) {
						if (data_stack.size() >= 1) {
							int v1 = stoi(data_stack.back());
							data_stack.pop_back();
							

							if (v1 > 0) {
								flags.IfTrue = true;

							}
						}
						else {
							disp_error(ERRORS::MISSING_STACK_OPERANDS, __LINE__);
						}

					}
					else {
						disp_error(ERRORS::OPERATION_NEED_BLOCK, __LINE__);
					}
					flags.InIfDef = true;
					break;
				}
				case AST_TYPE::OP_THEN: {
					if (flags.InFuncDef) {
						if (data_stack.size() >= 1) {
							
							if (flags.IfTrue) {
								cout << "Found true flags\n";
								AST temp_ast;

								for (int i = ast.size() - 2; get<0>(ast.at(i)) != AST_TYPE::OP_IF; i--) {
									temp_ast.push_back(ast.at(i));
								}
								 
								this->interp_AST(temp_ast);

							}
							else {

							}
							flags.InIfDef = false;
						}
						else {
							disp_error(ERRORS::MISSING_STACK_OPERANDS, __LINE__);
						}

					} else {
						disp_error(ERRORS::OPERATION_NEED_BLOCK, __LINE__);
					}
					flags.IfTrue = false;
					

					break;
				}
				default:
					disp_error(ERRORS::UNKNOWN_OP, __LINE__);
					should_print = false;
					break;
				}
			}
			/*if (this->std_repl) {
				if (should_print) {
					cout << data_stack[data_stack.size() - 1];
				}
			}*/
		}
		
	}


	void interp(const string& inp) {
		interp_AST(lex(inp));
	}

	void exec_func_string(const std::string& func) {
		AST temp_ast = func_map[func].func_ast;
		this->interp_AST(temp_ast);
	}
};



























