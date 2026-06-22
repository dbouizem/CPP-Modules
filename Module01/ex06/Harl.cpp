#include "Harl.hpp"

#include <iostream>

void Harl::debug(void)
{
	std::cout << "[ DEBUG ]" << std::endl;
	std::cout << "I love having extra bacon for my "
		"7XL-double-cheese-triple-pickle-special-ketchup burger. "
		"I really do!" << std::endl;
}

void Harl::info(void)
{
	std::cout << "[ INFO ]" << std::endl;
	std::cout << "I cannot believe adding extra bacon costs more money. "
		"You didn't put enough bacon in my burger! If you did, "
		"I wouldn't be asking for more!" << std::endl;
}

void Harl::warning(void)
{
	std::cout << "[ WARNING ]" << std::endl;
	std::cout << "I think I deserve to have some extra bacon for free. "
		"I've been coming for years, whereas you started working here "
		"just last month." << std::endl;
}

void Harl::error(void)
{
	std::cout << "[ ERROR ]" << std::endl;
	std::cout << "This is unacceptable! I want to speak to the manager now."
		<< std::endl;
}

void Harl::complain(std::string level)
{
	typedef void (Harl::*Complaint)(void);
	const std::string levels[4] = {"DEBUG", "INFO", "WARNING", "ERROR"};
	Complaint complaints[4] = {
		&Harl::debug,
		&Harl::info,
		&Harl::warning,
		&Harl::error
	};
	int levelIndex;

	levelIndex = 0;
	while (levelIndex < 4 && level != levels[levelIndex])
		++levelIndex;
	switch (levelIndex)
	{
	case 0:
		(this->*complaints[0])();
		std::cout << std::endl;
		// fall through
	case 1:
		(this->*complaints[1])();
		std::cout << std::endl;
		// fall through
	case 2:
		(this->*complaints[2])();
		std::cout << std::endl;
		// fall through
	case 3:
		(this->*complaints[3])();
		break;
	default:
		std::cout << "[ Probably complaining about insignificant problems ]"
			<< std::endl;
	}
}
