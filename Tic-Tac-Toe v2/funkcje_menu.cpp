#include "funkcje_menu.h"

void obsluga_menu_glowne() // MENU
{
     while(  (program_quit_flag == false) && (proces_gry == PID_MENU_GLOWNE)  )
     {
         while( SDL_PollEvent(&event) )
         {
              if( event.type == SDL_KEYDOWN )
              {

              }
              // CONTROLS
              rbt_pVSp->OnEvent(&event);
              rbt_pVScom->OnEvent(&event);
              rbt_pVSp_online->OnEvent(&event);
              
              if( rbt_pVSp_online->is_ticked() == true )
              {
                  rbt_serwer->OnEvent(&event);
                  rbt_klient->OnEvent(&event);
                  btnStd_Disconnect->OnEvent(&event);
             
                  if( rbt_klient->is_ticked() == true )
                  {
                      btnStd_TryConnectToSerwer->OnEvent(&event);
                      editB_client_ip->OnEvent(&event);
                  }
              }
              else 
              {
                  btnStd_StartGame->OnEvent(&event);
              }
              //  END OF CONTROLD
              
              if( event.type == SDL_QUIT ) { program_quit_flag = true; }
              //pop.handle_events();
         }
           
         // Logic

         //Show
         SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 236, 233, 216 ) );
         apply_surface( 30, 30, menu_ply, screen );
         
         label_opcje->show();
         label_tryb_gry->show();
         
         
         
         if( rbt_pVSp_online->is_ticked() == true )
         {
             rbt_serwer->show();
             rbt_klient->show();
             btnStd_Disconnect->show();
             label_opcje_online->show();
             
             if( rbt_klient->is_ticked() == true )
             {
                 btnStd_TryConnectToSerwer->show();
                 editB_client_ip->show();
                 label_ip->show();
             }
         }
         else 
         {
             btnStd_StartGame->show();
         }
         
         rbt_pVSp->show();
         rbt_pVScom->show();
         rbt_pVSp_online->show();
         

         
         if( SDL_Flip( screen ) == -1 ) { MessageBox(NULL,"Flip Problem","Error", MB_OK); program_quit_flag = false; }
         //if( fps->get_ticks() < 1000 / FRAMES_PER_SECOND ) { SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - fps.get_ticks() ); }
    }
     
}

//==============================================================================
//==============================================================================
//==============================================================================


void rozgrywka() // ROZGRYWKA
{
     if( ( program_quit_flag == false ) && ( proces_gry == PID_ROZGRYWKA )  )
     {
         while( ( program_quit_flag == false ) && ( proces_gry == PID_ROZGRYWKA )  )
         {
             for( int a = 0; a < 3; a++ )
             {
                  for( int a2 = 0; a2 < 3; a2++ )
                  {
                       plansza[a][a2] = GP_NONE;
                  }
             }
             
             if ( gametype == GT_PP ) { rozgrywka_PvsP(); }
             if ( gametype == GT_PCOM ) { rozgrywka_PvsCOM(); }
             //if ( gametype == GT_S ) { rozgrywka_PvsP_S(); }
             //if ( gametype == GT_C ) { rozgrywka_PvsP_C(); }
         }
        
     }
     
}

//==============================================================================
//==============================================================================
//==============================================================================

void rozgrywka_PvsP()
{
    koniec_gry = false;
    wygrany = GP_NONE;
    if( gracz == GP_NONE ){ gracz = GP_X; SDL_WM_SetCaption( "Tic-Tac-Toe: Player X", NULL ); }
    if( gracz == GP_X ){ gracz = GP_O; SDL_WM_SetCaption( "Tic-Tac-Toe: Player O", NULL ); } else{ gracz = GP_X; SDL_WM_SetCaption( "Tic-Tac-Toe: Player X", NULL ); }
    
    while(  ( program_quit_flag == false ) && ( koniec_gry == false) && ( proces_gry == PID_ROZGRYWKA ) )
    {
         while( SDL_PollEvent(&event) )
         {
              if( event.type == SDL_MOUSEBUTTONUP )
              {
                  if( event.button.button == SDL_BUTTON_LEFT )
                  {
                      int mouse_x = event.button.x;
                      int mouse_y = event.button.y;
                      
                      if( (mouse_x > 30) && (mouse_x < 570) && (mouse_y > 30) && (mouse_y < 570) )
                      {
                          look_for_click( mouse_x, mouse_y );
                      }
                  }
              }
              // CONTROLS
              btnStd_KoniecGry->OnEvent(&event);
              //  END OF CONTROLD
              
              if( event.type == SDL_QUIT ) { program_quit_flag = true; }
         }
           
         // Logic
         check_zasadyGry();
         
         //Show
         SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 236, 233, 216 ) );
         apply_surface( 30, 30, playground_surface, screen );
         
         label_opcje->show();
         
         btnStd_KoniecGry->show();
         
         redraw_sur();
         
         if( SDL_Flip( screen ) == -1 ) { MessageBox(NULL,"Flip Problem","Error", MB_OK); program_quit_flag = false; }
         
         if( wygrany != GP_NONE )
         {
             SDL_WM_SetCaption( "Tic-Tac-Toe", NULL );
             if( wygrany == GP_X )
             {
                 MessageBox(NULL,"Player X won the game.","Congratulation!", MB_OK);
             }
             if( wygrany == GP_O )
             {
                 MessageBox(NULL,"Player O won the game.","Congratulation!", MB_OK);
             }
             if( wygrany == GP_REMIS )
             {
                 MessageBox(NULL,"Draw","The end!", MB_OK);
             }
             koniec_gry = true;
             proces_gry = PID_MENU_GLOWNE;
         }
         //if( fps.get_ticks() < 1000 / FRAMES_PER_SECOND ) { SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - fps.get_ticks() ); } 
    } 
}

