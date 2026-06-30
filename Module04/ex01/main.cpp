#include "Animal.hpp"
#include "Cat.hpp"
#include "Dog.hpp"

static void	testAnimalArray()
{
	const int	size = 4;
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

static void	testDogCopyConstructor()
{
	std::cout << std::endl;
	std::cout << "----- Dog copy constructor test -----" << std::endl;
	Dog	basic;

	basic.setIdea(0, "basic keeps this idea");
	std::cout << "basic idea : " << basic.getIdea(0) << std::endl;
	{
		Dog	tmp = basic;

		tmp.setIdea(0, "tmp has its own idea");
		std::cout << "tmp idea: " << tmp.getIdea(0) << std::endl;
	}
	std::cout << "basic idea after tmp destruction: "
		<< basic.getIdea(0) << std::endl;
}
/*
Parce que si tu as fait une shallow copy :
basic.brain et tmp.brain pointent vers le même Brain
Donc quand tmp est détruit, il delete le Brain commun.
Après, basic.getIdea(0) peut crash ou afficher n’importe quoi.
*/

static void	testAssignment()
{
	std::cout << std::endl;
	std::cout << "----- Assignment deep copy test -----" << std::endl;
	Dog	dog1;
	Dog	dog2;
	Cat	cat1;
	Cat	cat2;

	dog1.setIdea(0, "dog1 original idea");
	dog2 = dog1;
	dog2.setIdea(0, "dog2 changed idea");
	std::cout << "dog1 idea: " << dog1.getIdea(0) << std::endl;
	std::cout << "dog2 idea: " << dog2.getIdea(0) << std::endl;

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
	testDogCopyConstructor();
	testAssignment();
	return (0);
}
