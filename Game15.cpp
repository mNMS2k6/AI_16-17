#include <stdlib.h>
#include <iostream>
#include <unordered_map>
#include <queue>
#include <stack>

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

// hastable to represent viseted nodes
unordered_map<string, bool> table;

//matrix temporary called in paste
int mat2[MAX][MAX];

// type of search
int flag2;

//dfs_iter limiter
int dfs_limit=0;

//queue for BFS
queue<data> bfs;

//stack for dfs
stack<data> dfs;

void print(int matriz[][MAX]) {
	for (int i = 0; i < MAX; i++) {
		for (int j = 0; j < MAX; j++) {
			cout << matriz[i][j] << " ";
		}
		cout << endl;
	}
}

string converter(int mat[][MAX]) {
	string keychild;
	for (int i = 0; i < MAX; i++) {
		for (int j = 0; j < MAX; j++) {
			keychild += mat[i][j] + 'A';
		}
	}
	return keychild;
}

//completation of function solve (only assign variables)
void swap(mystruct *teste, int x, int y) {
	int temp = teste->config[x][y];
	teste->config[x][y] = 0;
	teste->config[teste->linha][teste->coluna] = temp;
	teste->linha = x;
	teste->coluna = y;
}

// change postions of 0 int to up ('w'), down('s'), left('a'), rigth('d')
mystruct* solve(char dir, mystruct *Game1) {
	if (dir == 'w') // dir UP
			{
		swap(Game1, Game1->linha - 1, Game1->coluna);
	} else if (dir == 's') // dir DOWN
			{
		swap(Game1, Game1->linha + 1, Game1->coluna);
	}
	if (dir == 'a') // dir LEFT
			{
		swap(Game1, Game1->linha, Game1->coluna - 1);
	}
	if (dir == 'd') // dir RIGHT
			{
		swap(Game1, Game1->linha, Game1->coluna + 1);
	}
	return Game1;
}

bool is_Solution(string keychild) {
	if (keychild.compare(SGameF) == 0)
		return true;
	else
		return false;
}

// past the info in mat2 to mat1
void copy(int mat1[][MAX], int mat2[][MAX]) {
	int i, j;
	for (i = 0; i < MAX; i++)
		for (j = 0; j < MAX; j++)
			mat1[i][j] = mat2[i][j];
}

