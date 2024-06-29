CXX=g++
CXXFLAGS=-std=c++11 -Werror -Wsign-conversion
VALGRIND_FLAGS=-v --leak-check=full --show-leak-kinds=all --error-exitcode=99

HEADERS=Player.hpp Game.hpp DevelopmentCard.hpp Tile.hpp Robber.hpp Board.hpp
SOURCES=Player.cpp Game.cpp DevelopmentCard.cpp Tile.cpp Robber.cpp Board.cpp
MAIN_SOURCES=Demo.cpp $(SOURCES)
GAME_SOURCES=Main.cpp $(SOURCES)
TEST_SOURCES=Test.cpp $(SOURCES)

MAIN_OBJECTS=$(MAIN_SOURCES:.cpp=.o)
GAME_OBJECTS=$(GAME_SOURCES:.cpp=.o)
TEST_OBJECTS=$(TEST_SOURCES:.cpp=.o)

all: demo game test

demo: $(MAIN_OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o demo

game: $(GAME_OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o game

test: $(TEST_OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o test

tidy:
	clang-tidy $(SOURCES) $(HEADERS) -checks=bugprone-,clang-analyzer-,cppcoreguidelines-,performance-,portability-,readability-,-cppcoreguidelines-pro-bounds-pointer-arithmetic,-cppcoreguidelines-owning-memory --warnings-as-errors=-* --

valgrind: demo game test
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./demo 2>&1 | { egrep "lost| at " || true; }
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./game 2>&1 | { egrep "lost| at " || true; }
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./test 2>&1 | { egrep "lost| at " || true; }

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f *.o demo game test
