#pragma once
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <set>

using namespace std;
// Difference Literal AST node types
enum AST_TYPE {
	LITERAL_NUMBER,
	POP_STACK,
	OP_ADD,
	OP_SUB,
	OP_MUL,
	OP_POW,
	WHITESPACE,
	LITERAL_STRING,
	OP_DUP,
	OP_SWAP,
	OP_ISNEG,
	OP_ISZERO,
	OP_ISPOS,
	OP_LESSTHAN,
	OP_NOTEQ,
	OP_EQ,
	OP_TO_R,
	OP_GREATERTHAN,
	OP_EXCLAIM,
	OP_PLUSEXCLAIM,
	OP_START_SUB,
	OP_END_SUB,
	OP_EMIT,
	OP_CR,
	OP_MOD,
	OP_OVER,
	OP_ROT,
	OP_DROP,
	OP_IF,
	OP_AND,
	OP_OR,
	FUNCTION,
	OP_THEN

};





typedef tuple<AST_TYPE, string> AST_NODE;
typedef vector<AST_NODE> AST;

#define SWITCH_AST_TYPE_FORMAT(TYPE) \
	case AST_TYPE::TYPE : { \
		cout << "AST_NODE<AST_TYPE::" << #TYPE << ", " << get<1>(a) << ">\n"; \
		break; \
	} 




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

// Convert memory formated string to pointer
void* mem_str_to_ptr(const string& str) {
	unsigned long ul;


	sscanf_s(str.c_str(), "%lx", &ul);
	return (void*)(uintptr_t)ul;
}

//Convert pointer to memory formated string
std::string ptr_to_mem_str(void* ptr) {
	std::ostringstream addr;
	addr << (void const*)ptr;
	return addr.str();
}


// Error Types
enum ERRORS {
	MISSING_STACK_OPERANDS,
	UNKNOWN_OP,
	
	//function not in function map ("func_map")
	UNKNOWN_FUNC,
	// Needs to be in ":" block
	OPERATION_NEED_BLOCK
};

// Display Errors
// @TODO add token or line number or smth to errors
void disp_error(ERRORS e, int line) {
	switch (e)
	{
	case MISSING_STACK_OPERANDS:
		cout << "[" << line << "] Interp. Error: MISSING_STACK_OPERANDS\n";
		break;
	case UNKNOWN_OP:
		cout << "[" << line << "] Interp. Error: UNKNOWN_OP\n";
		break;
	case OPERATION_NEED_BLOCK:
		cout << "[" << line << "] Interp. Error: OPERATION_NEED_BLOCK\n";
		break;
	case UNKNOWN_FUNC:
		cout << "[" << line << "] Interp. Error: UNKNOWN_FUNC\n";
		break;
	default:
		cout << "[" << line << "] Interp. Error: UNKNOWN_ERROR";
		break;
	}
}


 struct ParseFlags {
	 bool InFuncDef;
	 bool InIfDef;
	 bool IfTrue;

};