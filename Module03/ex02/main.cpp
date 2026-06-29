#include "ScavTrap.hpp"
#include "FragTrap.hpp"
#include <iostream>

int	main(void)
{
	std::cout << "=== ScavTrap from ex01 ===" << std::endl;
	ScavTrap	scav("Scavy");

	scav.attack("target");
	scav.guardGate();

	std::cout << "\n=== FragTrap from ex02 ===" << std::endl;
	FragTrap	frag("Fraggy");

	frag.attack("target");
	frag.takeDamage(40);
	frag.beRepaired(15);
	frag.highFivesGuys();

	std::cout << "\n=== End of tests ===" << std::endl;
	return (0);
}
