#ifndef CCOMBOBOX_H
#define CCOMBOBOX_H

#include <list>
#include "CRamki.h"
#include "CEvent.h"

class CComboBox : public CEvent
{
      private:
          SDL_Surface* m_unactive;
          SDL_Surface* m_mouseOn;
          SDL_Surface* m_mouseOn_box;
          SDL_Surface* m_clicked;
          SDL_Surface* m_disabled;
          SDL_Surface* m_valueS;
          
          std::string m_value;
          
          SDL_Rect m_rect;
          CRamki* m_ramki;
          
          int m_max_objects;
          int m_znacznik;
          int m_wybrany;
          
          bool m_mouse_on_box;
          bool m_mouse_on_arrow;
          bool m_arrow_pressed;
          bool m_enabled;
          
          bool m_open_list;
          
          TTF_Font *m_font;
          SDL_Color m_font_color;
          
          // ListBox elementy
          SDL_Surface* m_rama;
          SDL_Surface* m_plansza;
          SDL_Surface* m_scroll_bg;
          
          SDL_Rect m_rect_lb;
          SDL_Rect m_obszar_plansza;
          SDL_Rect m_scroll_rect;
          
          std::list<std::string> m_dane;
          
          int m_height_elemntu;
          bool m_mouse_on_scroll;
          bool m_scroll_up_mouse;
          bool m_scroll_down_mouse;
          bool m_scroll_up_pressed;
          bool m_scroll_down_pressed;
          bool m_scroll_updown_moved;
          bool m_scroll_focus;
          bool m_duzo_obiektow;
          bool m_mouse_on_plansza;
          
          SDL_Color m_click_font_color;
          SDL_Color m_click_bg_color;
      public:
          CComboBox( CRamki* obiekt_ramek, int posx, int posy, int width, int fontSize = 10);
          ~CComboBox();
          
          void OnEvent(SDL_Event* Event);
          void OnMouseMove(int mX, int mY, int relX, int relY, bool Left,bool Right,bool Middle);
          void OnLButtonDown(int mX, int mY);
          void OnLButtonUp(int mX, int mY);
          
          void show();
          void refresh_items();
          void dodaj(std::string napis);
          void usun(int index);
          void usun_all();
          int get_size();
          int get_znacznik();
          int get_value_index();
          bool get_statusOpened();
          void set_znacznik( int liczba );
          void set_value( int liczba );
          void set_enabled( bool val );
};

#endif
