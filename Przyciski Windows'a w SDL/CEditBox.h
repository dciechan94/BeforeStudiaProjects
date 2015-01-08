#ifndef CEDITBOX_H
#define CEDITBOX_H

#include "CRamki.h"
#include "CEvent.h"
#include "CTimer.h"

class CEditBox : public CEvent
{
      private:
           SDL_Surface* m_textSquare;
           SDL_Surface* m_znacznik;
           SDL_Surface* m_writeFocus;
           SDL_Surface* m_mouseOn;
           SDL_Surface* m_unactive;
           SDL_Surface* m_disabled;
           SDL_Rect m_rect;
           SDL_Rect m_background;
           
           CRamki* m_ramki;
           CTimer m_tmr_znacznik;
           bool m_on_target;
           bool m_clickedWrite_focus;
           bool m_use_length;
           bool m_full_line;
           bool m_enabled;
           int m_max_length;
           std::string m_napis;
           
           static int m_akapit_gora;
           static int m_akapit_lewo;
           static int m_akapit_prawo;
           static int m_akapit_dol;
           
           TTF_Font *m_font;
           SDL_Color m_font_color;
           
      public:
           CEditBox( CRamki* obiekt_ramek, int posx, int posy, int width, std::string napis, int max_length = 0, int fontSize = 12);
           ~CEditBox();
           
           void OnEvent(SDL_Event* Event);
           void OnMouseMove(int mX, int mY, int relX, int relY, bool Left,bool Right,bool Middle);
           void OnLButtonDown(int mX, int mY);
           void OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode);
           
           void set_enabled( bool val );
           std::string get_napis();
           void refresh_surfaces();
           void refresh();
           void napisz( std::string nowy );
           void show();
           
           
};

#endif
