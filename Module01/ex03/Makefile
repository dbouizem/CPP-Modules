NAME = violence

CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98

SRCS = main.cpp Weapon.cpp HumanA.cpp HumanB.cpp
OBJ_DIR = obj/
OBJS = $(addprefix $(OBJ_DIR), $(SRCS:.cpp=.o))
LEGACY_OBJS = $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o: %.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)main.o: HumanA.hpp HumanB.hpp Weapon.hpp
$(OBJ_DIR)Weapon.o: Weapon.hpp
$(OBJ_DIR)HumanA.o: HumanA.hpp Weapon.hpp
$(OBJ_DIR)HumanB.o: HumanB.hpp Weapon.hpp

clean:
	rm -rf $(OBJ_DIR)
	rm -f $(LEGACY_OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
