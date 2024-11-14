sfml-app: Object/main.o Object/Entity.o Object/Weapon.o Object/Game.o Object/State.o Object/MainMap.o Object/Player.o Object/Mortar.o Object/Bullet.o Object/Enemy.o Object/HealthBar.o Object/Hitbox.o Object/Pistol.o Object/Shotgun.o Object/MainMenu.o Object/Button.o Object/Map.o
	g++ -g -Wall Object/*.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system

Object/main.o: Source/main.cpp Resource/GameManager/Game.h
	g++ -Wall -c Source/main.cpp -o Object/main.o

Object/Entity.o: Source/Entity/Entity.cpp Resource/Entity/Entity.h
	g++ -Wall -c Source/Entity/Entity.cpp -o Object/Entity.o

Object/Weapon.o: Source/Weapons/Weapon.cpp Resource/Weapons/Weapon.h
	g++ -Wall -c Source/Weapons/Weapon.cpp -o Object/Weapon.o

Object/Game.o: Source/GameManager/Game.cpp Resource/GameManager/Game.h
	g++ -Wall -c Source/GameManager/Game.cpp -o Object/Game.o

Object/State.o: Source/GameManager/State.cpp Resource/GameManager/State.h
	g++ -Wall -c Source/GameManager/State.cpp -o Object/State.o

Object/MainMap.o: Source/GameManager/MainMap.cpp Resource/GameManager/MainMap.h
	g++ -Wall -c Source/GameManager/MainMap.cpp -o Object/MainMap.o

Object/Player.o: Source/Entity/Player.cpp Resource/Entity/Player.h
	g++ -Wall -c Source/Entity/Player.cpp -o Object/Player.o

Object/Mortar.o: Source/Weapons/Mortar.cpp Resource/Weapons/Mortar.h
	g++ -Wall -c Source/Weapons/Mortar.cpp -o Object/Mortar.o

Object/Bullet.o: Source/Weapons/Bullet.cpp Resource/Weapons/Bullet.h
	g++ -Wall -c Source/Weapons/Bullet.cpp -o Object/Bullet.o

Object/Pistol.o: Source/Weapons/Pistol.cpp Resource/Weapons/Pistol.h
	g++ -Wall -c Source/Weapons/Pistol.cpp -o Object/Pistol.o

Object/Shotgun.o: Source/Weapons/Shotgun.cpp Resource/Weapons/Shotgun.h
	g++ -Wall -c Source/Weapons/Shotgun.cpp -o Object/Shotgun.o

Object/Enemy.o: Source/Entity/Enemy.cpp Resource/Entity/Enemy.h
	g++ -Wall -c Source/Entity/Enemy.cpp -o Object/Enemy.o

Object/HealthBar.o: Source/Entity/HealthBar.cpp Resource/Entity/HealthBar.h
	g++ -Wall -c Source/Entity/HealthBar.cpp -o Object/HealthBar.o

Object/Hitbox.o: Source/Entity/Hitbox.cpp Resource/Entity/Hitbox.h
	g++ -Wall -c Source/Entity/Hitbox.cpp -o Object/Hitbox.o

Object/MainMenu.o: Source/GameManager/MainMenu.cpp Resource/GameManager/MainMenu.h
	g++ -Wall -c Source/GameManager/MainMenu.cpp -o Object/MainMenu.o

Object/Button.o: Source/GameManager/Button.cpp Resource/GameManager/Button.h
	g++ -Wall -c Source/GameManager/Button.cpp -o Object/Button.o

Object/Map.o: Source/GameManager/Map.cpp Resource/GameManager/Map.h
	g++ -Wall -c Source/GameManager/Map.cpp -o Object/Map.o

clean:
	rm Object/*

raw:
	g++ -g -Wall Source/Entity/*.cpp Source/GameManager/*.cpp Source/Weapons/*.cpp Source/main.cpp -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system