#include "Animal.hpp"
#include "Cat.hpp"
#include "Dog.hpp"

static void	testAbstractAnimal()
{
	std::cout << "----- Abstract Animal test -----" << std::endl;
	std::cout << "Animal cannot be instantiated directly in ex02." << std::endl;
	std::cout << "Only concrete children like Dog and Cat can be created." << std::endl;
	// Animal animal; // impossible: Animal is abstract
	// Animal* meta = new Animal(); // impossible too
}

static void	testPolymorphism()
{
	std::cout << std::endl;
	std::cout << "----- Polymorphism test -----" << std::endl;
	Animal*	animals[4];

	animals[0] = new Dog();
	animals[1] = new Dog();
	animals[2] = new Cat();
	animals[3] = new Cat();
	for (int i = 0; i < 4; i++)
	{
		std::cout << animals[i]->getType() << ": ";
		animals[i]->makeSound();
	}
	for (int i = 0; i < 4; i++)
		delete animals[i];
}

int	main()
{
	testAbstractAnimal();
	testPolymorphism();

	return (0);
}
