 #ifndef h_block
 #define h_block
 
struct block{
  int x;
  int y;
  int color;
  int time;
  int type;
  char point;
};
 
 #endif 

void initial_blocks(struct block **,
	     int *, int, int, int, int);
void add_blocks(struct block **,
	 int *, int, int, int, int);
void delete_blocks(struct block **, int *);
void work_blocks(struct block **,
	  int, int, int, int, int);
void visible_blocks(struct block *, int );

