
#include <stdio.h>
#include "../GLCD/GLCD.h"
#include "game.h"
#include "../map/map.h"
#include "../players/players.h"
#include "../walls/walls.h"


union playerMove {
    struct {
        uint8_t PlayerID : 8;
        uint8_t PW: 4; // Player_move or Wall_placement
        uint8_t VH : 4; //Vertical or Horizontal
        uint8_t Y : 8;
        uint8_t X : 8;
    }fields;
    uint32_t move;
};

unsigned int turn;
unsigned int map[13][13];
unsigned int walls[2]; // remaining wall for wach player
unsigned int time;
unsigned int orientation; //wall orientation 0 horizontal, 1 vertical
unsigned int wallFlag; // 1 if in wall mode, otherwise 0
unsigned int px[2],py[2]; // players postion
unsigned int currX,currY; // temporary wall position
union playerMove move;
int centers[]={19,35,51,67,83,99,115,131,147,163,179,195,211}; // centers of boxes ad walls
 
void printSchema(){
	 int x=6;int y;
	 LCD_Clear(White);
	 // upper Schema part
	 while(x<230){
		 LCD_DrawLine(x,6,x,229,Black);
		 LCD_DrawLine(6,x,229,x,Black);
		 x+=26;
		 LCD_DrawLine(6,x,229,x,Black);
		 LCD_DrawLine(x,6,x,229,Black);
		 x+=6;
	 }
	 x=33;
	 while(x<230){
		 for(y=0;y<5;y++){
			 LCD_DrawLine(x+y,6,x+y,229,White);
			 LCD_DrawLine(6,x+y,229,x+y,White);
		 }
		 x+=32;
	 }
	 // Lower schema part
	 LCD_DrawLine(6,240,224,240,Black);
	 LCD_DrawLine(6,300,224,300,Black);
	 LCD_DrawLine(6,240,6,300,Black);
	 LCD_DrawLine(64,240,64,300,Black);
	 LCD_DrawLine(70,240,70,300,Black);
	 LCD_DrawLine(160,240,160,300,Black);
	 LCD_DrawLine(166,240,166,300,Black);
	 LCD_DrawLine(224,240,224,300,Black);
	 for(y=0;y<5;y++){
			LCD_DrawLine(65+y,240,65+y,300,White);
			LCD_DrawLine(161+y,240,161+y,300,White);
		}
	 return;
}
 
void printTime(){
	char t[3];
	uint8_t	s[]="s";
	if(time>9){sprintf(t,"%d",time);}
	else{sprintf(t,"0%d",time);}
	GUI_Text(103,260,(uint8_t*)t,Black,White);
	GUI_Text(123,260,s,Black,White);
	return;
}
void printRemainingWalls(){
	 uint8_t P1walls[]="P1 Wall";
	 uint8_t P2walls[]="P2 Wall";
	 char N1[2],N2[2];
	 sprintf(N1,"%d",walls[0]);
	 sprintf(N2,"%d",walls[1]);
	 
	 GUI_Text(8,250,P1walls,Black,White);
	 GUI_Text(29,270,(uint8_t*)N1,Black,White);
	 GUI_Text(168,250,P2walls,Black,White);
	 GUI_Text(195,270,(uint8_t*)N2,Black,White);
	 return;
} 
void initWalls(){
	 walls[0]=8;
	 walls[1]=8;
	 return;
}
// set move sets the 32 bit variabile with move informations
void setMove(){
	if(wallFlag==0){
		move.fields.PlayerID=turn;
		move.fields.PW=wallFlag;
		move.fields.VH=orientation;
		move.fields.X=px[turn];
		move.fields.Y=py[turn];
	}
	else{
		move.fields.PlayerID=turn;
		move.fields.PW=wallFlag;
		move.fields.VH=orientation;
		move.fields.X=currX;
		move.fields.Y=currY;
	}
	return;
}

void variablesInit(){
	time=20;
	orientation=1;
	wallFlag=0;
}

void gameInit(){
	initWalls(); // initiales available walls to each player to 8
	mapInit(); // clear the global variable map
	turn=0; 
	variablesInit(); // Initializes global variables
	printSchema(); // prints game board
	printStartingPlayers();
	printRemainingWalls();
	printTime();
}

void nextMove(){
	setMove(); // sets the 32 variable representing the move
	turn=turn^1; // exor of turn
	variablesInit(); // reinizializes time,orientation and and wallFlag
	printTime();
}

int checkVictory(){
	int i,endgame=0;
	uint8_t P1Victory[]="Victory Player Blue";
	uint8_t P2Victory[]="Victory Player Red";
	if(py[1]<=19){
		endgame=1;
		for(i=71;i<160;i++){
			LCD_DrawLine(7,i,223,i,Red);
		}
		GUI_Text(40,110,P2Victory,Black,Red);
	}
	if(py[0]>=211){
		endgame=1;
		for(i=71;i<160;i++){
			LCD_DrawLine(7,i,223,i,Blue);
		}
		GUI_Text(40,110,P1Victory,Black,Blue);
	}
	return endgame;
}
