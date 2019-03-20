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
			ret += " " + std::get<1>(n);
		}
		return ret;
	}



};