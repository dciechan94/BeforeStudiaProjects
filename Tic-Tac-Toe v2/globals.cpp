#include "globals.h"


// SDL ==> SCREEN
int SCREEN_WIDTH = 800;
int SCREEN_HEIGHT = 600;
int SCREEN_BPP = 32;
int FRAMES_PER_SECOND = 20;
SDL_Surface *screen = NULL;
SDL_Surface *menu_ply = NULL;
SDL_Surface *playground_surface = NULL;
SDL_Surface *playground_surface2 = NULL;
SDL_Surface *x_surface = NULL;
SDL_Surface *o_surface = NULL;

// SDL ==> PROGRAM_INTERIOR
SDL_Event event;
bool program_quit_flag = false;


// INNE
PROGRAM_ID proces_gry = PID_MENU_GLOWNE;
GAMETYPE gametype = GT_PP;
bool koniec_gry = false;
GRACZ_PLAYER gracz = GP_NONE;
GRACZ_PLAYER plansza[3][3];
GRACZ_PLAYER wygrany = GP_NONE;
GRACZ_PLAYER computerP = GP_NONE;

//TTF_Font *font = NULL; 
//SDL_Color textColor = { 0, 0, 0 }; 
//CTimer fps;
//Uint8 *keystates = SDL_GetKeyState( NULL );
//MENU_TAB menu_tab = MT_MENU1;
//CTimer lol;
