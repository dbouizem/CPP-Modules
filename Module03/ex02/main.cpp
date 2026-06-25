#include "ScavTrap.hpp"
#include "FragTrap.hpp"
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
	scav.takeDamage(25);
	scav.beRepaired(10);
	scav.guardGate();

	std::cout << std::endl;
	std::cout << "=== FragTrap construction and actions ===" << std::endl;
	FragTrap	frag("Fraggy");

	frag.attack("training dummy");
	frag.takeDamage(40);
	frag.beRepaired(15);
	frag.highFivesGuys();

	/*
	std::cout << std::endl;
	std::cout << "=== Extra FragTrap tests ===" << std::endl;

	std::cout << "--- Test: ScavTrap vs FragTrap differences ---"
		<< std::endl;
	ScavTrap	scavCompare("ScavCompare");
	FragTrap	fragCompare("FragCompare");

	scavCompare.attack("comparison target");
	scavCompare.guardGate();
	fragCompare.attack("comparison target");
	fragCompare.highFivesGuys();

	std::cout << std::endl;
	std::cout << "--- Test: 100 hit points ---" << std::endl;
	FragTrap	hpTest("FragHpTest");

	hpTest.takeDamage(99);
	hpTest.attack("target after 99 damage");
	hpTest.takeDamage(1);
	hpTest.attack("target after 100 damage");
	hpTest.beRepaired(10);

	std::cout << std::endl;
	std::cout << "--- Test: 100 energy points ---" << std::endl;
	FragTrap	energyTest("FragEnergyTest");

	for (int i = 0; i < 101; i++)
		energyTest.attack("energy target");
	energyTest.beRepaired(5);

	std::cout << std::endl;
	std::cout << "--- Test: construction/destruction inside a block ---"
		<< std::endl;
	{
		FragTrap	blockTest("FragBlockTest");

		blockTest.highFivesGuys();
	}
	std::cout << "Block ended" << std::endl;
	*/

	std::cout << std::endl;
	std::cout << "=== FragTrap copy and assignment ===" << std::endl;
	FragTrap	copy(frag);
	FragTrap	assigned;

	assigned = frag;

	std::cout << std::endl;
	std::cout << "=== End of main ===" << std::endl;
	return (0);
}
