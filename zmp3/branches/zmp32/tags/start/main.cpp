#include <iostream>
#include <pthread.h>
#include <stdlib.h>

#include "lcd.h"
#include "dateioperationen.h"
#include "musicplay.h"
#include "aktionen.h"
#include "menu.h"

#define MUSIKPFAD	"/home/tiwaz/Musik/Donots/"

using namespace std;

pthread_mutex_t  mutexPlayliste = PTHREAD_MUTEX_INITIALIZER; //Für Zugriffe auf die Playliste
//pthread_mutex_t  mutexDateiliste = PTHREAD_MUTEX_INITIALIZER; //Für Zugriffe auf die Dateiliste
pthread_mutex_t  mutexAktionsliste = PTHREAD_MUTEX_INITIALIZER; //Für Zugriffe auf die Aktionsliste

Dateiliste* lPlayliste=0;
Aktionsliste* lAktionsliste=0;
TMenuElement* lMenu=0;
TMenuElement* lDateimenu=0;

int main( int argc, char **argv )
{
int MenuPos=0;
Dateiliste* lDateiliste;
TMenuElement* lTopmenu;
TMenuElement* lDelMenu;

Aktionsliste* lLetzteAktion;
TAktion LetzteAktion;

pthread_t MusikThread;
pthread_t AktionenThread;

ClientSocket* Display1 = LCDconnect(0);

LCDclear(Display1);

LCDwrite(Display1,0,"        zmp3       ");
LCDwrite(Display1,1,"       v.2.0       ");
LCDwrite(Display1,2,"                   ");
LCDwrite(Display1,3,"MP3/OGG/CDA/LS   DJ");
sleep(0);
LCDclear(Display1);

LCDwrite(Display1,0,"Musik-Thread       ");
pthread_create(&MusikThread, 0, &Musikwiedergabe, 0 );
LCDwrite(Display1,0,"Musik-Thread    [OK]");

LCDwrite(Display1,1,"Aktionen-Thread     ");
pthread_create(&AktionenThread, 0, &AktionenSammeln, 0 );
LCDwrite(Display1,1,"Aktionen-Thread [OK]");

LCDwrite(Display1,2,"Dateiliste          ");
lDateiliste = DateilisteErstellen(MUSIKPFAD,0);
while (lDateiliste->Vorheriger != 0)
{
	lDateiliste = lDateiliste->Vorheriger;
}

LCDwrite(Display1,2,"Dateiliste      [OK]");
LCDwrite(Display1,3,"GUI starten         ");
sleep(0);

lDateimenu = ErstelleDateimenu(Display1, lDateiliste);

lTopmenu = ErstelleTopmenu(Display1);

ZeigeMenu(lTopmenu, Display1);

lMenu = lTopmenu;
for (;;)
{
LetzteAktion = Nichts;
pthread_mutex_lock(&mutexAktionsliste);

if (lAktionsliste != 0)
{
	LetzteAktion = lAktionsliste->GetAktion();
	lLetzteAktion = lAktionsliste;
	lAktionsliste = lAktionsliste->Naechster;
	delete lLetzteAktion;
	lLetzteAktion=0;
}
pthread_mutex_unlock(&mutexAktionsliste);
	switch (LetzteAktion)
	{
		case Hoch:
			lMenu = lMenu->Vorheriger;
			ZeigeMenu(lMenu, Display1);
			MenuPos++;
		break;
		case Runter:
			lMenu = lMenu->Naechster;
			ZeigeMenu(lMenu,Display1);
			MenuPos--;
		break;
		case Rechts:
				lMenu->Aktion();
				ZeigeMenu(lMenu, Display1);
		break;
		case Links:
			//Erstmal das alte menü löschen, sonst gibts nachher spaß wenn ein menü zum 
			//hundertsten mal verlassen wurde
			while (lMenu != 0)
			{
				lDelMenu = lMenu;
				lMenu = lMenu->Naechster;
				delete lDelMenu;
			}
			lMenu = lTopmenu;
			ZeigeMenu(lMenu, Display1);
		break;
		case Nichts:
		break;
	};
//usleep(250);
usleep(250000);
}
return 0;
}
