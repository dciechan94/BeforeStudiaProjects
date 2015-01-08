#include "globals.h"


int SCREEN_WIDTH = 800;
int SCREEN_HEIGHT = 600;
int SCREEN_BPP = 32;

int FRAMES_PER_SECOND = 10;
int intro_alpha = SDL_ALPHA_TRANSPARENT;
int mouse_x;                    
int mouse_y; 
int plansza[17][10];
int klocek_taby = 0;
int klocek_tabx = 3;
int wynik = 0;

SDL_Surface *screen = NULL;
SDL_Surface *juzio_producion_presents = NULL;
SDL_Surface *papirus = NULL;
SDL_Surface *menu_tlo = NULL;
SDL_Surface *game_tlo = NULL;
SDL_Surface *klocek = NULL;

SDL_Event event;

SDL_Thread *th_downtimer = NULL;

TTF_Font *font = NULL; 
SDL_Color textColor = { 0, 0, 0 };

bool quit = false;
bool intro_fadein = true;
bool block_in_table = false;

CTimer fps;

Uint8 *keystates = SDL_GetKeyState( NULL );

GAMESTATE gamestate = GS_NONE;
KLOCEK_TYPE blocktype = KT_NONE;
