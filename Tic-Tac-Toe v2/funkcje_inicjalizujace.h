#ifndef FUNKCJE_INICJALIZUJACE_H
#define FUNKCJE_INICJALIZUJACE_H

#include "CTimer.h"
#include "Kontrolki.h"

class CLabel;
class CRamki;
class CEvent;
class CCheckBox;
class CButton_std;
class CEditBox;
class CRadioButton;
class CListBox;

void przygotuj();
void usuwaj();


extern CRamki *p_ramki;

extern CLabel *label_opcje;
extern CLabel *label_tryb_gry;
extern CLabel *label_opcje_online;
extern CLabel *label_ip;

extern CRadioButton *rbt_pVSp;
extern CRadioButton *rbt_pVScom;
extern CRadioButton *rbt_pVSp_online;
extern CRadioButton *rbt_serwer;
extern CRadioButton *rbt_klient;

extern CButton_std *btnStd_TryConnectToSerwer;
extern CButton_std *btnStd_Disconnect;
extern CButton_std *btnStd_StartGame;
//extern CButton_std *btnStd_SartServering;
extern CButton_std *btnStd_KoniecGry;

extern CEditBox *editB_client_ip;
/*extern CLabel *label_hpE;
extern CCheckBox *chkbox_AntiLog;
extern CButton_std *btnStd_LOADPROFILE;
extern CButton_std *btnStd_AddToEnemy;
extern CEditBox *editB_EnemyAdder;
extern CListBox *listB_EnemyList;*/
extern CTimer *timer_fps;



#endif