//==============================================================================
//==============================================================================
//==============================================================================

void rozgrywka_PvsCOM()
{
    koniec_gry = false;
    wygrany = GP_NONE;
    
    switch(rand() % 2)
    {
        case 0: computerP = GP_X; gracz = GP_O; break;
        case 1: computerP = GP_O; gracz = GP_X; break;
        default: computerP = GP_O; gracz = GP_X; break;
    }
    
    if( computerP == GP_O )
    {
        comp_move( computerP );
    }
    
    while(  ( program_quit_flag == false ) && ( koniec_gry == false) && ( proces_gry == PID_ROZGRYWKA ) )
    {
         while( SDL_PollEvent(&event) )
         {
              if( event.type == SDL_MOUSEBUTTONUP )
              {
                  if( event.button.button == SDL_BUTTON_LEFT )
                  {
                      int mouse_x = event.button.x;
                      int mouse_y = event.button.y;
                      
                      if( (mouse_x > 30) && (mouse_x < 570) && (mouse_y > 30) && (mouse_y < 570) )
                      {
                          look_for_click( mouse_x, mouse_y );
                      }
                  }
              }
              // CONTROLS
              btnStd_KoniecGry->OnEvent(&event);
              //  END OF CONTROLD
              
              if( event.type == SDL_QUIT ) { program_quit_flag = true; }
         }
           
         // Logic
         check_zasadyGry();
         
         //Show
         SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 236, 233, 216 ) );
         apply_surface( 30, 30, playground_surface, screen );
         
         label_opcje->show();
         
         btnStd_KoniecGry->show();
         
         redraw_sur();
         
         if( SDL_Flip( screen ) == -1 ) { MessageBox(NULL,"Flip Problem","Error", MB_OK); program_quit_flag = false; }
         
         if( wygrany != GP_NONE )
         {
             SDL_WM_SetCaption( "Tic-Tac-Toe", NULL );
             if( wygrany == GP_X )
             {
                 MessageBox(NULL,"Player X won the game.","Congratulation!", MB_OK);
             }
             if( wygrany == GP_O )
             {
                 MessageBox(NULL,"Player O won the game.","Congratulation!", MB_OK);
             }
             if( wygrany == GP_REMIS )
             {
                 MessageBox(NULL,"Draw","The end!", MB_OK);
             }
             koniec_gry = true;
             proces_gry = PID_MENU_GLOWNE;
         }
         //if( fps.get_ticks() < 1000 / FRAMES_PER_SECOND ) { SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - fps.get_ticks() ); } 
    } 
}

void look_for_click( int mouse_x, int mouse_y )
{
    for( int i = 0; i < 3; i++ )
    {
        for( int j = 0; j < 3; j++ )
        {
            if( (mouse_x > 30+i*180) && (mouse_x < 30+(i+1)*180) && (mouse_y > 30+j*180) && (mouse_y < 30+(j+1)*180) )
            {
                if( plansza[i][j] == GP_NONE )
                {
                    plansza[i][j] = gracz;
         
                    if( gracz == GP_X ) 
                    { 
                        if( gametype == GT_PP )
                        {
                            gracz = GP_O; 
                            SDL_WM_SetCaption( "Tic-Tac-Toe: Player O", NULL ); 
                        }
                        else
                        {
                            SDL_WM_SetCaption( "Tic-Tac-Toe: Computer", NULL ); 
                            comp_move( computerP );
                        }
                    } 
                    else 
                    { 
                        if( gametype == GT_PP )
                        {
                            gracz = GP_X; 
                            SDL_WM_SetCaption( "Tic-Tac-Toe: Player X", NULL ); 
                        }
                        else
                        {
                            SDL_WM_SetCaption( "Tic-Tac-Toe: Computer", NULL );
                            comp_move( computerP ); 
                        }
                    }
                }
            }
        }
    }

}

