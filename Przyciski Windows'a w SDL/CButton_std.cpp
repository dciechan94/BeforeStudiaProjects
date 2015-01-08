#include "CButton_std.h"


CButton_std::CButton_std( CRamki* obiekt_ramek, int posx, int posy, std::string napis, void (*event_fn_LButtonUp)(), int width = 1 )
{
    m_ramki = obiekt_ramek;
    m_rect.x = posx;
    m_rect.y = posy;
    m_napis = napis;
    m_event_fn_LButtonUp = event_fn_LButtonUp;
    m_on_target = false;
    m_clicked_focus = false;
    m_enabled = true;
    m_font = TTF_OpenFont( "font/tahoma.ttf", 12 );
    if( m_font == NULL ) { std::cerr << "CButton_sutd error\n"; this->~CButton_std(); }
    m_rect.w = width;
    m_rect.h = m_ramki->m_button_std[0]->h;
    
    m_btn_mouse = NULL;
    m_btn_click = NULL;
    m_btn_unactive = NULL;
    m_btn_disabled = NULL;
    
    this->refresh_surfaces();
}


CButton_std::~CButton_std()
{
    SDL_FreeSurface( m_textSquare );
    SDL_FreeSurface( m_btn_mouse );
    SDL_FreeSurface( m_btn_click );
    SDL_FreeSurface( m_btn_unactive );
    SDL_FreeSurface( m_btn_disabled );
    TTF_CloseFont( m_font );
}


void CButton_std::OnEvent(SDL_Event* Event)
{
    CEvent::OnEvent(Event);
}

void CButton_std::OnMouseMove(int mX, int mY, int relX, int relY, bool Left,bool Right,bool Middle)
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

void CButton_std::OnLButtonUp(int mX, int mY)
{
    if(  (m_on_target == true) && (m_clicked_focus == true)  )
    {
         m_event_fn_LButtonUp();
    }
    m_clicked_focus = false;
}

void CButton_std::OnLButtonDown(int mX, int mY)
{
    if( m_on_target == true )
    {
        m_clicked_focus = true;
    }
}

void CButton_std::set_caption( std::string napis )
{
    m_napis = napis;
    this->refresh_surfaces();
}

void CButton_std::set_enabled( bool val )
{
    m_enabled = val;
}

void CButton_std::show()
{
    if( m_enabled == true )
    {
        if( m_on_target == true )
        {
            if( m_clicked_focus == true )
            {
                apply_surface( m_rect.x, m_rect.y, m_btn_click, m_ramki->m_screen );
            }
            else
            {
                apply_surface( m_rect.x, m_rect.y, m_btn_mouse, m_ramki->m_screen );
            }
        }
        else
        {
            apply_surface( m_rect.x, m_rect.y, m_btn_unactive, m_ramki->m_screen );
        }
    }
    else
    {
        apply_surface( m_rect.x, m_rect.y, m_btn_disabled, m_ramki->m_screen );
    }
}



