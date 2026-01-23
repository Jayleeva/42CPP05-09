NAME = btc

SRC = 	main.cpp \
		BitcoinExchange.cpp \

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