data Add(data parent) {
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
string backtrack(data child) {
	data tmp = child;
	string path;
	string p_tmp;

	while (Game != tmp) {
		path = tmp->last_direction;

		path += p_tmp;

		p_tmp = path;

		tmp = tmp->parent;
	}
	return p_tmp;
}

void creat_childs(data child, string keychild, char dir) {
	if (is_Solution(keychild))
	{
		cout << "###CONFIG FINAL###" << endl;
		print(child->config);
		cout << child->depth << endl;
		cout << "###CONFIG FINAL###" << endl << endl;

		switch (dir) {
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
		cout << backtrack(child) << endl;
		exit(0);
	}
	else if(table.find(keychild) == table.end()) //if the tmp node isn't created yet
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

		// adiciona à hashtable
		pair<string, bool> pare(keychild, true);
		table.insert(pare);

		if (flag2 == 1)
		{
			bfs.push(child);
		}
		else if (flag2 == 2 || flag2==3)
		{
			dfs.push(child);
		}
	}
	else
	{
	}
}

void general_search()
{
	// start searching for solution
	while (!bfs.empty() || !dfs.empty())
	{
		//cout << dfs.size() << endl;

		data parent;
		if (flag2 == 1)
		{
			parent = bfs.front(); // taking 1 node
			bfs.pop(); //remove the node taked from the queu
		}
		if (flag2 == 2 || flag2==3)
		{
			parent = dfs.top(); // taking 1 node
			dfs.pop(); //remove the node taked from the stack
		}

		if(parent->depth == 13)
		{
		cout << "--------PAI-----------" << endl;
		print(parent->config);
		cout << "depth: " << parent->depth << endl;
		cout << endl;
		}

		if (parent->coluna + 1 < MAX && (parent->depth + 1 <= dfs_limit || flag2!=3))
		{
			data child = Add(parent);
			child->depth = parent->depth + 1;
			child = solve('d', child);
			string keychild = converter(child->config);
			creat_childs(child, keychild, 'd');
		}

		if (parent->coluna - 1 >= 0 && (parent->depth + 1 <= dfs_limit || flag2!=3))
		{
			data child = Add(parent);
			child->depth = parent->depth + 1;
			child = solve('a', child);
			string keychild = converter(child->config);
			creat_childs(child, keychild, 'a');
		}

		if (parent->linha + 1 < MAX && (parent->depth + 1 <= dfs_limit || flag2!=3))
		{
			data child = Add(parent);
			child->depth = parent->depth + 1;
			child = solve('s', child);
			string keychild = converter(child->config);
			creat_childs(child, keychild, 's');
		}

		if (parent->linha - 1 >= 0 && (parent->depth + 1 <= dfs_limit || flag2!=3))
		{
			data child = Add(parent);
			child->depth = parent->depth + 1;
			child = solve('w', child);
			string keychild = converter(child->config);
			creat_childs(child, keychild, 'w');
		}

	}
	cout << "Solution not Founded!" << endl;
}


// check if 1st board i can solve to the last board
bool completude(){
	int inv_first = 0; //number of inversions of 1st board
	int inv_last = 0; //number of inversions of last board

	int i = 0, j = 0;

	int first_config[MAX * MAX]; // vetor saving matrix initial
	int last_config[MAX * MAX]; //vetor saving matrix final

	int a = 0; //running on vetor

	// copy matrix to vetor
	for (i = 0; i < MAX; i++) {
		for (j = 0; j < MAX; j++) {
			first_config[a++] = Game->config[i][j];
		}
	}

	// count number of inversions
	for (i = 0; i < MAX * MAX; i++) {
		//cout << "i: " << a << "|  num: position: " << first_config[i] << endl;
		for (j = i; j < MAX * MAX; j++) {
			int k = first_config[i];
			if (k > first_config[j] && 0 != first_config[j]) // if 1 positions is lower than everyone in front
				inv_first++;
		}
	}

	a = 0;

	// copy matrix to vetor
	for (i = 0; i < MAX; i++) {
		for (j = 0; j < MAX; j++) {
			last_config[a++] = GameF->config[i][j];
		}
	}

	// count number of inversions
	for (i = 0; i < MAX * MAX; i++) {
		//cout << "i: " << a << "|  num: position: " << first_config[i] << endl;
		for (j = i; j < MAX * MAX; j++) {
			int k = last_config[i];
			if (k > last_config[j] && 0 != last_config[j]) // if 1 positions is lower than everyone in front
				inv_last++;
		}
	}

	//cout << "inv_first: " << inv_first << endl;
	//cout << "inv_last: " << inv_last << endl;

	// 0 em linha par e inversoes impar
	// 0 em linha impar e inversoes par

	if ((Game->linha % 2 == 0 && inv_first % 2 != 0) == (GameF->linha % 2 != 0 && inv_last % 2 == 0))
		return true;
	if ((Game->linha % 2 != 0 && inv_first % 2 == 0)== (GameF->linha % 2 == 0 && inv_last % 2 != 0))
		return true;
	else
		return false;
}

void dfs_inter()
{
	if (completude())
	{
		/*
		 *
		 *while (dfs_limit < 13)
		{
		*/
			dfs_limit=13;

			while (!dfs.empty())
			{
				dfs.pop();
			}
			table.clear();

			dfs.push(Game);
			Game->depth = 0;
			general_search();
		//}
		cout << "Solution not foud! - DFS_iter" << endl;
	}
}

void read(int flag) {

	int i = 0, j = 0;

	Game = (struct mystruct*) malloc(sizeof(struct mystruct));

	// initial config 1
	if (flag == 1) {
		int config1[MAX][MAX] = { { 1, 2, 3, 4 }, { 5, 6, 8, 12 },
				{ 13, 9, 0, 7 }, { 14, 11, 10, 15 } };

		// search and save 0 int postion on config board
		for (i = 0; i < MAX; i++) {
			for (j = 0; j < MAX; j++) {
				Game->config[i][j] = config1[i][j];
				if (config1[i][j] == 0) {
					Game->linha = i;
					Game->coluna = j;
				}
			}
		}
	}

	// initial config 2
	else {
		int config2[MAX][MAX] = { { 1, 2, 3, 4 }, { 13, 6, 8, 12 },
				{ 5, 9, 0, 7 }, { 14, 11, 10, 15 } };

		// search and save 0 int postion on config board
		for (i = 0; i < MAX; i++) {
			for (j = 0; j < MAX; j++) {
				Game->config[i][j] = config2[i][j];
				if (config2[i][j] == 0) {
					Game->linha = i;
					Game->coluna = j;
				}
			}
		}
	}

	//Final configration
	GameF = (struct mystruct*) malloc(sizeof(struct mystruct));

	// final config
	int config1[MAX][MAX] = { { 1, 2, 3, 4 }, { 5, 6, 7, 8 }, { 9, 10, 11, 12 },
			{ 13, 14, 15, 0 } };

	// assign valeus and save 0 int postion on config board
	for (i = 0; i < MAX; i++) {
		for (j = 0; j < MAX; j++) {
			GameF->config[i][j] = config1[i][j];
			if (config1[i][j] == 0) {
				GameF->linha = i;
				GameF->coluna = j;
			}
		}
	}

	if (flag2 == 1)
	{
		bfs.push(Game); //add initial config to queu
		string keyInicial = converter(Game->config);
		pair<string, bool> pare(keyInicial, true);
		table.insert(pare);
	}
	else if (flag2 == 2 || flag2==3)
	{
		dfs.push(Game); //add initial config to stack
		string keyInicial = converter(Game->config);
		pair<string, bool> pare(keyInicial, true);
		table.insert(pare);
	}

	cout << "INICIAL" << endl;
	print(Game->config);
	cout << endl;

	cout << "FINAL" << endl;
	print(GameF->config);
	cout << endl;

	SGameF = converter(GameF->config);

}

int main()

{

	// decide what initial configuration i wan't
	cout << "Insert kind of search: 1-BFS || 2-DFS-iter" << endl;
	cin >> flag2;
	int flag;
	cout << "Insert initial config: 1-w/Solution || 2-n/Solution" << endl;
	cin >> flag;

	read(flag);

	if (flag2 == 3)
		dfs_inter();
	else
		general_search();

	return 0;
}
