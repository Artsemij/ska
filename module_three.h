#ifndef h_snake
 #define h_snake
 
struct snake{
  int x;
  int y;
  int color;
  struct snake *next;
  
};
 
 #endif 

void initial_snake(struct snake **, int, int, int);
void show_snake(struct snake *);
void  add_snake(struct snake **, char, int, int);
void delete_snake(struct snake *);
void move_snake(struct snake *, char, int, int);
_Bool conflict_body(struct snake *);
void conflict_block(struct snake **, struct block *, int, char, int, int, int *);
_Bool conflict_field(struct snake *, _Bool [][getmaxy(stdscr)], int, int);

