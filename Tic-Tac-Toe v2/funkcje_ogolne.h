#ifndef FUNKCJE_OGOLNE_H
#define FUNCKJE_OGOLNE_H

#include "globals.h"
#include "windows.h"


//  SDL ==> CONTROL
bool init_SDL();
bool load_files();
//int th_pobieranie_danych_f( void *data );
void clean_up();


//  SDL ==> GRAPHIC
SDL_Surface *load_image( std::string filename );
void apply_surface(int x, int y, SDL_Surface *source, SDL_Surface *destination);
void apply_surface(int x, int y, SDL_Surface *source, SDL_Surface *destination, SDL_Rect *mms);



//std::string IntToStr( int value );
void juzio_intro();


#endif
