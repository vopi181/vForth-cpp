#pragma once
#include "Common.hpp"

class Function {

public:
	AST func_ast;
	
	Function(AST ast) {
		this->func_ast = ast;
	}
	Function() {
		
	}

	~Function() {

	}

	string Dump_AST() {

		// it gets optimized away ok bud?
		string ret = "";
		for (AST_NODE n : func_ast) {
			if (std::get<0>(n) == AST_TYPE::OP_ADD) {
				ret += " +";
			} else if (std::get<0>(n) == AST_TYPE::OP_SUB) {
				ret += " -";
			
			} else if (std::get<0>(n) == AST_TYPE::OP_MUL) {
				ret += " *";
			}
			else {
				ret += " " + std::get<1>(n);

			}
		}
		return ret;
	}



};