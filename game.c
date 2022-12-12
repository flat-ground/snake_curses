#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>
#include <unistd.h>
#include <time.h>
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

void place_target(int max_x,int max_y)
{
	char view = '*';
	int x, y, c;
	
	
	/*do{
		x = rand() % max_x + 1;
		y = rand() % max_y + 1;
		/* x must be an even number, because char height 2 times greater then its width*/		
	/*	if(x%2 != 0) x = !x ? 0: x - 1;
		c = mvgetch(y,x);
	} while(c != -1 && c != ' ');*/
	
	mvaddch(20, 20, view);
}

void check_collisions(struct snake *s, int dir_x, int dir_y)
{
	int collision_x = s->head->x + dir_x;
	int collision_y = s->head->y + dir_y;
	mvprintw(0,0,"%d : %d" , collision_x, s->head->x);
	mvprintw(1,0,"%d : %d" , collision_y, s->head->y);
	mvprintw(2,0,"%d" , mvgetch(20,20));

	if(mvgetch(collision_y, collision_x) == '*'){ 
		snake_add(s, collision_x, collision_y);
	}
}

int main(int argc, char **argv)
{
	srand(time(0));
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
	place_target(col, row);
	check_collisions(player, x_dir, y_dir);
	move_snake(player, x_dir, y_dir);
	
	refresh();	
	sleep(1);
	}
	
	getch();
	endwin();
	return 0;
}


