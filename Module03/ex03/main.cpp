#include "DiamondTrap.hpp"
#include <iostream>

int	main(void)
{
	std::cout << "=== DiamondTrap construction and names ===" << std::endl;
	DiamondTrap	diamond("Diamond");

	std::cout << std::endl;
	diamond.whoAmI();

	std::cout << "\n=== DiamondTrap inherited actions ===" << std::endl;
	diamond.attack("training dummy");
	diamond.takeDamage(40);
	diamond.beRepaired(15);
	diamond.guardGate();
	diamond.highFivesGuys();

	std::cout << "\n=== DiamondTrap copy and assignment ===" << std::endl;
	DiamondTrap	copy(diamond);
	std::cout << std::endl;

	DiamondTrap	assigned;
	std::cout << std::endl;

	assigned = diamond;
	std::cout << std::endl;

	copy.whoAmI();
	std::cout << std::endl;

	assigned.whoAmI();
	std::cout << std::endl;

	std::cout << "=== End of main ===" << std::endl;
	return (0);
}
