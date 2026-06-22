#include "Contact.hpp"
#include <iomanip>
#include <iostream>

Contact::Contact()
{

}

void	Contact::setContact(const std::string &first,
				const std::string &last, const std::string &nick,
				const std::string &phone, const std::string &secret)
{
	firstName = first;
	lastName = last;
	nickname = nick;
	phoneNumber = phone;
	darkestSecret = secret;
}

static	std::string formatField(const std::string &str)
{
	if (str.length() > 10)
		return (str.substr(0, 9) + ".");
	return str;
}

void	Contact::displayShort(int index) const
{
	std::cout << std::setw(10) << index << "|";
	std::cout << std::setw(10) << formatField(firstName) << "|";
	std::cout << std::setw(10) << formatField(lastName) << "|";
	std::cout << std::setw(10) << formatField(nickname) << std::endl;
}

void	Contact::displayFull() const
{
	std::cout << "First name: " << firstName << std::endl;
	std::cout << "Last name: " << lastName << std::endl;
	std::cout << "Nickname: " << nickname << std::endl;
	std::cout << "Phone number: " << phoneNumber << std::endl;
	std::cout << "Darkest secret: " << darkestSecret << std::endl;
}
