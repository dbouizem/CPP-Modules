#include "Character.hpp"

Character::Character() : name("")
{
	for (int i = 0; i < 4; i++)
		this->inventory[i] = 0;
	for (int i = 0; i < 100; i++)
		this->floor[i] = 0;
}

Character::Character(const std::string& name) : name(name)
{
	for (int i = 0; i < 4; i++)
		this->inventory[i] = 0;
	for (int i = 0; i < 100; i++)
		this->floor[i] = 0;
}

Character::Character(const Character& other) : name(other.name)
{
	for (int i = 0; i < 4; i++)
		this->inventory[i] = 0;
	for (int i = 0; i < 100; i++)
		this->floor[i] = 0;
	for (int i = 0; i < 4; i++)
	{
		if (other.inventory[i])
			this->inventory[i] = other.inventory[i]->clone();
	}
}

Character&	Character::operator=(const Character& other)
{
	if (this != &other)
	{
		this->clearInventory();
		this->clearFloor();
		this->name = other.name;
		for (int i = 0; i < 4; i++)
		{
			if (other.inventory[i])
				this->inventory[i] = other.inventory[i]->clone();
			else
				this->inventory[i] = 0;
		}
	}
	return (*this);
}

Character::~Character()
{
	this->clearInventory();
	this->clearFloor();
}

void	Character::clearInventory()
{
	for (int i = 0; i < 4; i++)
	{
		delete this->inventory[i];
		this->inventory[i] = 0;
	}
}

void	Character::clearFloor()
{
	for (int i = 0; i < 100; i++)
	{
		delete this->floor[i];
		this->floor[i] = 0;
	}
}

void	Character::saveOnFloor(AMateria* materia)
{
	if (!materia)
		return ;
	for (int i = 0; i < 100; i++)
	{
		if (!this->floor[i])
		{
			this->floor[i] = materia;
			return ;
		}
	}
}

const std::string&	Character::getName() const
{
	return (this->name);
}

void	Character::equip(AMateria* m)
{
	if (!m)
		return ;
	for (int i = 0; i < 4; i++)
	{
		if (!this->inventory[i])
		{
			this->inventory[i] = m;
			return ;
		}
	}
}

void	Character::unequip(int idx)
{
	if (idx < 0 || idx >= 4 || !this->inventory[idx])
		return ;
	this->saveOnFloor(this->inventory[idx]);
	this->inventory[idx] = 0;
}

void	Character::use(int idx, ICharacter& target)
{
	if (idx < 0 || idx >= 4 || !this->inventory[idx])
		return ;
	this->inventory[idx]->use(target);
}
