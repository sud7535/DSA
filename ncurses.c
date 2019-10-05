#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
int startx = 0;
int starty = 0;
WINDOW  *marks,*answers,*heading,*timer,*question;
void timex(int a,int b);
int main(int argc,char *argv[])
{
  int row,col,p=0,i=0;
  
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
  marks=newwin(row/5,col/5,0,0);
  box(marks,0,0);
  mvwprintw(marks,2,2,"Marks");
  wrefresh(marks);
  heading=newwin(row/5,3*col/5,0,col/5);
  box(heading,0,0);
  mvwprintw(heading,1,5,"d8888b.  .d8b.  d8888b. d888888b d8888b.    .d88b.  db    db d888888b d88888D ");
  mvwprintw(heading,2,5,"88  `8D d8' `8b 88  `8D   `88'   88  `8D   .8P  Y8. 88    88   `88'   YP  d8' ");
  mvwprintw(heading,3,5,"88oobY' 88ooo88 88oodD'    88    88   88   88    88 88    88    88       d8'  ");
  mvwprintw(heading,4,5,"88`8b   88~~~88 88~~~      88    88   88   88    88 88    88    88      d8'   ");
  mvwprintw(heading,5,5,"88 `88. 88   88 88        .88.   88  .8D   `8P  d8' 88b  d88   .88.    d8' db ");
  mvwprintw(heading,6,5,"88   YD YP   YP 88      Y888888P Y8888D'    `Y88'Y8 ~Y8888P' Y888888P d88888P ");
  wrefresh(heading);
  answers=newwin(2*row/5,col,3*row/5,0);
  box(answers,0,0);
  mvwprintw(answers,2,2,"Answers");
  wrefresh(answers);
  timex(row,col);
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
void timex(int a,int b){
    int time;
    for(time=600;time>=0;time--)
    {
        timer=newwin(a/5,b/5,0,4*b/5);
	box(timer,0,0);
	mvwprintw(timer,3,5,"%d",time);
	wrefresh(timer);
	sleep(1);
    }//If quiz is for 10 minutes,time=10*60=600
    if(time==-1)
        exit(0);
}



 


