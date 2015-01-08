#include "CComboBox.h"


CComboBox::CComboBox( CRamki* obiekt_ramek, int posx, int posy, int width, int fontSize)
{
    m_ramki = obiekt_ramek;
    m_rect.x = posx;
    m_rect.y = posy;
    m_rect.w = width;
    m_rect.h = 21;
    
    m_mouse_on_box = false;
    m_mouse_on_arrow = false;
    m_arrow_pressed = false;
    m_enabled = true;
    
    m_open_list = false;
    //m_pusta = true;
    
    m_max_objects = 10;
    m_znacznik = 0;
    m_wybrany = m_znacznik;
    
    m_font = TTF_OpenFont( "font/tahoma.ttf", fontSize );
    if( m_font == NULL ) { std::cerr << "CComboBox Error"; this->~CComboBox(); }
    m_font_color.r = 0x00;
    m_font_color.g = 0x00;
    m_font_color.b = 0x00;
    
    m_mouseOn = SDL_CreateRGBSurface( SDL_SWSURFACE, m_rect.w, m_rect.h, 32,0,0,0,0 );
    Uint32 colorkey = SDL_MapRGB( m_mouseOn->format, 0, 0xFF, 0xFF ); 
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
    apply_surface( m_rect.w-m_ramki->m_combobox[1]->w, 0, m_ramki->m_combobox[1],m_mouseOn );
    
    
    m_clicked = SDL_CreateRGBSurface( SDL_SWSURFACE, m_rect.w, m_rect.h, 32,0,0,0,0 ); 
    SDL_SetColorKey( m_clicked, SDL_SRCCOLORKEY, colorkey );
    SDL_FillRect( m_clicked, &m_clicked->clip_rect, SDL_MapRGB( m_clicked->format, 0xFF, 0xFF, 0xFF ) );
    
    apply_surface( 0, 0, m_ramki->m_border_std[16],m_clicked );
    apply_surface( 0 + m_rect.w - m_ramki->m_border_std[18]->w, 0, m_ramki->m_border_std[18],m_clicked );
    apply_surface( 0, 0 + m_rect.h - m_ramki->m_border_std[21]->h, m_ramki->m_border_std[21],m_clicked );
    apply_surface( 0 + m_rect.w - m_ramki->m_border_std[23]->w, 0 + m_rect.h - m_ramki->m_border_std[23]->h, m_ramki->m_border_std[23],m_clicked );
    for( int i = 0; i < m_rect.w - m_ramki->m_border_std[16]->w - m_ramki->m_border_std[18]->w; i++ )
    {
        apply_surface( 0 + m_ramki->m_border_std[16]->w + i, 0, m_ramki->m_border_std[17],m_clicked );
        apply_surface( 0 + m_ramki->m_border_std[21]->w + i, 0 + m_rect.h - m_ramki->m_border_std[22]->h, m_ramki->m_border_std[22],m_clicked );
    }
    for( int i = 0; i < m_rect.h - m_ramki->m_border_std[16]->h - m_ramki->m_border_std[21]->h; i++ )
    {
        apply_surface( 0, 0 + m_ramki->m_border_std[16]->h + i, m_ramki->m_border_std[19],m_clicked );
        apply_surface( 0 + m_rect.w - m_ramki->m_border_std[17]->w, 0 + m_ramki->m_border_std[16]->h + i, m_ramki->m_border_std[20],m_clicked );
    }
    apply_surface( m_rect.w-m_ramki->m_combobox[2]->w, 0, m_ramki->m_combobox[2],m_clicked );
    
    // Trzeba zrobic !!!!!!!!!!!!!
    
    m_disabled = SDL_CreateRGBSurface( SDL_SWSURFACE, m_rect.w, m_rect.h, 32,0,0,0,0 ); 
    SDL_SetColorKey( m_disabled, SDL_SRCCOLORKEY, colorkey );
    SDL_FillRect( m_disabled, &m_disabled->clip_rect, SDL_MapRGB( m_disabled->format, 0xFF, 0xFF, 0xFF ) );
    apply_surface( 0, 0, m_ramki->m_border_std[24], m_disabled );
    apply_surface( 0 + m_rect.w - m_ramki->m_border_std[26]->w, 0, m_ramki->m_border_std[26], m_disabled );
    apply_surface( 0, 0 + m_rect.h - m_ramki->m_border_std[29]->h, m_ramki->m_border_std[29], m_disabled );
    apply_surface( 0 + m_rect.w - m_ramki->m_border_std[29]->w, 0 + m_rect.h - m_ramki->m_border_std[31]->h, m_ramki->m_border_std[31], m_disabled );
    for( int i = 0; i < m_rect.w - m_ramki->m_border_std[24]->w - m_ramki->m_border_std[26]->w; i++ )
    {
        apply_surface( 0 + m_ramki->m_border_std[24]->w + i, 0, m_ramki->m_border_std[25], m_disabled );
        apply_surface( 0 + m_ramki->m_border_std[24]->w + i, 0 + m_rect.h - m_ramki->m_border_std[30]->h, m_ramki->m_border_std[30], m_disabled );
    }
    for( int i = 0; i < m_rect.h - m_ramki->m_border_std[24]->h - m_ramki->m_border_std[29]->h; i++ )
    {
        apply_surface( 0, 0 + m_ramki->m_border_std[24]->h + i, m_ramki->m_border_std[27],m_disabled );
        apply_surface( 0 + m_rect.w - m_ramki->m_border_std[26]->w, 0 + m_ramki->m_border_std[26]->h + i, m_ramki->m_border_std[28],m_disabled );
    }
    // ---
    
    m_mouseOn_box = SDL_CreateRGBSurface( SDL_SWSURFACE, m_rect.w, m_rect.h, 32,0,0,0,0 );
    SDL_SetColorKey( m_mouseOn_box, SDL_SRCCOLORKEY, colorkey );
    SDL_FillRect( m_mouseOn_box, &m_mouseOn_box->clip_rect, SDL_MapRGB( m_mouseOn_box->format, 0xFF, 0xFF, 0xFF ) );
    apply_surface( m_rect.w-m_ramki->m_combobox[0]->w, 0, m_ramki->m_combobox[0],m_mouseOn_box );
    apply_surface( 0, 0, m_ramki->m_border_std[8],m_mouseOn_box );
    apply_surface( 0 + m_rect.w - m_ramki->m_border_std[10]->w, 0, m_ramki->m_border_std[10],m_mouseOn_box );
    apply_surface( 0, 0 + m_rect.h - m_ramki->m_border_std[13]->h, m_ramki->m_border_std[13],m_mouseOn_box );
    apply_surface( 0 + m_rect.w - m_ramki->m_border_std[15]->w, 0 + m_rect.h - m_ramki->m_border_std[15]->h, m_ramki->m_border_std[15],m_mouseOn_box );
    for( int i = 0; i < m_rect.w - m_ramki->m_border_std[8]->w - m_ramki->m_border_std[10]->w; i++ )
    {
        apply_surface( 0 + m_ramki->m_border_std[8]->w + i, 0, m_ramki->m_border_std[9],m_mouseOn_box );
        apply_surface( 0 + m_ramki->m_border_std[13]->w + i, 0 + m_rect.h - m_ramki->m_border_std[14]->h, m_ramki->m_border_std[14],m_mouseOn_box );
    }
    for( int i = 0; i < m_rect.h - m_ramki->m_border_std[8]->h - m_ramki->m_border_std[13]->h; i++ )
    {
        apply_surface( 0, 0 + m_ramki->m_border_std[8]->h + i, m_ramki->m_border_std[11],m_mouseOn_box );
        apply_surface( 0 + m_rect.w - m_ramki->m_border_std[9]->w, 0 + m_ramki->m_border_std[8]->h + i, m_ramki->m_border_std[12],m_mouseOn_box );
    }
    
    m_unactive = SDL_CreateRGBSurface( SDL_SWSURFACE, m_rect.w, m_rect.h, 32,0,0,0,0 );
    SDL_SetColorKey( m_unactive, SDL_SRCCOLORKEY, colorkey );
    SDL_FillRect( m_unactive, &m_unactive->clip_rect, SDL_MapRGB( m_unactive->format, 0xFF, 0xFF, 0xFF ) );
    apply_surface( m_rect.w-m_ramki->m_combobox[0]->w, 0, m_ramki->m_combobox[0],m_unactive );
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
    
    // ListBox elementy:
    m_click_font_color.r = 0xFF;
    m_click_font_color.g = 0xFF;
    m_click_font_color.b = 0xFF;
    m_click_bg_color.r = 51;
    m_click_bg_color.g = 153;
    m_click_bg_color.b = 255;
    
    m_value = "<none>";
    m_valueS = TTF_RenderText_Blended( m_font, m_value.c_str(), m_font_color );
    m_height_elemntu = m_valueS->h;
    
    m_mouse_on_scroll = false;
    m_scroll_up_mouse = false;
    m_scroll_down_mouse = false;
    m_scroll_up_pressed = false;
    m_scroll_down_pressed = false;
    m_scroll_updown_moved = false;
    m_scroll_focus = false;
    m_duzo_obiektow = false;
    m_mouse_on_plansza = false;
    
    m_rect_lb.x = 0;
    m_rect_lb.y = 0;
    m_rect_lb.w = width;
    m_rect_lb.h = 6*m_height_elemntu+2+2;
    
    m_obszar_plansza.x = 0;
    m_obszar_plansza.y = 0;
    m_obszar_plansza.w = width - m_ramki->m_border2[2]->w;
    m_obszar_plansza.h = 6*m_height_elemntu;
    
    m_scroll_rect.x = m_rect_lb.w - m_ramki->m_border2[0]->w - m_ramki->m_border_scroll[0]->w;
    m_scroll_rect.y = m_ramki->m_border2[0]->h;
    m_scroll_rect.w = m_ramki->m_border_scroll[0]->w;
    m_scroll_rect.h = m_rect_lb.h - m_ramki->m_border2[0]->h - m_ramki->m_border2[7]->h;
    
    m_plansza = SDL_CreateRGBSurface( SDL_SWSURFACE, m_obszar_plansza.w-2, m_obszar_plansza.h, 32,0,0,0,0 );
    colorkey = SDL_MapRGB( m_plansza->format, 0, 0xFF, 0xFF ); 
    SDL_SetColorKey( m_plansza, SDL_SRCCOLORKEY, colorkey );
    SDL_FillRect( m_plansza, &m_plansza->clip_rect, SDL_MapRGB( m_plansza->format, 0xFF, 0xFF, 0xFF ) );
    
    m_scroll_bg = SDL_CreateRGBSurface( SDL_SWSURFACE, m_scroll_rect.w, m_scroll_rect.h, 32,0,0,0,0 );
    colorkey = SDL_MapRGB( m_scroll_bg->format, 0, 0xFF, 0xFF ); 
    SDL_SetColorKey( m_scroll_bg, SDL_SRCCOLORKEY, colorkey );
    SDL_FillRect( m_scroll_bg, &m_scroll_bg->clip_rect, SDL_MapRGB( m_scroll_bg->format, 0xFF, 0xFF, 0xFF ) );
    
    m_rama = SDL_CreateRGBSurface( SDL_SWSURFACE, m_rect_lb.w, m_rect_lb.h, 32,0,0,0,0 );
    SDL_SetColorKey( m_rama, SDL_SRCCOLORKEY, colorkey );
    SDL_FillRect( m_rama, &m_rama->clip_rect, SDL_MapRGB( m_rama->format, 0xFF, 0xFF, 0xFF ) );
    apply_surface( 0, 0, m_ramki->m_border2[0],m_rama );
    apply_surface( m_rect_lb.w-m_ramki->m_border2[2]->w, 0, m_ramki->m_border2[2],m_rama );
    apply_surface( 0, m_rect_lb.h-m_ramki->m_border2[5]->h, m_ramki->m_border2[5],m_rama );
    apply_surface( m_rect_lb.w-m_ramki->m_border2[7]->w, m_rect_lb.h-m_ramki->m_border2[7]->h, m_ramki->m_border2[7],m_rama );
    for( int i = 0; i < m_rect_lb.w - m_ramki->m_border2[0]->w - m_ramki->m_border2[2]->w ; i++ )
    {
         apply_surface( i + m_ramki->m_border2[0]->w, 0, m_ramki->m_border2[1],m_rama );
         apply_surface( i + m_ramki->m_border2[0]->w, m_rect_lb.h-m_ramki->m_border2[6]->h, m_ramki->m_border2[6],m_rama );
    }
    for( int i = 0; i < m_rect_lb.h - m_ramki->m_border2[0]->h - m_ramki->m_border2[5]->h ; i++ )
    {
         apply_surface( 0, i + m_ramki->m_border2[0]->h, m_ramki->m_border2[3],m_rama );
         apply_surface( m_rect_lb.w -m_ramki->m_border2[4]->w , i + m_ramki->m_border2[0]->h, m_ramki->m_border2[4],m_rama );
    }
    
    for( int i = 0; i < m_scroll_rect.h; i++ )
    {
         apply_surface( 0, 0+i, m_ramki->m_border_scroll[17], m_scroll_bg );
    }
    // ----
}


