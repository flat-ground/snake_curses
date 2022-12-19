#include "snake.h"
#include <stdlib.h>
#include <ncurses.h>

static void snake_put(struct snake *s, int x, int y)
{
	struct snake_item *tmp = malloc(sizeof(struct snake_item));
	tmp->next = NULL;
	tmp->x = x;
	tmp->y = y;
	if(s->head){
		s->head->next = tmp;
		s->head = tmp;
	} else{
		s->head = s->tail = tmp;
	}
}

static void snake_get(struct snake *s)
{
	struct snake_item *tmp;
	tmp = s->tail;
	s->tail = s->tail->next;
	free(tmp);
}

struct snake *create_snake(int cell_count, int x, int y, char c)
{
	struct snake *s = malloc(sizeof(struct snake));
	s->view = c;
	s->is_stopped = 0;
	
	/* x must be an even number, because char height 2 times greater then its width*/
	if(x%2 != 0) x = !x? 0: x - 1; 
		
	for(int i = 0; i < cell_count; i++){
		snake_put(s, x, y-i);
	}
	return s;	
}

void draw_snake(struct snake *s)
{
	char c  = s->view;
	struct snake_item *tmp;
	for(tmp = s->tail; tmp; tmp = tmp->next){
		mvaddch(tmp->y, tmp->x, c);
	}
}

void move_snake(struct snake *s, int dx, int dy)
{
	snake_put(s, s->head->x + dx, s->head->y + dy);
	mvaddch(s->tail->y, s->tail->x, ' ');
	mvaddch(s->head->y, s->head->x, s->view);
	snake_get(s);
}

void snake_add(struct snake *s, int x, int y)
{
	snake_put(s, x, y);
	mvaddch(s->head->y, s->head->x, s->view);
}



