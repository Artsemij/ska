#include<stdio.h>
#include<stdlib.h>
#include<ncurses.h>
#include<time.h>
#include<unistd.h>
#include"module_one.h"
#include"module_two.h"
#include"module_three.h"


int main(){
  initscr();	
  _Bool start_game=FALSE;
  int blocks_p;
  struct block *arr_block=NULL;
  int xmax=getmaxx(stdscr),
      ymax=getmaxy(stdscr), 
      count_block=5;
  _Bool arr_field[xmax][ymax];
  char direct='R';
  int points=0, count_conflict=3;
  int speed=70000, count_body=5;
  int time_life=70;
  struct snake *body=NULL;
  start_color();
  init_pair(1, COLOR_WHITE, COLOR_WHITE);
  init_pair(2, COLOR_WHITE, COLOR_BLACK);
  init_pair(3, COLOR_BLACK, COLOR_RED);
  init_pair(4, COLOR_BLACK, COLOR_GREEN);
  init_pair(5, COLOR_BLACK, COLOR_YELLOW);
  init_pair(6, COLOR_BLACK, COLOR_BLUE);
  init_pair(7, COLOR_BLACK, COLOR_MAGENTA);
  init_pair(8, COLOR_BLACK, COLOR_CYAN);
  init_pair(9, COLOR_BLACK, COLOR_BLACK);
  raw();
  noecho();
  curs_set(0);
  timeout(-1);
  chtype c=' ';
  keypad(stdscr, TRUE);
  
  while(c!='q'){
    timeout(-1);
    clear();
    move(1,2);
    addstr("q-Exit\n");
    move(2,2);
    addstr("1 - automatic field\n");
    move(3,2);
    addstr("2 - manual field\n");
    move(4,2);
    addstr("3 - new game\n");
    move(5,2);
    addstr("4 - continue game\n");
    switch (c){
     case '1':
      automatic_field(arr_field, xmax,ymax);
      clear(); 
      show_field(arr_field,xmax, ymax);
      break;
     case '2':
      clear();
      manual_field(arr_field,xmax,ymax);
      raw();
      noecho();
      keypad(stdscr, TRUE);
      timeout(0);
      break;
     case '3':
      start_game=TRUE;
      count_block=5;
      initial_blocks(&arr_block, &count_block, xmax, ymax, time_life, 8);
      initial_snake(&body,xmax/2,ymax/2,5);
      points=0;
      for (int i=0;i<count_body;i++) add_snake(&body,direct, xmax,ymax);
      timeout(0);
      while (c!='q'){
      clear();
      show_field(arr_field, xmax,ymax);
      work_blocks(&arr_block, count_block,xmax, ymax, time_life, 8);
      visible_blocks(arr_block, count_block);
      move(0,0);
      printw("Points: %d; q - exit; a - less speed; z - more speed",points);
      if (c==KEY_DOWN) direct='D';
      if (c==KEY_UP) direct='U';
      if (c==KEY_LEFT) direct='L';
      if (c==KEY_RIGHT) direct='R';
      if (c=='a') speed=(int)(speed*1.1);
      if (c=='z') speed=(int)(speed*0.9);
      if (c==KEY_RESIZE) {
        echo();
        noraw();
        keypad(stdscr, FALSE);
        endwin();
        printf("Game over!\n");
        return 0;     
       }
      move_snake(body,direct, xmax,ymax);
      conflict_block(&body, arr_block, count_block, direct, xmax, ymax, &points);
      if (conflict_field(body, arr_field, xmax, ymax) || conflict_body(body)) points-=count_conflict;
      show_snake(body);
      blocks_p=rand()%10;
        if (blocks_p>=6 && blocks_p<8) add_blocks(&arr_block, &count_block,xmax, ymax, time_life, 8);
        else
          if (blocks_p>=8) delete_blocks(&arr_block, &count_block);
      refresh();
      usleep(speed);
      c=getch();
      }
      break;

     case '4':
      if (start_game){
      timeout(0);
      while (c!='q'){
        clear();
        show_field(arr_field, xmax,ymax);
        work_blocks(&arr_block, count_block,xmax, ymax, time_life, 8);
        visible_blocks(arr_block, count_block);
        move(0,0);
        printw("Points: %d; q - exit; a - less speed; z - more speed",points);
        if (c==KEY_DOWN) direct='D';
        if (c==KEY_UP) direct='U';
        if (c==KEY_LEFT) direct='L';
        if (c==KEY_RIGHT) direct='R';
        if (c=='a') speed=(int)(speed*1.1);
        if (c=='z') speed=(int)(speed*0.9);
        if (c==KEY_RESIZE) {
        echo();
        noraw();
        keypad(stdscr, FALSE);
        endwin();
        printf("Game over!\n");
        return 0;     
       }
        move_snake(body,direct, xmax,ymax);
        conflict_block(&body, arr_block, count_block, direct, xmax, ymax, &points);
        if (conflict_field(body, arr_field, xmax, ymax) || conflict_body(body)) points-=count_conflict;
        show_snake(body);
        blocks_p=rand()%10;
        if (blocks_p>=6 && blocks_p<8) add_blocks(&arr_block, &count_block,xmax, ymax, time_life, 8);
        else
          if (blocks_p>=8) delete_blocks(&arr_block, &count_block);
        refresh();
        usleep(speed);
        c=getch();
       }
      }
      break; 
     default:
       break;
     }
     c=getch();
     if (c==KEY_RESIZE) {
        echo();
        noraw();
        keypad(stdscr, FALSE);
        endwin();
        printf("Game over!\n");
        return 0;     
       }
    }
  echo();
  noraw();
  keypad(stdscr, FALSE);
  endwin();
  return 0;
}
