#include <stdlib.h>
#include <iostream>
#define MAX 4
using namespace std;
//int config1[MAX][MAX];
struct mystruct {
    int config[MAX][MAX];
    int depth;
    int cost;
    mystruct *next;
    mystruct *pai;
};

mystruct *Game;
void solve(char dir){
    int temp=0;
    if(dir=='w'){
        for (int i=0; i<MAX; i++) {
            for (int j=0; j<MAX; j++) {
                if(Game->config[i][j]==0){
                    temp=Game->config[i-1][j];
                    Game->config[i-1][j]=Game->config[i][j];
                    Game->config[i][j]=temp;
                }
            }
        }
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
            }
        }
    }
    else{
        int config1[MAX][MAX]={{1,2,3,4},{13,6,8,12},{5,9,0,7},{14,11,10,15}};
        for(i=0;i<MAX;i++){
            for(j=0;j<MAX;j++){
                Game->config[i][j]=config1[i][j];
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
