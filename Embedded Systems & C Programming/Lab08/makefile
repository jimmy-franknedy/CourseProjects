all: rpg

rpg: Player.c Game.c Lab8_main.c
	gcc -Wall Player.c Game.c Lab8_main.c -o rpg

clean:
	rm Player.o Game.o Lab8_main.o

Player.o: Player.c
	gcc –c Player.c

Player: Player.o
	gcc Player.o -o Player

Game.o: Game.c
	gcc –c Game.c

Game: Game.o
	gcc Game.o -o Game
	
Lab8_main.o: Lab8_main.c
	gcc –c Lab8_main.c

Lab8_main: Lab8_main.o
	gcc Lab8_main.o -o Lab8_main
	
	