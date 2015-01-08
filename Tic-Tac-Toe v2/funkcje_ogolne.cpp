#include "funkcje_ogolne.h"



bool init_SDL()
{
    if( SDL_Init( SDL_INIT_VIDEO ) == -1 )  { return false; } 
    
    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_DOUBLEBUF | SDL_SWSURFACE );
    
    if( screen == NULL ) { return false; } 
    if( TTF_Init() == -1 ) { return false; } 
    
    SDL_WM_SetCaption( "Kó³ko i krzy¿yk", NULL ); 
    return true;
}

//  load files
bool load_files()
{
    menu_ply = load_image( "gfx/ply.png" );
    if( menu_ply == NULL ) { return false; }
    playground_surface = load_image( "gfx/playboard.png" );
    if( playground_surface == NULL ) { return false; }
    playground_surface2 = load_image( "gfx/playboard2.png" );
    if( playground_surface2 == NULL ) { return false; }
    x_surface = load_image( "gfx/x.png" );
    if( x_surface == NULL ) { return false; }
    o_surface = load_image( "gfx/o.png" );
    if( o_surface == NULL ) { return false; }
    return true;
}

//  clean UP
void clean_up() 
{
    SDL_FreeSurface( screen );
    SDL_FreeSurface( menu_ply );
    SDL_FreeSurface( playground_surface );
    SDL_FreeSurface( playground_surface2 );
    SDL_FreeSurface( x_surface );
    SDL_FreeSurface( o_surface );
    
    //SDL_KillThread( th_pobieranie_danych ); 
    
    TTF_Quit(); 
    SDL_Quit(); 
}



//  apply_surface
void apply_surface(int x, int y, SDL_Surface *source, SDL_Surface *destination, SDL_Rect *mms=NULL)
{
     SDL_Rect offset;
     
     offset.x = x;
     offset.y = y;
     
     SDL_BlitSurface(source, mms, destination, &offset);
}
void apply_surface(int x, int y, SDL_Surface *source, SDL_Surface *destination)
{
     SDL_Rect offset;
     
     offset.x = x;
     offset.y = y;
     
     SDL_BlitSurface(source, NULL, destination, &offset);
}

// Load Image
SDL_Surface *load_image( std::string filename )
{ 
            SDL_Surface* loadedImage = NULL; 
            SDL_Surface* optimizedImage = NULL; 
            
            loadedImage = IMG_Load( filename.c_str() ); 
            
            if( loadedImage != NULL ) 
            { 
                optimizedImage = SDL_DisplayFormat( loadedImage ); 
                
                SDL_FreeSurface( loadedImage ); 
                
                if ( optimizedImage != NULL)
                {
                     Uint32 colorkey = SDL_MapRGB( optimizedImage->format, 0, 0xFF, 0xFF ); 
                     SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, colorkey ); 
                }
            } 
            return optimizedImage; 
} 

void juzio_intro()
{
     bool juz = false;
     int intro_alpha = SDL_ALPHA_TRANSPARENT;
     bool intro_fadein = true;
     SDL_Surface* juzio_intro_surf = NULL;
     juzio_intro_surf = load_image( "gfx/Juzio94zgrPresents.png" );
     CTimer timer_fps;
     timer_fps.start();
     
     while(  (program_quit_flag == false) && (juz == false)  )
     {
         while( SDL_PollEvent( &event ) )
         {
             if( event.type == SDL_KEYDOWN )
             {
                 if( (event.key.keysym.sym == SDLK_RETURN) || (event.key.keysym.sym == SDLK_SPACE) ) { juz = true; }
             }
             if( event.type == SDL_QUIT ) { program_quit_flag = true; }
         }
         
         // Logic
         SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0x00, 0x00, 0x00 ) );
              
         if( (intro_alpha < SDL_ALPHA_OPAQUE-15) && (intro_fadein == true) ) { intro_alpha = intro_alpha+5; }
         if( (intro_alpha <= SDL_ALPHA_OPAQUE) && (intro_fadein == false) ) { intro_alpha = intro_alpha-5; }
         if( intro_alpha >= SDL_ALPHA_OPAQUE-15 ) { intro_fadein = false; Sleep(1500); }
         if( intro_alpha <= SDL_ALPHA_TRANSPARENT ) { juz = true; }
              
         SDL_SetAlpha( juzio_intro_surf, SDL_SRCALPHA, intro_alpha );
              
         //Show
         apply_surface( 0, 0, juzio_intro_surf, screen, NULL );
              
         if( SDL_Flip( screen ) == -1 ) { MessageBox(NULL,"Flip Problem","Error", MB_OK); program_quit_flag = false; }
         if( timer_fps.get_ticks() < 1000 / FRAMES_PER_SECOND ) { SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - timer_fps.get_ticks() ); }
     }
     
     SDL_FreeSurface( juzio_intro_surf );
     SDL_Delay( 500 );
}



