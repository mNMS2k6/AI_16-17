#include <stdlib.h>
#include <iostream>
#include <unordered_map>
#include <queue>
#include <stack>
#include <vector>         // std::vector
#include <functional>     // std::greater
#include <cmath>
#include <ctime>

using namespace std;

#define MAX 4 // game board size

struct mystruct
{
  int config[MAX][MAX]; // game board
  int depth; // depth of node
  int cost; //cost of node
  int linha; // x position of 0 int
  int coluna; // y position of 0 int
  char last_direction; // save last position
  mystruct * parent; // pointer to parent
};
typedef mystruct* data;

mystruct *Game; //pointer to the 1st game struct
mystruct * GameF; //pointer to the last game struct
string SGameF; //key of the final configuration
string::iterator sit;

// hastable to represent viseted nodes
unordered_map<string, int> table;
//iterator to manage hashtable
unordered_map<string, int>:: iterator it;

//matrix temporary called in paste
int mat2[MAX][MAX];

//matrix to save position x and y of every num on initial config
int posXY[(MAX*MAX)+1][2];

// type of search
int flag2;

//dfs_iter limiter
int dfs_limit = 0;

//queue for BFS
queue<data> bfs;

//stack for dfs
stack<data> dfs;

// how priority_queu is sorted
auto compare = [](data left, data right)
{
  return (left->cost) > (right->cost);
};
// priority_queu for A*
priority_queue <data, std::vector<data>, decltype(compare)> pqueu(compare);


void print(int matriz[][MAX])
{
  for (int i = 0; i < MAX; i++)
    {
      for (int j = 0; j < MAX; j++)
	{
	  cout << matriz[i][j] << " ";
	}
      cout << endl;
    }
}

string converter(int mat[][MAX])
{
  string keychild;
  for (int i = 0; i < MAX; i++)
    {
      for (int j = 0; j < MAX; j++)
	{
	  keychild += mat[i][j] + 'A';
	}
    }
  return keychild;
}

int heuristica (int mat[][MAX])
{
  int c=0;
  for(int i=0; i< MAX; i++)
    for(int j=0; j<MAX; j++)
      if(posXY[mat[i][j]][0] != i || posXY[mat[i][j]][1] != j)
	c += abs(i - posXY[mat[i][j]][0]) + abs(j - posXY[mat[i][j]][1]);
  return c;
}

//completation of function solve (only assign variables)
void swap(mystruct *teste, int x, int y)
{
  int temp = teste->config[x][y];
  teste->config[x][y] = 0;
  teste->config[teste->linha][teste->coluna] = temp;
  teste->linha = x;
  teste->coluna = y;
}

// change postions of 0 int to up ('w'), down('s'), left('a'), rigth('d')
mystruct* solve(char dir, mystruct *Game1)
{
  if (dir == 'w') // dir UP
    {
      swap(Game1, Game1->linha - 1, Game1->coluna);
    }
  else if (dir == 's') // dir DOWN
    {
      swap(Game1, Game1->linha + 1, Game1->coluna);
    }
  else if (dir == 'a') // dir LEFT
    {
      swap(Game1, Game1->linha, Game1->coluna - 1);
    }
  else if (dir == 'd') // dir RIGHT
    {
      swap(Game1, Game1->linha, Game1->coluna + 1);
    }
  return Game1;
}

bool is_Solution(string keychild)
{
  if (keychild.compare(SGameF) == 0)
    return true;
  else
    return false;
}

// past the info in mat2 to mat1
void copy(int mat1[][MAX], int mat2[][MAX])
{
  int i, j;
  for (i = 0; i < MAX; i++)
    for (j = 0; j < MAX; j++)
      mat1[i][j] = mat2[i][j];
}

data Add(data parent)
{
  data tmp;
  tmp = (data) malloc(sizeof(struct mystruct));

  copy(tmp->config, parent->config);
  tmp->depth = parent->depth;
  tmp->cost = parent->cost;
  tmp->linha = parent->linha;
  tmp->coluna = parent->coluna;
  tmp->last_direction = parent->last_direction;
  tmp->parent = parent;

  return tmp;
}

//give the path from the initial config to the last config
string backtrack(data child)
{
  data tmp = child;
  string path;
  string p_tmp;

  while (Game != tmp)
    {
      path = tmp->last_direction;

      path += p_tmp;

      p_tmp = path;

      tmp = tmp->parent;
    }
  return p_tmp;
}

