#ifndef GLOBALS_H
#define GLOBALS_H

#include <string>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_thread.h>
#include "enums.h"
#include "funkcje_inicjalizujace.h"
#include <windows.h>

//#include "CTimer.h"
//#include "Kontrolki.h"
//#include "enums.h"

//#include "funkcje_ogolne.h"

class CLabel;

// SDL ==> SCREEN
extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;
extern int SCREEN_BPP;
extern int FRAMES_PER_SECOND;

extern SDL_Surface *screen;
extern SDL_Surface *menu_ply;
extern SDL_Surface *playground_surface;
extern SDL_Surface *playground_surface2;
extern SDL_Surface *x_surface;
extern SDL_Surface *o_surface;

// SDL ==> PROGRAM_INTERIOR
extern SDL_Event event;
extern bool program_quit_flag;


// INNE
extern PROGRAM_ID proces_gry;
extern GAMETYPE gametype;
extern bool koniec_gry;
extern GRACZ_PLAYER gracz;
extern GRACZ_PLAYER plansza[3][3];
extern GRACZ_PLAYER wygrany;
extern GRACZ_PLAYER computerP;

//extern TTF_Font *font;
//extern SDL_Color textColor;
//extern CTimer fps;
//extern Uint8 *keystates;
//extern MENU_TAB menu_tab;
//extern CTimer lol;

#endif
