#include <stdlib.h>
#include <iostream>

using namespace std;

#define MAX 4 // game board size

struct mystruct
{
  int config[MAX][MAX]; // game board
  int depth; // depth of node
  int cost; //cost of node
  int linha; // x position of 0 int 
  int coluna; // y position of 0 int
  mystruct *next; // pointer to child
  mystruct *pai; // pointer to parent
};

mystruct *Game; //pointer to the game struct


// completation of function solve (only assign variables)
void swap(mystruct *teste, int x, int y)
{
  int temp = teste->config[x][y];
  teste->config[x][y] = 0;
  teste->config[teste->linha][teste->coluna] = temp;
  teste->linha = x;
  teste->coluna = y;
}

void print()
{
  for(int i=0;i<MAX  ;i++)
    {
      for(int j=0;j<MAX;j++)
	{
	  cout << Game->config[i][j] << " " ;
	}
      cout << endl;
    }
}

// change postions of 0 int to up ('w'), down('s'), left('a'), rigth('d')
void solve(char dir)
{
  if(dir=='w') // dir UP
    {
      if(Game->linha!=0)
	{
	  swap(Game,Game->linha-1,Game->coluna);
	}
    }
  else if(dir=='s') // dir DOWN
    {
      if(Game->linha!=MAX-1)
	swap(Game,Game->linha+1,Game->coluna);
    }
  if(dir=='a') // dir RIGTH
    {
      if(Game->coluna!=0)
	swap(Game,Game->linha,Game->coluna-1);
    }
  if(dir=='d') // dir LEFT
    {
      if(Game->coluna!=MAX-1)
	swap(Game,Game->linha,Game->coluna+1);
    }
}


void read(int flag){

  int i=0,j=0;

  Game=(struct mystruct*)malloc(sizeof(struct mystruct));

  // initial config 1
  if(flag==1)
    {
      int config1[MAX][MAX]={{3,10,2,4},{5,6,8,12},{13,9,1,7},{14,11,0,15}};

      // search and save 0 int postion on config board
      for(i=0;i<MAX;i++)
	{
	  for(j=0;j<MAX;j++)
	    {
	      Game->config[i][j]=config1[i][j];
	      if(config1[i][j]==0)
		{
		  Game->linha=i;
		  Game->coluna=j;
		}
	    }
	}
    }
  // initial config 2
  else
    {
      int config2[MAX][MAX]={{1,2,3,4},{13,6,8,12},{5,9,0,7},{14,11,10,15}};

      // search and save 0 int postion on config board
      for(i=0;i<MAX;i++)
	{
	  for(j=0;j<MAX;j++)
	    {
	      Game->config[i][j]=config2[i][j];
	      if(config2[i][j]==0)
		{
		  Game->linha=i;
		  Game->coluna=j;
		}
	    }
	}
    }
  
  //decide what postion 0 goes up('w'), down('s'), left('a'), rigth('d')  
  char dir;
  cin >> dir;
  //print();
  solve(dir);
}



int main()
{

  // decide what initial configuration i wan't
  int flag;
  cin >> flag;
  
  read(flag);

  print();

  return 0;
}
