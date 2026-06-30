#include "AMateria.hpp"
#include "ICharacter.hpp"

AMateria::AMateria() : type("")
{
}

AMateria::AMateria(const std::string& type) : type(type)
{
}

AMateria::AMateria(const AMateria& other) : type(other.type)
{
}

AMateria&	AMateria::operator=(const AMateria& other)
{
	(void)other;
	return (*this);
}

AMateria::~AMateria()
{
}

const std::string&	AMateria::getType() const
{
	return (this->type);
}

void	AMateria::use(ICharacter& target)
{
	(void)target;
}
