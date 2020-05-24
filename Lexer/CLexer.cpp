#include "CLexer.h"
#include <iostream>

CLexer::CLexer(std::istream& input, std::ofstream& output)
	: m_input(input)
	, m_output(output)
{
}

std::string CLexer::GetTokenName(Token token)
{
	switch (token.type)
	{
	case TokenType::Identifier:
		return "Identifier";
	case TokenType::Integer:
		return "Integer";
	case TokenType::Float:
		return "Float";
	case TokenType::Binary:
		return "Binary";
	case TokenType::Octal:
		return "Octal";
	case TokenType::Hexadecimal:
		return "Hexadecimal";
	case TokenType::Char:
		return "Char";
	case TokenType::String:
		return "String";
	case TokenType::Array:
		return "Array";
	case TokenType::Keyword:
		return "Keyword";
	case TokenType::ArithmeticOperator:
		return "ArithmeticOperation";
	case TokenType::ComparisonOperator:
		return "ComparisonOperator";
	case TokenType::LogicOperator:
		return "LogicOperator";
	case TokenType::Bracket:
		return "Bracket";
	case TokenType::Separator:
		return "Separator";
	case TokenType::Comment:
		return "Comment";
	case TokenType::Error:
		return "Error";
	default:
		return "unknown type";
	}
}

bool CLexer::FindStringInVector(std::vector<std::string> vector, std::string string)
{
	return std::find(vector.begin(), vector.end(), string) != vector.end();
}

bool CLexer::IsKeyword(std::string string)
{
	return FindStringInVector(m_keywords, string);
}

bool CLexer::IsArray(std::string string)
{
	return FindStringInVector(m_array, string);
}

bool CLexer::IsComment(std::string string)
{
	return FindStringInVector(m_comments, string);
}

bool CLexer::IsArithmeticalOperator(std::string string)
{
	return FindStringInVector(m_arithmeticalOperators, string);
}

bool CLexer::IsComparisonOperator(std::string string)
{
	return FindStringInVector(m_comparisonOperators, string);
}

bool CLexer::IsLogicOperator(std::string string)
{
	return FindStringInVector(m_logicOperators, string);
}

bool CLexer::IsBracket(std::string string)
{
	return FindStringInVector(m_brackets, string);
}

bool CLexer::IsSeparator(std::string string)
{
	return FindStringInVector(m_separators, string);
}

bool CLexer::IsBinary(std::string string)
{
	return FindStringInVector(m_binary, string);
}

bool CLexer::IsOctal(std::string string)
{
	return FindStringInVector(m_octal, string);
}

bool CLexer::IsDecimal(std::string string)
{
	return FindStringInVector(m_decimal, string);
}

bool CLexer::IsHexadecimal(std::string string)
{
	return FindStringInVector(m_hexadecimal, string);
}

bool CLexer::IsLetter(std::string string)
{
	return FindStringInVector(m_letters, string);
}

TokenType CLexer::GetTokenType(Token token)
{
	std::string s;

	if (IsKeyword(token.value))
		return TokenType::Keyword;
	if (IsArray(token.value))
		return TokenType::Array;
	if (token.value[0] == '"' && token.value[token.value.length() - 1] == '"')
		return (token.value.length() == 3) ? TokenType::Char : TokenType::String;
	if (IsArithmeticalOperator(token.value))
		return TokenType::ArithmeticOperator;
	if (IsComparisonOperator(token.value))
		return TokenType::ComparisonOperator;
	if (IsLogicOperator(token.value))
		return TokenType::LogicOperator;
	if (IsBracket(token.value))
		return TokenType::Bracket;
	if (IsSeparator(token.value))
		return TokenType::Separator;
	for (int i = 0; i < token.value.length(); i++)
	{
		s = token.value[i];
		if (!(IsLetter(s) || IsDecimal(s) || s == "_"))
			break;
		s = token.value[0];
		if (IsLetter(s) && i + 1 == token.value.length())
			return TokenType::Identifier;
	}

	if (token.value.length() > 2)
	{
		std::string base = token.value.substr(0, 2);
		std::string digits;
		
		if (base == "0b")
		{
			digits = token.value.substr(2, -1);
			bool isDigits = true;
			for (int i = 0; i < digits.length(); i++)
			{
				s = digits[i];
				if (!IsBinary(s))
					isDigits = false;
			}
			if (isDigits)
				return TokenType::Binary;
		}
		else if(base == "0o")
		{
			digits = token.value.substr(2, -1);
			bool isDigits = true;
			for (int i = 0; i < digits.length(); i++)
			{
				s = digits[i];
				if (!IsOctal(s))
					isDigits = false;
			}
			if (isDigits)
				return TokenType::Octal;
		}
		else if (base == "0x")
		{
			digits = token.value.substr(2, -1);
			bool isDigits = true;
			for (int i = 0; i < digits.length(); i++)
			{
				s = digits[i];
				if (!IsHexadecimal(s))
					isDigits = false;
			}
			if (isDigits)
				return TokenType::Hexadecimal;
		}
	}
	bool wereDot = false;
	for (int i = 0; i < token.value.length(); i++)
	{
		s = token.value[i];
		if (IsDecimal(s))
			continue;
		else if (s == ".")
			if (wereDot == false)
				wereDot = true;
			else
				return TokenType::Error;
		else
			return TokenType::Error;
	}
	if (wereDot)
		return TokenType::Float;
	else
		return TokenType::Integer;

	return TokenType::Error;
}

