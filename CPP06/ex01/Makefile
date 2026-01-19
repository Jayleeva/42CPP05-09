NAME = serializer

SRC = 	main.cpp \
		Serializer.cpp \

OBJ = $(SRC:.cpp=.o)

DIR = ./utils

CC = c++
CPPFLAGS = -Wall -Wextra -Werror -std=c++98
#-Wshadow -Wno-shadow

MKDIR = mkdir -p
RM = rm -rf

all: $(NAME)

$(DIR):
	$(MKDIR) $(DIR)

$(NAME): $(OBJ) | $(DIR)
	$(CC) $(CPPFLAGS) $(OBJ) -o $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean $(NAME)

.PHONY: all clean fclean re