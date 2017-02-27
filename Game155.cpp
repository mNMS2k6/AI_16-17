#include <stdlib.h>
#include <iostream>
#include <unordered_map>
#include <queue>

using namespace std;

#define MAX 4 // game board size

struct mystruct {
	int config[MAX][MAX]; // game board
	int depth; // depth of node
	int cost; //cost of node
	int linha; // x position of 0 int
	int coluna; // y position of 0 int
	char last_direction; // save last position
	//mystruct *next; // pointer to child
	mystruct * parent; // pointer to parent
};
typedef mystruct* data;

mystruct *Game; //pointer to the 1st game struct
mystruct * GameF; //pointer to the last game struct
string SGameF;

//hastable
unordered_map<string, bool> table; // hastable to represent viseted nodes
//string keychild= "";
int mat2[MAX][MAX]; //matrix temporary called in paste

//queue for BFS
queue<data> bfs;

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

// check if 1st board i can solve to the last board
bool completude()
{
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

	return (((Game->linha % 2 == 0 && inv_first % 2 != 0)
			== (GameF->linha % 2 == 0 && inv_last % 2 != 0))
			&& ((Game->linha % 2 != 0 && inv_first % 2 == 0)
					== (GameF->linha % 2 != 0 && inv_last % 2 == 0)));
}

// change postions of 0 int to up ('w'), down('s'), left('a'), rigth('d')
mystruct* solve(char dir, mystruct *Game1) {
	if (dir == 'w') // dir UP
	{
			swap(Game1, Game1->linha - 1, Game1->coluna);
	}
	else if (dir == 's') // dir DOWN
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

void copy(int mat1[][MAX], int mat2[][MAX])  // Faz uma copia da mat2 para a mat1
{
  int i, j;
  for(i=0; i<MAX; i++)
    for(j=0; j<MAX; j++)
      mat1[i][j]=mat2[i][j];
}

data Add(data parent)
{
	data tmp;
	tmp = (data)malloc(sizeof(struct mystruct));
	copy(tmp->config,parent->config);
	tmp->depth = parent->depth;
	tmp->cost = parent->cost;
	tmp->linha = parent->linha;
	tmp->coluna = parent->coluna;
	tmp->last_direction = parent->last_direction;
	tmp->parent = parent;

	return tmp;
}


void creat_childs(data child, string keychild, char dir)
{
		string inicial = converter(Game->config);

/*
		cout << "#######################" << endl << keychild << "-creat_child.key: " << endl;
		cout << inicial << " -inicial: " << endl;
		cout << SGameF << " -final: " << endl;
*/
//print(child->config);
/*cout << "### " << child->linha << " , " << child->coluna << endl << endl;
cout << keychild << " keychild #####" << endl;*/
		if(is_Solution(keychild)) //isSolution
	{
			cout << " final " << endl;
			exit(0);
	}

	else if (table.find(keychild) == table.end()) //if the tmp node isn't created yet
	{
		//cout << " ERER " << endl;
		child->last_direction = dir;

		cout << " ####### ADICIONAR Á PILHA ########" << endl;
		print(child->config);
		cout << " ####### ADICIONAR Á PILHA ######## FINAL" << endl;

		bfs.push(child);

		// adiciona à hash
		pair<string,bool> pare (keychild, true);
		table.insert(pare);
	}
	else{
		cout << "o joao é burro" << endl;
		//bfs.pop();
		//table.erase(keychild);
	}
}

void general_search()
{
	int count = 0;
	// start searching for solution
	while (!bfs.empty() && count < 30)
	{
		count ++;
		data parent = bfs.front(); // taking 1 node
		bfs.pop(); //remove the node taked from the queu
		cout << "######### PAI ##############" << endl;
		print(parent->config);
		cout << "############################" << endl;

		cout << "## d" << endl;

		if(parent->coluna+1 < MAX)
		{
				data child = Add(parent);

				child = solve('d', child);

				string keychild = converter(child->config);

				creat_childs(child, keychild, 'd');
				print(child->config);
		}
		cout << "## a" << endl;
		if(parent->coluna-1 >= 0)
		{
				data child = Add(parent);

				child = solve('a', child);

				string keychild = converter(child->config);

				creat_childs(child, keychild, 'a');
				print(child->config);
		}
		cout << "## s" << endl;
		if(parent->linha+1 < MAX)
		{
				data child = Add(parent);

				child = solve('s', child);

				string keychild = converter(child->config);

				creat_childs(child, keychild, 's');
				print(child->config);
		}
		cout << "## w" << endl;
		if(parent->linha-1 >= 0)
		{
				data child = Add(parent);

				child = solve('w', child);

				string keychild = converter(child->config);

				creat_childs(child, keychild, 'w');
				print(child->config);
		}

	}
	cout << "Solution not Founded!" << endl;
}

void read(int flag) {

	int i = 0, j = 0;

	Game = (struct mystruct*) malloc(sizeof(struct mystruct));

	// initial config 1
	if (flag == 1) {
		int config1[MAX][MAX] = { { 1, 2, 3, 4 }, { 5, 6, 0, 8},
				{ 9, 10, 7, 11 }, { 13, 14, 15, 12 } };

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

	bfs.push(Game); //add initial config to queu

	string keyInicial = converter(Game->config);
	pair<string,bool> pare (keyInicial, true);
	table.insert(pare);

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
	cout << "INICIAL"<< endl;
	print(Game->config);
	cout << "FINAL"<< endl;
	print(GameF->config);

	SGameF=converter(GameF->config);

}

int main()

{

	// decide what initial configuration i wan't
	int flag;
	cin >> flag;

	read(flag);

	general_search();
	//print();

	//cout << converter(Game) << endl;
	//cout << converter(GameF) << endl;
	//cout << "solution: " << is_Solution(Game,GameF) << endl;
	return 0;
}