CComboBox::~CComboBox()
{
    SDL_FreeSurface( m_unactive );
    SDL_FreeSurface( m_mouseOn );
    SDL_FreeSurface( m_mouseOn_box );
    SDL_FreeSurface( m_clicked );
    SDL_FreeSurface( m_disabled );
    SDL_FreeSurface( m_rama );
    SDL_FreeSurface( m_plansza );
    SDL_FreeSurface( m_scroll_bg );
    SDL_FreeSurface( m_valueS );
    TTF_CloseFont( m_font );
}


void CComboBox::show()
{
    if( m_enabled == true )
    {
        if( m_open_list == true )
        {
            apply_surface( m_rect.x, m_rect.y, m_clicked, m_ramki->m_screen );
            apply_surface( m_rect.x, m_rect.y+m_rect.h, m_rama, m_ramki->m_screen );
            apply_surface( m_rect.x+2, m_rect.y+m_rect.h+2, m_plansza, m_ramki->m_screen, &m_obszar_plansza );
            if( m_duzo_obiektow == true )
            {
                apply_surface( m_rect.x + m_scroll_rect.x, m_rect.y+m_rect.h + m_scroll_rect.y, m_scroll_bg, m_ramki->m_screen );
                apply_surface( m_rect.x + m_scroll_rect.x, m_rect.y +m_rect.h+ m_scroll_rect.y, m_ramki->m_border_scroll[0], m_ramki->m_screen );
                apply_surface( m_rect.x + m_scroll_rect.x, m_rect.y+m_rect.h + m_ramki->m_border2[2]->h + m_scroll_rect.h - m_ramki->m_border_scroll[4]->h, m_ramki->m_border_scroll[4], m_ramki->m_screen );
            }
            if( m_mouse_on_scroll == true )
            {   //Mouse On
                apply_surface( m_rect.x + m_scroll_rect.x, m_rect.y+m_rect.h + m_scroll_rect.y, m_ramki->m_border_scroll[1], m_ramki->m_screen );
                apply_surface( m_rect.x + m_scroll_rect.x, m_rect.y+m_rect.h + m_ramki->m_border2[2]->h + m_scroll_rect.h - m_ramki->m_border_scroll[5]->h, m_ramki->m_border_scroll[5], m_ramki->m_screen );
            }   
            if( m_scroll_up_mouse == true )
            {
                apply_surface( m_rect.x + m_scroll_rect.x, m_rect.y+m_rect.h + m_scroll_rect.y, m_ramki->m_border_scroll[2], m_ramki->m_screen );
            }
            if( m_scroll_down_mouse == true )
            {
                apply_surface( m_rect.x + m_scroll_rect.x, m_rect.y+m_rect.h + m_ramki->m_border2[2]->h + m_scroll_rect.h - m_ramki->m_border_scroll[4]->h, m_ramki->m_border_scroll[6], m_ramki->m_screen );
            }
            //Pressed
            if( m_scroll_up_pressed == true )
            {
                apply_surface( m_rect.x + m_scroll_rect.x, m_rect.y+m_rect.h + m_scroll_rect.y, m_ramki->m_border_scroll[3], m_ramki->m_screen );
            }
            if( m_scroll_down_pressed == true )
            {
                apply_surface( m_rect.x + m_scroll_rect.x, m_rect.y+m_rect.h + m_ramki->m_border2[2]->h + m_scroll_rect.h - m_ramki->m_border_scroll[4]->h, m_ramki->m_border_scroll[7], m_ramki->m_screen );
            }
        }
        else
        {
            if( m_mouse_on_box == true )
            {
                if( m_mouse_on_arrow == true )
                {
                    apply_surface( m_rect.x, m_rect.y, m_mouseOn, m_ramki->m_screen );
                }
                else
                {
                    apply_surface( m_rect.x, m_rect.y, m_mouseOn_box, m_ramki->m_screen );
                }
            }
            else
            {
                apply_surface( m_rect.x, m_rect.y, m_unactive, m_ramki->m_screen );
            }
        }
        apply_surface( m_rect.x+3, m_rect.y+3, m_valueS, m_ramki->m_screen );
    }
    else
    {
        apply_surface( m_rect.x, m_rect.y, m_disabled, m_ramki->m_screen );
        apply_surface( m_rect.x+m_rect.w-m_ramki->m_combobox[3]->w, m_rect.y, m_ramki->m_combobox[3], m_ramki->m_screen );
        
        
    }
}

