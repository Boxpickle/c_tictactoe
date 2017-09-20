#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int LEN = 9;
int GRID[9] = {0,0,0,0,0,0,0,0,0};
int LEN_WIN = 8;
int WIN_CHECK[8] = {0,0,0,0,0,0,0,0};

void print_blank();
void print_top_vertical();
void print_horizontal();
void print_human_lines(int turn);
void start();
void play();
void winner(int win);
void check_win();

int main()
{
  int turn = 0;
  srand(time(NULL)); //more random for computer guesses
  start();

  while(turn < 9)
  {
    if(turn==0)
    {
      printf("\n1 2 3\n4 5 6\n7 8 9\n");
      printf("\nYour turn (x):\n");
    }
    play(turn);
    print_human_lines(turn);
    check_win();
    turn = turn + 1;
  }
  
	if(turn==9)
	{
		system("clear");
		printf("\n\n   DRAW!\n\n\n");
	}

  return 0;
}
//========================

//========================
void print_blank()
{
  print_top_vertical();
  print_top_vertical();
  print_horizontal();
  print_top_vertical();
  print_top_vertical();
  print_horizontal();
  print_top_vertical();
  print_top_vertical();
}
//=====
void print_top_vertical()
{
  //     "12345678901234567
  printf("     |     |     \n");
}
//=====
void print_horizontal()
{
  printf("-----------------\n");
}
//=====
void print_human_lines(int turn)
{
  int i;
  char s[] = "         ";

  for(i=0;i<LEN;i++)
    {
      if(GRID[i] != 0)
	{
	  if(GRID[i]>0)
	    {
	      s[i] = 'X';
	    }else
	    {
	      s[i] = 'O';
	    }
	}
    }
  

  system("clear");
  
  print_top_vertical();
  printf("  %c  |  %c  |  %c  \n",s[0],s[1],s[2]);
  print_horizontal();
  print_top_vertical();
  printf("  %c  |  %c  |  %c  \n",s[3],s[4],s[5]);
  print_horizontal();
  print_top_vertical();
  printf("  %c  |  %c  |  %c  \n",s[6],s[7],s[8]);

  printf("\n1 2 3\n4 5 6\n7 8 9\n");
  
  if(turn%2 == 0)
  {
    printf("\nComputer's turn (o):\n");
  }else
  {
    printf("\nYour turn (x):\n");
  }
}
//=====
void start()
{
  system("clear");
  print_blank();
}
//=====
void play(int turn)
{
  int change;
  int check=-1;

  while(check == -1)
  {
    if(turn%2==0)
    {
      //human turn -> get input from console
      scanf("%d",&change);
    }else
    {
      //computer turn -> randomized guesses
      change = (rand()%9)+1;
    }
    
    if(GRID[change-1] == 0)
    {
      if(turn%2==0)
      {
	  //X
	GRID[change-1] = 1;
      }else
      {
	  //0
	GRID[change-1] = -1;
      }
      check = 0;
    }else
    {
      printf("Bad choice.\n");
    }
  }
}
//=====
void winner(int win)
{
  if(win != 0)
  {
    if(win == 1)
      {
	system("clear");
	printf("\n\n     YOU WIN!\n\n\n");
	exit(0);
      }else if(win == -1)
      {
	system("clear");
	printf("\n\n     COMPUTER WINS!\n\n\n");
	exit(0);
      }
  }
  
}
//=====
void check_win()
{
  int a = 0;
  int i;

  for(i=0;i<LEN_WIN;i++)
  {
    WIN_CHECK[i]=0;
  }
  //elements of WIN_CHECK
  //0 : h top          = 1+2+3
  //1 : h mid          = 4+5+6
  //2 : h bot          = 7+8+9
  //3 : v left         = 1+4+7
  //4 : v mid          = 2+5+8
  //5 : v right        = 3+6+9
  //6 : d topL -> botR = 1+5+9
  //7 : d botL -> topR = 7+5+3

  //horizontal
  WIN_CHECK[0] = GRID[0]+GRID[1]+GRID[2];
  WIN_CHECK[1] = GRID[3]+GRID[4]+GRID[5];
  WIN_CHECK[2] = GRID[6]+GRID[7]+GRID[8];

  //veritcal
  WIN_CHECK[3] = GRID[0]+GRID[3]+GRID[6];
  WIN_CHECK[4] = GRID[1]+GRID[4]+GRID[7];
  WIN_CHECK[5] = GRID[2]+GRID[5]+GRID[8];
  
  //diagonal
  WIN_CHECK[6] = GRID[0]+GRID[4]+GRID[8];
  WIN_CHECK[7] = GRID[6]+GRID[4]+GRID[2];
  
  for(i=0;i<LEN_WIN;i++)
  {
    if(WIN_CHECK[i]==3)
    {
      a = 1;
    }else if(WIN_CHECK[i]==-3)
    {
      a = -1;
    }
    winner(a);
  }
}
