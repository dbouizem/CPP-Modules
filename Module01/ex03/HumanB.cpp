#include "HumanB.hpp"
#include <iostream>

HumanB::HumanB(std::string name) : name(name), weapon(NULL)
{
}

void HumanB::setWeapon(Weapon& weapon)
{
	this->weapon = &weapon;
}

void HumanB::attack(void) const
{
	if (weapon == NULL)
	{
		std::cout << name << " has no weapon" << std::endl;
		return;
	}
	std::cout << name << " attacks with their " << weapon->getType()
		<< std::endl;
}
