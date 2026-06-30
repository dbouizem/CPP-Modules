#include "Animal.hpp"
#include "Cat.hpp"
#include "Dog.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"

int	main()
{
	std::cout << "----- Subject test -----" << std::endl;
	const Animal*	meta = new Animal();
	const Animal*	j = new Dog();
	const Animal*	i = new Cat();

	std::cout << j->getType() << " " << std::endl;
	std::cout << i->getType() << " " << std::endl;
	i->makeSound();
	j->makeSound();
	meta->makeSound();

	delete meta;
	delete j;
	delete i;

	std::cout << std::endl;
	std::cout << "----- Wrong polymorphism test -----" << std::endl;
	const WrongAnimal*	wrong = new WrongCat();

	std::cout << wrong->getType() << " " << std::endl;
	wrong->makeSound();
	delete wrong;
	return (0);
}

/*
Si on n’utilise pas virtual, le compilateur utilise le type du pointeur,
pas le type réel de l’objet.
*/
