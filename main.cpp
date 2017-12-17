#include <iostream>
#include <exception>

#include "shady.h"

int main(int argc, char* argv[])
{
	try
	{
		Shady shady;
		shady.run();
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}

	return 0;
}
