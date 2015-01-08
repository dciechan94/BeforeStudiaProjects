#ifndef CLISTBOX_H
#define CLISTBOX_H

#include <list>
#include "CRamki.h"
#include "CEvent.h"


class CListBox : public CEvent
{
      private:
           // Pierwszy element listy ma index 1, index 0 - brak zaznaczenia na lisœcie
           SDL_Surface* m_rama;
           SDL_Surface* m_plansza;
           SDL_Surface* m_scroll_bg;
           
           SDL_Rect m_rect;
           SDL_Rect m_rama_rect;
           SDL_Rect m_obszar_plansza;
           SDL_Rect m_scroll_rect;
           
           CRamki* m_ramki;
           bool m_mouse_on_scroll;
           bool m_scroll_up_mouse;
           bool m_scroll_down_mouse;
           bool m_scroll_up_pressed;
           bool m_scroll_down_pressed;
           bool m_scroll_updown_moved;
           bool m_scroll_focus;
           bool m_duzo_obiektow;
           bool m_mouse_on_plansza;
           int m_height_elemntu;
           int m_znacznik;
           
           bool m_enabled;
           
           std::list<std::string> m_dane;
           
           TTF_Font *m_font;
           SDL_Color m_font_color;
           SDL_Color m_click_font_color;
           SDL_Color m_click_bg_color;
           
      public:
           CListBox( CRamki* obiekt_ramek, int posx, int posy, int width, int height, int fontSize = 10);
           ~CListBox();
           
           void OnEvent(SDL_Event* Event);
           void OnMouseMove(int mX, int mY, int relX, int relY, bool Left,bool Right,bool Middle);
           void OnLButtonDown(int mX, int mY);
           void OnLButtonUp(int mX, int mY);
           
           void set_enabled( bool val );
           int get_size();
           void set_znacznik( int val );
           int get_znacznik();
           
           void show();
           void dodaj( std::string napis );
           void import_lista( std::list<std::string> lista, bool append );
           void usun( int index );
           void usun_all();
           void refresh_items();
};

#endif