void creat_childs(data child, string keychild, char dir)
{
  if (is_Solution(keychild))
    {
      cout << "###FINAL CONFIG###" << endl;
      print(child->config);
      cout << "###FINAL CONFIG###" << endl;
      cout << "-->Depth: " << child->depth << endl << endl;
      
      switch (dir)
	{
	case 'w':
	  child->last_direction = 'U';
	  break;
	case 's':
	  child->last_direction = 'D';
	  break;
	case 'a':
	  child->last_direction = 'L';
	  break;
	case 'd':
	  child->last_direction = 'R';
	  break;
	}
      cout << "Path from the 1st config:  " << backtrack(child) << endl << endl;
      exit(0);
    }
  
  else if (table.find(keychild) == table.end()) //if the tmp node isn't created yet
    {
      switch (dir)
	{
	case 'w':
	  child->last_direction = 'U';
	  break;
	case 's':
	  child->last_direction = 'D';
	  break;
	case 'a':
	  child->last_direction = 'L';
	  break;
	case 'd':
	  child->last_direction = 'R';
	  break;
	}
      if( flag2==5)
	{
	  child->cost = heuristica(child->config) + child->depth;
	  pqueu.push(child);
	}
      if(flag2==4)
	{
	  //cout << "heuristica: " << heuristica(child->config) << endl;
	  child->cost = heuristica(child->config);
	  pqueu.push(child);
	}    
      if(flag2!=3)
	{
	  pair<string, int> pare(keychild, 1);
	  table.insert(pare);
	}
      else
	{
	  pair<string, int> pare(keychild, child->depth);
	  table.insert(pare);
	}
      if (flag2 == 1)
	{
	  bfs.push(child);
	}
      else if (flag2 == 2 || flag2 == 3)
	{
	  dfs.push(child);
	}
    }

  if(flag2==3)
    {
      if(table.find(keychild) != table.end())
	{
	  switch (dir)
	    {
	    case 'w':
	      child->last_direction = 'U';
	      break;
	    case 's':
	      child->last_direction = 'D';
	      break;
	    case 'a':
	      child->last_direction = 'L';
	      break;
	    case 'd':
	      child->last_direction = 'R';
	      break;
	    }
	  it = table.find(keychild);
	  if(it->second > child->depth)
	    {
	      table.erase(it->first);
	  
	      pair<string, int> pare(keychild, child->depth);
	      table.insert(pare);

	      dfs.push(child);
	    }
	}
    }
}

void general_search()
{
  // start searching for solution
  while (!bfs.empty() || !dfs.empty() || !pqueu.empty())
    {
      data parent;
      
      if (flag2 == 1)
	{
	  parent = bfs.front(); // taking 1 node
	  bfs.pop(); //remove the node taked from the queu
	}
      if (flag2 == 2 || flag2 == 3)
	{
	  parent = dfs.top(); // taking 1 node
	  dfs.pop(); //remove the node taked from the stack
	}
      if(flag2==4 || flag2==5)
	{
	  parent = pqueu.top();
	  pqueu.pop();
	}

      if (parent->coluna+1 < MAX && (parent->depth+1 <= dfs_limit || flag2 != 3) )
	{
	  data child = Add(parent);
	  child->depth = parent->depth+1;
	  child = solve('d', child);
	  string keychild = converter(child->config);
	  creat_childs(child, keychild, 'd');
	}
      
      if (parent->coluna-1 >= 0 && (parent->depth+1 <= dfs_limit || flag2 != 3) )
	{
	  data child = Add(parent);
	  child->depth = parent->depth+1;
	  child = solve('a', child);
	  string keychild = converter(child->config);
	  creat_childs(child, keychild, 'a');
	}
      
      if (parent->linha+1 < MAX && (parent->depth+1 <= dfs_limit || flag2 != 3) )
	{
	  data child = Add(parent);
	  child->depth = parent->depth+1;
	  child = solve('s', child);
	  string keychild = converter(child->config);
	  creat_childs(child, keychild, 's');
	}

      if (parent->linha-1 >= 0 && (parent->depth+1 <= dfs_limit || flag2 != 3) )
	{
	  data child = Add(parent);
	  child->depth = parent->depth+1;
	  child = solve('w', child);
	  string keychild = converter(child->config);
	  creat_childs(child, keychild, 'w');
	}
    }
  
  if(flag2!=3)
    {
      cout << "Solution not Founded!" << endl;
    }
}

// check if 1st board i can solve to the last board
bool completude()
{
  int inv_first = 0; //number of inversions of 1st board
  int inv_last = 0; //number of inversions of last board

  int i = 0, j = 0;

  int first_config[MAX * MAX]; // vetor saving matrix initial
  int last_config[MAX * MAX]; //vetor saving matrix final

  int a = 0; //running on vetor

  // copy 1st matrix to vetor
  for (i = 0; i < MAX; i++)
    {
      for (j = 0; j < MAX; j++)
	{
	  first_config[a++] = Game->config[i][j];
	}
    }

  // count number inversions of the 1st matrix
  for (i = 0; i < MAX * MAX; i++)
    {
      for (j = i; j < MAX * MAX; j++)
	{
	  int k = first_config[i];
	  if (k > first_config[j] && 0 != first_config[j]) // if 1 positions is lower than everyone in front
	    inv_first++;
	}
    }

  a = 0;

  // copy last matrix to vetor
  for (i = 0; i < MAX; i++)
    {
      for (j = 0; j < MAX; j++)
	{
	  last_config[a++] = GameF->config[i][j];
	}
    }

  // count number inversions of last matrix
  for (i = 0; i < MAX * MAX; i++)
    {
      for (j = i; j < MAX * MAX; j++)
	{
	  int k = last_config[i];
	  if (k > last_config[j] && 0 != last_config[j]) // if 1 positions is lower than everyone in front
	    inv_last++;
	}
    }

  // 0 in even row & no. of inversions odd 
  if ((Game->linha % 2 == 0 && inv_first % 2 != 0) == (GameF->linha % 2 != 0 && inv_last % 2 == 0))
    return true;
  // 0 in odd row & no. of inversions even
  else if ((Game->linha % 2 != 0 && inv_first % 2 == 0) == (GameF->linha % 2 == 0 && inv_last % 2 != 0))
    return true;
  else
    return false;
}