void CButton_std::refresh_surfaces()
{
    m_font_color.r = 0x00;
    m_font_color.g = 0x00;
    m_font_color.b = 0x00;
    m_textSquare = TTF_RenderText_Blended( m_font, m_napis.c_str(), m_font_color ); 
    if( m_rect.w < m_ramki->m_button_std[0]->w + m_textSquare->w + m_ramki->m_button_std[2]->w ) { m_rect.w = m_ramki->m_button_std[0]->w + m_textSquare->w + m_ramki->m_button_std[2]->w; }
    
    SDL_FreeSurface( m_btn_mouse );
    SDL_FreeSurface( m_btn_click );
    SDL_FreeSurface( m_btn_unactive );
    SDL_FreeSurface( m_btn_disabled );
    
    m_btn_click = SDL_CreateRGBSurface( SDL_SWSURFACE, m_rect.w, m_rect.h, 32, 0, 0, 0, 0 );
    SDL_FillRect( m_btn_click, &m_btn_click->clip_rect, SDL_MapRGB( m_btn_click->format, 0, 0xFF, 0xFF ) );
    Uint32 colorkey = SDL_MapRGB( m_btn_click->format, 0, 0xFF, 0xFF );
    SDL_SetColorKey( m_btn_click, SDL_SRCCOLORKEY, colorkey );
    apply_surface( 0, 0, m_ramki->m_button_std[6], m_btn_click );
    apply_surface( 0+m_rect.w-m_ramki->m_button_std[8]->w, 0, m_ramki->m_button_std[8], m_btn_click );
    for( int i = 0; i < m_rect.w -(m_ramki->m_button_std[6]->w+m_ramki->m_button_std[8]->w); i++ )
    {
        apply_surface( 0+i+m_ramki->m_button_std[6]->w, 0, m_ramki->m_button_std[7], m_btn_click );
    }
    apply_surface( (0+(m_rect.w-m_textSquare->w)/2), (0+(m_rect.h-m_textSquare->h)/2), m_textSquare, m_btn_click );
    
    m_btn_mouse = SDL_CreateRGBSurface( SDL_SWSURFACE, m_rect.w, m_rect.h, 32, 0, 0, 0, 0 );
    SDL_FillRect( m_btn_mouse, &m_btn_mouse->clip_rect, SDL_MapRGB( m_btn_mouse->format, 0, 0xFF, 0xFF ) );
    SDL_SetColorKey( m_btn_mouse, SDL_SRCCOLORKEY, colorkey );
    apply_surface( 0, 0, m_ramki->m_button_std[3], m_btn_mouse );
    apply_surface( 0+m_rect.w-m_ramki->m_button_std[5]->w, 0, m_ramki->m_button_std[5], m_btn_mouse );
    for( int i = 0; i < m_rect.w -(m_ramki->m_button_std[3]->w+m_ramki->m_button_std[5]->w); i++ )
    {
        apply_surface( 0+i+m_ramki->m_button_std[3]->w, 0, m_ramki->m_button_std[4], m_btn_mouse );
    }
    apply_surface( (0+(m_rect.w-m_textSquare->w)/2), (0+(m_rect.h-m_textSquare->h)/2), m_textSquare, m_btn_mouse );
    
    m_btn_unactive = SDL_CreateRGBSurface( SDL_SWSURFACE, m_rect.w, m_rect.h, 32, 0, 0, 0, 0 );
    SDL_FillRect( m_btn_unactive, &m_btn_unactive->clip_rect, SDL_MapRGB( m_btn_unactive->format, 0, 0xFF, 0xFF ) );
    SDL_SetColorKey( m_btn_unactive, SDL_SRCCOLORKEY, colorkey );
    apply_surface( 0, 0, m_ramki->m_button_std[0], m_btn_unactive );
    apply_surface( 0+m_rect.w-m_ramki->m_button_std[2]->w, 0, m_ramki->m_button_std[2], m_btn_unactive );
    for( int i = 0; i < m_rect.w -(m_ramki->m_button_std[0]->w+m_ramki->m_button_std[2]->w); i++ )
    {
        apply_surface( 0+i+m_ramki->m_button_std[0]->w, 0, m_ramki->m_button_std[1], m_btn_unactive );
    }
    apply_surface( (0+(m_rect.w-m_textSquare->w)/2), (0+(m_rect.h-m_textSquare->h)/2), m_textSquare, m_btn_unactive );
    
    m_font_color.r = 0x83;
    m_font_color.g = 0x83;
    m_font_color.b = 0x83;
    SDL_FreeSurface( m_textSquare );
    m_textSquare = TTF_RenderText_Blended( m_font, m_napis.c_str(), m_font_color ); 
    
    m_btn_disabled = SDL_CreateRGBSurface( SDL_SWSURFACE, m_rect.w, m_rect.h, 32, 0, 0, 0, 0 );
    SDL_FillRect( m_btn_disabled, &m_btn_disabled->clip_rect, SDL_MapRGB( m_btn_disabled->format, 0, 0xFF, 0xFF ) );
    SDL_SetColorKey( m_btn_disabled, SDL_SRCCOLORKEY, colorkey );
    apply_surface( 0, 0, m_ramki->m_button_std[9], m_btn_disabled );
    apply_surface( 0+m_rect.w-m_ramki->m_button_std[11]->w, 0, m_ramki->m_button_std[11], m_btn_disabled );
    for( int i = 0; i < m_rect.w -(m_ramki->m_button_std[9]->w+m_ramki->m_button_std[11]->w); i++ )
    {
        apply_surface( 0+i+m_ramki->m_button_std[9]->w, 0, m_ramki->m_button_std[10], m_btn_disabled );
    }
    apply_surface( (0+(m_rect.w-m_textSquare->w)/2), (0+(m_rect.h-m_textSquare->h)/2), m_textSquare, m_btn_disabled );
}


    
