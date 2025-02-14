

#include <stdio.h>
#include "../GLCD/GLCD.h"
#include "../game/game.h"
#include "../map/map.h"
#include "../players/players.h"

// centersPlayers {19,51,83,115,147,179,211};
uint16_t color[2]={Blue,Red};
unsigned int tmpx[2],tmpy[2]; // takes track of player movement before finalizing the move

void printPlayer(int x,int y,unsigned short Color){
	int i,x1,x2,y1,y2;
	x1=x-10;
	x2=x+10;
	y1=y-10;
	y2=y+10;
	for(i=x1;i<=x2;i++){
		LCD_DrawLine(i,y1,i,y2,Color);
	}
	return;
}


void printStartingPlayers(){
	px[0]=px[1]=115;py[0]=19;py[1]=211;
	tmpx[0]=tmpx[1]=115;tmpy[0]=19;tmpy[1]=211;
	printPlayer(px[0],py[0],Blue);
	mapPlayer(px[0],py[0]);
	printPlayer(px[1],py[1],Red);
	mapPlayer(px[1],py[1]);
	return;
}
void setTemporaryPosition(int x,int y){
	tmpx[turn]=x;
	tmpy[turn]=y;
}

void showMoves(){
	int x,y,posx,posy;
	posx=px[turn];
	posy=py[turn];
	x=mapIndex(posx);
	y=mapIndex(posy);
	// maps player possible poistions on map by setting vlaue to 3
	// for each direction considers the possibility of jumping the other player
	// draws the possible boxes with Cyan
	if(x-2>=0){
		if(map[x-1][y]==0 && map[x-2][y]==0){
			printPlayer(posx-32,posy,Cyan);
			map[x-2][y]=3;
		}
		if(x-4>=0){
			if(map[x-1][y]==0 && map[x-2][y]==2 &&	map[x-3][y]==0){
				printPlayer(posx-64,posy,Cyan);
				map[x-4][y]=3;
			}
		}
	}
	if(x+2<=12){
		if(map[x+1][y]==0 && map[x+2][y]==0){
			printPlayer(posx+32,posy,Cyan);
			map[x+2][y]=3;
		}
		if(x+4<=12){
			if(map[x+1][y]==0 && map[x+2][y]==2 &&	map[x+3][y]==0){
				printPlayer(posx+64,posy,Cyan);
				map[x+4][y]=3;
			}
		}
	}
	if(y-2>=0){
		if(map[x][y-1]==0 && map[x][y-2]==0){
			printPlayer(posx,posy-32,Cyan);
			map[x][y-2]=3;
		}
		if(y-4>=0){
			if(map[x][y-1]==0 && map[x][y-2]==2 &&	map[x][y-3]==0){
				printPlayer(posx,posy-64,Cyan);
				map[x][y-4]=3;
			}
		}
	}
	if(y+2<=12){
		if(map[x][y+1]==0 && map[x][y+2]==0){
			printPlayer(posx,posy+32,Cyan);
			map[x][y+2]=3;
		}
		if(y+4<=12){
			if(map[x][y+1]==0 && map[x][y+2]==2 &&	map[x][y+3]==0){
				printPlayer(posx,posy+64,Cyan);
				map[x][y+4]=3;
			}
		}
	}
}
// cleans both board and map from the possible moves
void cleanMoves(){
	int i,j;
	for(i=0;i<13;i++){
		for(j=0;j<13;j++){
			if(map[i][j]==3){
				map[i][j]=0;
				printPlayer(centers[i],centers[j],White);
			}
		}
	}
}
// next 4 function moves the player in the 4 direction
// they usa tmpx and tmpy as starting position beacause the move may not be final
void moveRightPlayer(){
	int x,y;
	x=mapIndex(tmpx[turn]);
	y=mapIndex(tmpy[turn]);
	if(x+2<=12){
		if(map[x+2][y]==3){
			map[x+2][y]=2;
			printPlayer(centers[x+2],centers[y],color[turn]);
			printPlayer(centers[x],centers[y],Cyan);
			setTemporaryPosition(centers[x+2],centers[y]);
			map[x][y]=3;
		}
		else{
		 if(x+4<=12){
			if(map[x+4][y]==3){
				map[x+4][y]=2;
				printPlayer(centers[x+4],centers[y],color[turn]);
				printPlayer(centers[x],centers[y],Cyan);
				setTemporaryPosition(centers[x+4],centers[y]);
				map[x][y]=3;
			}
		}
	 }
	}
}
void moveLeftPlayer(){
	int x,y;
	x=mapIndex(tmpx[turn]);
	y=mapIndex(tmpy[turn]);
	if(x-2>=0){
		if(map[x-2][y]==3){
			map[x-2][y]=2;
			printPlayer(centers[x-2],centers[y],color[turn]);
			printPlayer(centers[x],centers[y],Cyan);
			setTemporaryPosition(centers[x-2],centers[y]);
			map[x][y]=3;
		}
		else{
		 if(x-4>=0){
			if(map[x-4][y]==3){
				map[x-4][y]=2;
				printPlayer(centers[x-4],centers[y],color[turn]);
				printPlayer(centers[x],centers[y],Cyan);
				setTemporaryPosition(centers[x-4],centers[y]);
				map[x][y]=3;
			}
		 }
	 }
	}
}
void moveDownPlayer(){
	int x,y;
	x=mapIndex(tmpx[turn]);
	y=mapIndex(tmpy[turn]);
	if(y+2<=12){
		if(map[x][y+2]==3){
			map[x][y+2]=2;
			printPlayer(centers[x],centers[y+2],color[turn]);
			printPlayer(centers[x],centers[y],Cyan);
			setTemporaryPosition(centers[x],centers[y+2]);
			map[x][y]=3;
		}
		else{
		 if(y+4<=12){
			if(map[x][y+4]==3){
				map[x][y+4]=2;
				printPlayer(centers[x],centers[y+4],color[turn]);
				printPlayer(centers[x],centers[y],Cyan);
				setTemporaryPosition(centers[x],centers[y+4]);
				map[x][y]=3;
			}
		 }
	  } 
	}
}
void moveUpPlayer(){
	int x,y;
	x=mapIndex(tmpx[turn]);
	y=mapIndex(tmpy[turn]);
	if(y-2>=0){
		if(map[x][y-2]==3){
			map[x][y-2]=2;
			printPlayer(centers[x],centers[y-2],color[turn]);
			printPlayer(centers[x],centers[y],Cyan);
			setTemporaryPosition(centers[x],centers[y-2]);
			map[x][y]=3;
		}
		else{
		 if(y-4>=0){
			if(map[x][y-4]==3){
				map[x][y-4]=2;
				printPlayer(centers[x],centers[y-4],color[turn]);
				printPlayer(centers[x],centers[y],Cyan);
				setTemporaryPosition(centers[x],centers[y-4]);
				map[x][y]=3;
			}
		 }
	  }
	}
}
// finalizes the player move
void setPlayerMove(){
	px[turn]=tmpx[turn];
	py[turn]=tmpy[turn];
	cleanMoves();
	return;
}
// restores the correct postion in case the player started moving then decides to put a wall
// or started moving but his time was over before finalizing the move
void restorePlayerMove(){
	int i,j;
	for(i=0;i<13;i++){
		 for(j=0;j<13;j++){
			if(map[i][j]>1){ // cleans both players for sake of simplicity
				map[i][j]=0;
				printPlayer(centers[i],centers[j],White);
			}
		 }
	 }
	printPlayer(px[0],py[0],Blue);
	printPlayer(px[1],py[1],Red);
	tmpx[0]=px[0];tmpx[1]=px[1];
	tmpy[0]=py[0];tmpy[1]=py[1];
	mapPlayer(px[0],py[0]);
	mapPlayer(px[1],py[1]);
	return;
}


