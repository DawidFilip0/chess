CXX = g++
CXXFLAGS = -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion -Wshadow -Wold-style-cast -Wnon-virtual-dtor -g

LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

TARGET = sfml-app
OBJ = main.o graphics/window.o board/Board.o  userInput/inputHandler.o

$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: clean
