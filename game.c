#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>
#include <unistd.h>
#include "snake.h"


enum { key_escape = 27 };

static void init()
{
	initscr();
	cbreak();
	keypad(stdscr, 1);
	noecho();
	curs_set(0);
	timeout(0);
}

int main(int argc, char **argv)
{
	int snake_size = 1;
	char c = '#';
	if(argc > 1){
		snake_size = atoi(argv[1]);
		if(argc > 2) c = *argv[2];
	}
	
	init();
	int row, col;
	getmaxyx(stdscr, row, col);
	
	struct snake *player = create_snake(snake_size, col/2, row/2, c);
	draw_snake(player);
	
	int x_dir = 0, y_dir = -1;
	int last_key_pressed = KEY_UP;
	
	
	/* -Main loop- */
		
	while(1){
					
		for(int tmp; (tmp = getch()) != ERR; last_key_pressed = tmp);
					
		if(last_key_pressed == key_escape) break;
		
		switch(last_key_pressed) {
		case KEY_UP:
			x_dir = 0;
			y_dir = -1;
			break;
		case KEY_DOWN:
			x_dir = 0;
			y_dir = 1;
			break;
		case KEY_RIGHT:
			x_dir = 2;
			y_dir = 0;
			break;
		case KEY_LEFT:
			x_dir = -2;
			y_dir =  0;
			break;	
		}
		
	move_snake(player, x_dir, y_dir);
	refresh();	
	sleep(1);
	}
	
	getch();
	endwin();
	return 0;
}


