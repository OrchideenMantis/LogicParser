#pragma once

#include "OperatorNode.h"

class LogTree
{
public:
	LogTree();
	LogTree(std::string logString);

	~LogTree();

public:
	bool calculateTreeValue();

	void setRoot(std::string logString);
	void cleanRoots();

private:
	std::string verifyLogString(std::string logString);

protected:
	NodeInterface* rootNode;
};
