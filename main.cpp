#include "LogTree.h"

int main()
{
	LogTree logTree = LogTree("1 == \"1\"");

	std::cout << logTree.calculateTreeValue() << std::endl;
}