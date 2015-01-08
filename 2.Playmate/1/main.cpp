#include "globals.h"
#include "funkcje.h"
#include "CMenu.h"
#include "time.h"


int main( int argc, char* args[] )
{
    
    // Szukaj b³êdów
    if( init_SDL() == false ) { MessageBox (0, "Blad krytyczny", "Error",MB_ICONHAND ); return 1; }
    if( load_files() == false ){ MessageBox (0, "Nie mozna zaladowac plikow", "Error",MB_ICONHAND ); return 1; }
    
    srand ( time(NULL) );
    gamestate = GS_PLAY;
    Sleep(200);
    fps.start();
    CMenu menu;
    menu.init();
    th_downtimer = SDL_CreateThread( th_downtimer_f, NULL ); 
    
    for( int i = 0; i < 17; i++ )
    {
         for( int j = 0; j < 10; j++ )
         {
              plansza[i][j] = 0;
         }
    }
    
    while( quit == false )
    {
    //==========================================================================
        
        while(  (quit == false) && (gamestate == GS_INTRO) )
        {
              while( SDL_PollEvent( &event ) )
              {
                     if( event.type == SDL_KEYDOWN )
                     {
                         if( (event.key.keysym.sym == SDLK_RETURN) || (event.key.keysym.sym == SDLK_SPACE) ) { gamestate = GS_MENU; }
                     }
                     if( event.type == SDL_QUIT ) { quit = true; }
              }
              // Logic
              SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0x00, 0x00, 0x00 ) );
              
              if( (intro_alpha < SDL_ALPHA_OPAQUE-15) && (intro_fadein == true) ) { intro_alpha = intro_alpha+5; }
              if( (intro_alpha <= SDL_ALPHA_OPAQUE) && (intro_fadein == false) ) { intro_alpha = intro_alpha-5; }
              if( intro_alpha >= SDL_ALPHA_OPAQUE-15 ) { intro_fadein = false; Sleep(1500); }
              if( intro_alpha <= SDL_ALPHA_TRANSPARENT ) { gamestate = GS_MENU; }
              
              SDL_SetAlpha( juzio_producion_presents, SDL_SRCALPHA, intro_alpha );
              
              //Show
              apply_surface( 0, 0, juzio_producion_presents, screen );
              
              if( SDL_Flip( screen ) == -1 ) { return 1; }
              if( fps.get_ticks() < 1000 / FRAMES_PER_SECOND ) { SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - fps.get_ticks() ); }
        }
        
        
        //======================================================================
        //======================================================================
        //======================================================================
        while(  (quit == false) && (gamestate == GS_MENU) )
        {
              
              while( SDL_PollEvent( &event ) )
              {
                     menu.handle_events();
                     if( event.type == SDL_KEYDOWN )
                     {
                         //if( (event.key.keysym.sym == SDLK_RETURN) || (event.key.keysym.sym == SDLK_SPACE) ) { gamestate = GS_MENU; }
                     }
                     if( event.type == SDL_QUIT ) { quit = true; }
              }
              
              //SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0xFF, 0xFF, 0xFF ) );
              apply_surface( 0, 0, menu_tlo, screen );
              apply_surface( 0, 0, papirus, screen );
              menu.show();
              if( SDL_Flip( screen ) == -1 ) { return 1; }
              if( fps.get_ticks() < 1000 / FRAMES_PER_SECOND ) { SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - fps.get_ticks() ); }
        }
        
        
        //======================================================================
        //======================================================================
        //======================================================================
        while(  (quit == false) && (gamestate == GS_PLAY) )
        {
              
              while( SDL_PollEvent( &event ) )
              {
                     
                     if( event.type == SDL_KEYDOWN )
                     {
                         if( event.key.keysym.sym == SDLK_LEFT) 
                         { 
                             if( (klocek_tabx != 0) && (plansza[klocek_taby][klocek_tabx-1] != 1))
                             {
                                 klocek_tabx = klocek_tabx - 1;
                                 plansza[klocek_taby][klocek_tabx] = 1;
                                 plansza[klocek_taby][klocek_tabx+1] = 0;
                             }
                         }
                         if( event.key.keysym.sym == SDLK_RIGHT) 
                         { 
                             if( (klocek_tabx != 9) && (plansza[klocek_taby][klocek_tabx+1] != 1) )
                             {
                                 klocek_tabx = klocek_tabx + 1;
                                 plansza[klocek_taby][klocek_tabx] = 1;
                                 plansza[klocek_taby][klocek_tabx-1] = 0;
                             }
                         }
                         if( event.key.keysym.sym == SDLK_DOWN) 
                         { 
                             if( plansza[klocek_taby+1][klocek_tabx] != 1 )
                             {
                                 klocek_taby++;
                                 plansza[klocek_taby][klocek_tabx] = 1;
                                 plansza[klocek_taby-1][klocek_tabx] = 0;
                             }
                             else
                             {
                                 plansza[klocek_taby][klocek_tabx] = 1;
                                 block_in_table = false;
                             }
                         }
                         if( (event.key.keysym.sym == SDLK_RETURN) || (event.key.keysym.sym == SDLK_SPACE) ) { gamestate = GS_MENU; }
                     }
                     if( event.type == SDL_QUIT ) { quit = true; }
              }
              
              if( block_in_table == false)
              {
                  check_for_full_lines();
                  Sleep(400);
                  int losuj = 0;
                  losuj = rand() % 7 + 1;
                  switch(losuj)
                  {
                       case 1: blocktype = KT_K1_P1; break;
                       case 2: blocktype = KT_K2_P1; break;
                       case 3: blocktype = KT_K3_P1; break;
                       case 4: blocktype = KT_K4_P1; break;
                       case 5: blocktype = KT_K5_P1; break;
                       case 6: blocktype = KT_K6_P1; break;
                       case 7: blocktype = KT_K7_P1; break;
                       default: blocktype = KT_K8_P1; break;
                  }
                  setblockstartpos( blocktype );
                  klocek_taby = 0;
                  klocek_tabx = 3;
                  block_in_table = true;
              }
                  
              if( klocek_taby == 16 )
              {
                  plansza[klocek_taby][klocek_tabx] = 1;
                  block_in_table = false;
              }
              
              
              
              //SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0xFF, 0xFF, 0xFF ) );
              apply_surface( 0, 0, menu_tlo, screen );
              apply_surface( 0, 0, game_tlo, screen );
              
              for( int i = 0; i < 17; i++ )
              {
                   for( int j = 0; j < 10; j++ )
                   {
                        if( plansza[i][j] == 1 )
                        {
                            apply_surface( j*24, i*24, klocek, screen );
                        }
                   }
              }
              
              if( SDL_Flip( screen ) == -1 ) { return 1; }
              if( fps.get_ticks() < 1000 / FRAMES_PER_SECOND ) { SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - fps.get_ticks() ); }
        }
                      
            
    
    
    
    
    
    /*
    
        fps.start();
        while( SDL_PollEvent( &event ) )
        {
            
            if( event.type == SDL_QUIT ) { quit = true; }
        }

        SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0xFF, 0xFF, 0xFF ) );


        //Update the screen + FPS
        if( SDL_Flip( screen ) == -1 ) { return 1; }
        if( fps.get_ticks() < 1000 / FRAMES_PER_SECOND )
        {
            SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - fps.get_ticks() );
        }*/
    }

    clean_up();

    return 0;
}




