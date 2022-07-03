#include "OperatorNode.h"

OperatorNode::OperatorNode(LogOperator logOperator, std::string firstChildString, std::string secondChildString) :
	logOperator(logOperator)
{
	initializeChildren(firstChildString, secondChildString);
}

OperatorNode::~OperatorNode()
{
	delete firstChild;
	delete secondChild;
}

//=================================================================================================

bool OperatorNode::calculateNodeValue()
{
	bool nodeValue = false;

	switch (logOperator)
	{
	case LogOperator::AND:
		if (firstChild->calculateNodeValue() && secondChild->calculateNodeValue()) { nodeValue = true; }
		break;
	case LogOperator::NAND:
		if (!(firstChild->calculateNodeValue() && secondChild->calculateNodeValue())) { nodeValue = true; }
		break;
	case LogOperator::NOR:
		if (!(firstChild->calculateNodeValue() || secondChild->calculateNodeValue())) { nodeValue = true; }
		break;
	case LogOperator::OR:
		if (firstChild->calculateNodeValue() || secondChild->calculateNodeValue()) { nodeValue = true; }
		break;
	case LogOperator::XNOR:
		if (!( (!firstChild->calculateNodeValue() && secondChild->calculateNodeValue()) || (firstChild->calculateNodeValue() && !secondChild->calculateNodeValue()) )) { nodeValue = true; }
		break;
	case LogOperator::XOR:
		if ( (!firstChild->calculateNodeValue() && secondChild->calculateNodeValue()) || (firstChild->calculateNodeValue() && !secondChild->calculateNodeValue()) ) { nodeValue = true; }
		break;
	default:
		std::cout << "Invalid Operator!" << std::endl;
		exit(1);
	}

    return nodeValue;
}

//=================================================================================================

std::pair<int, std::string> OperatorNode::determineNextParentOperator(std::string logString)
{
	bool ignore = false;

	int index = -1;
	int bIndex = -1;

	int bLayer = 0;
	int bLayerOperator = 0;

	std::string tempString;
	std::pair<int, std::string> parentOperator;

	for (char c : logString)
	{
		index++;

		if (c == '"') { ignore = !ignore; }
		if (ignore) { continue; }

		if (c == '(') { bLayer++; }
		if (c == ')') { bLayer--; }

		if (c == ' ')
		{
			LogOperator logConjunction = convertStringToOperator(tempString);

			if ((logConjunction != LogOperator::UNDEFINED) && (bLayer <= bLayerOperator))
			{
				bLayerOperator = bLayer;

				parentOperator.first = bIndex + 1;
				parentOperator.second = tempString;
			}

			bIndex = index;
			tempString.clear();

			continue;
		}

		tempString += c;
	}

	if (!parentOperator.second.empty()) { return parentOperator; }

	//===========================================

	index = -1;
	bIndex = -1;

	tempString.clear();

	for (char c : logString)
	{
		index++;

		if (c == ' ')
		{
			LogComparator logComparator = convertStringToComparator(tempString);

			if (logComparator != LogComparator::UNDEFINED)
			{
				parentOperator.first = bIndex + 1;
				parentOperator.second = tempString;

				return parentOperator;
			}

			bIndex = index;
			tempString.clear();

			continue;
		}

		tempString += c;
	}

	if (parentOperator.second.empty()) 
	{ 
		std::cout << logString << " has no valid operator!" << std::endl;
		exit(1); 
	}

	return parentOperator;
}

std::pair<std::string, std::string> OperatorNode::determineChildStrings(std::string logString, int parentOperatorIndex)
{
	std::string firstChild;
	std::string secondChild;

	int parentOperatorIndexEnd = parentOperatorIndex;

	for (int i = parentOperatorIndex; i < logString.length(); i++)
	{
		if (logString[i] == ' ') { break; }
		parentOperatorIndexEnd++;
	}

	int index = -1;

	for (char c : logString)
	{
		index++;

		if (index < (parentOperatorIndex - 1)) { firstChild += c; }
		if (index > (parentOperatorIndexEnd)) { secondChild += c; }
	}

	std::pair<std::string, std::string> childStrings;

	childStrings.first = firstChild;
	childStrings.second = secondChild;

	return childStrings;
}

