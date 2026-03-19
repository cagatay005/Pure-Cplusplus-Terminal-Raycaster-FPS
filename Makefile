CXX = g++
CXXFLAGS = -Wall -Iinclude -O2

SRC = src/main.cpp src/Motor.cpp src/Oyuncu.cpp src/Terminal.cpp src/Harita.cpp src/Dusman.cpp src/Ses.cpp
OBJ = $(SRC:.cpp=.o)
EXEC = fps_oyun

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) $(OBJ) -o $@

clean:
	rm -f $(OBJ) $(EXEC)