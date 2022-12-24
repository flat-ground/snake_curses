SRCMODULES = snake.c level_loader.c
OBJMODULES = $(SRCMODULES:.c=.o)
CFLAGS = -g -Wall

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $< -o $@

snake: game.c $(OBJMODULES) 
	$(CC) $(CFLAGS) $^ -lncurses -o $@

ifneq (clean, $(MAKECMDGOALS))
-include deps.mk
endif

clean:
	rm -f *.o snake
	
deps.mk: $(SRCMODULES)
	$(CC) -MM $^ > $@
