#include "CEditBox.h"


int CEditBox::m_akapit_gora = 1;
int CEditBox::m_akapit_lewo = 2;
int CEditBox::m_akapit_prawo = 4;
int CEditBox::m_akapit_dol = 1;

CEditBox::CEditBox( CRamki* obiekt_ramek, int posx, int posy, int width, std::string napis, int max_length, int fontSize )
{
    m_ramki = obiekt_ramek;
    m_rect.x = posx;
    m_rect.y = posy;
    m_rect.w = width;
    m_napis = napis;
    m_on_target = false;
    m_clickedWrite_focus = false;
    m_enabled = true;
    m_textSquare = NULL;
    m_znacznik = NULL;
    m_writeFocus = NULL;
    m_mouseOn = NULL;
    m_unactive = NULL;
    m_disabled = NULL;
    m_font = TTF_OpenFont( "font/tahoma.ttf", fontSize );
    if( m_font == NULL ) { std::cerr << "CEditBox Error\n"; this->~CEditBox(); }
    m_font_color.r = 0x00;
    m_font_color.g = 0x00;
    m_font_color.b = 0x00;
    m_textSquare = TTF_RenderText_Blended( m_font, m_napis.c_str(), m_font_color ); 
    m_rect.h = m_ramki->m_border_std[0]->h + m_akapit_gora + m_textSquare->h + m_akapit_dol + m_ramki->m_border_std[7]->h;
    m_background.x = posx +1;
    m_background.y = posy +1;
    m_background.w = m_rect.w-2;
    m_background.h = m_rect.h-2;
    m_max_length = max_length;
    if( m_max_length != 0 ) { m_use_length = true; } else { m_use_length = false; }
    m_full_line = false;
    m_znacznik = TTF_RenderText_Blended( m_font, "|", m_font_color ); 
    SDL_EnableUNICODE( SDL_ENABLE );
    this->refresh_surfaces();
}


CEditBox::~CEditBox()
{
    SDL_FreeSurface( m_textSquare );
    SDL_FreeSurface( m_znacznik );
    
    SDL_FreeSurface( m_writeFocus );
    SDL_FreeSurface( m_mouseOn );
    SDL_FreeSurface( m_unactive );
    SDL_FreeSurface( m_disabled );

    TTF_CloseFont( m_font );
    SDL_EnableUNICODE( SDL_DISABLE ); 
}

void CEditBox::napisz( std::string napis )
{
    m_napis = napis;
    this->refresh();
}

void CEditBox::set_enabled( bool val )
{
    m_enabled = val;
    this->refresh();
}

