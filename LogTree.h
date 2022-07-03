#pragma once

#include "OperatorNode.h"

class LogTree
{
public:
	LogTree();
	LogTree(std::string logString);

	~LogTree();

public:
	void setRoot(std::string logString);
	bool calculateTreeValue();

public:
	virtual void clean();

protected:
	NodeInterface* rootNode;
};
