#include "ClapTrap.hpp"
#include <iostream>

int	main(void)
{
	ClapTrap	alpha("Alpha");
	ClapTrap	beta("Beta");

	std::cout << std::endl;
	alpha.attack("Beta");
	beta.takeDamage(4);
	beta.beRepaired(2);

	std::cout << std::endl;
	for (int i = 0; i < 10; i++)
		alpha.attack("training dummy");

	std::cout << std::endl;
	alpha.beRepaired(5);

	std::cout << std::endl;
	beta.takeDamage(50);
	beta.attack("Alpha");
	beta.beRepaired(10);

	std::cout << std::endl;
	ClapTrap	copy(alpha);
	ClapTrap	assigned;

	assigned = beta;
	std::cout << std::endl;
	return (0);
}
