#ifndef CRADIOBUTTON_H
#define CRADIOBUTTON_H

#include "CRamki.h"
#include "CEvent.h"


class CRadioButton : public CEvent
{
      private:
           SDL_Surface* m_textSquare;
           SDL_Rect m_rect;
           
           CRamki* m_ramki;
           bool m_ticked;
           bool m_on_target;
           bool m_clicked_focus;
           bool m_enabled;
           std::string m_napis;
           static int m_dist_img_txt; 
           
           TTF_Font *m_font;
           SDL_Color m_font_color;
           
           void (*m_event_fn_LButtonUp)();
           
      public:
           CRadioButton( CRamki* obiekt_ramek, int posx, int posy, std::string napis, bool ticked, void (*event_fn_LButtonUp)(), int);
           ~CRadioButton();
           
           void OnEvent(SDL_Event* Event);
           void OnMouseMove(int mX, int mY, int relX, int relY, bool Left,bool Right,bool Middle);
           void OnLButtonDown(int mX, int mY);
           void OnLButtonUp(int mX, int mY);
           
           bool is_ticked();
           void set_ticked( bool val, bool make_event );
           void set_enabled( bool val );
           void show();
           
};

#endif
