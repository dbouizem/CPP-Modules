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
	const Animal*	dog = new Dog();
	const Animal*	cat = new Cat();

	std::cout << dog->getType() << ": ";
	dog->makeSound();
	std::cout << cat->getType() << ": ";
	cat->makeSound();

	delete dog;
	delete cat;
}

int	main()
{
	testAbstractAnimal();
	testPolymorphism();

	/*
		Previous ex01 tests still work, but ex02 focuses on Animal
		being abstract. Keep these as optional checks:

		Animal* animals[4];
		animals[0] = new Dog();
		animals[1] = new Dog();
		animals[2] = new Cat();
		animals[3] = new Cat();
		for (int i = 0; i < 4; i++)
			delete animals[i];

		Dog dog1;
		dog1.setIdea(0, "I like bones");
		Dog dog2(dog1);
		dog2.setIdea(0, "I like sleeping");
	*/

	return (0);
}
