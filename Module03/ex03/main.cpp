#include "DiamondTrap.hpp"
#include <iostream>

int	main(void)
{
	std::cout << "=== ClapTrap test ===" << std::endl;
	ClapTrap	clap("Basic");

	clap.attack("target");
	clap.takeDamage(3);
	clap.beRepaired(2);

	std::cout << std::endl;
	std::cout << "=== ScavTrap test ===" << std::endl;
	ScavTrap	scav("Serena");

	scav.attack("training dummy");
	scav.guardGate();

	std::cout << std::endl;
	std::cout << "=== FragTrap test ===" << std::endl;
	FragTrap	frag("Fraggy");

	frag.attack("training dummy");
	frag.highFivesGuys();

	std::cout << std::endl;
	std::cout << "=== DiamondTrap construction and actions ===" << std::endl;
	DiamondTrap	diamond("Diamond");

	diamond.whoAmI();
	diamond.attack("training dummy");
	diamond.takeDamage(40);
	diamond.beRepaired(15);
	diamond.guardGate();
	diamond.highFivesGuys();

	/*
	std::cout << std::endl;
	std::cout << "=== Extra DiamondTrap tests ===" << std::endl;

	std::cout << "--- Test: one ClapTrap construction in diamond ---"
		<< std::endl;
	{
		DiamondTrap	blockTest("BlockDiamond");

		blockTest.whoAmI();
		blockTest.attack("block target");
	}
	std::cout << "Block ended" << std::endl;

	std::cout << std::endl;
	std::cout << "--- Test: 50 energy points from ScavTrap ---"
		<< std::endl;
	DiamondTrap	energyTest("EnergyDiamond");

	for (int i = 0; i < 51; i++)
		energyTest.attack("energy target");
	energyTest.beRepaired(5);

	std::cout << std::endl;
	std::cout << "--- Test: 100 hit points from FragTrap ---"
		<< std::endl;
	DiamondTrap	hpTest("HpDiamond");

	hpTest.takeDamage(99);
	hpTest.attack("target after 99 damage");
	hpTest.takeDamage(1);
	hpTest.attack("target after 100 damage");
	hpTest.beRepaired(10);
	*/

	std::cout << std::endl;
	std::cout << "=== DiamondTrap copy and assignment ===" << std::endl;
	DiamondTrap	copy(diamond);
	DiamondTrap	assigned;

	assigned = diamond;
	copy.whoAmI();
	assigned.whoAmI();

	std::cout << std::endl;
	std::cout << "=== End of main ===" << std::endl;
	return (0);
}
