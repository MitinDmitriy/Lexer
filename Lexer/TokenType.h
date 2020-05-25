#pragma once

enum class TokenType
{
	Identifier,				
	Integer,				
	Float,					
	Binary,					
	Octal,					
	Hexadecimal,			
	Char,					
	String,					
	Array,
	Keyword,
	ArithmeticOperator,		
	ComparisonOperator,		
	LogicOperator,			
	Bracket,				
	Separator,				
	Comment,				
	Error,
	EoF
};