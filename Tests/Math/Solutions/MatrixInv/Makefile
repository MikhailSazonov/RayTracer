SRC = test_matrix.cpp ../../../../Math/Solutions/MatrixInv.cpp ../../../../Math/Solutions/Linear4x.cpp

NAME = test

OBJ = $(SRC:.cpp=.o)

CPPFLAGS = -std=c++20 -Wall -Wextra -Werror -g -fsanitize=address -I../../../../Math/

$(NAME): $(SRC)
	g++ $(CPPFLAGS) $(SRC) -o $(NAME)

all: $(NAME)

debug:
	g++ $(CPPFLAGS) $(DEBUGFLAGS) $(SRC) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
