NAME = converter

SRC = 	main.cpp \
		ScalarConverter.cpp \
		is_type.cpp \
		sto.cpp \
		convert_and_display.cpp \
		display.cpp

OBJ = $(SRC:.cpp=.o)


CC = c++
CPPFLAGS = -Wall -Wextra -Werror -std=c++98
#-Wshadow -Wno-shadow

MKDIR = mkdir -p
RM = rm -rf

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CPPFLAGS) $(OBJ) -o $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean $(NAME)

.PHONY: all clean fclean re