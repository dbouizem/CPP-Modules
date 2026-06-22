#ifndef CONTACT_HPP
# define CONTACT_HPP

# include <string>

class Contact
{
	private:
		std::string firstName;
		std::string lastName;
		std::string nickname;
		std::string phoneNumber;
		std::string darkestSecret;
	public:
		Contact();

			void	setContact(const std::string &first,
						const std::string &last, const std::string &nick,
						const std::string &phone, const std::string &secret);

		void	displayShort(int index) const;
		void	displayFull() const;
};

#endif
