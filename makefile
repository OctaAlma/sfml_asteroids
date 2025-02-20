makefile:
all: game

clean:
	-rm game
	g++ -std=c++17 -o game Laser.cpp AsteroidBelt.cpp Asteroid.cpp Definitions.cpp Player.cpp Game.cpp main.cpp -lsfml-graphics -lsfml-window -lsfml-system