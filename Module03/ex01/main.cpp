#include "ScavTrap.hpp"
#include <iostream>

int	main(void)
{
	std::cout << "=== ClapTrap base class ===" << std::endl;
	ClapTrap	clap("Clappy");

	clap.attack("target");

	std::cout << "\n=== ScavTrap derived class ===" << std::endl;
	ScavTrap	scav("Scavy");

	scav.attack("target");
	scav.takeDamage(25);
	scav.beRepaired(10);
	scav.guardGate();

	std::cout << "\n=== End of tests ===" << std::endl;
	return (0);
}
