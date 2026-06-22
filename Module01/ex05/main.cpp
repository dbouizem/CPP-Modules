#include "Harl.hpp"

#include <iostream>

int main(int argc, char **argv)
{
	Harl harl;
	const std::string levels[4] = {"DEBUG", "INFO", "WARNING", "ERROR"};

	if (argc > 1)
	{
		for (int i = 1; i < argc; ++i)
			harl.complain(argv[i]);
	}
	else
	{
		for (int i = 0; i < 4; ++i)
		{
			std::cout << "[ " << levels[i] << " ]" << std::endl;
			harl.complain(levels[i]);
			if (i < 3)
				std::cout << std::endl;
		}
	}
	return 0;
}
