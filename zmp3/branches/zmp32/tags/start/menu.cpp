#include "menu.h"

extern TMenuElement* lMenu;
extern TMenuElement* lDateimenu;
extern pthread_mutex_t  mutexPlayliste;
extern Dateiliste* lPlayliste;

using namespace std;

void ZeigeMenu(TMenuElement* MenuEintrag, ClientSocket* Display)
{
LCDclear(Display);
LCDwrite(Display,0,MenuEintrag->Vorheriger->GetText());
LCDwrite(Display,1,"*" + MenuEintrag->GetText());
LCDwrite(Display,2,MenuEintrag->Naechster->GetText());
LCDwrite(Display,3,MenuEintrag->Naechster->Naechster->GetText());
}

void ZeigeDateiliste(ClientSocket* Display)
{
	lMenu = lDateimenu;
}

void ZeigeRandom(ClientSocket* Display)
{
	LCDclear(Display);
	LCDwrite(Display,0,"Randomsong:");
	LCDwrite(Display,1,"song xyz -artist zxy");
}

void ZeigeArtistSearch(ClientSocket* Display)
{
	LCDclear(Display);
	LCDwrite(Display,0,"Search for Artist:");
	LCDwrite(Display,2,"|A_________________|");
}

void ZeigeSongSearch(ClientSocket* Display)
{
	LCDclear(Display);
	LCDwrite(Display,0,"Search for Song:");
	LCDwrite(Display,2,"|A_________________|");
}

void ZeigePlayliste(ClientSocket* Display)
{
pthread_mutex_lock(&mutexPlayliste);
if (lPlayliste==0)
{
	pthread_mutex_unlock(&mutexPlayliste);
	LCDclear(Display);
	LCDwrite(Display,1,"Die Playliste ");
	LCDwrite(Display,2,"ist leer");
	sleep(2);
}
else
{
	Dateiliste* lTmp = lPlayliste;
	TMenuElement* lStart = 0;
	TMenuElement* lLetzter = 0;
	TMenuElement* lNeu = 0;
	while (lTmp != 0)
	{
		if (lStart == 0)
		{
			lStart = new TMenuElement ( lTmp->GetSong() + " - " + lTmp->GetArtist() , 0, Display);
			lLetzter = lStart;
		}
		else
		{
			lNeu = new TMenuElement (lTmp->GetSong() + " - " + lTmp->GetArtist(), 0 ,Display);
			lLetzter->Naechster = lNeu;
			lNeu->Vorheriger = lLetzter;
			lLetzter = lNeu;
		}
		lTmp = lTmp->Naechster;
	}
	lNeu = new TMenuElement ("-----",0,Display);
	lLetzter->Naechster = lNeu;
	lNeu->Vorheriger = lLetzter;
	lNeu->Naechster = lStart;
	lStart->Vorheriger = lNeu;
	
	lMenu = lStart;
	pthread_mutex_unlock(&mutexPlayliste);	
}
}

void ZeigeFlushliste(ClientSocket* Display)
{
	LCDclear(Display);
	LCDwrite(Display,2,"Playlist has been flushed");
	Dateiliste* lDelMenu = lPlayliste;
	while (lPlayliste != 0)
	{
		lDelMenu = lPlayliste;
		lPlayliste = lPlayliste->Naechster;
		delete lDelMenu;
	}
	
}



