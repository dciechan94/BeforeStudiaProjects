#include "CMenu.h"


CMenu::CMenu()
{
     m_nowagra_box.x = 108;
     m_nowagra_box.y = 260;
     m_nowagra_box.w = 238;
     m_nowagra_box.h = 52;
     
     m_opcje_box.x = 150;
     m_opcje_box.y = 317;
     m_opcje_box.w = 143;
     m_opcje_box.h = 50;
     
     m_wyjscie_box.x = 490;
     m_wyjscie_box.y = 450;
     m_wyjscie_box.w = 180;
     m_wyjscie_box.h = 50;
     
     m_nowagra = false;
     m_opcje = false;
     m_wyjscie = false;
     
     m_znacznik = NULL;
}

CMenu::~CMenu()
{
     SDL_FreeSurface( m_znacznik );
}

void CMenu::init()
{
     m_znacznik = load_image( "gfx/znacznik2.png" );
}

void CMenu::handle_events()
{
     mouse_x = event.button.x;
     mouse_y = event.button.y;
     if( ( mouse_x > m_nowagra_box.x ) && ( mouse_x < m_nowagra_box.x + m_nowagra_box.w ) && ( mouse_y > m_nowagra_box.y ) && ( mouse_y < m_nowagra_box.y + m_nowagra_box.h ) )
     {
          m_nowagra = true;
     } else { m_nowagra = false; }
     if( ( mouse_x > m_opcje_box.x ) && ( mouse_x < m_opcje_box.x + m_opcje_box.w ) && ( mouse_y > m_opcje_box.y ) && ( mouse_y < m_opcje_box.y + m_opcje_box.h ) )
     {
          m_opcje = true;
     } else { m_opcje = false; }
     if( ( mouse_x > m_wyjscie_box.x ) && ( mouse_x < m_wyjscie_box.x + m_wyjscie_box.w ) && ( mouse_y > m_wyjscie_box.y ) && ( mouse_y < m_wyjscie_box.y + m_wyjscie_box.h ) )
     {
          m_wyjscie = true;
     } else { m_wyjscie = false; }
     
     if( (event.button.button == SDL_BUTTON_LEFT) && (m_wyjscie==true) )
     {
         quit = true;
     }
     if( (event.button.button == SDL_BUTTON_LEFT) && (m_nowagra==true) )
     {
         gamestate = GS_PLAY;
     }
}

void CMenu::show()
{
     if( m_nowagra == true )
     {
         apply_surface( 0, 0, m_znacznik, screen );
     }

}
