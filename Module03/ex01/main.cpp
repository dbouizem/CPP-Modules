#include "ScavTrap.hpp"
#include <iostream>

int	main(void)
{
	std::cout << "=== ClapTrap test ===" << std::endl;
	ClapTrap	clap("Basic");

	clap.attack("target");
	clap.takeDamage(3);
	clap.beRepaired(2);

	std::cout << std::endl;
	std::cout << "=== ScavTrap construction and actions ===" << std::endl;
	ScavTrap	scav("Serena");

	scav.attack("training dummy");
	scav.takeDamage(25);
	scav.beRepaired(10);
	scav.guardGate();

	/*
	std::cout << std::endl;
	std::cout << "=== Extra ScavTrap tests ===" << std::endl;

	std::cout << "--- Test: 100 hit points ---" << std::endl;
	ScavTrap	hpTest("HpTest");

	hpTest.takeDamage(99);
	hpTest.attack("target after 99 damage");
	hpTest.takeDamage(1);
	hpTest.attack("target after 100 damage");
	hpTest.beRepaired(10);

	std::cout << std::endl;
	std::cout << "--- Test: 50 energy points ---" << std::endl;
	ScavTrap	energyTest("EnergyTest");

	for (int i = 0; i < 51; i++)
		energyTest.attack("energy target");
	energyTest.beRepaired(5);

	std::cout << std::endl;
	std::cout << "--- Test: construction/destruction inside a block ---"
		<< std::endl;
	{
		ScavTrap	blockTest("BlockTest");

		blockTest.guardGate();
	}
	std::cout << "Block ended" << std::endl;
	*/

	std::cout << std::endl;
	std::cout << "=== ScavTrap copy and assignment ===" << std::endl;
	ScavTrap	copy(scav);
	ScavTrap	assigned;

	assigned = scav;

	std::cout << std::endl;
	std::cout << "=== End of main ===" << std::endl;
	return (0);
}
