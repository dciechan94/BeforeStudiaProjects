#ifndef KONTROLKI_H
#define KONTROLKI_H

#include <list>
#include "globals.h"
#include "funkcje_ogolne.h"
#include "CEvent.h"
#include "CRamki.h"

class CEvent;
class CRamki;


class CLabel
{
      private:
           SDL_Surface* m_textSquare;
           SDL_Rect m_rect;
           
           std::string m_napis;
           
           TTF_Font *m_font;
           SDL_Color m_font_color;
           
      public:
           CLabel( int posx, int posy, std::string napis, int fontSize = 12 );
           ~CLabel();
           
           void set_caption( std::string );
           void show();
           
};


class CCheckBox : public CEvent
{
      private:
           SDL_Surface* m_textSquare;
           SDL_Rect m_rect;
           
           CRamki* m_ramki;
           bool m_ticked;
           bool m_on_target;
           bool m_clicked_focus;
           std::string m_napis;
           static int m_dist_img_txt; 
           
           TTF_Font *m_font;
           SDL_Color m_font_color;
           
      public:
           CCheckBox( CRamki* obiekt_ramek, int posx, int posy, std::string napis, bool ticked, int fontSize = 12 );
           ~CCheckBox();
           
           void OnEvent(SDL_Event* Event);
           void OnMouseMove(int mX, int mY, int relX, int relY, bool Left,bool Right,bool Middle);
           void OnLButtonDown(int mX, int mY);
           void OnLButtonUp(int mX, int mY);
           
           bool is_ticked();
           void set_ticked( bool val );
           void show();
           
};


class CButton_std : public CEvent
{
      private:
           SDL_Surface* m_textSquare;
           SDL_Rect m_rect;
           
           CRamki* m_ramki;
           bool m_on_target;
           bool m_clicked_focus;
           std::string m_napis; 
           
           TTF_Font *m_font;
           SDL_Color m_font_color;
           
           BUTTON_STD_TYPE m_id;
           
      public:
           CButton_std( CRamki* obiekt_ramek, int posx, int posy, std::string napis, BUTTON_STD_TYPE id, int width = 1);
           ~CButton_std();
           
           void OnEvent(SDL_Event* Event);
           void OnMouseMove(int mX, int mY, int relX, int relY, bool Left,bool Right,bool Middle);
           void OnLButtonDown(int mX, int mY);
           void OnLButtonUp(int mX, int mY);
           
           void show();
           
};

class CEditBox : public CEvent
{
      private:
           SDL_Surface* m_textSquare;
           SDL_Surface* m_znacznik;
           //SDL_Surface* m_pole[3];
           SDL_Rect m_rect;
           SDL_Rect m_background;
           
           CRamki* m_ramki;
           bool m_on_target;
           bool m_clickedWrite_focus;
           bool m_use_length;
           bool m_full_line;
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
           
           std::string get_napis();
           //void init_surfaces();
           void refresh();
           void napisz( std::string nowy );
           void show();
           
           
};

class CRadioButton : public CEvent
{
      private:
           SDL_Surface* m_textSquare;
           SDL_Rect m_rect;
           
           CRamki* m_ramki;
           bool m_ticked;
           bool m_on_target;
           bool m_clicked_focus;
           std::string m_napis;
           static int m_dist_img_txt; 
           
           TTF_Font *m_font;
           SDL_Color m_font_color;
           
           RADIO_BUTTON_TYPE m_id;
           
      public:
           CRadioButton( CRamki* obiekt_ramek, int posx, int posy, std::string napis, bool ticked, RADIO_BUTTON_TYPE id, int);
           ~CRadioButton();
           
           void OnEvent(SDL_Event* Event);
           void OnMouseMove(int mX, int mY, int relX, int relY, bool Left,bool Right,bool Middle);
           void OnLButtonDown(int mX, int mY);
           void OnLButtonUp(int mX, int mY);
           
           bool is_ticked();
           void set_ticked( bool val );
           void show();
           
};


class CListBox : public CEvent
{
      private:
           //SDL_Surface* m_textSquare;
           //SDL_Surface* m_znacznik;
           //SDL_Surface* m_pole[3];
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
           //bool m_clickedWrite_focus;
           //bool m_use_length;
           //bool m_full_line;
           int m_height_elemntu;
           int m_max_objects;
           int m_znacznik;
           
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
           void OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode);
           
           void show();
           void dodaj( std::string napis );
           void usun( int index );
           void usun_all();
           void refresh_items();
           void set_znacznik( int liczba );
           int get_znacznik();
           int get_size();
           
};

#endif