void CEditBox::refresh_surfaces()
{
    this->refresh();
    

    SDL_FreeSurface( m_textSquare );
    SDL_FreeSurface( m_writeFocus );
    SDL_FreeSurface( m_mouseOn );
    SDL_FreeSurface( m_unactive );
    SDL_FreeSurface( m_disabled );
    
    
    m_textSquare = TTF_RenderText_Blended( m_font, m_napis.c_str(), m_font_color ); 
    
    m_disabled = SDL_CreateRGBSurface( SDL_SWSURFACE, m_rect.w, m_rect.h, 32,0,0,0,0 );
    Uint32 colorkey = SDL_MapRGB( m_disabled->format, 0, 0xFF, 0xFF );
    SDL_SetColorKey( m_disabled, SDL_SRCCOLORKEY, colorkey );
    SDL_FillRect( m_disabled, &m_disabled->clip_rect, SDL_MapRGB( m_disabled->format, 0xFF, 0xFF, 0xFF ) );
    apply_surface( 0, 0, m_ramki->m_border_std[24],m_disabled );
    apply_surface( 0 + m_rect.w - m_ramki->m_border_std[26]->w, 0, m_ramki->m_border_std[26],m_disabled );
    apply_surface( 0, 0 + m_rect.h - m_ramki->m_border_std[29]->h, m_ramki->m_border_std[29],m_disabled );
    apply_surface( 0 + m_rect.w - m_ramki->m_border_std[31]->w, 0 + m_rect.h - m_ramki->m_border_std[31]->h, m_ramki->m_border_std[31],m_disabled );
    for( int i = 0; i < m_rect.w - m_ramki->m_border_std[24]->w - m_ramki->m_border_std[26]->w; i++ )
    {
        apply_surface( 0 + m_ramki->m_border_std[23]->w + i, 0, m_ramki->m_border_std[25],m_disabled );
        apply_surface( 0 + m_ramki->m_border_std[29]->w + i, 0 + m_rect.h - m_ramki->m_border_std[30]->h, m_ramki->m_border_std[30],m_disabled );
    }
    for( int i = 0; i < m_rect.h - m_ramki->m_border_std[24]->h - m_ramki->m_border_std[29]->h; i++ )
    {
        apply_surface( 0, 0 + m_ramki->m_border_std[24]->h + i, m_ramki->m_border_std[27],m_disabled );
        apply_surface( 0 + m_rect.w - m_ramki->m_border_std[28]->w, 0 + m_ramki->m_border_std[24]->h + i, m_ramki->m_border_std[28],m_disabled );
    }
    
    m_font_color.r = 0x00;
    m_font_color.g = 0x00;
    m_font_color.b = 0x00;
    
    m_writeFocus = SDL_CreateRGBSurface( SDL_SWSURFACE, m_rect.w, m_rect.h, 32,0,0,0,0 ); 
    SDL_SetColorKey( m_writeFocus, SDL_SRCCOLORKEY, colorkey );
    SDL_FillRect( m_writeFocus, &m_writeFocus->clip_rect, SDL_MapRGB( m_writeFocus->format, 0xFF, 0xFF, 0xFF ) );
    apply_surface( 0, 0, m_ramki->m_border_std[16],m_writeFocus );
    apply_surface( 0 + m_rect.w - m_ramki->m_border_std[18]->w, 0, m_ramki->m_border_std[18],m_writeFocus );
    apply_surface( 0, 0 + m_rect.h - m_ramki->m_border_std[21]->h, m_ramki->m_border_std[21],m_writeFocus );
    apply_surface( 0 + m_rect.w - m_ramki->m_border_std[23]->w, 0 + m_rect.h - m_ramki->m_border_std[23]->h, m_ramki->m_border_std[23],m_writeFocus );
    for( int i = 0; i < m_rect.w - m_ramki->m_border_std[16]->w - m_ramki->m_border_std[18]->w; i++ )
    {
        apply_surface( 0 + m_ramki->m_border_std[16]->w + i, 0, m_ramki->m_border_std[17],m_writeFocus );
        apply_surface( 0 + m_ramki->m_border_std[21]->w + i, 0 + m_rect.h - m_ramki->m_border_std[22]->h, m_ramki->m_border_std[22],m_writeFocus );
    }
    for( int i = 0; i < m_rect.h - m_ramki->m_border_std[16]->h - m_ramki->m_border_std[21]->h; i++ )
    {
        apply_surface( 0, 0 + m_ramki->m_border_std[16]->h + i, m_ramki->m_border_std[19],m_writeFocus );
        apply_surface( 0 + m_rect.w - m_ramki->m_border_std[17]->w, 0 + m_ramki->m_border_std[16]->h + i, m_ramki->m_border_std[20],m_writeFocus );
    }
    
    m_mouseOn = SDL_CreateRGBSurface( SDL_SWSURFACE, m_rect.w, m_rect.h, 32,0,0,0,0 );
    SDL_SetColorKey( m_mouseOn, SDL_SRCCOLORKEY, colorkey );
    SDL_FillRect( m_mouseOn, &m_mouseOn->clip_rect, SDL_MapRGB( m_mouseOn->format, 0xFF, 0xFF, 0xFF ) );
    apply_surface( 0, 0, m_ramki->m_border_std[8],m_mouseOn );
    apply_surface( 0 + m_rect.w - m_ramki->m_border_std[10]->w, 0, m_ramki->m_border_std[10],m_mouseOn );
    apply_surface( 0, 0 + m_rect.h - m_ramki->m_border_std[13]->h, m_ramki->m_border_std[13],m_mouseOn );
    apply_surface( 0 + m_rect.w - m_ramki->m_border_std[15]->w, 0 + m_rect.h - m_ramki->m_border_std[15]->h, m_ramki->m_border_std[15],m_mouseOn );
    for( int i = 0; i < m_rect.w - m_ramki->m_border_std[8]->w - m_ramki->m_border_std[10]->w; i++ )
    {
        apply_surface( 0 + m_ramki->m_border_std[8]->w + i, 0, m_ramki->m_border_std[9],m_mouseOn );
        apply_surface( 0 + m_ramki->m_border_std[13]->w + i, 0 + m_rect.h - m_ramki->m_border_std[14]->h, m_ramki->m_border_std[14],m_mouseOn );
    }
    for( int i = 0; i < m_rect.h - m_ramki->m_border_std[8]->h - m_ramki->m_border_std[13]->h; i++ )
    {
        apply_surface( 0, 0 + m_ramki->m_border_std[8]->h + i, m_ramki->m_border_std[11],m_mouseOn );
        apply_surface( 0 + m_rect.w - m_ramki->m_border_std[9]->w, 0 + m_ramki->m_border_std[8]->h + i, m_ramki->m_border_std[12],m_mouseOn );
    }
    
    m_unactive = SDL_CreateRGBSurface( SDL_SWSURFACE, m_rect.w, m_rect.h, 32,0,0,0,0 );
    SDL_SetColorKey( m_unactive, SDL_SRCCOLORKEY, colorkey );
    SDL_FillRect( m_unactive, &m_unactive->clip_rect, SDL_MapRGB( m_unactive->format, 0xFF, 0xFF, 0xFF ) );
    apply_surface( 0, 0, m_ramki->m_border_std[0],m_unactive );
    apply_surface( 0 + m_rect.w - m_ramki->m_border_std[2]->w, 0, m_ramki->m_border_std[2],m_unactive );
    apply_surface( 0, 0 + m_rect.h - m_ramki->m_border_std[5]->h, m_ramki->m_border_std[5],m_unactive );
    apply_surface( 0 + m_rect.w - m_ramki->m_border_std[7]->w, 0 + m_rect.h - m_ramki->m_border_std[7]->h, m_ramki->m_border_std[7],m_unactive );
    for( int i = 0; i < m_rect.w - m_ramki->m_border_std[0]->w - m_ramki->m_border_std[2]->w; i++ )
    {
        apply_surface( 0 + m_ramki->m_border_std[0]->w + i, 0, m_ramki->m_border_std[1],m_unactive );
        apply_surface( 0 + m_ramki->m_border_std[5]->w + i, 0 + m_rect.h - m_ramki->m_border_std[6]->h, m_ramki->m_border_std[6],m_unactive );
    }
    for( int i = 0; i < m_rect.h - m_ramki->m_border_std[0]->h - m_ramki->m_border_std[5]->h; i++ )
    {
        apply_surface( 0, 0 + m_ramki->m_border_std[0]->h + i, m_ramki->m_border_std[3],m_unactive );
        apply_surface( 0 + m_rect.w - m_ramki->m_border_std[1]->w, 0 + m_ramki->m_border_std[0]->h + i, m_ramki->m_border_std[4],m_unactive );
    }
}

