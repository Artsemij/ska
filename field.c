#include<ncurses.h>

void show_field(_Bool arr[][getmaxy(stdscr)],
	  int xmax, int ymax){
  chtype border=' '|COLOR_PAIR(1);
  chtype body = ' '|COLOR_PAIR(2);
  for (int i=0;i<xmax;i++){
    for (int j=0;j<ymax;j++){
      if (arr[i][j])
	{
	  move(j,i);
	  addch(border);
	}
      else
	{
	  move(j,i);
	  addch(body);
	}
    }
  }
  refresh();
}


void automatic_field(_Bool arr[][getmaxy(stdscr)],
	       int xmax, int ymax){
  for (int i=0;i<ymax;i++)
    {
      for (int j=0;j<xmax;j++)
	  if ((i==0)||(i==(ymax-1)))
	      arr[j][i]=1;
	  else
	    if ((j==0)||(j==(xmax-1)))
		arr[j][i]=1;
	    else
		arr[j][i]=0;
    } 
  
}

void manual_field(_Bool arr[][getmaxy(stdscr)],
	    int xmax, int ymax){
  for (int i=0;i<xmax;i++)
	for (int j=0;j<ymax;j++)
	  arr[i][j]=0;
  int x_current=xmax/2,y_current=ymax/2;
  raw();
  noecho();
  keypad(stdscr, TRUE);
  chtype space_color=' '|COLOR_PAIR(1),
    space_bground='*'|COLOR_PAIR(2),c;
  int p=0;
  move(0, 0);
  printw("q - quit\n");
  printw("c - clear screen\n");
  printw("z - change color");
  move(y_current,x_current);
  while(c!='q'){
    c=getch();
    if (c==KEY_DOWN)
      {
      if (p==0) {move(y_current,x_current);addch(' '|COLOR_PAIR(9));refresh();}
      y_current=(y_current+1)%ymax;
      }
    if (c==KEY_UP) {
      if (p==0) {move(y_current,x_current);addch(' '|COLOR_PAIR(9));refresh();}
      y_current=(y_current-1)%ymax;
      if (y_current<0) y_current=ymax-1;}
    if (c==KEY_LEFT) {
      if (p==0) {move(y_current,x_current);addch(' '|COLOR_PAIR(9));refresh();}
      x_current=(x_current-1)%xmax;
      if (x_current<0) x_current=xmax-1;}
    if (c==KEY_RIGHT){
      if (p==0) {move(y_current,x_current);addch(' '|COLOR_PAIR(9));refresh();}
      x_current=(x_current+1)%xmax;}
    if (c=='c') {
      clear();
      move(0, 0);
      printw("q - quit\n");
      printw("c - clear screen\n");
      printw("z - change color");
      x_current=xmax/2;
      y_current=ymax/2;
      for (int i=0;i<xmax;i++)
	for (int j=0;j<ymax;j++)
	  arr[i][j]=0;
    }
    if (c=='z') p=(p+1)%2;
    move(y_current, x_current);
    if (p) {
      addch(space_color);
      arr[x_current][y_current]=1;
    }
    else {
      addch(space_bground);
      arr[x_current][y_current]=0;
    }
    refresh();
  }
  echo();
  noraw();
  keypad(stdscr, FALSE);
}




