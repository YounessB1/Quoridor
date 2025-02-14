
#include "../game/game.h"
#include "map.h"

void mapInit(){
	int i,j;
	for(i=0;i<13;i++){
		for(j=0;j<13;j++){
			map[i][j]=0;
		}
	}
}

int mapIndex(int pos){
	int t,i;
	for(i=0;i<13;i++){
		if(centers[i]==pos){
			t=i;
		}
	}
	return t;
}


void mapWall(int posx, int posy, int orientation){
	int x,y;
	x=mapIndex(posx);
	y=mapIndex(posy);
	if(orientation==1){
		map[x][y]=1;
		map[x-1][y]=1;
		map[x+1][y]=1;
	}
	if(orientation==0){
		map[x][y]=1;
		map[x][y-1]=1;
		map[x][y+1]=1;
	}
	return;
}

void mapPlayer(int posx, int posy){
	int x,y;
	x=mapIndex(posx);
	y=mapIndex(posy);
	map[x][y]=2;
	return;
}
