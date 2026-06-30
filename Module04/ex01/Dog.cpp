#include "Dog.hpp"

Dog::Dog()
{
	this->type = "Dog";
	this->brain = new Brain();
	std::cout << "Dog default constructor called" << std::endl;
}

Dog::Dog(const Dog& other) : Animal(other)
{
	this->brain = new Brain(*other.brain); // nouveau Brain copié // (Shallow copy)❌ his->brain = other.brain; //  copie seulement l’adresse
	std::cout << "Dog copy constructor called" << std::endl;
}

Dog&	Dog::operator=(const Dog& other)
{
	std::cout << "Dog copy assignment operator called" << std::endl;
	if (this != &other)
	{
		Animal::operator=(other);
		delete this->brain; // supprime l’ancien Brain // (Shallow copy)❌ rien a delete
		this->brain = new Brain(*other.brain); // nouveau Brain copié // (Shallow copy)❌ this->brain = other.brain; // copie seulement l’adresse
	}
	return (*this);
}

Dog::~Dog()
{
	std::cout << "Dog destructor called" << std::endl;
	delete this->brain; // supprime son propre Brain // (Shallow copy)❌ risque double delete
}

void	Dog::makeSound() const
{
	std::cout << "Woof!" << std::endl;
}

void	Dog::setIdea(int index, const std::string& idea)
{
	this->brain->setIdea(index, idea);
}

const std::string&	Dog::getIdea(int index) const
{
	return (this->brain->getIdea(index));
}
