#include "Zombie.hpp"
#include <iostream>

Zombie::Zombie(void)
{
}

Zombie::~Zombie(void)
{
	std::cout << name << " has been destroyed" << std::endl;
}

void Zombie::setName(std::string name)
{
	this->name = name;
}

void Zombie::announce(void)
{
	std::cout << name << ": BraiiiiiiinnnzzzZ..." << std::endl;
}
