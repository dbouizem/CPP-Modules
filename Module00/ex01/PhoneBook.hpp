#ifndef PHONEBOOK_HPP
# define PHONEBOOK_HPP

# include "Contact.hpp"

class PhoneBook
{
	private:
			enum { MAX_CONTACTS = 8 };
			Contact	contacts[MAX_CONTACTS];
				int		contactCount;
				int		nextIndex;

	public:
			PhoneBook();
			void	addContact();
			void	searchContact() const;
};

#endif
