#include "CListBox.h"


CListBox::CListBox( CRamki* obiekt_ramek, int posx, int posy, int width, int height, int fontSize)
{
    m_ramki = obiekt_ramek;
    m_rect.x = posx;
    m_rect.y = posy;
    m_rect.w = width;
    m_rect.h = height;
    
    m_mouse_on_scroll = false;
    m_scroll_up_mouse = false;
    m_scroll_down_mouse = false;
    m_scroll_up_pressed = false;
    m_scroll_down_pressed = false;
    m_scroll_updown_moved = false;
    m_scroll_focus = false;
    m_duzo_obiektow = false;
    m_mouse_on_plansza = false;
    
    //m_max_objects = 30;
    m_znacznik = 0;
    
    m_enabled = true;
    
    m_font = TTF_OpenFont( "font/tahoma.ttf", fontSize );
    if( m_font == NULL ) { std::cerr << "CListBox Error\n"; this->~CListBox(); }
    m_font_color.r = 0x00;
    m_font_color.g = 0x00;
    m_font_color.b = 0x00;
    m_click_font_color.r = 0xFF;
    m_click_font_color.g = 0xFF;
    m_click_font_color.b = 0xFF;
    m_click_bg_color.r = 51;
    m_click_bg_color.g = 153;
    m_click_bg_color.b = 255;
    
    m_rama_rect.x = 0;
    m_rama_rect.y = 0;
    m_rama_rect.w = width;
    m_rama_rect.h = height;
    
    m_scroll_rect.x = m_rama_rect.w - m_ramki->m_border2[0]->w - m_ramki->m_border_scroll[0]->w;
    m_scroll_rect.y = m_ramki->m_border2[0]->h;
    m_scroll_rect.w = m_ramki->m_border_scroll[0]->w;
    m_scroll_rect.h = m_rama_rect.h - m_ramki->m_border2[0]->h - m_ramki->m_border2[7]->h;
    
    m_rama = NULL;
    m_plansza = NULL;
    m_scroll_bg = NULL;
    
    m_rama = SDL_CreateRGBSurface( SDL_SWSURFACE, m_rect.w, m_rect.h, 32,0,0,0,0 );
    Uint32 colorkey = SDL_MapRGB( m_rama->format, 0, 0xFF, 0xFF ); 
    SDL_SetColorKey( m_rama, SDL_SRCCOLORKEY, colorkey );
    SDL_FillRect( m_rama, &m_rama->clip_rect, SDL_MapRGB( m_rama->format, 0xFF, 0xFF, 0xFF ) );
    
    m_plansza = SDL_CreateRGBSurface( SDL_SWSURFACE, m_rect.w-4, m_rect.h-4, 32,0,0,0,0 );
    colorkey = SDL_MapRGB( m_plansza->format, 0, 0xFF, 0xFF ); 
    SDL_SetColorKey( m_plansza, SDL_SRCCOLORKEY, colorkey );
    SDL_FillRect( m_plansza, &m_plansza->clip_rect, SDL_MapRGB( m_plansza->format, 0xFF, 0xFF, 0xFF ) );
    
    m_scroll_bg = SDL_CreateRGBSurface( SDL_SWSURFACE, m_scroll_rect.w, m_scroll_rect.h, 32,0,0,0,0 );
    colorkey = SDL_MapRGB( m_scroll_bg->format, 0, 0xFF, 0xFF ); 
    SDL_SetColorKey( m_scroll_bg, SDL_SRCCOLORKEY, colorkey );
    SDL_FillRect( m_scroll_bg, &m_scroll_bg->clip_rect, SDL_MapRGB( m_scroll_bg->format, 0xFF, 0xFF, 0xFF ) );
    
    SDL_Surface *temp = NULL;
    temp = TTF_RenderText_Blended( m_font, "Lol", m_font_color );
    m_height_elemntu = temp->h;
    SDL_FreeSurface(temp);
    
    m_obszar_plansza.x = 0;
    m_obszar_plansza.y = 0;
    m_obszar_plansza.w = width - m_ramki->m_border2[2]->w;
    m_obszar_plansza.h = height - m_ramki->m_border2[5]->h - m_ramki->m_border2[1]->h;
    
    
    apply_surface( 0, 0, m_ramki->m_border2[0],m_rama );
    apply_surface( m_rect.w-m_ramki->m_border2[2]->w, 0, m_ramki->m_border2[2],m_rama );
    apply_surface( 0, m_rect.h-m_ramki->m_border2[5]->h, m_ramki->m_border2[5],m_rama );
    apply_surface( m_rect.w-m_ramki->m_border2[7]->w, m_rect.h-m_ramki->m_border2[7]->h, m_ramki->m_border2[7],m_rama );
    for( int i = 0; i < m_rect.w - m_ramki->m_border2[0]->w - m_ramki->m_border2[2]->w ; i++ )
    {
         apply_surface( i + m_ramki->m_border2[0]->w, 0, m_ramki->m_border2[1],m_rama );
         apply_surface( i + m_ramki->m_border2[0]->w, m_rect.h-m_ramki->m_border2[6]->h, m_ramki->m_border2[6],m_rama );
    }
    for( int i = 0; i < m_rect.h - m_ramki->m_border2[0]->h - m_ramki->m_border2[5]->h ; i++ )
    {
         apply_surface( 0, i + m_ramki->m_border2[0]->h, m_ramki->m_border2[3],m_rama );
         apply_surface( m_rect.w -m_ramki->m_border2[4]->w , i + m_ramki->m_border2[0]->h, m_ramki->m_border2[4],m_rama );
    }
    
    for( int i = 0; i < m_scroll_rect.h; i++ )
    {
         apply_surface( 0, 0+i, m_ramki->m_border_scroll[17], m_scroll_bg );
    }
}


