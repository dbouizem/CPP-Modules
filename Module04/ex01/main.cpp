#include "Animal.hpp"
#include "Cat.hpp"
#include "Dog.hpp"

static void	testAnimalArray()
{
	const int	size = 6;
	Animal*		animals[size];

	std::cout << "----- Animal array test -----" << std::endl;
	for (int i = 0; i < size; i++)
	{
		if (i < size / 2)
			animals[i] = new Dog();
		else
			animals[i] = new Cat();
	}
	for (int i = 0; i < size; i++)
	{
		std::cout << animals[i]->getType() << ": ";
		animals[i]->makeSound();
	}
	for (int i = 0; i < size; i++)
		delete animals[i];
}

static void	testDogDeepCopy()
{
	std::cout << std::endl;
	std::cout << "----- Dog deep copy test -----" << std::endl;
	Dog	dog1;

	dog1.setIdea(0, "I like bones");
	Dog	dog2(dog1);
	dog2.setIdea(0, "I like sleeping");

	std::cout << "dog1 idea: " << dog1.getIdea(0) << std::endl;
	std::cout << "dog2 idea: " << dog2.getIdea(0) << std::endl;
}

static void	testCatAssignment()
{
	std::cout << std::endl;
	std::cout << "----- Cat assignment test -----" << std::endl;
	Cat	cat1;
	Cat	cat2;

	cat1.setIdea(0, "I want fish");
	cat2 = cat1;
	cat2.setIdea(0, "I want a nap");

	std::cout << "cat1 idea: " << cat1.getIdea(0) << std::endl;
	std::cout << "cat2 idea: " << cat2.getIdea(0) << std::endl;
}

int	main()
{
	std::cout << "----- Subject leak test -----" << std::endl;
	const Animal*	j = new Dog();
	const Animal*	i = new Cat();

	delete j;
	delete i;

	std::cout << std::endl;
	testAnimalArray();
	testDogDeepCopy();
	testCatAssignment();
	return (0);
}