void CEditBox::refresh()
{
    if( m_enabled == true)
    {
        m_font_color.r = 0x00;
        m_font_color.g = 0x00;
        m_font_color.b = 0x00;
    }
    else
    {
        m_font_color.r = 0x83;
        m_font_color.g = 0x83;
        m_font_color.b = 0x83;
    }
    SDL_FreeSurface( m_textSquare );
    if( m_napis == "" )
    {
        m_textSquare = TTF_RenderText_Blended( m_font, " ", m_font_color );
    }
    else
    {
        m_textSquare = TTF_RenderText_Blended( m_font, m_napis.c_str(), m_font_color );
    }
}

std::string CEditBox::get_napis()
{
    return m_napis;
}

void CEditBox::show()
{
     SDL_FillRect( m_ramki->m_screen, &m_background, SDL_MapRGB((m_ramki->m_screen)->format, 0xFF, 0xFF, 0xFF) );
     if( m_enabled == true )
     {
         if( m_clickedWrite_focus == true )
         {
             apply_surface( m_rect.x, m_rect.y, m_writeFocus, m_ramki->m_screen );
         }
         else
         {
             if( m_on_target == true )
             {
                 apply_surface( m_rect.x, m_rect.y, m_mouseOn, m_ramki->m_screen );
             }
             else
             {
                 apply_surface( m_rect.x, m_rect.y, m_unactive, m_ramki->m_screen );
             }
         }
         if( m_clickedWrite_focus == true )
         {
             if( m_tmr_znacznik.get_ticks() < 700 )
             {
                 if( m_napis == "" )
                 {
                     apply_surface( m_rect.x +(m_ramki->m_border_std[0]->w) + m_akapit_lewo -2, m_rect.y + (m_ramki->m_border_std[0]->h)-1, m_znacznik, m_ramki->m_screen );
                 }
                 else
                 {
                     apply_surface( m_rect.x +(m_ramki->m_border_std[0]->w) + m_akapit_lewo + m_textSquare->w -2, m_rect.y + (m_ramki->m_border_std[0]->h)-1, m_znacznik, m_ramki->m_screen );
                 }
             }
             if( m_tmr_znacznik.get_ticks() > 1250 )
             {
                 m_tmr_znacznik.start();
             }
         }
     }
     else
     {
         apply_surface( m_rect.x, m_rect.y, m_disabled, m_ramki->m_screen );
     }
     apply_surface( m_rect.x +(m_ramki->m_border_std[0]->w) + m_akapit_lewo, m_rect.y + (m_ramki->m_border_std[0]->h) + m_akapit_gora, m_textSquare, m_ramki->m_screen );
}


