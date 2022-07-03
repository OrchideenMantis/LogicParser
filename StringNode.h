#pragma once

#include "NodeInterface.h"

class StringNode : public NodeInterface
{
public:
	StringNode(LogComparator logComparator, std::string firstChildString, std::string secondChildString);

	~StringNode() = default;

public:
	bool calculateNodeValue();

private:
	std::string cleanChildString(std::string childString);

	void initializeChildren(std::string firstChildString, std::string secondChildString);

private:
	LogComparator logComparator;

	std::string firstChild;
	std::string secondChild;
};
