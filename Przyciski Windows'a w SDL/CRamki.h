#ifndef CRAMKI_H
#define CRAMKI_H

#include <string>
#include <iostream>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"

class CRamki
{
      public:
           SDL_Surface* m_button_std[4*3];
           SDL_Surface* m_button[10*3];
           SDL_Surface* m_checkbox[(1*2)*4];
           SDL_Surface* m_radiobutton[(1*2)*4];
           SDL_Surface* m_border_std[8*4];
           SDL_Surface* m_border2[8];
           SDL_Surface* m_border_scroll[(2*4)+(3*3)+1];
           SDL_Surface* m_combobox[4];
           
           std::string m_adresGrafik;
           
           SDL_Surface* m_screen;
           
           
           // 45% kolor górny <== button
           // reszta dolny
           
      public:
           CRamki();
           ~CRamki();
           bool laduj_ramki( SDL_Surface* ekran_glowny );
           SDL_Surface* load_image( std::string filename );
           
};

#endif
