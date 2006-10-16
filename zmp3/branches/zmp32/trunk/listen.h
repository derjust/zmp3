/********************************************************
 *		Prototypen der Listen-Klassen		*
 *							*
 *				by Sebastian Just	*
 * 27.06.2004 letzte Änderung				*
 ********************************************************
*/
#include <string>
#ifndef id3label_h
  #define id3label_h id3label_h
    #include "id3label.h"
#endif

#ifndef ClientSocket_h
  #define ClientSocket_h ClientSocket_h
    #include "ClientSocket.h"
#endif

using namespace std;

class Dateiliste
{
  public:
  	Dateiliste (string Datei, string Verzeichnis) ;
	string GetDatei ();
	string GetArtist ();
	string GetSong ();
	string GetVerzeichnis ();
	string GetKompletterDateipfad ();
	Dateiliste* Naechster;
	Dateiliste* Vorheriger;
  private:
  	string myDatei;
	string mySong;
	string myArtist;
	string myPfad;
	string myVerzeichnis;
};

enum TAktion
    {
      Hoch,	//0
      Runter,	//1
      Rechts,	//2
      Links,	//3
      Nichts	//4
    };

class Aktionsliste
{
  public:
  	Aktionsliste(TAktion Aktion);
	TAktion GetAktion();
	Aktionsliste* Naechster;
  private:
  	TAktion myAktion;
};

class TMenuElement
{
  public:
	TMenuElement(string Text, void (*Funktion)(ClientSocket*, Dateiliste*), ClientSocket* Display, Dateiliste* DateilistenEintrag);
	TMenuElement(string Text, void (*Funktion)(ClientSocket*), ClientSocket* Display);
	string GetText();
	void Aktion();
	TMenuElement* Naechster;
	TMenuElement* Vorheriger;
  private:
  	string myText;
	Dateiliste* myDateilistenEintrag;
	ClientSocket* myDisplay;
	void (*myFunktion)(ClientSocket*);
	void (*myPlayFunktion)(ClientSocket*, Dateiliste* DateilistenEintrag);
};
