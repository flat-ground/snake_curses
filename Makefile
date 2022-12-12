OBJMODULES = snake.o
CFLAGS = -g -Wall
CC = gcc

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $< -o $@

snake: game.c $(OBJMODULES) 
	$(CC) $(CFLAGS) $^ -lncurses -o $@
	
clean:
	rm -f *.o snake

