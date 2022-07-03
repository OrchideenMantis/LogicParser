#pragma once

#include <iostream>
#include <map>
#include <string>

#include "LogOperators.h"

class NodeInterface
{
public:
	virtual ~NodeInterface() = default;

public:
	virtual bool calculateNodeValue() = 0;

private:
	virtual std::string cleanChildString(std::string childString) = 0;

	virtual void initializeChildren(std::string firstString, std::string secondString) = 0;
};

