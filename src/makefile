####################################### Directories #########################################
# Here are the project directories

# Names of the executables
PROJECT_EXE = Project
TEST_EXE = ../Test

# Names of the directories
DIR_HEADERS = ../include
DIR_SOURCES = ../src
DIR_OBJECTS = ../obj
DIR_TESTS = ../tests
DIR_GCOV = ../docs/gcov



########################################## FLAGS ###########################################
# Specifies the compiler, the C++ version, and the flags used to compile the code

CC = g++ -std=c++11
CFLAGS = -I$(DIR_HEADERS) -ftest-coverage -fprofile-arcs
LIBS = -lm -lSDL2 -lSDL2_image

# Flags that I will need for SDL (the user will have to install these 4 packages)
# Uncomment when the interface is ready
#LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer



########################## Lists with the names of the code files ##########################
# Defines the location of the source code files and header files

_HEADERS = Piece.hpp Pawn.hpp Knight.hpp Bishop.hpp Rook.hpp Queen.hpp King.hpp States.hpp Texture.hpp Button.hpp Graphics.hpp GameState.hpp GUIBoard.hpp
HEADERS = $(patsubst %,$(DIR_HEADERS)/%,$(_HEADERS))

_OBJECTS = main.o Piece.o Pawn.o Knight.o Bishop.o Rook.o Queen.o King.o States.o Texture.o Button.o Graphics.o GameState.o GUIBoard.o
OBJECTS = $(patsubst %,$(DIR_OBJECTS)/%,$(_OBJECTS))

_TESTS = Test_Main.cpp
TESTS = $(patsubst %,$(DIR_TESTS)/%,$(_TESTS))



############################################ Make ############################################
# Here are defined the rules to compile the code generating object files and binaries

# Generates object files for all .cpp files that are located in the same directory as the makefile and then compiles
$(DIR_OBJECTS)/%.o: %.cpp $(HEADERS)
	$(CC) -c -o $@ $< $(CFLAGS) $(LIBS)

# Links all object files, generating binaries and creating the executable
$(PROJECT_EXE): $(OBJECTS)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

# Links all object files, generating binaries and creating the test executable; put here all modules used in the test
$(TEST_EXE): $(TESTS) Board.cpp Piece.cpp Pawn.cpp Knight.cpp Bishop.cpp Rook.cpp Queen.cpp King.cpp States.cpp
	$(CC) -o $@ --coverage $^ $(CFLAGS)

# MiniTutorial
# all: library.cpp main.cpp
# $@ - refers to the target name           - all
# $< - refers to the first prerequisite      - library.cpp
# $^ - refers to all prerequisites           - library.cpp main.cpp



################################## Other Make Rules ####################################
# Here are some useful make rules to facilitate work

# make project
# Clears the screen and automatically runs the software
project:
	clear
	./$(PROJECT_EXE)

# make test
# Calls the rule that compiles the test, then moves the residual .gcno file from src to obj
test: $(TEST_EXE)
	mv $(DIR_SOURCES)/*.gcno $(DIR_OBJECTS)

# make gcov
# Executes the test, moves the .gcno from obj to src, generates the gcov report and then moves all .gcno and .gcda files from src to obj
gcov:
	./$(TEST_EXE)

	mv $(DIR_OBJECTS)/*.gcno $(DIR_SOURCES)

	gcov -n *.gcda > $(DIR_GCOV)/relatorio-gcov.txt
	cat $(DIR_GCOV)/relatorio-gcov.txt

	mv $(DIR_SOURCES)/*.gcno $(DIR_OBJECTS)
	mv $(DIR_SOURCES)/*.gcda $(DIR_OBJECTS)

# make all
# Calls all the make rules
all: $(PROJECT_EXE) test gcov project



########################################## Clean ###########################################
# Deletes some project files (binaries, objects, gcov, and gcda files)

.PHONY: clean gcov

# make clean

clean:
	rm -f $(DIR_OBJECTS)/*.o *~ core $(INCDIR)/*~ *.gcda *.gcno *.gcov *.o ../obj/*.gcno ../obj/*.gcda $(PROJECT_EXE) $(DIR_OBJECTS)/*. $(TEST_EXE)
