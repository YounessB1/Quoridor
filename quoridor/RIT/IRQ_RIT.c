/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_RIT.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    RIT.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include "lpc17xx.h"
#include "RIT.h"
#include "../led/led.h"
#include "../game/game.h"
#include "../players/players.h"
#include "../walls/walls.h"
#include "../timer/timer.h"

/******************************************************************************
** Function name:		RIT_IRQHandler
**
** Descriptions:		REPETITIVE INTERRUPT TIMER handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/

volatile int key1=0;
volatile int int0=0;
volatile int key2=0;

void RIT_IRQHandler (void)
{	
	int enable=1;
	if((LPC_GPIO1->FIOPIN & (1<<25)) == 0){	// joystick select
		disable_timer(0); // when setting the move timer is disable to reduce bugs
		if(wallFlag==1){
			if(setWall()==1){ // if the wall is correctly placed moves on
				nextMove();
				showMoves();
			}
		}
		else{
			setPlayerMove();
			nextMove();
			if(checkVictory()) 
				enable=0; // disable timer if the game is over
			else
				showMoves(); // otherwise moves on
		}
		if(enable)
			enable_timer(0);
	}
	if((LPC_GPIO1->FIOPIN & (1<<26)) == 0){	//joystick down
		if(wallFlag==1){
			moveDownWall();
		}
		else{
			moveDownPlayer();
		}
	}
	if((LPC_GPIO1->FIOPIN & (1<<27)) == 0){	// joytick left
		if(wallFlag==1){
			moveLeftWall();
		}
		else{
			moveLeftPlayer();
		}
	}
	if((LPC_GPIO1->FIOPIN & (1<<28)) == 0){	// joystick right
		if(wallFlag==1){
			moveRightWall();
		}
		else{
			moveRightPlayer();
		}
	}
	if((LPC_GPIO1->FIOPIN & (1<<29)) == 0){	// joistick up
		if(wallFlag==1){
			moveUpWall();
		}
		else{
			moveUpPlayer();
		}
	}
	/* button management */
	/* INT0 pressed */
	if(int0>1){ 
		if((LPC_GPIO2->FIOPIN & (1<<10)) == 0){	
			switch(int0){				
				case 2:		
					gameInit();
					showMoves();
					enable_timer(0);
					break;
				default:
					break;
			}
			int0++;
		}
		else {	/* button released */
			int0=0;			
			NVIC_EnableIRQ(EINT0_IRQn);							 /* enable Button interrupts			*/
			LPC_PINCON->PINSEL4    |= (1 << 20);     /* External interrupt 0 pin selection */
		}
	}
	else{
			if(int0==1)
				int0++;
	}
	/* KEY1 pressed */
	if(key1>1){ 
		if((LPC_GPIO2->FIOPIN & (1<<11)) == 0){
			switch(key1){				
				case 2:		
					wallFlag=wallFlag^1;
					if(wallFlag==0){
						clearWall();
						showMoves();
					}
					else{
						restorePlayerMove();
						showStartingWall();
					}
					break;
				default:
					break;
			}
			key1++;
		}
		else {	/* button released */
			key1=0;			
			NVIC_EnableIRQ(EINT1_IRQn);							 /* enable Button interrupts			*/
			LPC_PINCON->PINSEL4    |= (1 << 22);     /* External interrupt 0 pin selection */
		}
	}
	else{
			if(key1==1)
				key1++;
	}
	/* KEY2 pressed */
	if(key2>1){ 
		if((LPC_GPIO2->FIOPIN & (1<<12)) == 0){	
			switch(key2){				
				case 2:		
					if(wallFlag==1){
						rotateWall();
					}
					break;
				default:
					break;
			}
			key2++;
		}
		else {	/* button released */
			key2=0;			
			NVIC_EnableIRQ(EINT2_IRQn);							 /* enable Button interrupts			*/
			LPC_PINCON->PINSEL4    |= (1 << 24);     /* External interrupt 0 pin selection */
		}
	}
	else{
			if(key2==1)
				key2++;
	}
	
  LPC_RIT->RICTRL |= 0x1;	/* clear interrupt flag */
	
  return;
}

/******************************************************************************
**                            End Of File
******************************************************************************/