void dfs_inter()
{
  if (completude())
    {
      while (1)
	{
	  dfs_limit++;

	  while (!dfs.empty())
	    {
	      dfs.pop();
	    }
	  table.clear();

	  dfs.push(Game);
	  Game->depth = 0;
	  general_search();
	}
    }
  cout << "Solution not fouded!" << endl;
}

void read()
{

  int i = 0, j = 0;

  Game = (struct mystruct*) malloc(sizeof(struct mystruct));
  /*
  // initial config 1
  if (flag == 1)
    {
      int config1[MAX][MAX] =
	{
	  { 1, 2, 3, 4},
	  { 5, 6, 8, 12},
	  { 13, 9, 0, 7},
	  { 14, 11, 10, 15}
	};
  */
  
  cout << "Please, insert the first configuration:" << endl;
  // assign and save 0 int postion on config
  for (i = 0; i < MAX; i++)
    {
      for (j = 0; j < MAX; j++)
	{
	  int k;
	  cin >> k;
	  Game->config[i][j]=k; //= config1[i][j];
	      
	  posXY[ k ][0] = i;
	  posXY[ k ][1] = j;
	      
	  if (k == 0)
	    {
	      Game->linha = i;
	      Game->coluna = j;
	    }
	}
    }
  
      //}

  /*
  // initial config 2
  else
    {
      int config2[MAX][MAX] =
	{
	  { 1, 2, 3, 4 },
	  { 13, 6, 8, 12 },
	  { 5, 9, 0, 7 },
	  { 14, 11, 10, 15 }
	};

      // assign and save 0 int postion on config
      for (i = 0; i < MAX; i++)
	{
	  for (j = 0; j < MAX; j++)
	    {
	      Game->config[i][j] = config2[i][j];
	      
	      posXY[ config2[i][j] ][0] = i;
	      posXY[ config2[i][j] ][1] = j;
	      
	      if (config2[i][j] == 0)
		{
		  Game->linha = i;
		  Game->coluna = j;
		}
	    }
	}
    }
  */
  
  //Final configration struct
  GameF = (struct mystruct*) malloc(sizeof(struct mystruct));

  /*
  // final config
  int config1[MAX][MAX] =
    {
      { 1, 2, 3, 4 },
      { 5, 6, 7, 8 },
      { 9, 10, 11, 12 },
      { 13, 14, 15, 0 }
    };
  */
  
  cout << "Please, insert the final configuration:" << endl;
  // assign and save 0 int postion on config
  for (i = 0; i < MAX; i++)
    {
      for (j = 0; j < MAX; j++)
	{
	  int k;
	  cin >> k;
	  GameF->config[i][j]=k; //= config1[i][j];
	  if (k == 0)
	    {
	      GameF->linha = i;
	      GameF->coluna = j;
	    }
	}
    }

  cout << endl;
  
  // saving the key of the final config
  SGameF = converter(GameF->config);
  
  if (flag2 == 1)
    {
      //add initial config to queu
      bfs.push(Game);
      //add initial config to hashtable
      string keyInicial = converter(Game->config);
      pair<string, int> pare(keyInicial, 1);
      table.insert(pare);
    }
  else if (flag2 == 2 || flag2 == 3)
    {
      //add initial config to stack
      dfs.push(Game);
      //add initial config to hashtable
      string keyInicial = converter(Game->config);
      pair<string, int> pare(keyInicial, 1);
      table.insert(pare);
      //reset limit to =0 if we go for DFS_Interative
      dfs_limit=0;
    }
  else if(flag2==4 || flag2 == 5)
    {
      pqueu.push(Game);
    }
  
  cout << "###INITIAL CONFIG###" << endl;
  print(Game->config);
  cout << "###INITIAL CONFIG###" << endl << endl;
}

int main()
{
  //decide what initial configuration i want
  cout << "Insert kind of search: 1-BFS || 2-DFS|| 3-DFS_Interative || 4-Greedy || 5-A*" << endl;
  cin >> flag2;

  /*
  int flag;
  cout << "Insert initial config: 1-w/Solution || 2-n/Solution" << endl;
  cin >> flag;
  */
  
  read();
  
  if(completude())
    {
      if (flag2 == 3)
	{
	  dfs_inter();
	}
      else
	{
	  general_search();
	}
    }
  else
    {
      cout << "No solution for that configurations" << endl;
    }
  return 0;
}
