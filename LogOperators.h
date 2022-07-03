#pragma once

enum class LogComparator
{
	Equal,
	Greater,
	GreaterEqual,
	Lesser,
	LesserEqual,
	NotEqual,
	UNDEFINED
};

enum class LogOperator
{
	AND,
	NAND,
	NOR,
	OR,
	XOR,
	XNOR,
	UNDEFINED
};
