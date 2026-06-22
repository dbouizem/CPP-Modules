#include "Zombie.hpp"
#include <cstddef>

int main(void)
{
	const int hordeSize = 5;
	Zombie* horde = zombieHorde(hordeSize, "Walker");

	if (horde == NULL)
		return 1;
	for (int i = 0; i < hordeSize; ++i)
		horde[i].announce();
	delete[] horde;
	return 0;
}
/*
new objet		-> delete objet
new Objet[N]	-> delete[] objets
*/
