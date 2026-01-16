NAME = converter

SRC_DIR = ./src
OBJ_DIR = ./obj
DIR = ./obj ./obj/utils

SRC =	main.cpp \
		ScalarConverter.cpp \
		utils/is_type.cpp \
		utils/sto.cpp \
		utils/convert_and_display.cpp \
		utils/from_char.cpp \
		utils/from_int.cpp \
		utils/from_float.cpp \
		utils/from_double.cpp \
		utils/display.cpp 

SRCS = $(addprefix $(SRC_DIR)/, $(SRC))

OBJ = $(SRC:.c=.o)
OBJS = $(addprefix $(OBJ_DIR)/, $(OBJ))

INCLUDES = -I/usr/include

CC = c++
CPPFLAGS = -Wall -Wextra -Werror -I ./inc -g -std=c++98
#-Wshadow -Wno-shadow
MKDIR = mkdir -p
RM = rm -f

all: $(NAME)

$(DIR):
	$(MKDIR) $(DIR)

$(NAME): $(OBJS) | $(DIR)
	@${CC} ${CPPFLAGS} ${OBJS} -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(DIR)
	@$(CC) $(CFLAGS) -o $@ -c $< $(INCLUDES)

clean:
	@$(RM) $(OBJ_DIR)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re