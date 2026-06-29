#include "ClapTrap.hpp"
#include <iostream>

int	main(void)
{
	std::cout << "=== 1. Construction ===" << std::endl;
	ClapTrap	alpha("Alpha");
	ClapTrap	beta("Beta");

	std::cout << "\n=== 2. Basic actions ===" << std::endl;
	alpha.attack("Beta");
	beta.takeDamage(4);
	beta.beRepaired(2);

	std::cout << "\n=== 3. Energy limit ===" << std::endl;
	for (int i = 0; i < 10; i++)
		alpha.attack("training dummy");
	alpha.beRepaired(5);

	std::cout << "\n=== 4. Hit points limit ===" << std::endl;
	beta.takeDamage(50);
	beta.attack("Alpha");
	beta.beRepaired(10);

	std::cout << "\n=== 5. Copy and assignment ===" << std::endl;
	ClapTrap	copy(alpha);
	ClapTrap	assigned;
	assigned = beta;
	std::cout << std::endl;
	return (0);
}
