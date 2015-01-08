#include "funkcje.h"

//  £aduj i optymalizuj obrazek
SDL_Surface *load_image( std::string filename )
{ 
            SDL_Surface* loadedImage = NULL; 
            SDL_Surface* optimizedImage = NULL; 
            
            loadedImage = IMG_Load( filename.c_str() ); 
            
            if( loadedImage != NULL ) 
            { 
                //  Optymalizuj obrazek do formatu programu
                optimizedImage = SDL_DisplayFormat( loadedImage ); 
                
                SDL_FreeSurface( loadedImage ); 
                
                // Usuñ ColorKey  (zbêdne t³o obrazka)
                if ( optimizedImage != NULL)
                {
                     Uint32 colorkey = SDL_MapRGB( optimizedImage->format, 0, 0xFF, 0xFF ); 
                     SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, colorkey ); 
                }
            } 
            return optimizedImage; 
} ;


//  Rysuj obrazek na innym
void apply_surface(int x, int y, SDL_Surface *source, SDL_Surface *destination, SDL_Rect *mms)
{
     SDL_Rect offset;
     
     offset.x = x;
     offset.y = y;
     
     SDL_BlitSurface(source, mms, destination, &offset);
}


bool load_files()
{
    juzio_producion_presents = load_image( "gfx/Juzio94zgrPresents.png" );
    if( juzio_producion_presents == NULL ) { return false; }
    papirus = load_image( "gfx/Tetris-menu3.png" );
    if( papirus == NULL ) { return false; }
    menu_tlo = load_image( "gfx/pustynia.png" );
    if( menu_tlo == NULL ) { return false; }
    game_tlo = load_image( "gfx/Tetris-game4.png" );
    if( game_tlo == NULL ) { return false; }
    klocek = load_image( "gfx/klocek.png" );
    if( klocek == NULL ) { return false; }
    
    font = TTF_OpenFont( "FFF Tusj.ttf", 72 );
    if( font == NULL ) { return false; } TTF_SetFontStyle( font, TTF_STYLE_ITALIC);
    
    
    return true;
}

// Instaluj SDL, uruchom obraz
bool init_SDL()
{
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )  { return 1; } 
    
    screen = SDL_SetVideoMode(SCREEN_WIDTH,SCREEN_HEIGHT,SCREEN_BPP,SDL_SWSURFACE);
    if( screen == NULL ) { return 1; } 
    
    if( TTF_Init() == -1 ) { return false; } 
    
    SDL_WM_SetCaption( "Tetris", NULL ); 
    return true;
}

// Kasuj wszystkie u¿ywane Surface i wy³¹cz SDL
void clean_up() 
{
    SDL_FreeSurface( screen );
    SDL_FreeSurface( juzio_producion_presents );
    SDL_FreeSurface( papirus );
    SDL_FreeSurface( menu_tlo );
    SDL_FreeSurface( game_tlo );
    SDL_FreeSurface( klocek );
    
    TTF_CloseFont( font ); 
    
    SDL_KillThread( th_downtimer ); 
    
    TTF_Quit(); 
    SDL_Quit(); 
}

int th_downtimer_f( void *data ) 
{ 
    //While the program is not over 
    while( quit == false ) 
    { 
           if( block_in_table == true )
           {
               
               
               
               
               if( plansza[klocek_taby+1][klocek_tabx] != 1 )
               {
               klocek_taby++;
               plansza[klocek_taby][klocek_tabx] = 1;
               plansza[klocek_taby-1][klocek_tabx] = 0;
               SDL_Delay( 100 );
               }
               else
               {
                   plansza[klocek_taby][klocek_tabx] = 1;
                   block_in_table = false;
               }
           }
           
    } 
           
    return 0; 
} 

void check_for_full_lines()
{
     bool linia = false;
     for( int i = 0; i < 17; i++)
     {
          linia = true;
          for( int j = 0; j < 10; j++)
          {
               if( plansza[i][j] == 0 )
               {
                   linia = false;
               }
          }
          if( linia == true )
          {
              // delete line(i)
              for( int l = 0; l<10; l++ )
              {
                   plansza[i][l] = 0;
              }
              wynik += 500;
              // set down higher lines
              for( int n = i; n > 0 ; n-- )
              {
                   for( int m = 0; m < 10; m++ )
                   {
                        plansza[n][m] = plansza[n-1][m];
                        plansza[n-1][m] = 0;
                   }
              }
          }
     }
}

void setblockstartpos( KLOCEK_TYPE type )
{
     
     
}
