/*----------------------------------------------------------------------------
 * Name:    snake.c
 * Purpose: Snake Game
 * By: Mohib Khan
 *----------------------------------------------------------------------------*/
            
#include "stdio.h"
#include "stdlib.h"
#include "LPC17xx.h"
#include "KBD.h"
#include "GLCD.h"
#include "LED.h"

//Directions
#define UP		0
#define RIGHT	1
#define DOWN	2
#define LEFT	3

//Snake variables
int snake[100][2]; 
int x_snake; 
int y_snake; 
int length_snake; 
int direction; 
int prev_direction; 
int speed; 

//Snake food coordinates
int x_food, y_food; 

//Joystick vals
int joystick_val = KBD_UP; 
int joystick_prev_val = KBD_UP;

//Variable to hold score value
char str[20];

int isHit = 0;
int score = 0;
int isGameDone = 0;

int game(void);
int restart(void);
void eat_food(void);
void extend_body(void);
void state_check(void);
void update(void);
void dir(int);

//Delay Function
void delay (int count){
	int val= 10000000;
	val /= count;
	while(val--);
}



//Food location randomizer
void eat_food(){

	x_food = (rand()%8)+1; // 0th row used by score counter
	y_food = rand()%19;
	
	if(x_food == snake[0][0])
		if(y_food == snake[0][1])
			eat_food();
	
	//Display character to represent eat_food
	GLCD_SetTextColor(Red);
	GLCD_DisplayChar(x_food,y_food,1,0x81);
	
}

//Extend snake length and add to score
void extend_body(){
	length_snake++;
	score += 1;
}

//Status Checker
void state_check(){
	int i;
	
	if(x_food == snake[0][0])
		if(y_food == snake[0][1]){
			extend_body();
			eat_food();
		}
		
	for(i=1;i<length_snake;i++){
		if(snake[0][0] == snake[i][0])
			if(snake[0][1] == snake[i][1])
				isHit = 1;
	}
	
}

//Update Game (LCD, score, etc.)
void update(){
	int i;
	GLCD_SetTextColor(Black);
	if(direction == UP){ 
		for(i=length_snake;i>0;i--){
			if(i-1 == 0){
				snake[0][1] = y_snake;
				snake[0][0] = x_snake;				
			}else{
				GLCD_DisplayChar(snake[i-1][0],snake[i-1][1],1,' ');
				snake[i-1][1] = snake[i-2][1];
				snake[i-1][0] = snake[i-2][0];
			}
		}
		for(i=1;i<length_snake;i++){
			GLCD_DisplayChar(snake[0][0],snake[0][1],1,0x85);
			GLCD_DisplayChar(snake[i][0],snake[i][1],1,0x83);
		}
		delay(speed);
	}
	else if(direction == RIGHT){ 
		for(i=length_snake;i>0;i--){
			if(i -1 == 0){
				snake[0][1] = y_snake;
				snake[0][0] = x_snake;				
			}else{
				GLCD_DisplayChar(snake[i-1][0],snake[i-1][1],1,' ');
				snake[i-1][1] = snake[i-2][1];
				snake[i-1][0] = snake[i-2][0];
			}
		}		
		for(i=1;i<length_snake;i++){
			GLCD_DisplayChar(snake[0][0],snake[0][1],1,0x8B);
			GLCD_DisplayChar(snake[i][0],snake[i][1],1,0x83);
		}
		delay(speed);
	}
	else if(direction == DOWN){ 
		for(i=length_snake;i>0;i--){
			if(i -1 == 0){
				snake[0][1] = y_snake;
				snake[0][0] = x_snake;				
			}else{
				GLCD_DisplayChar(snake[i-1][0],snake[i-1][1],1,' ');
				snake[i-1][1] = snake[i-2][1];
				snake[i-1][0] = snake[i-2][0];
			}
		}
		for(i=1;i<length_snake;i++){
			GLCD_DisplayChar(snake[0][0],snake[0][1],1,0x87);
			GLCD_DisplayChar(snake[i][0],snake[i][1],1,0x83);
		}
		delay(speed);
	}
	else if(direction == LEFT){ 
		for(i=length_snake;i>0;i--){
			if(i -1 == 0){
				snake[0][1] = y_snake;
				snake[0][0] = x_snake;				
			}else{
				GLCD_DisplayChar(snake[i-1][0],snake[i-1][1],1,' ');
				snake[i-1][1] = snake[i-2][1];
				snake[i-1][0] = snake[i-2][0];
			}
		}
		for(i=1;i<length_snake;i++){
			GLCD_DisplayChar(snake[0][0],snake[0][1],1,0x89);
			GLCD_DisplayChar(snake[i][0],snake[i][1],1,0x83);
		}
		delay(speed);
	}
	state_check();
}

