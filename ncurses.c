#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
/*Array to store 10 random integers from 0 to 100*/

int r[10];
WINDOW  *marks,*answers,*heading,*timer,*question;
void ques(WINDOW *remp,int n,int y);
void print_menu(WINDOW *menu_win, int highlight);
int ans();

/*Function to store and generate 10 random integers*/
void randgen( ) {                                                                  
  srand( (unsigned)time( NULL ) );
  int num,i;
  for ( i = 0; i < 10; i++) {
  again:
    {int flag =0;
      num = rand()%1000;
      while(num%6!=0)
	{
          num++;
	}
      if(num>599)
	{
          flag=1;
	}
      else
	{
	  for(int j=0; j<i; j++)
	    {
              if(num==r[j])
		{
                  flag = 1;
		}
	    }
	}
      if (flag !=1 && num !=0)
        {
	  r[i]= num;
        }
      else{
	goto again;
      }           
    }
  }
}

int f=0;
int startx = 0;
int starty = 0;
int mark=0;

/*This function reads mcq.txt for answers and return the integer value store in it*/

int ret(int n)                      
{
  int c=0;
  char file_name[256] = "mcq.txt";
  char buf[512];
  FILE *f = fopen(file_name, "r");
  int lineNumber = 6*n;
  static const char filename[] = "mcq.txt";
  FILE *file = fopen(filename, "r");
  int count = 0;
  if ( file != NULL )
    {
      char line[256]; 
      c=lineNumber;
      while (fgets(line, sizeof line, file) != NULL) 
	{
	  if (count==n){
	    int g;
	    sscanf(line,"%d",&g);
	    return g;
      
	  }
	  count++;      
       
	}
      fclose(file);
    }
  else
    {
      printf("File does not exist");
    }
       
  fclose(f);
}

/*This is an all in one function to print line in the given window.
  Three variables are passed:
  1.WINDOWS in which operation to perform
  2.Line number from file which we have to print
  3.Column number in which it should be printed*/

void ques(WINDOW *remp,int n,int y){     
  int c=0;
  char file_name[256] = "mcq.txt";
  FILE *f = fopen(file_name, "r");
  int lineNumber = 6*n;
  static const char filename[] = "mcq.txt";
  FILE *file = fopen(filename, "r");
  int count = 0;
  if ( file != NULL )
    {
      char line[256]; 
      c=lineNumber;
      while (fgets(line, sizeof line, file) != NULL) 
	{
	  if (count==n){
            mvwprintw(remp,y,5,"%s",line);
	    wrefresh(remp);
	  }
	  count++;      
	}
      fclose(file);
    }
  /* else */
  /*   { */
  /*     printf("File does not exist"); */
  /*   } */
       
  fclose(f);
}

/*This is a special function which is used to highlight the column number in options window
  It uses many built in ncurses functions but it's syntax is easy to understand*/

int ans(int row,int col)
{
  WINDOW *answers;
  int highlight = 1;
  int choice = 0;
  int c;
  initscr();
  clear();
  noecho();
  cbreak(); 
  answers=newwin(2*row/5,col,3*row/5,0);		
  keypad(answers, TRUE);
  print_menu(answers, highlight);
  while(1)
    {
      c = wgetch(answers);
      switch(c)
	{	case KEY_UP:
	    if(highlight == 1)
	      highlight = 4;
	    else
	      --highlight;
	    break;
	case KEY_DOWN:
	  if(highlight == 5)
	    highlight = 1;
	  else 
	    ++highlight;
	  break;
	case 10:
	  choice = highlight;
	  break;
	default: continue;
	}
      if (choice-1==ret(r[f]+5)){
	mark=mark+1;
      }
      print_menu(answers, highlight);
      if(choice != 0)	/* User did a choice come out of the infinite loop */
	break;
    }	
  clrtoeol();
  refresh();
  endwin();
  return 0;
}

/*When choice is being made in ans() function we need a different function used to highlight the selected option
  This function is used to do just that*/

void print_menu(WINDOW *answers, int highlight)
{
  int x, y, i;	
  x = 2;
  y = 1;
  box(answers, 0, 0);
  for(i = 1; i < 5; ++i)
    {
      if(highlight == i + 1) /* High light the present choice */
	{
	  wattron(answers, A_REVERSE); 
	  ques(answers,i+r[f],y);
	  wattroff(answers, A_REVERSE);
	}
      else {
	ques(answers,i+r[f],y);
      }
      ++y;
    }
  wrefresh(answers);
}

/*WINDOW is a built in datatype of ncurses library
  Pointer is needed to perform any kind of operation in windows as we want it to 
  make the change at base address of the window*/ 

int main(int argc,char *argv[])
{
  int row,col,i=0;
  char ch;
  randgen();
  system("clear");
  initscr();
  keypad(stdscr, TRUE);
  cbreak();
  noecho();
  refresh();
  curs_set(0);
  getmaxyx(stdscr,row,col);
  /*Here a while loop is used as we want it to draw windows over and over
    Otherwise the program will end after a single question*/
  while(1){
    marks=newwin(row/5,col/5,0,0);
    box(marks,0,0);
    mvwprintw(marks,3,7,"Marks=%d/10",mark);
    wrefresh(marks);
    wrefresh(heading);
    heading=newwin(row/5,3*col/5,0,col/5);
    box(heading,0,0);
    mvwprintw(heading,1,25," .d88b.  db    db d888888b d88888D ");
    mvwprintw(heading,2,25,".8P  Y8. 88    88   `88'   YP  d8' ");
    mvwprintw(heading,3,25,"88    88 88    88    88       d8'  ");
    mvwprintw(heading,4,25,"88    88 88    88    88      d8'   ");
    mvwprintw(heading,5,25,"`8P  d8' 88b  d88   .88.    d8' db ");
    mvwprintw(heading,6,25," `Y88'Y8 ~Y8888P' Y888888P d88888P ");
    wrefresh(heading);
    timer=newwin(row/5,col/5,0,4*col/5);
    box(timer,0,0);
    mvwprintw(timer,3,3,"Questions Answered:%d/10",f);
    wrefresh(timer);
    wrefresh(question);
    question=newwin(2*row/5,col,row/5,0);
    box(question,0,0);
    ques(question,r[f],2);
    ans(row,col);
    f++;
    if (f==10)
      break;
  }
  endwin();
  system("clear");
  system("figlet Thank you for playing this quiz");
  printf("\n\n\nMarks obtained:\t%d out of 10\n\n\n",mark);
  /* printf("Thank you for playing this quiz!!\n\n"); */
  printf("Created By:-\n\n");
  printf("Thanushree DK\n\n");
  printf("Sushmitha G\n\n");
  printf("Syed Shahabaaz Ahmed\n\n");
  printf("Sudarshan Dodiya\n\n");
  return 0;
}
