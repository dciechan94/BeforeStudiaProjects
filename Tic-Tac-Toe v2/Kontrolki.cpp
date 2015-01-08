#include "Kontrolki.h"

//========================     C_LABEL
//========================
CLabel::CLabel( int posx, int posy, std::string napis, int fontSize )
{
    m_rect.x = posx;
    m_rect.y = posy;
    m_napis = napis;
    m_font = TTF_OpenFont( "font/tahoma.ttf", fontSize );
    if( m_font == NULL ) { /*MessageBox(NULL, "Could not load font", "Error", MB_OK);*/ this->~CLabel(); }
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
    m_textSquare = TTF_RenderText_Blended( m_font, m_napis.c_str(), m_font_color ); 
}

void CLabel::show()
{
     apply_surface( m_rect.x, m_rect.y, m_textSquare, screen );
}


//==============================================================================
//========================     C_CHECK_BOX
//========================

int CCheckBox::m_dist_img_txt = 5;

CCheckBox::CCheckBox( CRamki* obiekt_ramek, int posx, int posy, std::string napis, bool ticked, int fontSize )
{
    m_ramki = obiekt_ramek;
    m_rect.x = posx;
    m_rect.y = posy;
    m_napis = napis;
    m_ticked = ticked;
    m_on_target = false;
    m_clicked_focus = false;
    m_font = TTF_OpenFont( "font/tahoma.ttf", fontSize );
    if( m_font == NULL ) { /*MessageBox(NULL, "Could not load font", "Error", MB_OK);*/ this->~CCheckBox(); }
    m_font_color.r = 0x00;
    m_font_color.g = 0x00;
    m_font_color.b = 0x00;
    m_textSquare = TTF_RenderText_Blended( m_font, m_napis.c_str(), m_font_color ); 
    m_rect.w = m_ramki->m_checkbox[0]->w + m_dist_img_txt + m_textSquare->w;
    if( m_textSquare->h >= m_ramki->m_checkbox[0]->h ) { m_rect.h = m_textSquare->h; } else { m_rect.h = m_ramki->m_checkbox[0]->h; }
}


CCheckBox::~CCheckBox()
{
    SDL_FreeSurface( m_textSquare );
    TTF_CloseFont( m_font );
}

bool CCheckBox::is_ticked()
{
    if( m_ticked == false ) { return false; }
    return true;
}

void CCheckBox::set_ticked( bool val )
{
     m_ticked = val;
}

void CCheckBox::show()
{
     if( m_on_target == true )
     {
         if( m_ticked == true )
         {               // Ticked
             if( m_clicked_focus == true )
             {
                 // Pressed
                 apply_surface( m_rect.x, m_rect.y + (m_rect.h-m_ramki->m_checkbox[5]->h)/2, m_ramki->m_checkbox[5],screen );
             }
             else
             {
                 // Mouse On
                 apply_surface( m_rect.x, m_rect.y + (m_rect.h-m_ramki->m_checkbox[4]->h)/2, m_ramki->m_checkbox[4],screen );
             }
         }
         else
         {                // Unticked
             if( m_clicked_focus == true )
             {
                 // Pressed
                 apply_surface( m_rect.x, m_rect.y + (m_rect.h-m_ramki->m_checkbox[2]->h)/2, m_ramki->m_checkbox[2],screen );
             }
             else
             {
                 // Mouse On
                 apply_surface( m_rect.x, m_rect.y + (m_rect.h-m_ramki->m_checkbox[1]->h)/2, m_ramki->m_checkbox[1],screen );
             }
         }
     }
     else
     {
         if( m_ticked == true )
         {               // Ticked
             // Normal
             apply_surface( m_rect.x, m_rect.y + (m_rect.h-m_ramki->m_checkbox[3]->h)/2, m_ramki->m_checkbox[3],screen );
         }
         else
         {                // Unticked
             // Normal
             apply_surface( m_rect.x, m_rect.y + (m_rect.h-m_ramki->m_checkbox[0]->h)/2, m_ramki->m_checkbox[0],screen );
         }
         
     }
     
     apply_surface( m_rect.x +(m_ramki->m_checkbox[0]->w) + m_dist_img_txt, m_rect.y, m_textSquare,screen );
     //apply_surface( m_rect.x, m_rect.y + (m_rect.h-m_ramki->m_checkbox[0]->h)/2, m_ramki->m_checkbox[1],screen );
}

void CCheckBox::OnEvent(SDL_Event* Event)
{
    CEvent::OnEvent(Event);
}

void CCheckBox::OnMouseMove(int mX, int mY, int relX, int relY, bool Left,bool Right,bool Middle)
{
    if(  (mX > m_rect.x) && (mX < m_rect.x + m_rect.w) && (mY > m_rect.y) && (mY < m_rect.y + m_rect.h)  )
    {
         m_on_target = true;
    }
    else
    {
         m_on_target = false;
    }
    
    if( Left == true )
    {
        
    }
}