TMenuElement* ErstelleDateimenu(ClientSocket* Display, Dateiliste* lDateiliste)
{
void (*ptr)(ClientSocket*, Dateiliste*) = 0;
ptr= & SongEinreihen;
TMenuElement* lMenuStart=0;
TMenuElement* lNeu=0;
TMenuElement* lLetzter=0;

while (lDateiliste != 0)
{
//	cout << ptr << " " << lDateiliste->GetSong() << endl;
	if (lMenuStart==0)
	{
		
		lMenuStart = new TMenuElement(lDateiliste->GetSong() + " - " + lDateiliste->GetArtist(), ptr, Display, lDateiliste );
		lLetzter = lMenuStart;
	}
	else
	{
		lNeu = new TMenuElement(lDateiliste->GetSong() + " - " + lDateiliste->GetArtist(), ptr, Display, lDateiliste );
		lLetzter->Naechster = lNeu;
		lNeu->Vorheriger = lLetzter;
		lLetzter = lNeu;
	}
	lDateiliste = lDateiliste->Naechster;
}

lNeu = new TMenuElement("-----", 0, Display, 0 );

lLetzter->Naechster = lNeu;
lNeu->Vorheriger = lLetzter;
lNeu->Naechster = lMenuStart;
lMenuStart->Vorheriger = lNeu;

return lMenuStart;
}

void SongEinreihen(ClientSocket* Display, Dateiliste* DateilistenEintrag)
{
Dateiliste* lTmp;
pthread_mutex_lock(&mutexPlayliste);
lTmp=lPlayliste;
if (lPlayliste == 0)
{
	lPlayliste = new Dateiliste( DateilistenEintrag->GetDatei(), DateilistenEintrag->GetVerzeichnis() );
}
else
{

	while (lPlayliste->Naechster != 0)
	{
		lPlayliste = lPlayliste->Naechster;
	}
	lPlayliste->Naechster = new Dateiliste( DateilistenEintrag->GetDatei(), DateilistenEintrag->GetVerzeichnis() );
	lPlayliste = lTmp;
}
pthread_mutex_unlock(&mutexPlayliste);

	LCDclear(Display);
	LCDwrite(Display,0,"New Song inserted:");
	LCDwrite(Display,1,DateilistenEintrag->GetArtist());
	LCDwrite(Display,2,"         -         ");
	LCDwrite(Display,3,DateilistenEintrag->GetSong());
	sleep(1);
}

TMenuElement* ErstelleTopmenu(ClientSocket* Display)
{
void (*ptr)(ClientSocket*)=0;
TMenuElement* lMenuStart;
ptr = &ZeigeRandom;

lMenuStart = new TMenuElement("Random",ptr,Display);
TMenuElement* lMenuEintrag;

ptr = &ZeigeArtistSearch;
lMenuEintrag = new TMenuElement("Search Artist",ptr,Display);

lMenuStart->Naechster = lMenuEintrag;
lMenuEintrag->Vorheriger = lMenuStart;

TMenuElement* lMenuEintrag2;
ptr = & ZeigeSongSearch;
lMenuEintrag2 = new TMenuElement("Search Song", ptr,Display);

lMenuEintrag->Naechster = lMenuEintrag2;
lMenuEintrag2->Vorheriger = lMenuEintrag;

ptr = &ZeigePlayliste;
lMenuEintrag = new TMenuElement("Show P-List", ptr, Display);

lMenuEintrag2->Naechster = lMenuEintrag;
lMenuEintrag->Vorheriger = lMenuEintrag2;

ptr = &ZeigeDateiliste;
lMenuEintrag2 = new TMenuElement("Show S-List", ptr, Display);

lMenuEintrag->Naechster = lMenuEintrag2;
lMenuEintrag2->Vorheriger = lMenuEintrag;

ptr = & ZeigeFlushliste;
lMenuEintrag = new TMenuElement("Flush P-List", ptr, Display);

lMenuEintrag2->Naechster = lMenuEintrag;
lMenuEintrag->Vorheriger = lMenuEintrag2;

ptr=0;
lMenuEintrag2 = new TMenuElement("-----", ptr, Display);

lMenuEintrag->Naechster = lMenuEintrag2;
lMenuEintrag2->Vorheriger = lMenuEintrag;

lMenuEintrag2->Naechster = lMenuStart;
lMenuStart->Vorheriger = lMenuEintrag2;

return lMenuStart;
}

