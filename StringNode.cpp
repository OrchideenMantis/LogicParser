#include "StringNode.h"

StringNode::StringNode(LogComparator logComparator, std::string firstChildString, std::string secondChildString) :
	logComparator(logComparator)
{
	initializeChildren(firstChildString, secondChildString);
}

//=================================================================================================

bool StringNode::calculateNodeValue()
{
	bool nodeValue = false;

	switch (logComparator)
	{
	case LogComparator::Equal:
		if (firstChild == secondChild) { nodeValue = true; }
		break;
	case LogComparator::NotEqual:
		if (firstChild != secondChild) { nodeValue = true; }
		break;
	default:
		std::cout << "Invalid Comparator!" << std::endl;
		exit(1);
	}

	return nodeValue;
}

//=================================================================================================

std::string StringNode::cleanChildString(std::string childString)
{
	std::string childStringClean;

	bool startString = false;
	bool escape = false;

	for (char c : childString)
	{

		if (startString) 
		{ 

			if (escape) 
			{  
				escape = false;
				continue;
			}

			if (c == '"') { return childStringClean; }
			if (c == '\\') { escape = true; }

			childStringClean += c; 
		}

		if (c == '"') { startString = true; }
	}

	return childStringClean;
}

//=================================================================================================

void StringNode::initializeChildren(std::string firstChildString, std::string secondChildString)
{
	this->firstChild = cleanChildString(firstChildString);
	this->secondChild = cleanChildString(secondChildString);
}
