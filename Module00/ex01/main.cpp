#include "PhoneBook.hpp"
#include <iostream>
#include <string>

int	main()
{
	PhoneBook phoneBook;
	std::string command;

	while (true)
	{
		std::cout << "Command (ADD, SEARCH, EXIT): ";
		if (!std::getline(std::cin, command) || command == "EXIT")
			break ;
		if (command == "ADD")
			phoneBook.addContact();
		else if (command == "SEARCH")
			phoneBook.searchContact();
	}
	return (0);
}
