SRC = test_point.cpp ../../../Math/Basics/Point3D.cpp ../../../Math/Basics/Vector3D.cpp

NAME = test

OBJ = $(SRC:.cpp=.o)

CPPFLAGS = -std=c++20 -Wall -Wextra -Werror -g -fsanitize=address -I../../../Math/ -I../../../Raytracing

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
