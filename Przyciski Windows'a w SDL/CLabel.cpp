#include "CLabel.h"


CLabel::CLabel( CRamki* obiekt_ramek, int posx, int posy, std::string napis, int fontSize )
{
    m_ramki = obiekt_ramek;
    m_rect.x = posx;
    m_rect.y = posy;
    m_napis = napis;
    m_font = TTF_OpenFont( "font/tahoma.ttf", fontSize );
    if( m_font == NULL ) { std::cerr << "CLabel Error\n"; this->~CLabel(); }
    m_font_color.r = 0x00;
    m_font_color.g = 0x00;
    m_font_color.b = 0x00;
    m_textSquare = TTF_RenderText_Blended( m_font, m_napis.c_str(), m_font_color ); 
    m_rect.w = m_textSquare->w;
    m_rect.h = m_textSquare->h;
}


CLabel::~CLabel()
{
    SDL_FreeSurface( m_textSquare );
    TTF_CloseFont( m_font );
}


void CLabel::set_caption( std::string napis )
{
    m_napis = napis;
    SDL_FreeSurface( m_textSquare );
    m_textSquare = TTF_RenderText_Blended( m_font, m_napis.c_str(), m_font_color ); 
}

void CLabel::show()
{
     apply_surface( m_rect.x, m_rect.y, m_textSquare, m_ramki->m_screen );
}