void CCheckBox::OnLButtonUp(int mX, int mY)
{
    if(  (m_on_target == true) && (m_clicked_focus == true)  )
    {
         // Klikniêcie
         if( m_ticked == false) { m_ticked = true; } else { m_ticked = false; }
         
    }
    m_clicked_focus = false;
    
}

void CCheckBox::OnLButtonDown(int mX, int mY)
{
    if( m_on_target == true )
    {
        m_clicked_focus = true;
    }
}

//==============================================================================
//========================     C_BUTTON_STD
//========================


CButton_std::CButton_std( CRamki* obiekt_ramek, int posx, int posy, std::string napis, BUTTON_STD_TYPE id, int width)
{
    m_ramki = obiekt_ramek;
    m_rect.x = posx;
    m_rect.y = posy;
    m_napis = napis;
    m_id = id;
    m_on_target = false;
    m_clicked_focus = false;
    m_font = TTF_OpenFont( "font/tahoma.ttf", 12 );
    if( m_font == NULL ) { /*MessageBox(NULL, "Could not load font", "Error", MB_OK);*/ this->~CButton_std(); }
    m_font_color.r = 0x00;
    m_font_color.g = 0x00;
    m_font_color.b = 0x00;
    m_textSquare = TTF_RenderText_Blended( m_font, m_napis.c_str(), m_font_color ); 
    m_rect.w = width;
    if( width < m_ramki->m_button_std[0]->w + m_textSquare->w + m_ramki->m_button_std[2]->w ) { m_rect.w = m_ramki->m_button_std[0]->w + m_textSquare->w + m_ramki->m_button_std[2]->w; }
    m_rect.h = m_ramki->m_button_std[0]->h;
}


CButton_std::~CButton_std()
{
    SDL_FreeSurface( m_textSquare );
    TTF_CloseFont( m_font );
}

void CButton_std::show()
{
     if( m_on_target == true )
     {
         if( m_clicked_focus == true )
         {
             // Click
             apply_surface( m_rect.x, m_rect.y, m_ramki->m_button_std[6],screen );
             apply_surface( m_rect.x + m_rect.w - m_ramki->m_button_std[8]->w, m_rect.y, m_ramki->m_button_std[8],screen );
             for( int i = 0; i < m_rect.w - (m_ramki->m_button_std[6]->w+m_ramki->m_button_std[8]->w); i++)
             {
                  apply_surface( m_rect.x + i + m_ramki->m_button_std[6]->w, m_rect.y, m_ramki->m_button_std[7],screen );
             }
         }
         else
         {
             // Mouse
             apply_surface( m_rect.x, m_rect.y, m_ramki->m_button_std[3],screen );
             apply_surface( m_rect.x + m_rect.w - m_ramki->m_button_std[5]->w, m_rect.y, m_ramki->m_button_std[5],screen );
             for( int i = 0; i < m_rect.w - (m_ramki->m_button_std[3]->w+m_ramki->m_button_std[5]->w); i++)
             {
                  apply_surface( m_rect.x + i + m_ramki->m_button_std[3]->w, m_rect.y, m_ramki->m_button_std[4],screen );
             }
         }
     }
     else
     {
         // Normal
         apply_surface( m_rect.x, m_rect.y, m_ramki->m_button_std[0],screen );
         apply_surface( m_rect.x + m_rect.w - m_ramki->m_button_std[2]->w, m_rect.y, m_ramki->m_button_std[2],screen );
         for( int i = 0; i < m_rect.w - (m_ramki->m_button_std[0]->w+m_ramki->m_button_std[2]->w); i++)
         {
              apply_surface( m_rect.x + i + m_ramki->m_button_std[0]->w, m_rect.y, m_ramki->m_button_std[1],screen );
         }
     }
     
     apply_surface( (m_rect.x + (m_rect.w - m_textSquare->w)/2), m_rect.y + (m_rect.h - m_textSquare->h)/2, m_textSquare, screen );
}

void CButton_std::OnEvent(SDL_Event* Event)
{
    CEvent::OnEvent(Event);
}

void CButton_std::OnMouseMove(int mX, int mY, int relX, int relY, bool Left,bool Right,bool Middle)
{
    if(  (mX > m_rect.x) && (mX < m_rect.x + m_rect.w) && (mY > m_rect.y) && (mY < m_rect.y + m_rect.h)  )
    {
         m_on_target = true;
    }
    else
    {
         m_on_target = false;
    }
    
    if( Left == true )
    {
        
    }
}

