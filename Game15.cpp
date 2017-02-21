#include <stdlib.h>
#include <iostream>
#define MAX 4
using namespace std;
//int config1[MAX][MAX];
struct mystruct {
    int config[MAX][MAX];
    int depth;
    int cost;
    int linha;
    int coluna;
    mystruct *next;
    mystruct *pai;
};

mystruct *Game;

void swap(mystruct *teste, int x, int y){
  int temp = teste->config[x][y];
  teste->config[x][y] = 0;
  teste->config[teste->linha][teste->coluna] = temp;
  teste->linha = x;
  teste->coluna = y;
}

void solve(char dir){
    int temp=0;
    if(dir=='w'){
      if(Game->coluna!=0 )
        swap(Game,Game->linha-1,Game->coluna);
    }
    else if(dir=='s'){
      if(Game->linha!=MAX-1)
      swap(Game,Game->linha+1,Game->coluna);

    }
    if(dir=='a'){
      if(Game->coluna!=0)
      swap(Game,Game->linha,Game->coluna-1);
    }
    if(dir=='d'){
      if(Game->coluna!=MAX-1)
      swap(Game,Game->linha,Game->coluna+1);
    }
}

void read(int flag){

    int i=0,j=0;

    Game=(struct mystruct*)malloc(sizeof(struct mystruct));
    if(flag==1){
        int config1[MAX][MAX]={{1,2,3,4},{5,6,8,12},{13,9,0,7},{14,11,10,15}};
        for(i=0;i<MAX;i++){
            for(j=0;j<MAX;j++){
                Game->config[i][j]=config1[i][j];
                if(config1[i][j]==0) {
                  Game->coluna=i;
                  Game->linha=j;
                }
            }
        }
    }
    else{
        int config1[MAX][MAX]={{1,2,3,4},{13,6,8,12},{5,9,0,7},{14,11,10,15}};
        for(i=0;i<MAX;i++){
            for(j=0;j<MAX;j++){
                Game->config[i][j]=config1[i][j];
                if(config1[i][j]==0) {
                  Game->coluna=i;
                  Game->linha=j;
                }
            }
        }
    }
    char dir;
    cin >> dir;
    solve(dir);
}


void print(){
    for(int i=0;i<MAX  ;i++){
        for(int j=0;j<MAX;j++){
            cout << Game->config[i][j] << " " ;
        }
        cout << endl;
    }


}

int main(){
    int flag;
    cin >> flag;
    read(flag);
    print();

    return 0;

}
