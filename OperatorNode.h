#pragma once

#include "NodeInterface.h"

#include "NumNode.h"
#include "StringNode.h"

class OperatorNode : public NodeInterface
{
public:
	OperatorNode(LogOperator logOperator, std::string firstChildString, std::string secondChildString);

	~OperatorNode();

public:
	virtual bool calculateNodeValue();

public:
	static std::pair<int, std::string> determineNextParentOperator(std::string logString);
	static std::pair<std::string, std::string> determineChildStrings
	(std::string logString, int parentOperatorIndex);

	static NodeInterface* createChild(std::string childString);

	static LogComparator convertStringToComparator(std::string comparatorString);
	static LogOperator convertStringToOperator(std::string conjunctionString);

private:
	std::string cleanChildString(std::string childString);

	void initializeChildren(std::string firstChildString, std::string secondChildString);

private:
	LogOperator logOperator;

	NodeInterface* firstChild;
	NodeInterface* secondChild;
};