//=================================================================================================

LogComparator OperatorNode::convertStringToComparator(std::string comparatorString)
{
	LogComparator logComparator = LogComparator::UNDEFINED;

	std::map<std::string, LogComparator> comparators = 
	{	
		{"==", LogComparator::Equal},
		{">>", LogComparator::Greater},
		{">=", LogComparator::GreaterEqual},
		{"<<", LogComparator::Lesser},
		{"<=", LogComparator::LesserEqual},
		{"!=", LogComparator::NotEqual}	
	};

	if (comparators.find(comparatorString) != comparators.end())
	{
		logComparator = comparators[comparatorString];
	}

	return logComparator;
}

LogOperator OperatorNode::convertStringToOperator(std::string conjunctionString)
{
	LogOperator logConjunction = LogOperator::UNDEFINED;

	std::map<std::string, LogOperator> conjunctions = 
	{
		{"and", LogOperator::AND},
		{"&&", LogOperator::AND},
		{"nand", LogOperator::NAND},
		{"!&", LogOperator::NAND},
		{"nor", LogOperator::NOR},
		{"!|", LogOperator::NOR},
		{"or", LogOperator::OR},
		{"||", LogOperator::OR},
		{"xor", LogOperator::XOR},
		{"xnor", LogOperator::XNOR}
	};

	if (conjunctions.find(conjunctionString) != conjunctions.end())
	{
		logConjunction = conjunctions[conjunctionString];
	}

	return logConjunction;
}

//=================================================================================================

std::string OperatorNode::cleanChildString(std::string childString)
{
    std::string childStringClean;

	int bracketCounterOpen = 0;
    int bracketCounterClosed = 0;

	for (char c : childString)
    {
		if (c == ' ' && childString.empty()) { continue; }

		if (c == '(') { bracketCounterOpen++; }
        
		if (c == ')') { bracketCounterClosed++; }

		childStringClean += c;
    }

	if (bracketCounterOpen > bracketCounterClosed) { childStringClean.erase(0, 1); }
	if (bracketCounterClosed > bracketCounterOpen) { childStringClean.erase(childStringClean.length() - 1, 1); }

	return childStringClean;
}

//=================================================================================================

void OperatorNode::initializeChildren(std::string firstChildString, std::string secondChildString)
{
	this->firstChild = createChild(cleanChildString(firstChildString));
	this->secondChild = createChild(cleanChildString(secondChildString));
}

NodeInterface* OperatorNode::createChild(std::string childString)
{
    std::pair<int, std::string> parentOperator = OperatorNode::determineNextParentOperator(childString);
    std::pair<std::string, std::string> grandChildren = OperatorNode::determineChildStrings(childString, parentOperator.first);

    LogComparator logComparator = OperatorNode::convertStringToComparator(parentOperator.second);
    LogOperator logOperator = OperatorNode::convertStringToOperator(parentOperator.second);
	
	if (logOperator != LogOperator::UNDEFINED) 
	{
		return new OperatorNode(logOperator, grandChildren.first, grandChildren.second);
	}

	if (logComparator != LogComparator::UNDEFINED)
	{
		
		if ((grandChildren.first.find('"') == std::string::npos) && (grandChildren.second.find('"') == std::string::npos))
		{
			return new NumNode(logComparator, grandChildren.first, grandChildren.second);
		}
        
		if ((grandChildren.first.find('"') != std::string::npos) && (grandChildren.second.find('"') != std::string::npos))
		{
			return new StringNode(logComparator, grandChildren.first, grandChildren.second);
		}

		std::cout << "Cannot compare String to Numerical!" << std::endl;
		exit(1);
	}

	std::cout << "Child String: '" << childString << "' has no valid operator." << std::endl;
	exit(1);
}
