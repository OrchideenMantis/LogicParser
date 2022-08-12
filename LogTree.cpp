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

void LogTree::cleanRoots()
{
	delete rootNode;

	rootNode = nullptr;
}

std::string LogTree::verifyLogString(std::string logString)
{
	std::string logStringVerified;

	bool ignore = false;

	for (int i = 0; i < logString.length(); i++)
	{
		if (logString.at(i) == ' ' && logStringVerified.empty()) { continue; }
		if (logString.at(i) == ' ' && logString.at(i - 1) == ' ') { continue; }

	}

	return std::string();
}
