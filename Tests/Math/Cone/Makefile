SRC = test_cone.cpp ../../../Math/Basics/Point3D.cpp ../../../Math/Basics/Vector3D.cpp \
						../../../Math/Figures/Cone.cpp ../../../Math/Figures/Params/IntersectParams.cpp \
						../../../Math/Solutions/Quadr.cpp \
						../../../Math/Solutions/MatrixInv.cpp \
						../../../Math/Solutions/Linear4x.cpp \
						../../../Math/Transformers/TranslationTransformer.cpp \
						../../../Math/Transformers/ATransformer.cpp \
						../../../Raytracing/Illumination/Ray.cpp

NAME = test

OBJ = $(SRC:.cpp=.o)

CPPFLAGS = -std=c++20 -Wall -Wextra -Werror -g -fsanitize=address -I../../../Math -I../../../Raytracing

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
