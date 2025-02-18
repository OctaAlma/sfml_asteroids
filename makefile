makefile:
all: game

clean:
	-rm game
	g++ -o game Player.cpp Game.cpp main.cpp -lsfml-graphics -lsfml-window -lsfml-system
game: 
	g++ -o game Player.cpp Game.cpp main.cpp -lsfml-graphics -lsfml-window -lsfml-system