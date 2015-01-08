#ifndef CRAMKI_H
#define CRAMKI_H


#include "globals.h"
#include <windows.h>

class CRamki
{
      public: //private:
           SDL_Surface* m_button_std[3*3];
           SDL_Surface* m_button[10*3];
           SDL_Surface* m_checkbox[(1*2)*3];
           SDL_Surface* m_radiobutton[(1*2)*3];
           SDL_Surface* m_border_std[8*3];
           SDL_Surface* m_border2[8];
           SDL_Surface* m_border_scroll[(2*4)+(3*3)+1];
           
           std::string m_adresGrafik;
           
           
           // 45% kolor górny <== button
           // reszta dolny
           
      public:
           CRamki();
           ~CRamki();
           bool laduj_ramki();
           SDL_Surface* load_image( std::string filename );
           //void show();
           
};

#endif
