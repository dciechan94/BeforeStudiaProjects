#include "CRadioButton.h"


int CRadioButton::m_dist_img_txt = 5;

CRadioButton::CRadioButton( CRamki* obiekt_ramek, int posx, int posy, std::string napis, bool ticked, void (*event_fn_LButtonUp)(), int fontSize = 15 )
{
    m_ramki = obiekt_ramek;
    m_rect.x = posx;
    m_rect.y = posy;
    m_napis = napis;
    m_ticked = ticked;
    m_on_target = false;
    m_clicked_focus = false;
    m_enabled = true;
    m_font = TTF_OpenFont( "font/tahoma.ttf", fontSize );
    if( m_font == NULL ) { std::cerr << "CRadioButton Error\n"; this->~CRadioButton(); }
    m_font_color.r = 0x00;
    m_font_color.g = 0x00;
    m_font_color.b = 0x00;
    m_textSquare = TTF_RenderText_Blended( m_font, m_napis.c_str(), m_font_color ); 
    m_rect.w = m_ramki->m_radiobutton[0]->w + m_dist_img_txt + m_textSquare->w;
    if( m_textSquare->h >= m_ramki->m_radiobutton[0]->h ) { m_rect.h = m_textSquare->h; } else { m_rect.h = m_ramki->m_radiobutton[0]->h; }
    m_event_fn_LButtonUp = event_fn_LButtonUp;
}


CRadioButton::~CRadioButton()
{
    SDL_FreeSurface( m_textSquare );
    TTF_CloseFont( m_font );
}

bool CRadioButton::is_ticked()
{
    if( m_ticked == false ) { return false; }
    return true;
}

void CRadioButton::set_ticked( bool val, bool make_event )
{
    m_ticked = val;
    if( make_event == true ) m_event_fn_LButtonUp();
}

void CRadioButton::show()
{
    if( m_enabled == true )
    {
        if( m_on_target == true )
        {
            if( m_ticked == true )
            {   // Ticked
                if( m_clicked_focus == true )
                {   // Pressed
                    apply_surface( m_rect.x, m_rect.y + (m_rect.h-m_ramki->m_radiobutton[5]->h)/2, m_ramki->m_radiobutton[5], m_ramki->m_screen );
                }
                else
                {   // Mouse On
                    apply_surface( m_rect.x, m_rect.y + (m_rect.h-m_ramki->m_radiobutton[4]->h)/2, m_ramki->m_radiobutton[4], m_ramki->m_screen );
                }
            }
            else
            {   // Unticked
                if( m_clicked_focus == true )
                {   // Pressed
                    apply_surface( m_rect.x, m_rect.y + (m_rect.h-m_ramki->m_radiobutton[2]->h)/2, m_ramki->m_radiobutton[2], m_ramki->m_screen );
                }
                else
                {   // Mouse On
                    apply_surface( m_rect.x, m_rect.y + (m_rect.h-m_ramki->m_radiobutton[1]->h)/2, m_ramki->m_radiobutton[1], m_ramki->m_screen );
                }
            }
        }
        else
        {   
            if( m_ticked == true )
            {   // Ticked  // Normal
                apply_surface( m_rect.x, m_rect.y + (m_rect.h-m_ramki->m_radiobutton[3]->h)/2, m_ramki->m_radiobutton[3], m_ramki->m_screen );
            }
            else
            {   // Unticked  // Normal
                apply_surface( m_rect.x, m_rect.y + (m_rect.h-m_ramki->m_radiobutton[0]->h)/2, m_ramki->m_radiobutton[0], m_ramki->m_screen );
            }
        }
    }
    else
    {
        if( m_ticked == true )
        {   // Ticked  // Disabled
            apply_surface( m_rect.x, m_rect.y + (m_rect.h-m_ramki->m_radiobutton[7]->h)/2, m_ramki->m_radiobutton[7], m_ramki->m_screen );
        }
        else
        {   // Unticked  // Disabled
            apply_surface( m_rect.x, m_rect.y + (m_rect.h-m_ramki->m_radiobutton[6]->h)/2, m_ramki->m_radiobutton[6], m_ramki->m_screen );
        }
    }
     
    apply_surface( m_rect.x +(m_ramki->m_checkbox[0]->w) + m_dist_img_txt, m_rect.y, m_textSquare, m_ramki->m_screen );
}

void CRadioButton::OnEvent(SDL_Event* Event)
{
    CEvent::OnEvent(Event);
}

void CRadioButton::OnMouseMove(int mX, int mY, int relX, int relY, bool Left,bool Right,bool Middle)
{
    if( m_enabled == true )
    {
        if(  (mX > m_rect.x) && (mX < m_rect.x + m_rect.w) && (mY > m_rect.y) && (mY < m_rect.y + m_rect.h)  )
        {
             m_on_target = true;
        }
        else
        {
             m_on_target = false;
        }
    }
}

void CRadioButton::OnLButtonUp(int mX, int mY)
{
    if(  (m_on_target == true) && (m_clicked_focus == true)  )
    {
        // Klikniêcie
        m_event_fn_LButtonUp();
    }
    m_clicked_focus = false;
    
}

void CRadioButton::OnLButtonDown(int mX, int mY)
{
    if( m_on_target == true )
    {
        m_clicked_focus = true;
    }
}

void CRadioButton::set_enabled( bool val )
{
    m_enabled = val;
}
