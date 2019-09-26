#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
int startx = 0;
int starty = 0;

int main(int argc,char *argv[])
{
  int row,col,p=0;
  WINDOW  *marks,*answers,*heading,*timer,*question;
  char ch;
  system("clear");
  initscr();
  keypad(stdscr, TRUE);
  cbreak();
  noecho();
  refresh();
  getmaxyx(stdscr,row,col);
  question=newwin(2*row/5,col,row/5,0);
  box(question,0,0);
  mvwprintw(question,2,2,"Questions");
  wrefresh(question);
  timer=newwin(row/5,col/5,0,4*col/5);
  box(timer,0,0);
  mvwprintw(timer,2,2,"Timer");
  wrefresh(timer);
  marks=newwin(row/5,col/5,0,0);
  box(marks,0,0);
  mvwprintw(marks,2,2,"Marks");
  wrefresh(marks);
  heading=newwin(row/5,3*col/5,0,col/5);
  box(heading,0,0);
  mvwprintw(heading,2,2,"heading");
  wrefresh(heading);
  answers=newwin(2*row/5,col,3*row/5,0);
  box(answers,0,0);
  mvwprintw(answers,2,2,"Answers");
  wrefresh(answers);
  ch=getch();
  if(ch == KEY_F(1))		/* Without keypad enabled this will */
		printw("F1 Key pressed");/*  not get to us either	*/
					/* Without noecho() some ugly escape
					 * charachters might have been printed
					 * on screen			*/
	else
	{	printw("The pressed key is ");
		attron(A_BOLD);
		printw("%c", ch);
		attroff(A_BOLD);
	}
	refresh();			/* Print it on to the real screen */
    	getch();			/* Wait for user input */
	endwin();
  
  return 0;
}



 


