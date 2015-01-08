#ifndef FUNKCJE_H
#define FUNKCJE_H

#include "globals.h"

void apply_surface(int x, int y, SDL_Surface *source, SDL_Surface *destination, SDL_Rect *mms=NULL);
bool load_files();
bool init_SDL();
void clean_up();
SDL_Surface *load_image( std::string filename );
int th_downtimer_f( void *data ) ;
void check_for_full_lines();

#endif
