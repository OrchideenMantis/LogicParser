#include "NumNode.h"

NumNode::NumNode(LogComparator logComparator, std::string firstChildString, std::string secondChildString) :
	logComparator(logComparator)
{
	initializeChildren(firstChildString, secondChildString);
}
 
//=================================================================================================

bool NumNode::calculateNodeValue()
{
	bool nodeValue = false;

	switch (logComparator)
	{
	case LogComparator::Equal :
		if (firstChild == secondChild) { nodeValue = true; }
		break;
	case LogComparator::Greater :
		if (firstChild > secondChild) { nodeValue = true; }
		break;
	case LogComparator::GreaterEqual :
		if (firstChild >= secondChild) { nodeValue = true; }
		break;
	case LogComparator::Lesser :
		if (firstChild < secondChild) { nodeValue = true; }
		break;
	case LogComparator::LesserEqual :
		if (firstChild <= secondChild) { nodeValue = true; }
		break;
	case LogComparator::NotEqual :
		if (firstChild != secondChild) { nodeValue = true; }
		break;
	default:
		std::cout << "Invalid Comparator!" << std::endl;
		return false;
	}

	return nodeValue;
}

//=================================================================================================

std::string NumNode::cleanChildString(std::string childString)
{
	std::string childStringClean;

	for (char c : childString) 
	{ 
		if (c != '(' && c != ' ' && c != ')' && c != '!') { childStringClean += c; } 
	}

	return childStringClean;
}

double NumNode::convertNumString(std::string numString)
{
	double d = -1;

	try { d = std::stod(numString); }
	catch (std::invalid_argument&) { std::cout << numString << " is not a number!" << std::endl; }
	catch (std::out_of_range&) { std::cout << numString << " is out of Range!" << std::endl; }

	return d;
}

//=================================================================================================

void NumNode::initializeChildren(std::string firstChildString, std::string secondChildString)
{
	this->firstChild = convertNumString(cleanChildString(firstChildString));
	this->secondChild = convertNumString(cleanChildString(secondChildString));
}
