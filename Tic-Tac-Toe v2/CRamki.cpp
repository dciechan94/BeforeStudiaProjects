#include "CRamki.h"

CRamki::CRamki()
{
    for( int i = 0; i < 6; i++ )
    {
         m_checkbox[i] = NULL;
         m_radiobutton[i] = NULL;
    }
    for( int i = 0; i < 8; i++ )
    {
         m_border2[i] = NULL;
    }
    for( int i = 0; i < 9; i++ )
    {
         m_button_std[i] = NULL;
    }
    for( int i = 0; i < 18; i++ )
    {
         m_border_scroll[i] = NULL;
    }
    for( int i = 0; i < 24; i++ )
    {
         m_border_std[i] = NULL;
    }
    for( int i = 0; i < 30; i++ )
    {
         m_button[i] = NULL;
    }
    m_adresGrafik = "gfx";
}

CRamki::~CRamki()
{
    for( int i = 0; i < 6; i++ )
    {
         SDL_FreeSurface( m_checkbox[i] );
         SDL_FreeSurface( m_radiobutton[i] );
    }
    for( int i = 0; i < 8; i++ )
    {
         SDL_FreeSurface( m_border2[i] );
    }
    for( int i = 0; i < 9; i++ )
    {
         SDL_FreeSurface( m_button_std[i] );
    }
    for( int i = 0; i < 18; i++ )
    {
         SDL_FreeSurface( m_border_scroll[i] );
    }
    for( int i = 0; i < 24; i++ )
    {
         SDL_FreeSurface( m_border_std[i] );
    }
    for( int i = 0; i < 30; i++ )
    {
         SDL_FreeSurface( m_button[i] );
    }
}

SDL_Surface* CRamki::load_image( std::string filename )
{
    SDL_Surface* loadedImage = NULL;
    SDL_Surface* optimizedImage = NULL;
    
    loadedImage = IMG_Load( filename.c_str() );
    
    if( loadedImage != NULL )
    {
        optimizedImage = SDL_DisplayFormat( loadedImage );
        
        SDL_FreeSurface( loadedImage );
        
        if( optimizedImage != NULL )
        {
            Uint32 colorkey = SDL_MapRGB( optimizedImage->format, 0, 0xFF, 0xFF );
            SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, colorkey );
        }
    }
    return optimizedImage;
}

