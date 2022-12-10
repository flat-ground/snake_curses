#ifndef SNAKE_H_SENTRY
#define SNAKE_H_SENTRY

struct snake *create_snake(int cell_count, int x, int y, char c);
void move_snake(struct snake *s, int dx, int dy);
void draw_snake(struct snake *s);

#endif
