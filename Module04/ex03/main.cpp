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

static void	extraTests()
{
	std::cout << std::endl;
	std::cout << "----- Extra tests -----" << std::endl;
	MateriaSource	source;
	Character		me("mack");
	Character		target("sephir");
	AMateria*		tmp;

	source.learnMateria(new Ice());
	source.learnMateria(new Cure());
	tmp = source.createMateria("unknown");
	if (!tmp)
		std::cout << "unknown materia was not created" << std::endl;//unknown materia was not created
	me.equip(source.createMateria("ice"));
	me.equip(source.createMateria("cure"));
	me.equip(source.createMateria("ice"));
	me.equip(source.createMateria("cure"));
	tmp = source.createMateria("ice");
	me.equip(tmp);
	delete tmp;
	me.use(0, target);//* shoots an ice bolt at sephir *
	me.use(1, target);// * heals sephir's wounds *
	me.use(4, target);//n’affiche rien, index invalide
	me.unequip(0);
	me.use(0, target);//n’affiche rien, car le slot 0 est vide après unequip

	Character copy(me);
	copy.use(1, target);//* heals sephir's wounds *

	Character assigned("assigned");
	assigned = me;
	assigned.use(2, target);//* shoots an ice bolt at sephir *
}

int	main()
{
	subjectTest();
	extraTests();
	return (0);
}
