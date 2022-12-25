#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>
#include <unistd.h>
#include <time.h>
#include "snake.h"
#include "level_loader.h"

enum { key_escape = 27, apples = 16, delay_nano = 500000000,
		apple_view = '*', snake_view = 'X', wall = '#'};

static void init()
{
	initscr();
	cbreak();
	keypad(stdscr, 1);
	noecho();
	curs_set(0);
	timeout(0);
}

void place_target(int max_x,int max_y, char v)
{
	int x, y, c;
		
	do{
		x = rand() % max_x + 1;
		y = rand() % max_y + 1;
		/* x must be an even number, because char height 2 times greater then its width*/		
		if(x%2 != 0) x = !x ? 0: x - 1;
		c = mvinch(y,x)&A_CHARTEXT;
		/*mvprintw(0,0,"%d", c);*/
	} while(c != ' ');

	mvaddch(y, x, v);
}

void create_level(int apples_count, int max_x,int max_y)
{
	for(int i = 0; i < apples_count; i++)
		place_target(max_x, max_y, apple_view);
}

void check_collisions(struct snake *s, int dir_x, int dir_y)
{
	s->stopped = 0;
	if(!((dir_x + s->dir.x == 0) && (dir_y + s->dir.y == 0))){ 
		set_snake_dir(s, dir_x, dir_y);
	}
	
	int collision_x = s->head->x + s->dir.x;
	int collision_y = s->head->y + s->dir.y;
	char c = mvinch(collision_y, collision_x);
	
	switch (c)
	{
		case apple_view:
			s->stopped = 1; 
			snake_add(s, collision_x, collision_y);
			break;
		case wall:
			s->stopped = 1;
			break;
	}
}

int main(int argc, char **argv)
{
	srand(time(0));
	
	int snake_size = 1;
	if(argc > 1){
		snake_size = atoi(argv[1]);
	}
	
	init();
	int row, col;
	getmaxyx(stdscr, row, col);
	
	int loaded = load_level("./levels/1.txt");
	loaded ? mvprintw(0,0,"NO SUCH FILE OR DIRECTORY:") : mvprintw(0,0,"%d", loaded);
	
	create_level(apples, col, row);
	
	/*for experimental purposes*/
	for(int i = 0; i < 20; i++)
		place_target(col, row, wall);
	/**/
	
	struct snake *player = create_snake(snake_size, col/2, row/2, snake_view);
	draw_snake(player);
	
	int x_dir = 0, y_dir = -1;
	int last_key_pressed = KEY_UP;
	
	struct timespec tw = {0, delay_nano};
	struct timespec tr;
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
		case 's':
			int s = save_level("./save.txt", row, col);
			s ? mvprintw(0,0,"    SAVING ERROR    ") : mvprintw(0,0,"      SAVED       ");
				
		}
	check_collisions(player, x_dir, y_dir);
	move_snake(player, player->dir.x, player->dir.y);
	
	refresh();	
	nanosleep(&tw, &tr);
	}
	
	getch();
	endwin();
	return 0;
}


