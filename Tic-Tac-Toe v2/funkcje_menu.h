#ifndef FUNKCJE_MENU_H
#define FUNCKJE_MENU_H

#include "globals.h"
#include "funkcje_ogolne.h" 
#include "funkcje_inicjalizujace.h"
#include <windows.h>



void obsluga_menu_glowne();
void rozgrywka();

void look_for_click( int mouse_x, int mouse_y );
void check_zasadyGry();
void redraw_sur();
void comp_move( GRACZ_PLAYER sign );

void rozgrywka_PvsP();
void rozgrywka_PvsCOM();
/*void rozgrywka_PvsP_S();
void rozgrywka_PvsP_C();*/



#endif
