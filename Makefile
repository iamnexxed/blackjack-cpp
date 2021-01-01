# variables
# the compiler: gcc for C program, define as g++ for C++
CC = g++
RM = rm
# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
CFLAGS  = -g -Wall
INCDEPEND = -I include -L lib -l SDL2_image -l SDL2

# the build target executable:
TARGET = main

all: $(TARGET) 

# Link
$(TARGET): $(TARGET).o GameObjects/Game.o GameObjects/Deck.o GameObjects/Card.o GameObjects/Dealer.o GameObjects/Player.o GameObjects/Hand.o
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).o GameObjects/Game.o GameObjects/Deck.o GameObjects/Card.o GameObjects/Dealer.o GameObjects/Player.o GameObjects/Hand.o $(INCDEPEND)

# Compile
$(TARGET).o: $(TARGET).cpp GameObjects/Game.h 
	$(CC) $(CFLAGS) -c $(TARGET).cpp 

GameObjects/Game.o: GameObjects/Game.h GameObjects/Dealer.h GameObjects/Player.h

GameObjects/Deck.o: GameObjects/Deck.h GameObjects/Card.h 

GameObjects/Card.o: GameObjects/Card.h

GameObjects/Dealer.o: GameObjects/Dealer.h GameObjects/Deck.h GameObjects/Card.h

GameObjects/Player.o: GameObjects/Player.h GameObjects/Hand.h

GameObjects/Hand.o: GameObjects/Hand.h GameObjects/Card.h

clean:
	$(RM) $(TARGET)