void CLexer::PrintTokens()
{
	m_output << m_tokens.size() << std::endl;
	for (int i = 0; i < m_tokens.size(); i++)
	{
		m_output << GetTokenName(m_tokens[i]) << " <" << m_tokens[i].value << "> line: " << m_tokens[i].line << " position: " << m_tokens[i].position << std::endl;
	}

}

void CLexer::AddToken(Token token)
{
	if (token.value != "")
	{
		token.type = GetTokenType(token);
		if (token.type == TokenType::Identifier && token.value.length() > 64)
			token.type = TokenType::Error;
		if (token.type == TokenType::Integer && token.value.length() > 7)
			token.type = TokenType::Error;
		m_tokens.push_back(token);
	}
}

void CLexer::Run()
{
	int lineNumber = 0;
	std::string line;
	bool multiStringComment = false;
	bool string = false;
	while (getline(m_input, line))
	{
		lineNumber++;
		std::string tokenValue;
		Token token;
		std::string ch;
		bool identifier = true;
		for (int i = 0; i < line.size(); ++i)
		{
			if (i > 0 && !string && !multiStringComment)
			{
				if (line[i - 1] == '/' and line[i] == '/')
				{
					token.value == "";
					break;
				}
			}

			if (multiStringComment)
			{
				if (i > 0)
					if (line[i - 1] == '*' and line[i] == '/')
					{
						multiStringComment = false;
					}
				continue;
			}

			if (i > 0 && !string)
			{
				if (line[i - 1] == '/' and line[i] == '*')
				{
					multiStringComment = true;
					continue;
				}
			}

			if (token.value == "")
			{
				token.line = lineNumber;
				token.position = i + 1;
			}

			if ((line[i] == ' ' || line[i] == '	') && !string && !multiStringComment)
			{
				AddToken(token);
				token.value = "";
				continue;
			}

			if (string && !multiStringComment)
			{
				if (line[i] != '"')
				{
					token.value += line[i];
				}
				else
				{
					token.value += line[i];
					AddToken(token);
					string = false;
					token.value = "";
				}
				continue;
			}

			if (line[i] == '"' && !multiStringComment)
			{
				string = true;
				AddToken(token);
				token.value = line[i];
				continue;
			}

			ch = line[i];
			if (IsLetter(ch) || IsDecimal(ch) || ch == "." || ch == "_")
			{
				if (identifier)
				{
					token.value += line[i];
				}
				else
				{
					AddToken(token);
					(line[i] == ' ' || line[i] == '	') ? token.value = "" : token.value = line[i];
					identifier = true;
				}
			}
			else
			{
				if (identifier)
				{
					AddToken(token);
					if (line[i] == ' ' || line[i] == '	')
						token.value = "";
					else
						token.value = line[i];
					identifier = false;
				}
				else
				{
					if (line[i] != ' ')
						token.value += line[i];
					else
					{
						AddToken(token);
						token.value = "";
					}
				}
			}

			if (i + 1 == line.size() && !string && !multiStringComment)
				AddToken(token);
		}
	}

	PrintTokens();
}