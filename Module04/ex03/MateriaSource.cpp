#include "MateriaSource.hpp"

MateriaSource::MateriaSource()
{
	for (int i = 0; i < 4; i++)
		this->templates[i] = 0;
}

MateriaSource::MateriaSource(const MateriaSource& other)
{
	for (int i = 0; i < 4; i++)
		this->templates[i] = 0;
	for (int i = 0; i < 4; i++)
	{
		if (other.templates[i])
			this->templates[i] = other.templates[i]->clone();
	}
}

MateriaSource&	MateriaSource::operator=(const MateriaSource& other)
{
	if (this != &other)
	{
		this->clearTemplates();
		for (int i = 0; i < 4; i++)
		{
			if (other.templates[i])
				this->templates[i] = other.templates[i]->clone();
			else
				this->templates[i] = 0;
		}
	}
	return (*this);
}

MateriaSource::~MateriaSource()
{
	this->clearTemplates();
}

void	MateriaSource::clearTemplates()
{
	for (int i = 0; i < 4; i++)
	{
		delete this->templates[i];
		this->templates[i] = 0;
	}
}

void	MateriaSource::learnMateria(AMateria* materia)
{
	if (!materia)
		return ;
	for (int i = 0; i < 4; i++)
	{
		if (!this->templates[i])
		{
			this->templates[i] = materia->clone();
			delete materia;
			return ;
		}
	}
	delete materia;
}

AMateria*	MateriaSource::createMateria(const std::string& type)
{
	for (int i = 0; i < 4; i++)
	{
		if (this->templates[i] && this->templates[i]->getType() == type)
			return (this->templates[i]->clone());
	}
	return (0);
}
