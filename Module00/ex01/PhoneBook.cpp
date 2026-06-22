#include "PhoneBook.hpp"
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

PhoneBook::PhoneBook() : contactCount(0), nextIndex(0)
{
}

static	std::string readField(const std::string &message)
{
	std::string	input;

	while (input.empty())
	{
		std::cout << message;
		if (!std::getline(std::cin, input))
			return "";
		if (input.empty())
			std::cout << "Field cannot be empty." << std::endl;
	}
	return input;
}

void	PhoneBook::addContact()
{
	std::string first;
	std::string last;
	std::string nick;
	std::string phone;
	std::string secret;

	first = readField("First name: ");
	if (first.empty())
		return ;
	last = readField("Last name: ");
	if (last.empty())
		return ;
	nick = readField("Nickname: ");
	if (nick.empty())
		return ;
	phone = readField("Phone number: ");
	if (phone.empty())
		return ;
	secret = readField("Darkest secret: ");
	if (secret.empty())
		return ;
	contacts[nextIndex].setContact(first, last, nick, phone, secret);
	nextIndex = (nextIndex + 1) % MAX_CONTACTS;
	if (contactCount < MAX_CONTACTS)
		contactCount++;
}

void	PhoneBook::searchContact() const
{
	std::string		input;
	int				index;
	char			extra;
	int				i;

	if (contactCount == 0)
	{
		std::cout << "PhoneBook is empty." << std::endl;
		return ;
	}
	std::cout << std::setw(10) << "index" << "|";
	std::cout << std::setw(10) << "first name" << "|";
	std::cout << std::setw(10) << "last name" << "|";
	std::cout << std::setw(10) << "nickname" << std::endl;
	i = 0;
	while (i < contactCount)
	{
		contacts[i].displayShort(i);
		i++;
	}
	std::cout << "Index: ";
	if (!std::getline(std::cin, input))
		return ;
	std::istringstream stream(input);
	if (!(stream >> index) || (stream >> extra)
		|| index < 0 || index >= contactCount)
	{
		std::cout << "Invalid index." << std::endl;
		return ;
	}
	contacts[index].displayFull();
}
