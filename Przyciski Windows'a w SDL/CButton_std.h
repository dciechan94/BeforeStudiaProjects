#ifndef CBUTTON_STD_H
#define CBUTTON_STD_H

#include "CRamki.h"
#include "CEvent.h"


class CButton_std : public CEvent
{
      private:
           SDL_Surface* m_textSquare;
           SDL_Surface* m_btn_mouse;
           SDL_Surface* m_btn_click;
           SDL_Surface* m_btn_unactive;
           SDL_Surface* m_btn_disabled;
           SDL_Rect m_rect;
           
           CRamki* m_ramki;
           bool m_on_target;
           bool m_clicked_focus;
           bool m_enabled;
           std::string m_napis; 
           
           TTF_Font *m_font;
           SDL_Color m_font_color;
           
           void (*m_event_fn_LButtonUp)();
           
      public:
           CButton_std( CRamki* obiekt_ramek, int posx, int posy, std::string napis, void (*event_fn_LButtonUp)(), int width );
           ~CButton_std();
           
           void OnEvent(SDL_Event* Event);
           void OnMouseMove(int mX, int mY, int relX, int relY, bool Left,bool Right,bool Middle);
           void OnLButtonDown(int mX, int mY);
           void OnLButtonUp(int mX, int mY);
           
           void set_enabled( bool val );
           void set_caption( std::string napis );
           void refresh_surfaces();
           
           void show();
};

#endif
