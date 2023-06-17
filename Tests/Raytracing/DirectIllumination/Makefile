SRC = test_direct.cpp ../../../Math/Basics/Vector3D.cpp \
	../../../Math/Basics/Point3D.cpp ../../../Raytracing/Illumination/Ray.cpp \
	../../../Raytracing/Illumination/LightSources/DirectIllumination.cpp

NAME = test

OBJ = $(SRC:.cpp=.o)

CPPFLAGS = -std=c++20 -Wall -Wextra -Werror -g -fsanitize=thread -I../../../Raytracing/ -I../../../Math/ -I../../../

$(NAME): $(SRC)
	g++ $(CPPFLAGS) $(SRC) -o $(NAME)

all: $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
