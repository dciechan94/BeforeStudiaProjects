#ifndef CLABEL_H
#define CLABEL_H

#include "CRamki.h"
#include "CEvent.h"

class CLabel : CEvent
{
      private:
           SDL_Surface* m_textSquare;
           SDL_Rect m_rect;
           
           CRamki* m_ramki;
           std::string m_napis;
           
           TTF_Font *m_font;
           SDL_Color m_font_color;
           
      public:
           CLabel( CRamki* obiekt_ramek, int posx, int posy, std::string napis, int fontSize = 12 );
           ~CLabel();
           
           void set_caption( std::string );
           void show();
           
};

#endif