//Movement Control and Restraints
void dir(int joystick_val){

	switch(joystick_val){
		case KBD_UP:		
			if (joystick_prev_val == KBD_LEFT || joystick_prev_val == KBD_RIGHT){
				x_snake--;
				
				direction = UP;
				prev_direction = direction;
				joystick_prev_val = joystick_val;
				update();
			}
			break;
		case KBD_RIGHT:		
			if (joystick_prev_val == KBD_UP || joystick_prev_val == KBD_DOWN){
				y_snake++;

				direction = RIGHT;
				prev_direction = direction;
				joystick_prev_val = joystick_val;
				update();
			}
			break;			
		case KBD_DOWN:		
			if (joystick_prev_val == KBD_LEFT || joystick_prev_val == KBD_RIGHT){
				x_snake++;
				
				direction = DOWN;
				prev_direction = direction;
				joystick_prev_val = joystick_val;
				update();
			}
			break;
		case KBD_LEFT:		
			if (joystick_prev_val == KBD_UP || joystick_prev_val == KBD_DOWN){
				y_snake--;

				direction = LEFT;
				prev_direction = direction;
				joystick_prev_val = joystick_val;
				update();
			}
			break;

		default:		
			switch(direction){
				case RIGHT:
					y_snake++;
					if (y_snake > 20){
						y_snake = 0;
					}
					update();
					state_check();
					break;
				case LEFT:
					y_snake--;
					if (y_snake < 0){
						y_snake = 20;
					}
					update();
					state_check();
					break;
				case DOWN:
					x_snake++;
					if (x_snake > 9){
						x_snake = 0;
					}
					update();
					state_check();
					break;
				case UP:
					x_snake--;
					if (x_snake < 0){
						x_snake = 9;
					}
					update();
					state_check();
					break;
			}
			break;
	}	
}


int restart(void)
{
	game();
	return 0;
}

