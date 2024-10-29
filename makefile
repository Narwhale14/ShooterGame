sfml-app: Object/main.o Object/Entity.o Object/Weapon.o Object/Game.o Object/State.o Object/MainMap.o Object/Player.o Object/Mortar.o
	g++ -g -Wall Object/*.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system

Object/main.o: Source/main.cpp Resource/Game.h
	g++ -Wall -c Source/main.cpp -o Object/main.o

Object/Entity.o: Source/Entity.cpp Resource/Entity.h
	g++ -Wall -c Source/Entity.cpp -o Object/Entity.o

Object/Weapon.o: Source/Weapon.cpp Resource/Weapon.h
	g++ -Wall -c Source/Weapon.cpp -o Object/Weapon.o

Object/Game.o: Source/Game.cpp Resource/Game.h
	g++ -Wall -c Source/Game.cpp -o Object/Game.o

Object/State.o: Source/State.cpp Resource/State.h
	g++ -Wall -c Source/State.cpp -o Object/State.o

Object/MainMap.o: Source/MainMap.cpp Resource/MainMap.h
	g++ -Wall -c Source/MainMap.cpp -o Object/MainMap.o

Object/Player.o: Source/Player.cpp Resource/Player.h
	g++ -Wall -c Source/Player.cpp -o Object/Player.o

Object/Mortar.o: Source/Mortar.cpp Resource/Mortar.h
	g++ -Wall -c Source/Mortar.cpp -o Object/Mortar.o

clean:
	rm Object/*