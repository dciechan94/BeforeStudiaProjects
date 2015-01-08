#include "funkcje_inicjalizujace.h"
#include "Kontrolki.h"

     
CRamki *p_ramki;  

CLabel *label_opcje = NULL;
CLabel *label_tryb_gry = NULL;
CLabel *label_opcje_online = NULL;
CLabel *label_ip = NULL;

CRadioButton *rbt_pVSp = NULL;
CRadioButton *rbt_pVScom = NULL;
CRadioButton *rbt_pVSp_online = NULL;
CRadioButton *rbt_serwer = NULL;
CRadioButton *rbt_klient = NULL;

CButton_std *btnStd_StartGame = NULL;
//CButton_std *btnStd_SartServering = NULL;
CButton_std *btnStd_KoniecGry = NULL;
CButton_std *btnStd_TryConnectToSerwer = NULL;
CButton_std *btnStd_Disconnect = NULL;

CEditBox *editB_client_ip = NULL;

/*CLabel *label_hpE = NULL;

CCheckBox *chkbox_AntiLog = NULL;

CButton_std *btnStd_LOADPROFILE = NULL;

CEditBox *editB_EnemyAdder = NULL;

CListBox *listB_EnemyList = NULL;*/

CTimer *timer_fps = NULL;



void przygotuj()
{    
     p_ramki = new CRamki;
     p_ramki->laduj_ramki();
     
     //  LABEL
     label_opcje = new CLabel( 640, 215, "Opcje:", 25 );
     label_tryb_gry = new CLabel( 590, 260, "Tryb gry:", 12 );
     label_opcje_online = new CLabel( 590, 410, "Gra Online:", 12 );
     label_ip = new CLabel( 590, 517, "IP:", 12 );
     
     //  CHECK BOX
     //chkbox_AntiLog = new CCheckBox( p_ramki, 20, 175, "Anti-LogOut", false );

     // BUTTON STD
     btnStd_TryConnectToSerwer = new CButton_std( p_ramki, 590, 550, " CONNECT ", BST_CONNECT );
     btnStd_Disconnect = new CButton_std( p_ramki, 690, 550, " DISCONNECT ", BST_DCONNECT );
     btnStd_StartGame = new CButton_std( p_ramki, 640, 380, "  Start Game  ", BST_START );
     btnStd_KoniecGry = new CButton_std( p_ramki, 635, 280, "  Exit Game  ", BST_EXITTOMENU );
     //btnStd_SartServering = new CButton_std( p_ramki, 600, 550, "  START  ", BST_STARTSERVER );
     
     //  RADIO BUTTON
     //CRadioButton( CRamki* obiekt_ramek, int posx, int posy, std::string napis, bool ticked, RADIO_BUTTON_TYPE id, int);
     rbt_pVSp = new CRadioButton( p_ramki, 610, 290, "Player vs. Player", true, RBT_PvsP, 15 );
     rbt_pVScom = new CRadioButton( p_ramki, 610, 315, "Player vs. COM", false, RBT_PvsCOM, 15 );
     rbt_pVSp_online = new CRadioButton( p_ramki, 610, 340, "Player vs. Player Online", false, RBT_PvsP_ONLINE, 15 );
     rbt_serwer = new CRadioButton( p_ramki, 610, 430, "Server", true, RBT_SERVER, 15 );
     rbt_klient = new CRadioButton( p_ramki, 610, 455, "Client", false, RBT_CLIENT, 15 );
     
     //  EDIT BOX
     editB_client_ip = new CEditBox( p_ramki, 610, 515, 140, " " );
     //editB_EnemyAdder = new CEditBox( p_ramki, 20, 160, 140, " " );
     
     //  LIST BOX
     //listB_EnemyList = new CListBox( p_ramki, 20, 200, 140, 145 , 11);
     
     //  TIMER
     timer_fps = new CTimer();
     timer_fps->start();
     
}

void usuwaj()
{
     delete p_ramki;  
     
     delete label_opcje;
     delete label_tryb_gry;
     delete label_opcje_online;
     delete label_ip;

     delete rbt_pVSp;
     delete rbt_pVScom;
     delete rbt_pVSp_online;
     delete rbt_serwer;
     delete rbt_klient;

     delete btnStd_TryConnectToSerwer;
     delete btnStd_Disconnect;
     delete btnStd_StartGame;
     delete btnStd_KoniecGry;
     //delete btnStd_SartServering;

     delete editB_client_ip;
        
     delete timer_fps;
     
}
     
