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




};