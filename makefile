field: field.c
	gcc -c field.c -o field.o

block: block.c
	gcc -c block.c -o block.o

snake: snake.c
	gcc -c snake.c -o snake.o

game: main.c field block snake
	gcc main.c field.o block.o snake.o -o game -lncurses

run: game
	./game

clean:
	rm -f *.o
