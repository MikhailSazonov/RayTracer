SRC = main.cpp CmdLineParser.cpp Math/Basics/*.cpp Math/Figures/*.cpp \
		Math/Solutions/*.cpp  Raytracing/Illumination/*.cpp \
		Math/Transformers/*.cpp \
		Math/Transformers/RotationTransformers/*.cpp \
		Math/Transformers/ShearTransformers/*.cpp \
		Raytracing/Illumination/LightSources/*.cpp \
		Building/Camera/*.cpp Raytracing/FileUtils/*.cpp \
		Raytracing/Slicer/Slicer.cpp \
		Raytracing/RayTrace.cpp \
		Storage/SimpleStorage.cpp \
		ThreadPool/ThreadPool.cpp \
		Building/ConfigBuilder/*.cpp Building/Factories/*.cpp \
		Building/TransformerParser/TransformerParser.cpp \

NAME = raytracer

OBJ = $(SRC:.cpp=.o)

CPPFLAGS = -std=c++20 -Wall -Wextra -Werror -lpthread -pthread -I./Math/ -I./ \
			-I./Building/ -I./Raytracing -I./Storage -lconfig++

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
