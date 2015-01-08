#include <stdio.h>
#include <stdlib.h>

#include "globals.h"
#include "funkcje_ogolne.h"
#include "funkcje_menu.h"
#include <windows.h>

int main(int argc, char** argv)
{
    if( init_SDL() == false ) { MessageBox (0, "Blad krytyczny inicjalizacji!", "Error", MB_ICONHAND | MB_OK ); return 1; }
    if( load_files() == false ){ MessageBox (0, "Nie mozna zaladowac plikow!", "Error", MB_ICONHAND | MB_OK ); return 1; }
    
    przygotuj();
    juzio_intro();
    
    while( program_quit_flag == false )
    {
        obsluga_menu_glowne();
        rozgrywka();
    }

    usuwaj(); 
    clean_up();
    
	return 0;
}