CListBox::~CListBox()
{
    SDL_FreeSurface( m_rama );
    SDL_FreeSurface( m_plansza );
    SDL_FreeSurface( m_scroll_bg );
    TTF_CloseFont( m_font );
}

void CListBox::set_enabled( bool val )
{
    m_enabled = val;
    m_mouse_on_plansza = false;
    m_znacznik = 0;
    if( val == true )
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
    this->refresh_items();
}


void CListBox::show()
{
    if( m_enabled == true )
    {
        
        apply_surface( m_rect.x, m_rect.y, m_rama, m_ramki->m_screen );
        apply_surface( m_rect.x+2, m_rect.y+2, m_plansza, m_ramki->m_screen, &m_obszar_plansza );
        
        //ScrollBar
        if( m_duzo_obiektow == true )
        {
            
            apply_surface( m_rect.x + m_scroll_rect.x, m_rect.y + m_scroll_rect.y, m_scroll_bg, m_ramki->m_screen );
            
            apply_surface( m_rect.x + m_scroll_rect.x, m_rect.y + m_scroll_rect.y, m_ramki->m_border_scroll[0], m_ramki->m_screen );
            apply_surface( m_rect.x + m_scroll_rect.x, m_rect.y + m_ramki->m_border2[2]->h + m_scroll_rect.h - m_ramki->m_border_scroll[4]->h, m_ramki->m_border_scroll[4], m_ramki->m_screen );
            
            if( m_mouse_on_scroll == true )
            {
                //Mouse On
                apply_surface( m_rect.x + m_scroll_rect.x, m_rect.y + m_scroll_rect.y, m_ramki->m_border_scroll[1], m_ramki->m_screen );
                apply_surface( m_rect.x + m_scroll_rect.x, m_rect.y + m_ramki->m_border2[2]->h + m_scroll_rect.h - m_ramki->m_border_scroll[5]->h, m_ramki->m_border_scroll[5], m_ramki->m_screen );
                
                
                if( m_scroll_up_mouse == true )
                {
                    apply_surface( m_rect.x + m_scroll_rect.x, m_rect.y + m_scroll_rect.y, m_ramki->m_border_scroll[2], m_ramki->m_screen );
                }
                if( m_scroll_down_mouse == true )
                {
                    apply_surface( m_rect.x + m_scroll_rect.x, m_rect.y + m_ramki->m_border2[2]->h + m_scroll_rect.h - m_ramki->m_border_scroll[4]->h, m_ramki->m_border_scroll[6], m_ramki->m_screen );
                }
                
                //Pressed
                if( m_scroll_up_pressed == true )
                {
                    apply_surface( m_rect.x + m_scroll_rect.x, m_rect.y + m_scroll_rect.y, m_ramki->m_border_scroll[3], m_ramki->m_screen );
                }
                /*if( m_scroll_updown_moved == true )
                {
                    
                }*/
                if( m_scroll_down_pressed == true )
                {
                    apply_surface( m_rect.x + m_scroll_rect.x, m_rect.y + m_ramki->m_border2[2]->h + m_scroll_rect.h - m_ramki->m_border_scroll[4]->h, m_ramki->m_border_scroll[7], m_ramki->m_screen );
                }
                
            }
            
        }
    }
    else
    {
        apply_surface( m_rect.x, m_rect.y, m_rama, m_ramki->m_screen );
        apply_surface( m_rect.x+2, m_rect.y+2, m_plansza, m_ramki->m_screen, &m_obszar_plansza );
        if( m_duzo_obiektow == true )
        {
            apply_surface( m_rect.x + m_scroll_rect.x, m_rect.y + m_scroll_rect.y, m_scroll_bg, m_ramki->m_screen );
            
            apply_surface( m_rect.x + m_scroll_rect.x, m_rect.y + m_scroll_rect.y, m_ramki->m_border_scroll[0], m_ramki->m_screen );
            apply_surface( m_rect.x + m_scroll_rect.x, m_rect.y + m_ramki->m_border2[2]->h + m_scroll_rect.h - m_ramki->m_border_scroll[4]->h, m_ramki->m_border_scroll[4], m_ramki->m_screen );
            
        }
    }
}