bool CRamki::laduj_ramki()
{
    m_checkbox[0] = CRamki::load_image( m_adresGrafik + "/check_box/check_null_out.png" );
    if( m_checkbox[0] == NULL ) { MessageBox(NULL,"heh","heh2",MB_OK);return false; }
    m_checkbox[1] = CRamki::load_image( m_adresGrafik + "/check_box/check_null_over.png" );
    if( m_checkbox[1] == NULL ) { return false; }
    m_checkbox[2] = CRamki::load_image( m_adresGrafik + "/check_box/check_null_click.png" );
    if( m_checkbox[2] == NULL ) { return false; }
    m_checkbox[3] = CRamki::load_image( m_adresGrafik + "/check_box/check_tick_out.png" );
    if( m_checkbox[3] == NULL ) { return false; }
    m_checkbox[4] = CRamki::load_image( m_adresGrafik + "/check_box/check_tick_over.png" );
    if( m_checkbox[4] == NULL ) { return false; }
    m_checkbox[5] = CRamki::load_image( m_adresGrafik + "/check_box/check_tick_click.png" );
    if( m_checkbox[5] == NULL ) { return false; }
    
    
    m_button_std[0] = CRamki::load_image( m_adresGrafik + "/button_std/unactive_left.png" );
    if( m_button_std[0] == NULL ) { MessageBox(NULL,"heh","heh2",MB_OK);return false; }
    m_button_std[1] = CRamki::load_image( m_adresGrafik + "/button_std/unactive_center.png" );
    if( m_button_std[1] == NULL ) { return false; }
    m_button_std[2] = CRamki::load_image( m_adresGrafik + "/button_std/unactive_right.png" );
    if( m_button_std[2] == NULL ) { return false; }
    m_button_std[3] = CRamki::load_image( m_adresGrafik + "/button_std/mouse_left.png" );
    if( m_button_std[3] == NULL ) { return false; }
    m_button_std[4] = CRamki::load_image( m_adresGrafik + "/button_std/mouse_center.png" );
    if( m_button_std[4] == NULL ) { return false; }
    m_button_std[5] = CRamki::load_image( m_adresGrafik + "/button_std/mouse_right.png" );
    if( m_button_std[5] == NULL ) { return false; }
    m_button_std[6] = CRamki::load_image( m_adresGrafik + "/button_std/click_left.png" );
    if( m_button_std[6] == NULL ) { return false; }
    m_button_std[7] = CRamki::load_image( m_adresGrafik + "/button_std/click_center.png" );
    if( m_button_std[7] == NULL ) { return false; }
    m_button_std[8] = CRamki::load_image( m_adresGrafik + "/button_std/click_right.png" );
    if( m_button_std[8] == NULL ) { return false; }
    
    
    m_radiobutton[0] = CRamki::load_image( m_adresGrafik + "/radio_button/null_unactive.png" );
    if( m_radiobutton[0] == NULL ) { MessageBox(NULL,"heh","heh3",MB_OK);return false; }
    m_radiobutton[1] = CRamki::load_image( m_adresGrafik + "/radio_button/null_mouse.png" );
    if( m_radiobutton[1] == NULL ) { return false; }
    m_radiobutton[2] = CRamki::load_image( m_adresGrafik + "/radio_button/null_click.png" );
    if( m_radiobutton[2] == NULL ) { return false; }
    m_radiobutton[3] = CRamki::load_image( m_adresGrafik + "/radio_button/tick_unactive.png" );
    if( m_radiobutton[3] == NULL ) { return false; }
    m_radiobutton[4] = CRamki::load_image( m_adresGrafik + "/radio_button/tick_mouse.png" );
    if( m_radiobutton[4] == NULL ) { return false; }
    m_radiobutton[5] = CRamki::load_image( m_adresGrafik + "/radio_button/tick_click.png" );
    if( m_radiobutton[5] == NULL ) { return false; }
    
    
    m_border_std[0] = CRamki::load_image( m_adresGrafik + "/border/unactive_left_top.png" );
    if( m_border_std[0] == NULL ) { MessageBox(NULL,"heh","heh4",MB_OK);return false; }
    m_border_std[1] = CRamki::load_image( m_adresGrafik + "/border/unactive_up.png" );
    if( m_border_std[1] == NULL ) { return false; }
    m_border_std[2] = CRamki::load_image( m_adresGrafik + "/border/unactive_right_top.png" );
    if( m_border_std[2] == NULL ) { return false; }
    m_border_std[3] = CRamki::load_image( m_adresGrafik + "/border/unactive_left.png" );
    if( m_border_std[3] == NULL ) { return false; }
    m_border_std[4] = CRamki::load_image( m_adresGrafik + "/border/unactive_right.png" );
    if( m_border_std[4] == NULL ) { return false; }
    m_border_std[5] = CRamki::load_image( m_adresGrafik + "/border/unactive_left_bottom.png" );
    if( m_border_std[5] == NULL ) { return false; }
    m_border_std[6] = CRamki::load_image( m_adresGrafik + "/border/unactive_down.png" );
    if( m_border_std[6] == NULL ) { return false; }
    m_border_std[7] = CRamki::load_image( m_adresGrafik + "/border/unactive_right_bottom.png" );
    if( m_border_std[7] == NULL ) { return false; }
    m_border_std[8] = CRamki::load_image( m_adresGrafik + "/border/mouse_left_top.png" );
    if( m_border_std[8] == NULL ) { return false; }
    m_border_std[9] = CRamki::load_image( m_adresGrafik + "/border/mouse_up.png" );
    if( m_border_std[9] == NULL ) { return false; }
    m_border_std[10] = CRamki::load_image( m_adresGrafik + "/border/mouse_right_top.png" );
    if( m_border_std[10] == NULL ) { return false; }
    m_border_std[11] = CRamki::load_image( m_adresGrafik + "/border/mouse_left.png" );
    if( m_border_std[11] == NULL ) { return false; }
    m_border_std[12] = CRamki::load_image( m_adresGrafik + "/border/mouse_right.png" );
    if( m_border_std[12] == NULL ) { return false; }
    m_border_std[13] = CRamki::load_image( m_adresGrafik + "/border/mouse_left_bottom.png" );
    if( m_border_std[13] == NULL ) { return false; }
    m_border_std[14] = CRamki::load_image( m_adresGrafik + "/border/mouse_down.png" );
    if( m_border_std[14] == NULL ) { return false; }
    m_border_std[15] = CRamki::load_image( m_adresGrafik + "/border/mouse_right_bottom.png" );
    if( m_border_std[15] == NULL ) { return false; }
    m_border_std[16] = CRamki::load_image( m_adresGrafik + "/border/active_left_top.png" );
    if( m_border_std[16] == NULL ) { return false; }
    m_border_std[17] = CRamki::load_image( m_adresGrafik + "/border/active_up.png" );
    if( m_border_std[17] == NULL ) { return false; }
    m_border_std[18] = CRamki::load_image( m_adresGrafik + "/border/active_right_top.png" );
    if( m_border_std[18] == NULL ) { return false; }
    m_border_std[19] = CRamki::load_image( m_adresGrafik + "/border/active_left.png" );
    if( m_border_std[19] == NULL ) { return false; }
    m_border_std[20] = CRamki::load_image( m_adresGrafik + "/border/active_right.png" );
    if( m_border_std[20] == NULL ) { return false; }
    m_border_std[21] = CRamki::load_image( m_adresGrafik + "/border/active_left_bottom.png" );
    if( m_border_std[21] == NULL ) { return false; }
    m_border_std[22] = CRamki::load_image( m_adresGrafik + "/border/active_down.png" );
    if( m_border_std[22] == NULL ) { return false; }
    m_border_std[23] = CRamki::load_image( m_adresGrafik + "/border/active_right_bottom.png" );
    if( m_border_std[23] == NULL ) { return false; }
    
    
    m_border2[0] = CRamki::load_image( m_adresGrafik + "/border2/left_top.png" );
    if( m_border2[0] == NULL ) { MessageBox(NULL,"heh","heh5",MB_OK);return false; }
    m_border2[1] = CRamki::load_image( m_adresGrafik + "/border2/up.png" );
    if( m_border2[1] == NULL ) { return false; }
    m_border2[2] = CRamki::load_image( m_adresGrafik + "/border2/right_top.png" );
    if( m_border2[2] == NULL ) { return false; }
    m_border2[3] = CRamki::load_image( m_adresGrafik + "/border2/left.png" );
    if( m_border2[3] == NULL ) { return false; }
    m_border2[4] = CRamki::load_image( m_adresGrafik + "/border2/right.png" );
    if( m_border2[4] == NULL ) { return false; }
    m_border2[5] = CRamki::load_image( m_adresGrafik + "/border2/left_bottom.png" );
    if( m_border2[5] == NULL ) { return false; }
    m_border2[6] = CRamki::load_image( m_adresGrafik + "/border2/down.png" );
    if( m_border2[6] == NULL ) { return false; }
    m_border2[7] = CRamki::load_image( m_adresGrafik + "/border2/right_bottom.png" );
    if( m_border2[7] == NULL ) { return false; }
    
    
    m_border_scroll[0] = CRamki::load_image( m_adresGrafik + "/scroll_bar/up_unactive.png" );
    if( m_border_scroll[0] == NULL ) { return false; }
    m_border_scroll[1] = CRamki::load_image( m_adresGrafik + "/scroll_bar/up_mouse_on_object.png" );
    if( m_border_scroll[1] == NULL ) { return false; }
    m_border_scroll[2] = CRamki::load_image( m_adresGrafik + "/scroll_bar/up_active.png" );
    if( m_border_scroll[2] == NULL ) { return false; }
    m_border_scroll[3] = CRamki::load_image( m_adresGrafik + "/scroll_bar/up_pressed.png" );
    if( m_border_scroll[3] == NULL ) { return false; }
    m_border_scroll[4] = CRamki::load_image( m_adresGrafik + "/scroll_bar/down_unactive.png" );
    if( m_border_scroll[4] == NULL ) { return false; }
    m_border_scroll[5] = CRamki::load_image( m_adresGrafik + "/scroll_bar/down_mouse_on_object.png" );
    if( m_border_scroll[5] == NULL ) { return false; }
    m_border_scroll[6] = CRamki::load_image( m_adresGrafik + "/scroll_bar/down_active.png" );
    if( m_border_scroll[6] == NULL ) { return false; }
    m_border_scroll[7] = CRamki::load_image( m_adresGrafik + "/scroll_bar/down_pressed.png" );
    if( m_border_scroll[7] == NULL ) { return false; }
    m_border_scroll[8] = CRamki::load_image( m_adresGrafik + "/scroll_bar/updown_up_mouse_on_object.png" );
    if( m_border_scroll[8] == NULL ) { return false; }
    m_border_scroll[9] = CRamki::load_image( m_adresGrafik + "/scroll_bar/updown_up_pressed.png" );
    if( m_border_scroll[9] == NULL ) { return false; }
    m_border_scroll[10] = CRamki::load_image( m_adresGrafik + "/scroll_bar/updown_up_moved.png" );
    if( m_border_scroll[10] == NULL ) { return false; }
    m_border_scroll[11] = CRamki::load_image( m_adresGrafik + "/scroll_bar/updown_center_mouse_on_object.png" );
    if( m_border_scroll[11] == NULL ) { return false; }
    m_border_scroll[12] = CRamki::load_image( m_adresGrafik + "/scroll_bar/updown_center_pressed.png" );
    if( m_border_scroll[12] == NULL ) { return false; }
    m_border_scroll[13] = CRamki::load_image( m_adresGrafik + "/scroll_bar/updown_center_moved.png" );
    if( m_border_scroll[13] == NULL ) { return false; }
    m_border_scroll[14] = CRamki::load_image( m_adresGrafik + "/scroll_bar/updown_down_mouse_on_object.png" );
    if( m_border_scroll[14] == NULL ) { return false; }
    m_border_scroll[15] = CRamki::load_image( m_adresGrafik + "/scroll_bar/updown_down_pressed.png" );
    if( m_border_scroll[15] == NULL ) { return false; }
    m_border_scroll[16] = CRamki::load_image( m_adresGrafik + "/scroll_bar/updown_down_moved.png" );
    if( m_border_scroll[16] == NULL ) { return false; }
    m_border_scroll[17] = CRamki::load_image( m_adresGrafik + "/scroll_bar/bg_updown.png" );
    if( m_border_scroll[17] == NULL ) { return false; }
    
    
    //m_radiobutton[0] = CRamki::load_image( m_adresGrafik + "/radio_button/check_tick_out.png" );
    return true;
    
}

/*void CRamki::show()
{
     apply_surface( 1,1,m_checkbox[0],screen);
     }*/
