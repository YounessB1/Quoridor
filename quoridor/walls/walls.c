
#include <stdio.h>
#include "../GLCD/GLCD.h"
#include "../game/game.h"
#include "../map/map.h"
#include "walls.h"
#define START 131
// centerWalls={35,67,99,131,163,195};
	
 void printWall(unsigned short Color){ // prints the temporary wall with a given color, postion is given by currX and currY
	 int i,x1,x2,y1,y2;
	 if(orientation==1){
		 x1=currX-29;x2=currX+29;y1=currY-2;y2=currY+2;
		 for(i=x1;i<x2-6;i+=6){
				LCD_DrawLine(i,y1,i+6,y2,Color);
	 }
	 }
	 else if(orientation==0){ 
		 x1=currX-2;x2=currX+2;y1=currY-29;y2=currY+29;
		 for(i=y1;i<y2-6;i+=6){
				LCD_DrawLine(x1,i,x2,i+4,Color);
		 }
	 }
	 return;
 }

 void clearWall(){
	printWall(White);
	 return;
 }
 void showWall(){
		printWall(Blue);
	 return;
 }
 void showStartingWall(){
	 currX=START;
	 currY=START;
	 orientation=1;
	 showWall();
 }
 
/*
 checkBlock cheks, given a player position that he can reach hid destination given by dest
 player position and destination are map indexes
 tha algorithm is iterative and work by flooding
 at each cycle the boxes near the reachable one becomes reachable by putting value 2
 if the line destination contains 2 the function return 0 ------> no block
 if there are no new boxes reached means the player is stuck and the algorithm return 1 -----> block
*/
int checkBlock(int px, int py,int dest){
	 int block,end,nw,m[13][13],i,j;
	 for(i=0;i<13;i++){
		 for(j=0;j<13;j++){
				if(map[i][j]==1){m[i][j]=map[i][j];}
				else{m[i][j]=0;}
		 }
	 }
	 // map the new wall on m
	 i=mapIndex(currX);
	 j=mapIndex(currY);
	 if(orientation==1){
		m[i][j]=1;m[i-1][j]=1;m[i+1][j]=1;
	 }
	 if(orientation==0){
		m[i][j]=1;m[i][j-1]=1;m[i][j+1]=1;
	 }
	 // map one player on m
	 i=mapIndex(px);
	 j=mapIndex(py);
	 m[i][j]=2;
	 block=0;end=0;
	 // end = 1 means the aplyer reached his destination
	 // block = 1 means the player is stuck
	 while(block==0 && end==0){
		nw=0;
		for(i=0;i<13;i++){
		 for(j=0;j<13;j++){
				if(m[i][j]==2){
					if(i+2<13){
						if(m[i+2][j]==0 && m[i+1][j]==0){
							m[i+2][j]=2;nw++;
						}
					}
					if(i-2>=0){
						if(m[i-2][j]==0 && m[i-1][j]==0){
							m[i-2][j]=2;nw++;
						}
					}
					if(j+2<13){
						if(m[i][j+2]==0 && m[i][j+1]==0){
							m[i][j+2]=2;nw++;
						}
					}
					if(j-2>=0){
						if(m[i][j-2]==0 && m[i][j-1]==0){
							m[i][j-2]=2;nw++;
						}
					}
				}
		  }
		}
		for(i=0;i<13;i++){
			if(m[i][dest]==2){end=1;}
		}
		if(nw==0){block=1;}
	 }
	 return block;
}

// the checkBlock algorithm has to be executed one for each player, that's the purpose of check2Block
int check2Block(){
	int r1,r2;
	r2=checkBlock(px[1],py[1],0);
	r1=checkBlock(px[0],py[0],12);
	return (r1 || r2);
}
// thereIsAlreadyAWall no need to be explained
int thereIsAlreadyAWall(){
	int r=0,x,y;
	x=mapIndex(currX);
	y=mapIndex(currY);
	if(orientation==1){
		if(map[x][y]==1 || map[x-1][y]==1 || map[x+1][y]==1){
			r=1;
		}
	}
	else{
		if(map[x][y]==1 || map[x][y-1]==1 || map[x][y+1]==1){
			r=1;
		}
	}
	return r;
}
/* 
if creates a block, or the player has finished his walls, or there is already a block 
seWall returnes 0, meaning insuccess in placing the wall
otherwise returns 1
*/
int setWall(){
	 int i,x1,x2,y1,y2;
	 if(check2Block() || walls[turn]==0 || thereIsAlreadyAWall()){
		 return 0;
	 }
	 if(orientation==1){
		 x1=currX-29;x2=currX+29;y1=currY-2;y2=currY+2;
		 for(i=x1;i<x2;i++){
			 LCD_DrawLine(i,y1,i,y2,Black);
		 }
		 clearWall(); // this part is white to allow to see the temporary move if the wall is placed
	 }
	 else if(orientation==0){ 
		 x1=currX-2;x2=currX+2;y1=currY-29;y2=currY+29;
		 for(i=y1;i<y2;i++){
			 LCD_DrawLine(x1,i,x2,i,Black);
		 }
		 clearWall();
	 }
	 walls[turn]--;
	 mapWall(currX,currY,orientation);
	 printRemainingWalls();
	 return 1;
}
 
void rotateWall(){
	 if(orientation==0){
		 clearWall();
		 orientation=1;
		 showWall();
		 return;
	 }
	 if(orientation==1){
		 clearWall();
		 orientation=0;
		 showWall();
	 }
	 return;
}
									 
void moveUpWall(){
	 if(currY>35){
		 clearWall();
		 currY=currY-32;
		 showWall();
	 }
	 return;
}
void moveDownWall(){
	 if(currY<195){
		 clearWall();
		 currY=currY+32;
		 showWall();
	 }
	 return;
}
void moveLeftWall(){
	 if(currX>35){
		 clearWall();
		 currX=currX-32;
		 showWall();
	 }
	 return;
}
void moveRightWall(){
	 if(currX<195){
		 clearWall();
		 currX=currX+32;
		 showWall();
	 }
	 return;
}

