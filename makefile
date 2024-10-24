sfml-app: Object/main.o Object/Entity.o Object/Game.o Object/State.o Object/GameState.o Object/Player.o
	g++ -g -Wall Object/*.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system

Object/main.o: Source/main.cpp Resource/Game.h
	g++ -Wall -c Source/main.cpp -o Object/main.o

Object/Entity.o: Source/Entity.cpp Resource/Entity.h
	g++ -Wall -c Source/Entity.cpp -o Object/Entity.o

Object/Game.o: Source/Game.cpp Resource/Game.h
	g++ -Wall -c Source/Game.cpp -o Object/Game.o

Object/State.o: Source/State.cpp Resource/State.h
	g++ -Wall -c Source/State.cpp -o Object/State.o

Object/GameState.o: Source/GameState.cpp Resource/GameState.h
	g++ -Wall -c Source/GameState.cpp -o Object/GameState.o

Object/Player.o: Source/Player.cpp Resource/Player.h
	g++ -Wall -c Source/Player.cpp -o Object/Player.o

clean:
	rm Object/*