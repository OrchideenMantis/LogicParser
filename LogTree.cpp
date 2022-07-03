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
		std::cout << "No Root found! Set new Root." << std::endl;
		return 0; 
	}

	return rootNode->calculateNodeValue();
}

//=================================================================================================

void LogTree::clean()
{
	delete rootNode;

	rootNode = nullptr;
}