void CListBox::import_lista( std::list<std::string> lista, bool append )
{
    if( append == false ) { this->usun_all(); m_dane = lista; }
    else
    {
        for( std::list<std::string>::iterator it = lista.begin(); it != lista.end(); it++)
        {
             m_dane.push_back( *it );
        }
    }
    
    if( m_dane.size() * m_height_elemntu > m_rect.h - m_ramki->m_border2[1]->h - m_ramki->m_border2[6]->h )
    {
        m_duzo_obiektow = true;
        m_obszar_plansza.w = m_rama_rect.w - m_ramki->m_border2[0]->w - m_ramki->m_border2[2]->w - m_ramki->m_border_scroll[0]->w - 1;
    }
    this->refresh_items();
}

void CListBox::dodaj( std::string napis )
{
    m_dane.push_back( napis );
    if( m_dane.size() * m_height_elemntu > m_rect.h - m_ramki->m_border2[1]->h - m_ramki->m_border2[6]->h )
    {
        m_duzo_obiektow = true;
        m_obszar_plansza.w = m_rama_rect.w - m_ramki->m_border2[0]->w - m_ramki->m_border2[2]->w - m_ramki->m_border_scroll[0]->w - 1;
    }
    this->refresh_items();
}


void CListBox::usun( int index )
{
    if( index > 0 )
    {
        int i = 1; 
        for( std::list<std::string>::iterator iter = m_dane.begin(); iter != m_dane.end(); ++iter )
        {
             if( i == index )
             {
                 iter = m_dane.erase(iter);
                 m_znacznik--;
             }
             i++;
        }
        if( m_dane.size() * m_height_elemntu <= m_rect.h - m_ramki->m_border2[1]->h - m_ramki->m_border2[6]->h )
        {
            m_duzo_obiektow = false;
            m_obszar_plansza.w = m_rama_rect.w - m_ramki->m_border2[0]->w - m_ramki->m_border2[2]->w;
        }
        this->refresh_items();
    }
}

void CListBox::usun_all()
{
    if( m_dane.size() > 0 )
    {
        m_dane.clear();
        m_znacznik = 0;
        m_duzo_obiektow = false;
        m_obszar_plansza.w = m_rama_rect.w - m_ramki->m_border2[0]->w - m_ramki->m_border2[2]->w;
        this->refresh_items();
    }
}

void CListBox::refresh_items()
{
    SDL_FillRect( m_plansza, &m_plansza->clip_rect, SDL_MapRGB(m_plansza->format, 0xFF, 0xFF, 0xFF) );
    if( m_dane.empty() == false )
    {
        SDL_FreeSurface( m_plansza );
        m_plansza = SDL_CreateRGBSurface( SDL_SWSURFACE, m_rect.w-4, m_height_elemntu*m_dane.size(), 32,0,0,0,0 );
        Uint32 colorkey = SDL_MapRGB( m_plansza->format, 0, 0xFF, 0xFF ); 
        SDL_SetColorKey( m_plansza, SDL_SRCCOLORKEY, colorkey );
        SDL_FillRect( m_plansza, &m_plansza->clip_rect, SDL_MapRGB( m_plansza->format, 0xFF, 0xFF, 0xFF ) );
        
        SDL_Rect zaz;
        zaz.x = m_obszar_plansza.x;
        zaz.y = m_obszar_plansza.y;
        zaz.w = m_obszar_plansza.w;
        zaz.h = m_height_elemntu;
        int i = 1;
        SDL_Surface *temp;
        temp = NULL;
        for( std::list<std::string>::iterator it = m_dane.begin(); it != m_dane.end(); it++ )
        {
             if( i == m_znacznik )
             {
                 temp = TTF_RenderText_Blended( m_font, (*it).c_str(), m_click_font_color);
                 SDL_FillRect( m_plansza, &zaz, SDL_MapRGB(m_plansza->format, 51, 153, 255) );
                 apply_surface( 2, 0+m_height_elemntu*(i-1), temp, m_plansza );
                 SDL_FreeSurface(temp);
             }
             else
             {
                 temp = TTF_RenderText_Blended( m_font, (*it).c_str(), m_font_color );
                 apply_surface( 2, 0+m_height_elemntu*(i-1), temp, m_plansza );
                 SDL_FreeSurface(temp);
             }
             zaz.y = 0+m_height_elemntu*i;
             i++;
        }
    }
}