void CButton_std::OnLButtonUp(int mX, int mY)
{
    if(  (m_on_target == true) && (m_clicked_focus == true)  )
    {
         // Klikniêcie
         switch( m_id )
         {
             case BST_START:
                  proces_gry = PID_ROZGRYWKA;
                  break;
             case BST_CONNECT:
                  // Menadzer Polaczenia
                  // Zmien na PID_ROZGRYWKA
                  break;
             case BST_DCONNECT:
                  // Zakoncz polaczenie
                  // Zmien na PID_MENU_GLOWNE
                  break;
             case BST_EXITTOMENU:
                  proces_gry = PID_MENU_GLOWNE;
                  SDL_WM_SetCaption( "Tic-Tac-Toe", NULL );
                  break;
             case BST_NONE:
                  break;
             
             default: break;
         }
         // Obs³uga button id
         
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

//==============================================================================
//========================     C_EDIT_BOX
//========================

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
    m_font = TTF_OpenFont( "font/tahoma.ttf", fontSize );
    if( m_font == NULL ) { /*MessageBox(NULL, "Could not load font", "Error", MB_OK);*/ this->~CEditBox(); }
    m_font_color.r = 0x00;
    m_font_color.g = 0x00;
    m_font_color.b = 0x00;
    m_textSquare = TTF_RenderText_Blended( m_font, m_napis.c_str(), m_font_color ); 
    m_rect.h = m_ramki->m_border_std[0]->h + m_akapit_gora + m_textSquare->h + m_akapit_dol + m_ramki->m_border_std[7]->h;
    /*SDL_Rect rectx;
    rectx.x=0;
    rectx.y=0;
    rectx.w = SCREEN_WIDTH;
    rectx.h= SCREEN_HEIGHT;
    SDL_FillRect( m_pole[0], &rectx, SDL_MapRGB(screen->format, 0, 255, 255) );
    this->init_surfaces();*/
    m_background.x = posx +1;
    m_background.y = posy +1;
    m_background.w = m_rect.w-2;
    m_background.h = m_rect.h-2;
    m_max_length = max_length;
    if( m_max_length != 0 ) { m_use_length = true; } else { m_use_length = false; }
    m_full_line = false;
    m_znacznik = TTF_RenderText_Blended( m_font, "|", m_font_color ); 
    SDL_EnableUNICODE( SDL_ENABLE );
    
}


CEditBox::~CEditBox()
{
    SDL_FreeSurface( m_textSquare );
    SDL_FreeSurface( m_znacznik );
    //SDL_FreeSurface( m_pole[0] );m_znacznik
    //SDL_FreeSurface( m_pole[1] );
    //SDL_FreeSurface( m_pole[2] );
    TTF_CloseFont( m_font );
    SDL_EnableUNICODE( SDL_DISABLE ); 
}

void CEditBox::napisz( std::string napis )
{
    m_napis = napis;
    CEditBox::refresh();
}

void CEditBox::refresh()
{
    if( m_napis == "" )
    {
        m_textSquare = TTF_RenderText_Blended( m_font, " ", m_font_color );
    }
    else
    {
        m_textSquare = TTF_RenderText_Blended( m_font, m_napis.c_str(), m_font_color );
    }
    //m_textSquare = TTF_RenderText_Blended( m_font, m_napis.c_str(), m_font_color );
}

std::string CEditBox::get_napis()
{
    return m_napis;
}

void CEditBox::show()
{
     SDL_FillRect( screen, &m_background, SDL_MapRGB(screen->format, 0xFF, 0xFF, 0xFF) );
        
     if( m_clickedWrite_focus == true )
     {
         // Write Focus
         apply_surface( m_rect.x, m_rect.y, m_ramki->m_border_std[16],screen );
         apply_surface( m_rect.x + m_rect.w - m_ramki->m_border_std[18]->w, m_rect.y, m_ramki->m_border_std[18],screen );
         apply_surface( m_rect.x, m_rect.y + m_rect.h - m_ramki->m_border_std[21]->h, m_ramki->m_border_std[21],screen );
         apply_surface( m_rect.x + m_rect.w - m_ramki->m_border_std[23]->w, m_rect.y + m_rect.h - m_ramki->m_border_std[23]->h, m_ramki->m_border_std[23],screen );
         for( int i = 0; i < m_rect.w - m_ramki->m_border_std[16]->w - m_ramki->m_border_std[18]->w; i++ )
         {
              apply_surface( m_rect.x + m_ramki->m_border_std[16]->w + i, m_rect.y, m_ramki->m_border_std[17],screen );
              apply_surface( m_rect.x + m_ramki->m_border_std[21]->w + i, m_rect.y + m_rect.h - m_ramki->m_border_std[22]->h, m_ramki->m_border_std[22],screen );
         }
         for( int i = 0; i < m_rect.h - m_ramki->m_border_std[16]->h - m_ramki->m_border_std[21]->h; i++ )
         {
              apply_surface( m_rect.x, m_rect.y + m_ramki->m_border_std[16]->h + i, m_ramki->m_border_std[19],screen );
              apply_surface( m_rect.x + m_rect.w - m_ramki->m_border_std[17]->w, m_rect.y + m_ramki->m_border_std[16]->h + i, m_ramki->m_border_std[20],screen );
         }
     }
     else
     {
         if( m_on_target == true )
         {
             // Mouse On
             apply_surface( m_rect.x, m_rect.y, m_ramki->m_border_std[8],screen );
             apply_surface( m_rect.x + m_rect.w - m_ramki->m_border_std[10]->w, m_rect.y, m_ramki->m_border_std[10],screen );
             apply_surface( m_rect.x, m_rect.y + m_rect.h - m_ramki->m_border_std[13]->h, m_ramki->m_border_std[13],screen );
             apply_surface( m_rect.x + m_rect.w - m_ramki->m_border_std[15]->w, m_rect.y + m_rect.h - m_ramki->m_border_std[15]->h, m_ramki->m_border_std[15],screen );
             for( int i = 0; i < m_rect.w - m_ramki->m_border_std[8]->w - m_ramki->m_border_std[10]->w; i++ )
             {
                  apply_surface( m_rect.x + m_ramki->m_border_std[8]->w + i, m_rect.y, m_ramki->m_border_std[9],screen );
                  apply_surface( m_rect.x + m_ramki->m_border_std[13]->w + i, m_rect.y + m_rect.h - m_ramki->m_border_std[14]->h, m_ramki->m_border_std[14],screen );
             }
             for( int i = 0; i < m_rect.h - m_ramki->m_border_std[8]->h - m_ramki->m_border_std[13]->h; i++ )
             {
                  apply_surface( m_rect.x, m_rect.y + m_ramki->m_border_std[8]->h + i, m_ramki->m_border_std[11],screen );
                  apply_surface( m_rect.x + m_rect.w - m_ramki->m_border_std[9]->w, m_rect.y + m_ramki->m_border_std[8]->h + i, m_ramki->m_border_std[12],screen );
             }
         }
         else
         {
             // Unactive
             apply_surface( m_rect.x, m_rect.y, m_ramki->m_border_std[0],screen );
             apply_surface( m_rect.x + m_rect.w - m_ramki->m_border_std[2]->w, m_rect.y, m_ramki->m_border_std[2],screen );
             apply_surface( m_rect.x, m_rect.y + m_rect.h - m_ramki->m_border_std[5]->h, m_ramki->m_border_std[5],screen );
             apply_surface( m_rect.x + m_rect.w - m_ramki->m_border_std[7]->w, m_rect.y + m_rect.h - m_ramki->m_border_std[7]->h, m_ramki->m_border_std[7],screen );
             for( int i = 0; i < m_rect.w - m_ramki->m_border_std[0]->w - m_ramki->m_border_std[2]->w; i++ )
             {
                  apply_surface( m_rect.x + m_ramki->m_border_std[0]->w + i, m_rect.y, m_ramki->m_border_std[1],screen );
                  apply_surface( m_rect.x + m_ramki->m_border_std[5]->w + i, m_rect.y + m_rect.h - m_ramki->m_border_std[6]->h, m_ramki->m_border_std[6],screen );
             }
             for( int i = 0; i < m_rect.h - m_ramki->m_border_std[0]->h - m_ramki->m_border_std[5]->h; i++ )
             {
                  apply_surface( m_rect.x, m_rect.y + m_ramki->m_border_std[0]->h + i, m_ramki->m_border_std[3],screen );
                  apply_surface( m_rect.x + m_rect.w - m_ramki->m_border_std[1]->w, m_rect.y + m_ramki->m_border_std[0]->h + i, m_ramki->m_border_std[4],screen );
             }
             //apply_surface( 0, 0, m_pole[0],screen );
         }
     }
     
     apply_surface( m_rect.x +(m_ramki->m_border_std[0]->w) + m_akapit_lewo, m_rect.y + (m_ramki->m_border_std[0]->h) + m_akapit_gora, m_textSquare,screen );
     if( m_clickedWrite_focus == true )
     {
         apply_surface( m_rect.x +(m_ramki->m_border_std[0]->w) + m_akapit_lewo + m_textSquare->w -2, m_rect.y + (m_ramki->m_border_std[0]->h)-1, m_znacznik,screen );
     }
     
}

/*void CEditBox::init_surfaces()
{
    // Unactive
             apply_surface( m_rect.x, m_rect.y, m_ramki->m_border_std[0],m_pole[0] );
             apply_surface( m_rect.x + m_rect.w - m_ramki->m_border_std[2]->w, m_rect.y, m_ramki->m_border_std[2],m_pole[0] );
             apply_surface( m_rect.x, m_rect.y + m_rect.h - m_ramki->m_border_std[5]->h, m_ramki->m_border_std[5],m_pole[0] );
             apply_surface( m_rect.x + m_rect.w - m_ramki->m_border_std[7]->w, m_rect.y + m_rect.h - m_ramki->m_border_std[7]->h, m_ramki->m_border_std[7],m_pole[0] );
             for( int i = 0; i < m_rect.w - m_ramki->m_border_std[0]->w - m_ramki->m_border_std[2]->w; i++ )
             {
                  apply_surface( m_rect.x + m_ramki->m_border_std[0]->w + i, m_rect.y, m_ramki->m_border_std[1],m_pole[0] );
                  apply_surface( m_rect.x + m_ramki->m_border_std[5]->w + i, m_rect.y + m_rect.h - m_ramki->m_border_std[6]->h, m_ramki->m_border_std[6],m_pole[0] );
             }
             for( int i = 0; i < m_rect.h - m_ramki->m_border_std[0]->h - m_ramki->m_border_std[5]->h; i++ )
             {
                  apply_surface( m_rect.x, m_rect.y + m_ramki->m_border_std[0]->h + i, m_ramki->m_border_std[3],m_pole[0] );
                  apply_surface( m_rect.x + m_rect.w - m_ramki->m_border_std[1]->w, m_rect.y + m_ramki->m_border_std[0]->h + i, m_ramki->m_border_std[4],m_pole[0] );
             }
}*/


void CEditBox::OnEvent(SDL_Event* Event)
{
    CEvent::OnEvent(Event);
}

void CEditBox::OnMouseMove(int mX, int mY, int relX, int relY, bool Left,bool Right,bool Middle)
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

void CEditBox::OnLButtonDown(int mX, int mY)
{
    if( m_on_target == true )
    {
        m_clickedWrite_focus = true;
    }
    if( m_on_target == false )
    {
        m_clickedWrite_focus = false;
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
                    if( event.key.keysym.unicode == (Uint16)' ' )
                    {
                        m_napis += (char)event.key.keysym.unicode;
                    }
                    //If the key is a number
                    else if( ( event.key.keysym.unicode >= (Uint16)'0' ) && ( event.key.keysym.unicode <= (Uint16)'9' ) )
                    {
                        m_napis += (char)event.key.keysym.unicode;
                    }
                    //If the key is a uppercase letter
                    else if( ( event.key.keysym.unicode >= (Uint16)'A' ) && ( event.key.keysym.unicode <= (Uint16)'Z' ) )
                    {
                        m_napis += (char)event.key.keysym.unicode;
                    }
                    //If the key is a lowercase letter
                    else if( ( event.key.keysym.unicode >= (Uint16)'a' ) && ( event.key.keysym.unicode <= (Uint16)'z' ) )
                    {
                        m_napis += (char)event.key.keysym.unicode;
                    }
                    else if(  event.key.keysym.unicode == (Uint16)'.'  ) 
                    {
                        m_napis += (char)event.key.keysym.unicode;
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
                if( event.key.keysym.unicode == (Uint16)' ' )
                {
                    m_napis += (char)event.key.keysym.unicode;
                }
                //If the key is a number
                else if( ( event.key.keysym.unicode >= (Uint16)'0' ) && ( event.key.keysym.unicode <= (Uint16)'9' ) )
                {
                    m_napis += (char)event.key.keysym.unicode;
                }
                //If the key is a uppercase letter
                else if( ( event.key.keysym.unicode >= (Uint16)'A' ) && ( event.key.keysym.unicode <= (Uint16)'Z' ) )
                {
                    m_napis += (char)event.key.keysym.unicode;
                }
                //If the key is a lowercase letter
                else if( ( event.key.keysym.unicode >= (Uint16)'a' ) && ( event.key.keysym.unicode <= (Uint16)'z' ) )
                {
                    m_napis += (char)event.key.keysym.unicode;
                }
                else if(  event.key.keysym.unicode == (Uint16)'.'  ) 
                {
                    m_napis += (char)event.key.keysym.unicode;
                }
                
            }
            
            this->refresh();
            if( m_textSquare->w > m_rect.w - (m_ramki->m_border_std[0]->w + m_akapit_lewo + m_akapit_prawo + m_ramki->m_border_std[2]->w)  )
            {
                //Remove a character from the end
                m_napis.erase( m_napis.length() - 1 );
                this->refresh();
                if( m_use_length == true ) { m_full_line = false; }
            }

            //If backspace was pressed and the string isn't blank
            if( ( event.key.keysym.sym == SDLK_BACKSPACE ) && ( m_napis.length() != 0 ) )
            {
                //Remove a character from the end
                m_napis.erase( m_napis.length() - 1 );
                this->refresh();
                if( m_use_length == true ) { m_full_line = false; }
            }

                
            if( ( event.key.keysym.sym == SDLK_RETURN ) && ( m_napis.length() != 0 ) )
            {
                m_clickedWrite_focus = false;
            }
        }
    }
}


