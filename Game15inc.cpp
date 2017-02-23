#include <stdlib.h>
#include <iostream>
#include <unordered_map>
#include <queue>

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

mystruct *Game; //pointer to the 1st game struct
mystruct *GameF; //pointer to the last game struct

//hastable
unordered_map<string,bool> table; // hastable to represent viseted nodes

//queue for BFS
queue<struct *mystruct> bfs;

//convertion matrix to
string converter(mystruct *game)
{
  string key;
  for(int i=0; i<MAX; i++)
  {
    for (int j=0; j<MAX; j++)
    {
      key += Game->config[i][j] + 'A';
    }
  }
  return key;
}

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

// check if 1st board i can solve to the last board
bool completude()
{
  int inv_first=0; //number of inversions of 1st board
  int inv_last=0; //number of inversions of last board

  int i=0, j=0;

  int first_config[MAX*MAX]; // vetor saving matrix initial
  int last_config[MAX*MAX]; //vetor saving matrix final

  int a=0; //running on vetor

  // copy matrix to vetor
  for (i=0; i<MAX; i++)
  {
    for(j=0;j<MAX;j++)
    {
      first_config[a++] = Game->config[i][j];
    }
  }

  // count number of inversions
  for (i=0; i<MAX*MAX; i++)
  {
    //cout << "i: " << a << "|  num: position: " << first_config[i] << endl;
    for(j=i; j<MAX*MAX; j++)
    {
      int  k = first_config[i];
      if (k>first_config[j] && 0 != first_config[j]) // if 1 positions is lower than everyone in front
      inv_first++;
    }
  }

  a=0;

  // copy matrix to vetor
  for (i=0; i<MAX; i++)
  {
    for(j=0;j<MAX;j++)
    {
      last_config[a++] = GameF->config[i][j];
    }
  }

  // count number of inversions
  for (i=0; i<MAX*MAX; i++)
  {
    //cout << "i: " << a << "|  num: position: " << first_config[i] << endl;
    for(j=i; j<MAX*MAX; j++)
    {
      int  k = last_config[i];
      if (k>last_config[j] && 0 != last_config[j]) // if 1 positions is lower than everyone in front
      inv_last++;
    }
  }


  //cout << "inv_first: " << inv_first << endl;
  //cout << "inv_last: " << inv_last << endl;

  // 0 em linha par e inversoes impar
  // 0 em linha impar e inversoes par

  return ( ((Game->linha%2==0 && inv_first%2!=0) == (GameF->linha%2==0 && inv_last%2!=0)) && ((Game->linha%2!=0 && inv_first%2==0) == (GameF->linha%2!=0 && inv_last%2==0)) );
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

void play()
{
  mystruct tmp;
  tmp = bfs.pop();
  while (!bfs.empty())
    {

    }

}

void read(int flag){

  int i=0,j=0;

  Game=(struct mystruct*)malloc(sizeof(struct mystruct));

  // initial config 1
  if(flag==1)
  {
    int config1[MAX][MAX]={{1,2,3,4},{5,6,8,12},{13,9,0,7},{14,11,10,15}};

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

  //Final configration
  GameF=(struct mystruct*)malloc(sizeof(struct mystruct));

  // final config
  int config1[MAX][MAX]={{1,2,3,4},{5,6,7,8},{9,10,11,12},{13,14,15,0}};

  // assign valeus and save 0 int postion on config board
  for(i=0;i<MAX;i++)
  {
    for(j=0;j<MAX;j++)
    {
      GameF->config[i][j]=config1[i][j];
      if(config1[i][j]==0)
      {
        Game->linha=i;
        Game->coluna=j;
      }
    }
  }

  //decide what postion 0 goes up('w'), down('s'), left('a'), rigth('d')
  //char dir;
  //cin >> dir;
  //print();
  //solve(dir);
  //cout << completude() << endl;

  bfs.push(Game);
}



int main()
{

  // decide what initial configuration i wan't
  int flag;
  cin >> flag;

  read(flag);

  play();
  //print();

  cout << converter(Game) << endl;

  return 0;
}
