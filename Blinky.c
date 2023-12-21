/*--------------------------------------------------------------------------
* Name: Blinky.c
* Purpose: Media Center Project
* By: Mohib Khan
*---------------------------------------------------------------------------*/

#include <LPC17xx.h>
#include "GLCD.h"
#include "LED.h"
#include "KBD.h"

#define __FI 1

//Menu logos
extern unsigned char music_logo[];
extern unsigned char gallery_logo[];
extern unsigned char game_logo[];

//Initailize functions
extern int mp3_player(void);
extern int game(void);
extern int gallery(void);

void main_menu(void);

int button_pressed;

//Main Menu
void main_menu() {
	int active = 0;
	
	GLCD_Clear(White);
	while(1) {
		GLCD_SetBackColor(White);
		GLCD_SetTextColor(Red);
		GLCD_DisplayString(0,0,__FI,"      MAIN MENU     ");
		GLCD_SetTextColor(Blue);
		GLCD_DisplayString(8,0,__FI,"  UP/DOWN - Scroll  ");
		GLCD_DisplayString(9,0,__FI,"   SELECT - Select   ");
		
		button_pressed = get_button();
		if(button_pressed == KBD_DOWN) {
			if(active == 3) {
				active = 0;
			}
			else {
				active++;
			}
		}
		else if(button_pressed == KBD_UP){
			if(active ==0) {
					active = 3;
			}
			else {
				active--;
			}
		}
		
		//Gallery selected
		if(active==0) {
				GLCD_SetBackColor(Yellow);
				GLCD_SetTextColor(Blue);
				GLCD_DisplayString(3,0,__FI,"1) GALLERY          ");
				GLCD_SetBackColor(White);
				GLCD_SetTextColor(Blue);
				GLCD_DisplayString(4,0,__FI,"2) MUSIC            ");			
				GLCD_DisplayString(5,0,__FI,"3) GAME             ");
			
				
			
				if(button_pressed == KBD_SELECT) {
					GLCD_Clear(Blue);
					gallery();
				}
			}

		//MP3 selected
		if(active==1) {
				GLCD_SetBackColor(White);
				GLCD_SetTextColor(Blue);
				GLCD_DisplayString(3,0,__FI,"1) GALLERY          ");
				GLCD_SetBackColor(Yellow);
				GLCD_SetTextColor(Blue);
				GLCD_DisplayString(4,0,__FI,"2) MUSIC            ");
				GLCD_SetBackColor(White);
				GLCD_SetTextColor(Blue);			
				GLCD_DisplayString(5,0,__FI,"3) GAME             ");
			
			
			
				if(button_pressed == KBD_SELECT) {
					GLCD_Clear(White);
					mp3_player();
					GLCD_Clear(White);
				}
			}
		
			//Game selected
		if(active==2) {
				GLCD_SetBackColor(White);
				GLCD_SetTextColor(Blue);
				GLCD_DisplayString(3,0,__FI,"1) GALLERY          ");
				GLCD_DisplayString(4,0,__FI,"2) MUSIC            ");
				GLCD_SetBackColor(Yellow);
				GLCD_SetTextColor(Blue);		
				GLCD_DisplayString(5,0,__FI,"3) GAME             ");
			
				
			
				if(button_pressed == KBD_SELECT) {
					GLCD_Clear(White);
					game();
				}
			}
		}
	}

//Main
int main(void) {
		LED_Init();
		GLCD_Init();
		KBD_Init();
	
		GLCD_Clear(White);
		GLCD_SetBackColor(White);
		GLCD_SetTextColor(Blue);
		GLCD_DisplayString(5,0,__FI,"    MEDIA CENTER    ");
		GLCD_SetTextColor(Blue);		
		GLCD_DisplayString(7,0,__FI,"     Mohib Khan   ");
		GLCD_SetTextColor(Red);		
		GLCD_DisplayString(9,0,__FI,"   Select to Start   ");
	
		while(1) {
			if(get_button() == KBD_SELECT) {
					main_menu();
			}
		}
	}