//==============================================================================
//========================     C_RADIO_BUTTON
//========================

int CRadioButton::m_dist_img_txt = 5;

CRadioButton::CRadioButton( CRamki* obiekt_ramek, int posx, int posy, std::string napis, bool ticked, RADIO_BUTTON_TYPE id, int fontSize = 15 )
{
    m_ramki = obiekt_ramek;
    m_rect.x = posx;
    m_rect.y = posy;
    m_napis = napis;
    m_ticked = ticked;
    m_id = id;
    m_on_target = false;
    m_clicked_focus = false;
    m_font = TTF_OpenFont( "font/tahoma.ttf", fontSize );
    if( m_font == NULL ) { /*MessageBox(NULL, "Could not load font", "Error", MB_OK);*/ this->~CRadioButton(); }
    m_font_color.r = 0x00;
    m_font_color.g = 0x00;
    m_font_color.b = 0x00;
    m_textSquare = TTF_RenderText_Blended( m_font, m_napis.c_str(), m_font_color ); 
    m_rect.w = m_ramki->m_radiobutton[0]->w + m_dist_img_txt + m_textSquare->w;
    if( m_textSquare->h >= m_ramki->m_radiobutton[0]->h ) { m_rect.h = m_textSquare->h; } else { m_rect.h = m_ramki->m_radiobutton[0]->h; }
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

void CRadioButton::set_ticked( bool val )
{
    m_ticked = val;
}

void CRadioButton::show()
{
     if( m_on_target == true )
     {
         if( m_ticked == true )
         {               // Ticked
             if( m_clicked_focus == true )
             {
                 // Pressed
                 apply_surface( m_rect.x, m_rect.y + (m_rect.h-m_ramki->m_radiobutton[5]->h)/2, m_ramki->m_radiobutton[5],screen );
             }
             else
             {
                 // Mouse On
                 apply_surface( m_rect.x, m_rect.y + (m_rect.h-m_ramki->m_radiobutton[4]->h)/2, m_ramki->m_radiobutton[4],screen );
             }
         }
         else
         {                // Unticked
             if( m_clicked_focus == true )
             {
                 // Pressed
                 apply_surface( m_rect.x, m_rect.y + (m_rect.h-m_ramki->m_radiobutton[2]->h)/2, m_ramki->m_radiobutton[2],screen );
             }
             else
             {
                 // Mouse On
                 apply_surface( m_rect.x, m_rect.y + (m_rect.h-m_ramki->m_radiobutton[1]->h)/2, m_ramki->m_radiobutton[1],screen );
             }
         }
     }
     else
     {
         if( m_ticked == true )
         {               // Ticked
             // Normal
             apply_surface( m_rect.x, m_rect.y + (m_rect.h-m_ramki->m_radiobutton[3]->h)/2, m_ramki->m_radiobutton[3],screen );
         }
         else
         {                // Unticked
             // Normal
             apply_surface( m_rect.x, m_rect.y + (m_rect.h-m_ramki->m_radiobutton[0]->h)/2, m_ramki->m_radiobutton[0],screen );
         }
         
     }
     
     apply_surface( m_rect.x +(m_ramki->m_checkbox[0]->w) + m_dist_img_txt, m_rect.y, m_textSquare,screen );
     //apply_surface( m_rect.x, m_rect.y + (m_rect.h-m_ramki->m_checkbox[0]->h)/2, m_ramki->m_checkbox[1],screen );
}

void CRadioButton::OnEvent(SDL_Event* Event)
{
    CEvent::OnEvent(Event);
}

void CRadioButton::OnMouseMove(int mX, int mY, int relX, int relY, bool Left,bool Right,bool Middle)
{
    if(  (mX > m_rect.x) && (mX < m_rect.x + m_rect.w) && (mY > m_rect.y) && (mY < m_rect.y + m_rect.h)  )
    {
         m_on_target = true;
    }
    else
    {
         m_on_target = false;
    }
    
    if( Left == true )
    {
        
    }
}

void CRadioButton::OnLButtonUp(int mX, int mY)
{
    if(  (m_on_target == true) && (m_clicked_focus == true)  )
    {
         // Klikniêcie
         switch( m_id )
         {
             case RBT_PvsP:
                  rbt_pVSp->set_ticked(true);
                  rbt_pVScom->set_ticked(false);
                  rbt_pVSp_online->set_ticked(false);
                  gametype = GT_PP;
                  break;
             case RBT_PvsCOM:
                  rbt_pVSp->set_ticked(false);
                  rbt_pVScom->set_ticked(true);
                  rbt_pVSp_online->set_ticked(false);
                  gametype = GT_PCOM;
                  break;
             case RBT_PvsP_ONLINE:
                  rbt_pVSp->set_ticked(false);
                  rbt_pVScom->set_ticked(false);
                  rbt_pVSp_online->set_ticked(true);
                  if( rbt_serwer->is_ticked() == true ) { gametype = GT_S; } else { gametype = GT_C; }
                  break;
             case RBT_SERVER:
                  rbt_serwer->set_ticked(true);
                  rbt_klient->set_ticked(false);
                  gametype = GT_S;
                  break;
             case RBT_CLIENT:
                  rbt_serwer->set_ticked(false);
                  rbt_klient->set_ticked(true);
                  gametype = GT_C;
                  break;
             default: break;
         }
         
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


//==============================================================================
//========================     C_LIST_BOX
//========================

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
    
    m_max_objects = 30;
    m_znacznik = 0;
    
    
    m_font = TTF_OpenFont( "font/tahoma.ttf", fontSize );
    if( m_font == NULL ) { /*MessageBox(NULL, "Could not load font", "Error", MB_OK);*/ this->~CListBox(); }
    m_font_color.r = 0x00;
    m_font_color.g = 0x00;
    m_font_color.b = 0x00;
    m_click_font_color.r = 0xFF;
    m_click_font_color.g = 0xFF;
    m_click_font_color.b = 0xFF;
    m_click_bg_color.r = 51;
    m_click_bg_color.g = 153;
    m_click_bg_color.b = 255;
    m_rama = load_image( "gfx/null.png" ); if( m_rama == NULL ) { this->~CListBox(); }
    m_plansza = load_image( "gfx/null.png" ); if( m_plansza == NULL ) { this->~CListBox(); }
    m_scroll_bg = load_image( "gfx/null.png" ); if( m_scroll_bg == NULL ) { this->~CListBox(); }
    
    m_height_elemntu = (TTF_RenderText_Blended( m_font, "Lol", m_font_color ))->h;
    
    m_rama_rect.x = 0;
    m_rama_rect.y = 0;
    m_rama_rect.w = width;
    m_rama_rect.h = height;
    
    m_obszar_plansza.x = m_ramki->m_border2[0]->w;
    m_obszar_plansza.y = m_ramki->m_border2[0]->h;
    m_obszar_plansza.w = width - m_ramki->m_border2[0]->w - m_ramki->m_border2[2]->w;
    m_obszar_plansza.h = height - m_ramki->m_border2[0]->h - m_ramki->m_border2[5]->h;
    
    m_scroll_rect.x = m_rama_rect.w - m_ramki->m_border2[0]->w - m_ramki->m_border_scroll[0]->w;
    m_scroll_rect.y = m_ramki->m_border2[0]->h;
    m_scroll_rect.w = m_ramki->m_border_scroll[0]->w;
    m_scroll_rect.h = m_rama_rect.h - m_ramki->m_border2[0]->h - m_ramki->m_border2[7]->h;
    
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
         apply_surface( m_scroll_rect.x, m_scroll_rect.y+i, m_ramki->m_border_scroll[17], m_scroll_bg );
    }
}


CListBox::~CListBox()
{
    SDL_FreeSurface( m_rama );
    SDL_FreeSurface( m_plansza );
    SDL_FreeSurface( m_scroll_bg );
    TTF_CloseFont( m_font );
}


void CListBox::show()
{
    SDL_FillRect( screen, &m_rect, SDL_MapRGB(screen->format, 0xFF, 0xFF, 0xFF) );
    
    
    apply_surface( m_rect.x +2, m_rect.y+2, m_plansza, screen, &m_obszar_plansza );
    
    apply_surface( m_rect.x, m_rect.y, m_rama,screen, &m_rama_rect );
    
    //ScrollBar
    if( m_duzo_obiektow == true )
    {
        apply_surface( m_rect.x + m_scroll_rect.x, m_rect.y + m_scroll_rect.y, m_scroll_bg, screen, &m_scroll_rect );
        
        apply_surface( m_rect.x + m_scroll_rect.x, m_rect.y + m_scroll_rect.y, m_ramki->m_border_scroll[0], screen );
        apply_surface( m_rect.x + m_scroll_rect.x, m_rect.y + m_ramki->m_border2[2]->h + m_scroll_rect.h - m_ramki->m_border_scroll[4]->h, m_ramki->m_border_scroll[4], screen );
        
        if( m_mouse_on_scroll == true )
        {
            //Mouse On
            apply_surface( m_rect.x + m_scroll_rect.x, m_rect.y + m_scroll_rect.y, m_ramki->m_border_scroll[1], screen );
            apply_surface( m_rect.x + m_scroll_rect.x, m_rect.y + m_ramki->m_border2[2]->h + m_scroll_rect.h - m_ramki->m_border_scroll[5]->h, m_ramki->m_border_scroll[5], screen );
            
            
            if( m_scroll_up_mouse == true )
            {
                apply_surface( m_rect.x + m_scroll_rect.x, m_rect.y + m_scroll_rect.y, m_ramki->m_border_scroll[2], screen );
            }
            if( m_scroll_down_mouse == true )
            {
                apply_surface( m_rect.x + m_scroll_rect.x, m_rect.y + m_ramki->m_border2[2]->h + m_scroll_rect.h - m_ramki->m_border_scroll[4]->h, m_ramki->m_border_scroll[6], screen );
            }
            
            //Pressed
            if( m_scroll_up_pressed == true )
            {
                apply_surface( m_rect.x + m_scroll_rect.x, m_rect.y + m_scroll_rect.y, m_ramki->m_border_scroll[3], screen );
            }
            /*if( m_scroll_updown_moved == true )
            {
                
            }*/
            if( m_scroll_down_pressed == true )
            {
                apply_surface( m_rect.x + m_scroll_rect.x, m_rect.y + m_ramki->m_border2[2]->h + m_scroll_rect.h - m_ramki->m_border_scroll[4]->h, m_ramki->m_border_scroll[7], screen );
            }
            
        }
        
    }
    else
    {
        
    }
}

void CListBox::dodaj( std::string napis )
{
    if( m_dane.size() > m_max_objects )
    {
        this->usun( m_max_objects );
    }
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
    //m_dane.erase( m_dane.begin() + index - 1 );
    int i = 0;
    for( std::list<std::string>::iterator iter = m_dane.begin(); iter != m_dane.end(); ++iter )
    {
         if( i+1 == index )
         {
             iter = m_dane.erase(iter);
             m_znacznik = 0;
             
         }
         i++;
    }
    //m_dane.clear();
    if( m_dane.size() * m_height_elemntu <= m_rect.h - m_ramki->m_border2[1]->h - m_ramki->m_border2[6]->h )
    {
        m_duzo_obiektow = false;
        m_obszar_plansza.w = m_rama_rect.w - m_ramki->m_border2[0]->w - m_ramki->m_border2[2]->w;
    }
    this->refresh_items();
}

void CListBox::usun_all()
{
     m_dane.clear();
     m_duzo_obiektow = false;
     this->refresh_items();
}

int CListBox::get_size()
{
    return m_dane.size();
}

void CListBox::refresh_items()
{
    if( m_dane.empty() == true )
    {
        SDL_FillRect( m_plansza, &m_obszar_plansza, SDL_MapRGB(screen->format, 0xFF, 0xFF, 0xFF) );
    }
    if( m_dane.empty() == false )
    {
        SDL_Rect zaz;
        zaz.x = m_obszar_plansza.x;
        zaz.y = m_obszar_plansza.y;
        zaz.w = m_obszar_plansza.w;
        zaz.h = m_height_elemntu;
        
        SDL_FillRect( m_plansza, &m_plansza->clip_rect, SDL_MapRGB(m_plansza->format, 0xFF, 0xFF, 0xFF) );
        int i = 0;
        for( std::list<std::string>::iterator iter = m_dane.begin(); iter != m_dane.end(); ++iter )
        {
             if( i+1 == m_znacznik )
             {
                 SDL_FillRect( m_plansza, &zaz, SDL_MapRGB(m_plansza->format, 51, 153, 255) );
                 apply_surface( 0+m_ramki->m_border2[0]->w, 0+m_ramki->m_border2[0]->h+m_height_elemntu*i, TTF_RenderText_Blended( m_font, (*iter).c_str(), m_click_font_color),m_plansza );
             }
             else
             {
                 apply_surface( 0+m_ramki->m_border2[0]->w, 0+m_ramki->m_border2[0]->h+m_height_elemntu*i, TTF_RenderText_Blended( m_font, (*iter).c_str(), m_font_color ),m_plansza );
             }
             zaz.y = 0+m_ramki->m_border2[0]->h+m_height_elemntu*(i+1);
             i++;
        }
    }
}

void CListBox::set_znacznik( int liczba )
{
    m_znacznik = liczba;
}

int CListBox::get_znacznik()
{
    return m_znacznik;
}

void CListBox::OnEvent(SDL_Event* Event)
{
    CEvent::OnEvent(Event);
}

void CListBox::OnMouseMove(int mX, int mY, int relX, int relY, bool Left,bool Right,bool Middle)
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

void CListBox::OnLButtonDown(int mX, int mY)
{
     // Zaznacznik
     if( m_mouse_on_plansza == true )
     {
         /* wzw;
         wzw.x = 
         wzw.y = m_obszar_plansza.y;
         wzw.w = m_obszar_plansza.w;
         wzw.h = m_height_elemntu;*/
         
         for( int i = 0; i < m_obszar_plansza.h / m_height_elemntu; i++ )
         {
              if(  (mX > m_rect.x + m_ramki->m_border2[3]->w) && (mX < m_rect.x + m_ramki->m_border2[3]->w + m_obszar_plansza.w) && (mY > m_rect.y + m_ramki->m_border2[1]->h + i*m_height_elemntu) && (mY < m_rect.y + m_ramki->m_border2[1]->h + (i+1)*m_height_elemntu)  )
              {
                   m_znacznik = 1+ i + (m_obszar_plansza.y) / m_height_elemntu;
                   if( m_znacznik > m_dane.size() ) { m_znacznik = m_dane.size(); }
                   //this->set_znacznik( m_znacznik );
                   //char buffer[50];
                   //sprintf( buffer, "i = %d", m_znacznik);
                   //SDL_WM_SetCaption( buffer, NULL ); 
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
             if( m_obszar_plansza.y <= m_ramki->m_border2[0]->h ) { m_obszar_plansza.y = m_ramki->m_border2[0]->h; }
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
     //this->dodaj("string");
}

void CListBox::OnLButtonUp(int mX, int mY)
{
    m_scroll_focus = false;
    m_scroll_up_pressed = false;
    m_scroll_down_pressed = false;
}

void CListBox::OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode)
{
     //this->usun(m_znacznik);
}


