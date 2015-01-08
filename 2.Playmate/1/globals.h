#ifndef GLOBALS_H
#define GLOBALS_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_thread.h>

#include <sstream> 
#include <string>
#include <vector>
#include <cmath>

#include "enums.h"
#include "funkcje.h"
#include "CTimer.h"
#include "windows.h"

extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;
extern int SCREEN_BPP;

extern int FRAMES_PER_SECOND;
extern int intro_alpha;
extern int mouse_x;                    
extern int mouse_y; 
extern int plansza[17][10];
extern int klocek_taby;
extern int klocek_tabx;
extern int wynik;

extern SDL_Surface *screen;
extern SDL_Surface *juzio_producion_presents;
extern SDL_Surface *papirus;
extern SDL_Surface *menu_tlo;
extern SDL_Surface *game_tlo;
extern SDL_Surface *klocek;

extern SDL_Event event;

extern SDL_Thread *th_downtimer;

extern TTF_Font *font;
extern SDL_Color textColor;

extern bool quit;
extern bool intro_fadein;
extern bool block_in_table;


extern CTimer fps;
extern Uint8 *keystates; 

extern GAMESTATE gamestate;
extern KLOCEK_TYPE blocktype;


#endif 
