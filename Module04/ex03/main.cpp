#include "Character.hpp"
#include "Cure.hpp"
#include "Ice.hpp"
#include "MateriaSource.hpp"

static void	subjectTest()
{
	std::cout << "----- Subject test -----" << std::endl;
	IMateriaSource*	src = new MateriaSource();
	src->learnMateria(new Ice());
	src->learnMateria(new Cure());

	ICharacter*	me = new Character("me");
	AMateria*	tmp;

	tmp = src->createMateria("ice");
	me->equip(tmp);
	tmp = src->createMateria("cure");
	me->equip(tmp);

	ICharacter*	bob = new Character("bob");
	me->use(0, *bob);
	me->use(1, *bob);

	delete bob;
	delete me;
	delete src;
}

int	main()
{
	subjectTest();

	/*
		Optional extra tests:

		MateriaSource source;
		Character me("cloud");
		Character target("sephiroth");

		source.learnMateria(new Ice());
		source.learnMateria(new Cure());

		me.equip(source.createMateria("ice"));
		me.equip(source.createMateria("cure"));
		me.equip(source.createMateria("unknown"));
		me.use(0, target);
		me.use(1, target);
		me.use(2, target);
		me.unequip(0);
		me.use(0, target);

		Character copy(me);
		copy.use(1, target);
	*/

	return (0);
}
