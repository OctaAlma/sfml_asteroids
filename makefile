makefile:
all: game

run:
	-rm game
	g++ -std=c++17 -o game Laser.cpp AsteroidBelt.cpp Asteroid.cpp Definitions.cpp Player.cpp Game.cpp main.cpp -lsfml-graphics -lsfml-window -lsfml-system
	./game

game: 
	g++ -std=c++17 -o game Laser.cpp AsteroidBelt.cpp Asteroid.cpp Definitions.cpp Player.cpp Game.cpp main.cpp -lsfml-graphics -lsfml-window -lsfml-system

clean:
	-rm game