void CEditBox::OnEvent(SDL_Event* Event)
{
    CEvent::OnEvent(Event);
}

void CEditBox::OnMouseMove(int mX, int mY, int relX, int relY, bool Left,bool Right,bool Middle)
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

void CEditBox::OnLButtonDown(int mX, int mY)
{
    if( m_on_target == true )
    {
        m_clickedWrite_focus = true;
        m_tmr_znacznik.start();
    }
    if( m_on_target == false )
    {
        m_clickedWrite_focus = false;
        m_tmr_znacznik.stop();
    }
}

void CEditBox::OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode)
{
    if( m_clickedWrite_focus == true )
    {
        if( m_full_line == false )
        {
            if( m_use_length == true )
            {
                if( m_napis.length() < m_max_length )
                {
                    //If the key is a space
                    if( unicode == (Uint16)' ' )
                    {
                        m_napis += (char)unicode;
                    }
                    //If the key is a number
                    else if( ( unicode >= (Uint16)'0' ) && ( unicode <= (Uint16)'9' ) )
                    {
                        m_napis += (char)unicode;
                    }
                    //If the key is a uppercase letter
                    else if( ( unicode >= (Uint16)'A' ) && ( unicode <= (Uint16)'Z' ) )
                    {
                        m_napis += (char)unicode;
                    }
                    //If the key is a lowercase letter
                    else if( ( unicode >= (Uint16)'a' ) && ( unicode <= (Uint16)'z' ) )
                    {
                        m_napis += (char)unicode;
                    }
                }
                if( m_napis.length() == m_max_length )
                {
                    m_full_line = true;
                }
            }
            else
            {
                //If the key is a space
                if( unicode == (Uint16)' ' )
                {
                    m_napis += (char)unicode;
                }
                //If the key is a number
                else if( ( unicode >= (Uint16)'0' ) && ( unicode <= (Uint16)'9' ) )
                {
                    m_napis += (char)unicode;
                }
                //If the key is a uppercase letter
                else if( ( unicode >= (Uint16)'A' ) && ( unicode <= (Uint16)'Z' ) )
                {
                    m_napis += (char)unicode;
                }
                //If the key is a lowercase letter
                else if( ( unicode >= (Uint16)'a' ) && ( unicode <= (Uint16)'z' ) )
                {
                    m_napis += (char)unicode;
                }
            }
            
            this->refresh();
            if( m_textSquare->w > m_rect.w - (m_ramki->m_border_std[0]->w + m_akapit_lewo + m_akapit_prawo + m_ramki->m_border_std[2]->w)  )
            {
                //Remove a character from the end
                m_napis.erase( m_napis.length() - 1 );
                this->refresh();
            }

            //If backspace was pressed and the string isn't blank
            if( ( sym == SDLK_BACKSPACE ) && ( m_napis.length() != 0 ) )
            {
                //Remove a character from the end
                m_napis.erase( m_napis.length() - 1 );
                this->refresh();
            }
            if( ( sym == SDLK_RETURN ) && ( m_napis.length() != 0 ) )
            {
                m_clickedWrite_focus = false;
                m_tmr_znacznik.stop();
            }
        }
    }
}
