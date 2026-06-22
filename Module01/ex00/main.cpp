#include "Zombie.hpp"

int main(void)
{
	Zombie* heapZombie;

	randomChump("Stack zombie");
	heapZombie = newZombie("Heap zombie");
	heapZombie->announce();
	delete heapZombie;
	return 0;
}
