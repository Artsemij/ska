#include <ncurses.h>
#include <stdlib.h>
#include<stdio.h>
#include<time.h>
#include<unistd.h>
#include "module_two.h"
#include "module_three.h"


void move_snake(struct snake *body, char direct, int xmax,int ymax){
  struct snake *current=body;
  int x,y,x_old,y_old;
  x_old=current->x;y_old=current->y;
  if (direct=='R'){
    current->x=(body->x+1)%xmax;
    current->y=body->y;
  }
    if (direct=='L'){
    if ((body->x-1)>0) current->x=(body->x-1)%xmax;
    else current->x=xmax-1;
    current->y=body->y;
  }
  if (direct=='U'){
    if ((body->y-1)>0) current->y=(body->y-1)%ymax;
    else current->y=ymax-1;
    current->x=body->x;
  }
  if (direct=='D'){
    current->y=(body->y+1)%ymax;
    current->x=body->x;
  }
  while (current->next!=NULL){
    current=current->next;
    x=current->x;y=current->y;
    current->x=x_old;current->y=y_old;
    x_old=x;y_old=y;
  }
}

void initial_snake(struct snake **body, int x, int y, int color){
  if ((*body)!=NULL){
    while ((*body)->next !=NULL) delete_snake(*body);
    free(*body);
  }
  *body=(struct snake *)malloc(sizeof(struct snake));
  (*body)->x=x;
  (*body)->y=y;
  (*body)->color=color;
  (*body)->next=NULL;
}

void delete_snake(struct snake *body){
  struct snake *current=body, *pre_current;
  if (current->next !=NULL){
    while(current->next != NULL) {
      pre_current=current;
      current=current->next;
    }
    pre_current->next=NULL;
    free(current);    
  }
}

void  add_snake(struct snake **body, char direct, int xmax, int ymax){
  struct snake *current=(struct snake *)malloc(sizeof(struct snake));
  current->color=(*body)->color;
  current->next=(*body);
  if (direct=='R'){
    current->x=((*body)->x+1)%xmax;
    current->y=(*body)->y;
  }
  if (direct=='L'){
    if (((*body)->x-1)>0) current->x=((*body)->x-1)%xmax;
    else current->x=xmax-1;
    current->y=(*body)->y;
  }
  if (direct=='U'){
    if (((*body)->y-1)>0) current->y=((*body)->y-1)%ymax;
    else current->y=ymax-1;
    current->x=(*body)->x;
  }
  if (direct=='D'){
    current->y=((*body)->y+1)%ymax;
    current->x=(*body)->x;
  }
  *body=current;
}

void show_snake(struct snake *body){
  struct snake *current=body;
  chtype body_color;
  do{
    move(current->y,current->x);
    body_color=' '|COLOR_PAIR(current->color);
    addch(body_color);
    current=current->next;
  } while(current!=NULL);
}


_Bool conflict_body(struct snake *body){
  struct snake *current_one, *current_two;
  _Bool p=FALSE;
  current_one=body; current_two=body->next;
  while (current_one->next !=NULL){
    while (current_two != NULL){
     if (current_one->x==current_two->x && current_one->y==current_two->y)
      {p=TRUE;
       return p;
      }
     current_two=current_two->next;
    }
   current_one=current_one->next;
   if (current_one != NULL) current_two=current_one->next;
   }
  return p;
}

void conflict_block(struct snake **body, struct block *arr, int count, char direct, int xmax, int ymax, int *count_points){
  struct snake *current=*body;
  int k=0;
  while (current!=NULL){
    for (int i=0;i<count;i++){
      if (arr[i].x==current->x && arr[i].y==current->y && arr[i].time!=0) {
	if (arr[i].type) {k++; *count_points=(*count_points)+(arr[i].point-48);}
        else {k--; *count_points=(*count_points)+(arr[i].point-48);}
        arr[i].time=0;
      }
    }
    current=current->next;
  }
  if (k<0)
   for(int i=0;i<(-1)*k;i++) delete_snake(*body);
  else 
   for (int i=0;i<k;i++) add_snake(body,direct, xmax, ymax);
}

_Bool conflict_field(struct snake *body, _Bool arr[][getmaxy(stdscr)], int xmax, int ymax){
  _Bool p=FALSE;
  struct snake *current=body;
  while (current!=NULL){
	if (arr[current->x][current->y]==TRUE) {
	p=TRUE;
	return p;
      }
    current=current->next;
  }
  return p;  
}



int main(){
  struct snake *body=NULL;
  char direct='R';
  initscr();
  int xmax=getmaxx(stdscr),
    ymax=getmaxy(stdscr);
  start_color();
  init_pair(1, COLOR_WHITE, COLOR_WHITE);
  init_pair(2, COLOR_BLACK, COLOR_BLACK);
  init_pair(3, COLOR_RED, COLOR_RED);
  init_pair(4, COLOR_GREEN, COLOR_GREEN);
  init_pair(5, COLOR_YELLOW, COLOR_YELLOW);
  init_pair(6, COLOR_BLUE, COLOR_BLUE);
  init_pair(7, COLOR_MAGENTA, COLOR_MAGENTA);
  init_pair(8, COLOR_CYAN, COLOR_CYAN);
  raw();
  noecho();
  initial_snake(&body,xmax/2,ymax/2,5);
  add_snake(&body,direct, xmax,ymax);
  add_snake(&body,direct, xmax,ymax);
  add_snake(&body,direct, xmax,ymax);
  add_snake(&body,direct, xmax,ymax);
  add_snake(&body,direct, xmax,ymax);
  add_snake(&body,direct, xmax,ymax);
  add_snake(&body,direct, xmax,ymax);
  add_snake(&body,direct, xmax,ymax);
  add_snake(&body,direct, xmax,ymax);
  add_snake(&body,direct, xmax,ymax);
  add_snake(&body,direct, xmax,ymax);
  add_snake(&body,direct, xmax,ymax);
  clear();
  show_snake(body);
  chtype c='l';
  srand(time(NULL));
  keypad(stdscr, TRUE);
  curs_set(0);
  timeout(0);
  while (c!='q'){
    if (c==KEY_DOWN) direct='D';
    if (c==KEY_UP) direct='U';
    if (c==KEY_LEFT) direct='L';
    if (c==KEY_RIGHT) direct='R';
    move_snake(body,direct, xmax,ymax);
    clear();
    show_snake(body);
    refresh();
    usleep(70000);
    c=getch();
  }
  echo();
  noraw();
  keypad(stdscr, FALSE);
  endwin();
  
  return 0;
}
  




