#pragma once
#include "Token.h"
#include <vector>
#include <fstream>

class CLexer
{
public:
	CLexer(std::istream& input, std::ofstream& output);

	void Run();

private:
	TokenType GetTokenType(Token token);
	void PrintTokens();

	bool FindStringInVector(std::vector<std::string> vector, std::string string);
	std::string GetTokenName(Token token);
	void AddToken(Token token);

	bool IsKeyword(std::string str);
	bool IsArray(std::string str);
	bool IsArithmeticalOperator(std::string str);
	bool IsComparisonOperator(std::string str);
	bool IsLogicOperator(std::string str);
	bool IsBracket(std::string str);
	bool IsSeparator(std::string str);
	bool IsBinary(std::string str);
	bool IsOctal(std::string str);
	bool IsDecimal(std::string str);
	bool IsHexadecimal(std::string str);
	bool IsLetter(std::string str);
	bool IsComment(std::string str);

	const std::vector<std::string> m_keywords = { "if", "else", "while", "for", "read", "write", "return", "int", "float",
		"void", "main", "string", "char" };
	const std::vector<std::string> m_array = { "[", "]", "[]" };
	const std::vector<std::string> m_arithmeticalOperators = { "+", "-", "*", "/", "=" };
	const std::vector<std::string> m_comparisonOperators = { "==", "!=", ">", "<", ">=", "<=" };
	const std::vector<std::string> m_logicOperators = { "&&", "||", "!" };
	const std::vector<std::string> m_brackets = { "{", "}", "(", ")" };
	const std::vector<std::string> m_separators = { ",", ";" };
	const std::vector<std::string> m_binary = { "0", "1" };
	const std::vector<std::string> m_octal = { "0", "1", "2", "3", "4", "5", "6", "7" };
	const std::vector<std::string> m_decimal = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };
	const std::vector<std::string> m_hexadecimal = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "A", "B", "C", "D", "E", "F" };
	const std::vector<std::string> m_comments = { "//", "/*", "*/" };
	const std::vector<std::string> m_letters = { "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R",
		"S", "T", "U", "V", "W", "X", "Y", "Z", "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p",
		"q", "r", "s", "t", "u", "v", "w", "x", "y", "z" };



	std::istream& m_input;
	std::ofstream& m_output;
	std::vector<Token> m_tokens;
};