void check_zasadyGry()
{
    bool full = true;
    
    for( int i = 0; i < 3; i++ )
    {
        for( int j = 0; j < 3; j++ )
        {
            if( plansza[i][j] == GP_NONE )
            {
                full = false;
            }
        }
    }
    if( full == true ) { wygrany = GP_REMIS; }
     
    if( (plansza[0][0] == GP_X) && (plansza[0][1] == GP_X) && (plansza[0][2] == GP_X) ) { wygrany = GP_X; }
    if( (plansza[1][0] == GP_X) && (plansza[1][1] == GP_X) && (plansza[1][2] == GP_X) ) { wygrany = GP_X; }
    if( (plansza[2][0] == GP_X) && (plansza[2][1] == GP_X) && (plansza[2][2] == GP_X) ) { wygrany = GP_X; }
    if( (plansza[0][0] == GP_X) && (plansza[1][0] == GP_X) && (plansza[2][0] == GP_X) ) { wygrany = GP_X; }
    if( (plansza[0][1] == GP_X) && (plansza[1][1] == GP_X) && (plansza[2][1] == GP_X) ) { wygrany = GP_X; }
    if( (plansza[0][2] == GP_X) && (plansza[1][2] == GP_X) && (plansza[2][2] == GP_X) ) { wygrany = GP_X; }
    if( (plansza[0][0] == GP_X) && (plansza[1][1] == GP_X) && (plansza[2][2] == GP_X) ) { wygrany = GP_X; }
    if( (plansza[0][2] == GP_X) && (plansza[1][1] == GP_X) && (plansza[2][0] == GP_X) ) { wygrany = GP_X; }
    
    if( (plansza[0][0] == GP_O) && (plansza[0][1] == GP_O) && (plansza[0][2] == GP_O) ) { wygrany = GP_O; }
    if( (plansza[1][0] == GP_O) && (plansza[1][1] == GP_O) && (plansza[1][2] == GP_O) ) { wygrany = GP_O; }
    if( (plansza[2][0] == GP_O) && (plansza[2][1] == GP_O) && (plansza[2][2] == GP_O) ) { wygrany = GP_O; }
    if( (plansza[0][0] == GP_O) && (plansza[1][0] == GP_O) && (plansza[2][0] == GP_O) ) { wygrany = GP_O; }
    if( (plansza[0][1] == GP_O) && (plansza[1][1] == GP_O) && (plansza[2][1] == GP_O) ) { wygrany = GP_O; }
    if( (plansza[0][2] == GP_O) && (plansza[1][2] == GP_O) && (plansza[2][2] == GP_O) ) { wygrany = GP_O; } 
    if( (plansza[0][0] == GP_O) && (plansza[1][1] == GP_O) && (plansza[2][2] == GP_O) ) { wygrany = GP_O; }
    if( (plansza[0][2] == GP_O) && (plansza[1][1] == GP_O) && (plansza[2][0] == GP_O) ) { wygrany = GP_O; }
     
     
}

void redraw_sur()
{
    for( int i = 0; i < 3; i++ )
    {
        for( int j = 0; j < 3; j++ )
        {
            if( plansza[i][j] != GP_NONE )
            {
                if( plansza[i][j] == GP_X )
                {
                    apply_surface( 10+i*180 +30, 10+j*180+30, x_surface, screen);
                } 
                else 
                { 
                    apply_surface( 10+i*180+30, 10+j*180+30, o_surface, screen);
                }
            }
        }
    }
}

void comp_move( GRACZ_PLAYER sign )
{
     bool ruch = true;
     
     while( ruch )
     {
         switch( rand() % 9 )
         {
             case 0: if( plansza[0][0] == GP_NONE ) { plansza[0][0] = sign; ruch = false; } break;
             case 1: if( plansza[0][1] == GP_NONE ) { plansza[0][1] = sign; ruch = false; } break;
             case 2: if( plansza[0][2] == GP_NONE ) { plansza[0][2] = sign; ruch = false; } break;
             case 3: if( plansza[1][0] == GP_NONE ) { plansza[1][0] = sign; ruch = false; } break;
             case 4: if( plansza[1][1] == GP_NONE ) { plansza[1][1] = sign; ruch = false; } break;
             case 5: if( plansza[1][2] == GP_NONE ) { plansza[1][2] = sign; ruch = false; } break;
             case 6: if( plansza[2][0] == GP_NONE ) { plansza[2][0] = sign; ruch = false; } break;
             case 7: if( plansza[2][1] == GP_NONE ) { plansza[2][1] = sign; ruch = false; } break;
             case 8: if( plansza[2][2] == GP_NONE ) { plansza[2][2] = sign; ruch = false; } break;
         }
     }
     SDL_WM_SetCaption( "Tic-Tac-Toe: Player", NULL ); 
}
