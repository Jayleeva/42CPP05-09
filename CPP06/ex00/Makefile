SRC = main.cpp ScalarConverter.cpp is_type.cpp from_char.cpp from_int.cpp from_float.cpp from_double.cpp display.cpp 
OBJ = $(SRC:.cpp=.o)

CC = c++
RM = rm -f
CPPFLAGS = -Wall -Wextra -Werror -std=c++98
#-Wshadow -Wno-shadow

NAME = converter

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CPPFLAGS) $(OBJ) -o $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean $(NAME)

.PHONY: all clean fclean re