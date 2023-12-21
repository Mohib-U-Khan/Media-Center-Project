/*----------------------------------------------------------------------------
 * Name:    gallery.c
 * Purpose: Gallery
 * By: Mohib Khan
 *----------------------------------------------------------------------------*/
            

#include <LPC17xx.H>                    
#include "GLCD.h"
#include "LED.h"
#include "KBD.h"

#define __FI        1                      

//Gallery Pictures
#include "csgo_logo.c"
#include "valorant_logo.c"
#include "cod_logo.c"
#include "david.c"


//Picture Scroll
int gallery(void){
	int current = 0;
	int button_pressed = 0;

	
	GLCD_SetBackColor(White);
  GLCD_SetTextColor(Blue);
	
		while(1){
			
			GLCD_DisplayString(0, 0, __FI, "     - GALLERY -     ");
			GLCD_DisplayString(8, 0, __FI, " RIGHT/LEFT - SCROLL ");
			GLCD_DisplayString(9, 0, __FI, " SELECT - MAIN MENU ");
			
			button_pressed = get_button();
			
			if(button_pressed == KBD_LEFT){
				if(current == 0){
					current = 3;
					GLCD_Clear(Blue);
				}
				else {
					current--;
					GLCD_Clear(Blue);
				}
			}
			else if(button_pressed == KBD_RIGHT) {
				if(current == 3){
					current = 0;
					GLCD_Clear(Blue);
				}
				else {
					current++;
					GLCD_Clear(Blue);
				}
			}
			else if(button_pressed == KBD_SELECT){ 
					GLCD_Clear(White);
					return 0;
			
			}
			
			if(current == 0)  {
						GLCD_Bitmap (80, 55, 160,  90, (unsigned char *)CSGO_LOGO_pixel_data);	
			}
			else if (current == 1) {
						GLCD_Bitmap (80, 55, 160,  99, (unsigned char *)GIMP_IMAGE_pixel_data);
			}
			else if (current == 2) {
						GLCD_Bitmap (80, 55, 160,  90, (unsigned char *)VALORANT_LOGO_pixel_data);	
			}
			else if (current == 3)
			{
						GLCD_Bitmap (80, 25, 160,  166, (unsigned char *)DAVID_pixel_data);
			}
		}


}
