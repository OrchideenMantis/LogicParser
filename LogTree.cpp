#include "LogTree.h"

LogTree::LogTree() :
	rootNode(nullptr)
{}

LogTree::LogTree(std::string logString)
{
	setRoot(logString);
}

LogTree::~LogTree()
{
	delete rootNode;
}

//=================================================================================================

void LogTree::setRoot(std::string logString)
{
	this->rootNode = OperatorNode::createChild(logString);
}

bool LogTree::calculateTreeValue()
{
	if (rootNode == nullptr) 
	{ 
		std::cout << "Root is rotten. Set new Root!" << std::endl;
		exit(1);
	}

	return rootNode->calculateNodeValue();
}

//=================================================================================================

void LogTree::clean()
{
	delete rootNode;

	rootNode = nullptr;
}