void CListBox::OnEvent(SDL_Event* Event)
{
    CEvent::OnEvent(Event);
}

int CListBox::get_size()
{
    return m_dane.size();
}

void CListBox::OnMouseMove(int mX, int mY, int relX, int relY, bool Left,bool Right,bool Middle)
{
    if( m_enabled == true )
    {
        // Zaznacznik              
        if(  (mX > m_rect.x + m_ramki->m_border2[3]->w) && (mX < m_rect.x + m_ramki->m_border2[3]->w + m_obszar_plansza.w) && (mY > m_rect.y + m_ramki->m_border2[1]->h) && (mY < m_rect.y + m_ramki->m_border2[1]->h + m_obszar_plansza.h)  )
        {
            m_mouse_on_plansza = true;
        }
        else
        {
            m_mouse_on_plansza = false;
        }
        
    
        // Scroll
        if( m_duzo_obiektow == true )
        {
            if(  (mX > m_rect.x+m_scroll_rect.x) && (mX < m_rect.x+m_scroll_rect.x + m_scroll_rect.w) && (mY > m_rect.y+m_scroll_rect.y) && (mY < m_rect.y+m_scroll_rect.y + m_scroll_rect.h)  )
            {
                m_mouse_on_scroll = true;
                 
                if(  (mX > m_rect.x + m_scroll_rect.x) && (mX < m_rect.x + m_scroll_rect.x + m_scroll_rect.w) && (mY > m_rect.y+m_scroll_rect.y) && (mY < m_rect.y+m_scroll_rect.y + m_ramki->m_border_scroll[0]->h)  )
                {
                     m_scroll_up_mouse = true;
                }
                else
                {
                    m_scroll_up_mouse = false;
                }
                
                if(  (mX > m_rect.x+m_scroll_rect.x) && (mX < m_rect.x+m_scroll_rect.x + m_scroll_rect.w) && (mY > m_rect.y+m_scroll_rect.h - m_ramki->m_border_scroll[0]->h) && (mY < m_rect.y+m_scroll_rect.y + m_scroll_rect.h)  )
                {
                     m_scroll_down_mouse = true;
                }
                else
                {
                    m_scroll_down_mouse = false;
                }
            }
            else
            {
                 m_mouse_on_scroll = false;
                 m_scroll_up_mouse = false;
                 m_scroll_down_mouse = false;
            }
        }
    }
}

void CListBox::OnLButtonDown(int mX, int mY)
{
     // Zaznacznik
     if( m_mouse_on_plansza == true )
     {         
         for( int i = 0; i < m_obszar_plansza.h / m_height_elemntu; i++ )
         {
              if(  (mX > m_rect.x + m_ramki->m_border2[3]->w) && (mX < m_rect.x + m_ramki->m_border2[3]->w + m_obszar_plansza.w) && (mY > m_rect.y + m_ramki->m_border2[1]->h + i*m_height_elemntu) && (mY < m_rect.y + m_ramki->m_border2[1]->h + (i+1)*m_height_elemntu)  )
              {
                   m_znacznik = 1+ i + (m_obszar_plansza.y) / m_height_elemntu;
                   if( m_znacznik > m_dane.size() ) { m_znacznik = m_dane.size(); }
                   this->refresh_items();
              }
         }
     }
     
     // Scroll
     if( m_scroll_up_mouse == true )
     {
         m_scroll_up_pressed = true;
         
         if( m_scroll_focus == false )
         {
             m_obszar_plansza.y -= m_height_elemntu;
             if( m_obszar_plansza.y <= m_ramki->m_border2[0]->h ) { m_obszar_plansza.y = 0; }
             m_scroll_focus = true;
         }
     }
     if( m_scroll_down_mouse == true )
     {
         m_scroll_down_pressed = true;
         
         if( m_scroll_focus == false )
         {
             m_obszar_plansza.y += m_height_elemntu;
             if( m_obszar_plansza.y >= m_dane.size() * m_height_elemntu  ) { m_obszar_plansza.y -= m_height_elemntu; }
             m_scroll_focus = true;
         }
     }
}

void CListBox::OnLButtonUp(int mX, int mY)
{
    m_scroll_focus = false;
    m_scroll_up_pressed = false;
    m_scroll_down_pressed = false;
}

void CListBox::set_znacznik( int val )
{
    m_znacznik = val;
    this->refresh_items();
}

int CListBox::get_znacznik()
{
    return m_znacznik;
}

