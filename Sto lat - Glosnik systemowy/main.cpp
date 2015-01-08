#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <conio.h>
#include "windows.h"
/*
Beep(294, 400); // D
Beep(329, 400); // E
Beep(350, 400); // F
Beep(392, 400); // G
Beep(440, 200); // A
Beep(494, 200); // H
Beep(523, 200); // C2
*/
int dlugosc = 450;

using namespace std;

int main(int argc, char *argv[])
{
    Beep(392, dlugosc); 
    Sleep( dlugosc );
    Beep(392, dlugosc); 
    Sleep( dlugosc );
    Beep(392, dlugosc); 
    Sleep( dlugosc );
    Beep(392, dlugosc); 
    Sleep( dlugosc );
    
    cout << "Sto ";
    Beep(392, dlugosc); // Sto
    cout << "lat! ";
    Beep(329, dlugosc); // lat
    cout << "Sto ";
    Beep(392, dlugosc); // Sto
    cout << "lat! " << endl;
    Beep(329, dlugosc); // lat
    
    cout << "Niech ";
    Beep(392, dlugosc); // Niech
    cout << "zy";
    Beep(440, dlugosc/2); // 퓓-
    cout << "je, ";
    Beep(392, dlugosc/2); // -je
    cout << "zy";
    Beep(350, dlugosc/2); // 퓓-
    cout << "je ";
    Beep(329, dlugosc/2); // -je
    cout << "nam!" << endl << endl;
    Beep(350, dlugosc); // nam
    
    Sleep( dlugosc );
    
    cout << "Sto ";
    Beep(350, dlugosc); // Sto
    cout << "lat! ";
    Beep(294, dlugosc); // lat
    cout << "Sto ";
    Beep(350, dlugosc); // Sto
    cout << "lat! " << endl;
    Beep(294, dlugosc); // lat
    
    cout << "Niech ";
    Beep(350, dlugosc); // Niech
    cout << "zy";
    Beep(392, dlugosc/2); // 퓓-
    cout << "je, ";
    Beep(350, dlugosc/2); // -je
    cout << "zy";
    Beep(329, dlugosc/2); // 퓓-
    cout << "je ";
    Beep(294, dlugosc/2); // -je
    cout << "nam!" << endl << endl;
    Beep(329, dlugosc); // nam
    
    Sleep( dlugosc );
    
    cout << "Je";
    Beep(392, dlugosc/2); // Je-
    cout << "szcze ";
    Beep(392, dlugosc/2); // -szcze
    cout << "raz!  ";
    Beep(329, dlugosc); // raz
    
    cout << "Je";
    Beep(392, dlugosc/2); // Je-
    cout << "szcze ";
    Beep(392, dlugosc/2); // -szcze
    cout << "raz!  " << endl;
    Beep(329, dlugosc); // raz
    
    cout << "Niech ";
    Beep(392, dlugosc); // Niech
    cout << "zy";
    Beep(523, dlugosc/2); // 퓓-
    cout << "je, ";
    Beep(494, dlugosc/2); // -je
    cout << "zy";
    Beep(440, dlugosc/2); // 퓓-
    cout << "je ";
    Beep(416, dlugosc/2); // -je
    cout << "nam!" << endl << endl;
    Beep(440, dlugosc); // nam
    
    Sleep( dlugosc );
    
    cout << "^^^^  NIEEECH ";
    Beep(494, 2*dlugosc); // Nieech
    cout << "  ZY";
    Beep(494, dlugosc); 
    cout << "JE   ";
    Beep(494, dlugosc);
    cout << "NAAAM";
    Beep(523, 2*dlugosc); // nam
    cout << "!  ^^^^" << endl;
    Beep(2*523, 2*dlugosc);
    
    Sleep( 1000 );
    
    for( int i=0; i < 80; i++ ) { cout << "_"; Sleep(25); }
    cout << endl << endl << endl;
    Sleep(1000);
    cout << "[tu wpisz imie]," << endl;
    Sleep(1000);
    cout << "Wszystkiego najlepszego, szczescia i pomyslnosci." << endl;
    Sleep(1000);
    cout << "Na codzien usmiechu, milosci (a z tym) duzo radosci." << endl;
    Sleep(1000);
    cout << "Pracy wymarzonej, sensownej przelozonej." << endl;
    Sleep(1000);
    cout << "Dolarow bez liku w Twym portfeliku." << endl << endl;
    Sleep(1000);
    cout << "                          ****   zyczy  [tu wpisz imie]   **** " << endl << endl;
    getch();
    getch();
    getch();
    return 0;
}