int game(){
	//Menu
	int js_menu;
	int active_sel = 0;
	int sel_menu = 1;
	
	isGameDone = 0;
	
	//Initialize game
	score = 0;
	isHit = 0;
	direction = UP;
	prev_direction = UP;
	joystick_val = KBD_UP;
	joystick_prev_val = KBD_UP;
	length_snake = 2;
	x_snake = 4;
	y_snake = 9;
	
	KBD_Init();
	GLCD_Init();
	
	GLCD_Clear(White);
	GLCD_SetBackColor(Green);
	GLCD_SetTextColor(Black);
	GLCD_DisplayString(0, 0, 1, "     SNAKE GAME     ");
	GLCD_SetBackColor(White);
	GLCD_SetTextColor(White);
	GLCD_DisplayString(2, 0, 1, "                    ");
	GLCD_SetBackColor(Yellow);
	GLCD_SetTextColor(Black);
	GLCD_DisplayString(4, 0, 1, "       EASY         ");
	GLCD_SetBackColor(White);
	GLCD_SetTextColor(Black);
	GLCD_DisplayString(5, 0, 1, "       MEDIUM       ");
	GLCD_DisplayString(6, 0, 1, "       HARD         ");					
	GLCD_DisplayString(8, 0, 1, "       RETURN       "); 	
	
	while(!isGameDone){
		
			while(sel_menu)  {		
			
				js_menu = get_button();
				if(js_menu == KBD_DOWN){
					if(active_sel == 4){
						 active_sel = 0;
					}
					else {
						active_sel++;
					}
				}
				else if(js_menu == KBD_UP){
					if(active_sel == 0){
						active_sel = 4;
					}
					else {
						active_sel--;
					}
				}

				if(active_sel== 0)  {		//Hovering EASY
							GLCD_SetBackColor(Yellow);
							GLCD_SetTextColor(Black);
							GLCD_DisplayString(4, 0, 1, "       EASY         ");
							GLCD_SetBackColor(White);
							GLCD_SetTextColor(Black);
							GLCD_DisplayString(5, 0, 1, "       MEDIUM       ");
							GLCD_DisplayString(6, 0, 1, "       HARD         ");					
							GLCD_DisplayString(8, 0, 1, "       RETURN       "); 				
					
							if(js_menu == KBD_SELECT){
									speed = 2;
									break;
						
							}
				}
				else if (active_sel == 1)  {		//Hovering MEDIUM
							GLCD_SetBackColor(White);
							GLCD_SetTextColor(Black);
							GLCD_DisplayString(4, 0, 1, "       EASY         ");
							GLCD_SetBackColor(Yellow);
							GLCD_SetTextColor(Black);
							GLCD_DisplayString(5, 0, 1, "       MEDIUM       ");
							GLCD_SetBackColor(White);
							GLCD_SetTextColor(Black);
							GLCD_DisplayString(6, 0, 1, "       HARD         ");	
							GLCD_DisplayString(8, 0, 1, "       RETURN       "); 					
					
							if(js_menu == KBD_SELECT){
									speed = 4;
									break;
							}
				}
				else if (active_sel == 2) {			//Hovering HARD
							GLCD_SetBackColor(White);
							GLCD_SetTextColor(Black);
							GLCD_DisplayString(4, 0, 1, "       EASY         ");
							GLCD_DisplayString(5, 0, 1, "       MEDIUM       ");
							GLCD_SetBackColor(Yellow);
							GLCD_SetTextColor(Black);				 
							GLCD_DisplayString(6, 0, 1, "       HARD         ");	
							GLCD_SetBackColor(White);
							GLCD_SetTextColor(Black);					
							GLCD_DisplayString(8, 0, 1, "       RETURN       "); 
					
							if(js_menu == KBD_SELECT){
									speed = 6;
									break;						
							}
				}				
				else if (active_sel == 3) {				//Hovering RETURN
							GLCD_SetBackColor(White);
							GLCD_SetTextColor(Black);
							GLCD_DisplayString(4, 0, 1, "       EASY         ");
							GLCD_DisplayString(5, 0, 1, "       MEDIUM       ");		 
							GLCD_DisplayString(6, 0, 1, "       HARD         ");	
							GLCD_SetBackColor(Red);
							GLCD_SetTextColor(White);					
							GLCD_DisplayString(8, 0, 1, "       RETURN       "); 
					
							if(js_menu == KBD_SELECT){
									GLCD_Clear(White);
									isGameDone = 1;
									return 0;
							}
				}			
		}
			
		GLCD_Clear(White);
		GLCD_SetBackColor(White);
		eat_food();	
		while(isHit == 0){
			
			joystick_val = get_button();
			dir(joystick_val);
			sprintf(str,"SCORE: %d",score);
			GLCD_DisplayString(0, 5,1,(unsigned char *)str);	
		}
		if(isHit == 1){       
			GLCD_Clear(Maroon);
			GLCD_SetBackColor(Maroon);
			GLCD_SetTextColor(White);
			sprintf(str, "  FINAL SCORE: %d  ", score);
			GLCD_DisplayString(3,0,1,(unsigned char *)str);
			GLCD_DisplayString(5,0,1, "    YOU LOST LMAO   ");
			delay(1);
			delay(1);
			delay(1);
			delay(1);
			
			restart();
		}
		delay(1);
	}
	return 0;
}

