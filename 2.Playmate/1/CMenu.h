#ifndef CMENU_H
#define CMENU_H

#include "globals.h"

class CMenu
{
      private:
          SDL_Surface *m_znacznik;
          SDL_Rect m_nowagra_box;
          SDL_Rect m_opcje_box;
          SDL_Rect m_wyjscie_box;
          bool m_nowagra;
          bool m_opcje;
          bool m_wyjscie;
          
          
      public:
          CMenu();
          ~CMenu();
          
          void init();
          void handle_events();
          void show();
};

#endif
