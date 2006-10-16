#include <string.h>

#ifndef listen_h
  #define listen_h listen_h
    #include "listen.h"
#endif

#ifndef lcd_h
  #define lcd_h lcd_h
    #include "lcd.h"
#endif
using namespace std;

TMenuElement* ErstelleTopmenu(ClientSocket* Display);

TMenuElement* ErstelleDateimenu(ClientSocket* Display, Dateiliste* lDateiliste);

void ZeigeMenu(TMenuElement* MenuEintrag, ClientSocket* Display);

void ZeigeDateiliste(ClientSocket* Display);

void ZeigePlayliste(ClientSocket* Display);

void ZeigeFlushliste(ClientSocket* Display);

void ZeigeRandom(ClientSocket* Display);

void ZeigeArtistSearch(ClientSocket* Display);

void ZeigeSongSearch(ClientSocket* Display);

void SongEinreihen(ClientSocket* Display, Dateiliste* DateilisetnEintrag);