void CComboBox::OnEvent(SDL_Event* Event)
{
    CEvent::OnEvent(Event);
}

void CComboBox::OnMouseMove(int mX, int mY, int relX, int relY, bool Left,bool Right,bool Middle)
{
    if( m_enabled == true )
    {
        // Zaznacznik              
        if(  (mX > m_rect.x ) && (mX < m_rect.x + m_rect.w) && (mY > m_rect.y ) && (mY < m_rect.y +m_rect.h)  )
        {
            m_mouse_on_box = true;
            if( (mX > m_rect.x + m_rect.w - m_ramki->m_combobox[0]->w) )
            {
                m_mouse_on_arrow = true;
            }
            else
            {
                m_mouse_on_arrow = false;
            }
        }
        else
        {
            m_mouse_on_box = false;
            m_mouse_on_arrow = false;
        }
        if( m_open_list == true )
        {
            for( int i = 0; i < m_obszar_plansza.h / m_height_elemntu; i++ )
            {
              if(  (mX > m_rect.x + m_ramki->m_border2[3]->w) && (mX < m_rect.x + m_obszar_plansza.w - m_ramki->m_border2[3]->w) && (mY > m_rect.y+m_rect.h + m_ramki->m_border2[1]->h + i*m_height_elemntu) && (mY < m_rect.y+m_rect.h + m_ramki->m_border2[1]->h + (i+1)*m_height_elemntu)  )
              {
                   m_znacznik = 1+ i + (m_obszar_plansza.y+2) / m_height_elemntu;
                   if( m_znacznik > m_dane.size() ) { m_znacznik = m_dane.size(); }
                   //this->set_znacznik( m_znacznik );
                   //char buffer[50];
                   //sprintf( buffer, "i = %d", m_znacznik);
                   //SDL_WM_SetCaption( buffer, NULL ); 
                   this->refresh_items();
              }
            }
         }
    }
    
    
    // Scroll
    if( m_duzo_obiektow == true )
    {
        if(  (mX > m_rect.x+m_scroll_rect.x) && (mX < m_rect.x+m_scroll_rect.x + m_scroll_rect.w) && (mY > m_rect.y+m_scroll_rect.y+m_rect.h) && (mY < m_rect.y+m_rect.h+m_scroll_rect.y + m_scroll_rect.h)  )
        {
            m_mouse_on_scroll = true;
             
            if(  (mX > m_rect.x + m_scroll_rect.x) && (mX < m_rect.x + m_scroll_rect.x + m_scroll_rect.w) && (mY > m_rect.y+m_rect.h+m_scroll_rect.y) && (mY < m_rect.y+m_rect.h+m_scroll_rect.y + m_ramki->m_border_scroll[0]->h)  )
            {
                 m_scroll_up_mouse = true;
            }
            else
            {
                m_scroll_up_mouse = false;
            }
            
            if(  (mX > m_rect.x+m_scroll_rect.x) && (mX < m_rect.x+m_scroll_rect.x + m_scroll_rect.w) && (mY > m_rect.y+m_rect.h+m_scroll_rect.h - m_ramki->m_border_scroll[0]->h) && (mY < m_rect.y+m_rect.h+m_scroll_rect.y + m_scroll_rect.h)  )
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
    
    /*
    m_mouse_on_box = false;
            m_mouse_on_arrow = false;
    m_arrow_pressed = false;
    m_enabled = true;
    */
}

void CComboBox::OnLButtonDown(int mX, int mY)
{
     // Zaznacznik
     if( (m_mouse_on_box == true) )
     {
         if( m_open_list == false )
         {
             m_open_list = true;
         }
         else
         {
             m_open_list = false;
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

void CComboBox::OnLButtonUp(int mX, int mY)
{
    if( m_open_list == true )
    {
        if( (mX > m_rect.x + m_ramki->m_border2[3]->w) && (mX < m_rect.x + m_obszar_plansza.w - m_ramki->m_border2[3]->w) && (mY > m_rect.y+m_rect.h ) && (mY < m_rect.y+m_rect.h+m_obszar_plansza.h)  )
        {
            set_value( m_znacznik );
            m_open_list = false;
            m_mouse_on_box = false;
            m_mouse_on_arrow = false;
            m_arrow_pressed = false;
        }
    }
    
    m_scroll_focus = false;
    m_scroll_up_pressed = false;
    m_scroll_down_pressed = false;
    
}

void CComboBox::dodaj( std::string napis )
{
    if( m_dane.size() < m_max_objects )
    {
        m_dane.push_back( napis );
        if( m_dane.size() * m_height_elemntu > m_obszar_plansza.h )
        {
            m_duzo_obiektow = true;
            m_obszar_plansza.w = m_rect.w - m_ramki->m_border2[0]->w - m_ramki->m_border_scroll[0]->w - 1;
        }
        this->refresh_items();
    }
    {
        /*
            Komunikat o przekroczeniu pojemnosci ComboBoxa
        */
    }
}


void CComboBox::usun( int index )
{
    int i = 1;
    for( std::list<std::string>::iterator iter = m_dane.begin(); iter != m_dane.end(); ++iter )
    {
         if( i == index )
         {
             if( this->get_value_index() == i ) { this->set_value(0); }
             iter = m_dane.erase(iter);
             m_znacznik=0;
             break;
         }
         i++;
    }
    if( m_dane.size() * m_height_elemntu <= m_obszar_plansza.h )
    {
        m_duzo_obiektow = false;
        m_obszar_plansza.w = m_rect.w - m_ramki->m_border2[0]->w;
    }
    if( (m_dane.size() == 0) ) { this->set_value(0); }
    this->refresh_items();
}

void CComboBox::usun_all()
{
     if( m_dane.size() > 0 )
     {
         m_dane.clear();
         m_duzo_obiektow = false;
         m_wybrany = 0;
         m_znacznik = 0;
         this->set_value(0);
         m_obszar_plansza.w = m_rect.w - m_ramki->m_border2[0]->w;
         this->refresh_items();
     }
}

int CComboBox::get_size()
{
    return m_dane.size();
}

void CComboBox::refresh_items()
{
    SDL_FillRect( m_plansza, &m_plansza->clip_rect, SDL_MapRGB( m_plansza->format, 0xFF, 0xFF, 0xFF ) );
    
    if( m_dane.empty() == false )
    {
        SDL_FreeSurface( m_plansza );
        m_plansza = SDL_CreateRGBSurface( SDL_SWSURFACE, m_obszar_plansza.w-2, m_height_elemntu*m_dane.size(), 32,0,0,0,0 );
        Uint32 colorkey = SDL_MapRGB( m_plansza->format, 0, 0xFF, 0xFF ); 
        SDL_SetColorKey( m_plansza, SDL_SRCCOLORKEY, colorkey );
        SDL_FillRect( m_plansza, &m_plansza->clip_rect, SDL_MapRGB( m_plansza->format, 0xFF, 0xFF, 0xFF ) );
    
        SDL_Rect zaz;
        zaz.x = m_obszar_plansza.x;
        zaz.y = m_obszar_plansza.y;
        zaz.w = m_obszar_plansza.w-2;
        zaz.h = m_height_elemntu;
        
        int i = 1;
        SDL_Surface *temp;
        temp = NULL;
        for( std::list<std::string>::iterator iter = m_dane.begin(); iter != m_dane.end(); ++iter )
        {
             if( i == m_znacznik )
             {
                 temp = TTF_RenderText_Blended( m_font, (*iter).c_str(), m_click_font_color);
                 SDL_FillRect( m_plansza, &zaz, SDL_MapRGB(m_plansza->format, 51, 153, 255) );
                 apply_surface( 0, 0+m_height_elemntu*(i-1), temp, m_plansza );
                 SDL_FreeSurface( temp );
             }
             else
             {
                 temp = TTF_RenderText_Blended( m_font, (*iter).c_str(), m_font_color );
                 apply_surface( 0, 0+m_height_elemntu*(i-1), temp, m_plansza );
                 SDL_FreeSurface( temp );
             }
             zaz.y = 0+m_height_elemntu*i;
             i++;
        }
    }
}

void CComboBox::set_znacznik( int liczba )
{
    m_znacznik = liczba;
}

int CComboBox::get_znacznik()
{
    return m_znacznik;
}

int CComboBox::get_value_index()
{
    return m_wybrany;
}

void CComboBox::set_enabled( bool val )
{
    m_enabled = val;
    if( val == true )
    {
        m_font_color.r = 0x00;
        m_font_color.g = 0x00;
        m_font_color.b = 0x00;
    }
    else
    {
        m_mouse_on_box = false;
        m_open_list = false;
        m_font_color.r = 0x83;
        m_font_color.g = 0x83;
        m_font_color.b = 0x83;
    }
    this->set_value(m_wybrany);
}

void CComboBox::set_value( int liczba )
{
    if( liczba == 0 )
    {
        m_value = "<none>";
        SDL_FreeSurface( m_valueS );
        m_valueS = TTF_RenderText_Blended( m_font, m_value.c_str(), m_font_color );
        m_wybrany = 0;
        m_znacznik = 0;
    }
    if( (liczba > 0) && (liczba <= m_dane.size()) )
    {
        m_wybrany = liczba;
        m_znacznik = liczba;
        std::list<std::string>::iterator it = m_dane.begin();
        for( int i = 2; i <= liczba; i++ )
        {
            it++;
        }
        m_value = (*it);
        SDL_FreeSurface( m_valueS );
        m_valueS = TTF_RenderText_Blended( m_font, m_value.c_str(), m_font_color );
    }
}

bool CComboBox::get_statusOpened()
{
    return m_open_list;
}
