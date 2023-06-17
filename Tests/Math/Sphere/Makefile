SRC = test_sphere.cpp ../../../Math/Basics/Point3D.cpp ../../../Math/Basics/Vector3D.cpp \
						../../../Math/Figures/Sphere.cpp ../../../Math/Figures/Params/IntersectParams.cpp \
						../../../Math/Figures/AFigure.cpp \
						../../../Math/Transformers/BaseTransformer.cpp \
						../../../Math/Transformers/ATransformer.cpp \
						../../../Math/Solutions/Quadr.cpp \
						../../../Math/Solutions/MatrixInv.cpp \
						../../../Math/Solutions/Linear4x.cpp \
						../../../Raytracing/Illumination/Ray.cpp

NAME = test

OBJ = $(SRC:.cpp=.o)

CPPFLAGS = -std=c++20 -Wall -Wextra -Werror -g -fsanitize=address -I../../../Math -I../../../Raytracing -I../../../.

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
