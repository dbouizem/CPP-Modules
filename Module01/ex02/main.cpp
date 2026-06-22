#include <iostream>
#include <string>

int main(void)
{
	std::string string = "HI THIS IS BRAIN";
	std::string* stringPTR = &string;
	std::string& stringREF = string;

	std::cout << &string << std::endl;
	std::cout << stringPTR << std::endl;
	std::cout << &stringREF << std::endl;
	std::cout << string << std::endl;
	std::cout << *stringPTR << std::endl;
	std::cout << stringREF << std::endl;
	return 0;
}

/*
Le symbole * a ici deux utilisations :
	std::string* stringPTR;
Il indique que stringPTR est un pointeur.
	*stringPTR
Il déréférence le pointeur, c’est-à-dire qu’il récupère la valeur située à l’adresse.
*/
