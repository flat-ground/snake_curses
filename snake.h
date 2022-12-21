#ifndef SNAKE_H_SENTRY
#define SNAKE_H_SENTRY

struct snake {
	/*enum state { up, down, right, left } state;*/
	struct dir{ int x, y; } dir;
	char view;
	struct snake_item *tail, *head;
};

struct snake_item {
		int x, y;
		struct snake_item *next;
};

void snake_add(struct snake *s, int x, int y);
struct snake *create_snake(int cell_count, int x, int y, char c);
void move_snake(struct snake *s, int dx, int dy);
void draw_snake(struct snake *s);
void set_snake_dir(struct snake *s, int x, int y);

#endif
