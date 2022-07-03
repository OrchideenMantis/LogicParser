#pragma once

#include "NodeInterface.h"

class NumNode : public NodeInterface
{
public:
	NumNode(LogComparator logComparator, std::string firstChildString, std::string secondChildString);

	~NumNode() = default;

public:
	bool calculateNodeValue();

private:
	std::string cleanChildString(std::string childString);
	double convertNumString(std::string numString);

	void initializeChildren(std::string firstChildString, std::string secondChildString);

private:
	LogComparator logComparator;

	double firstChild;
	double secondChild;
};

