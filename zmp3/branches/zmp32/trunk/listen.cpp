/********************************************************
 *		Funktionen der Listen-Klassen		*
 *							*
 *				by Sebastian Just	*
 * 27.06.2004 letzte Änderung				*
 ********************************************************
*/
#include "listen.h"

using namespace std;


Dateiliste::Dateiliste (string Datei,string Verzeichnis) //Konstruktor
{
myDatei = Datei;
Naechster = 0;
Vorheriger = 0;
myVerzeichnis = Verzeichnis;
myArtist = ID3Artist(GetKompletterDateipfad());
mySong  = ID3Song(GetKompletterDateipfad());
}

string Dateiliste::GetDatei () 
{ 
return myDatei; 
}

string Dateiliste::GetVerzeichnis()
{
return myVerzeichnis;
}

string Dateiliste::GetArtist () 
{ 
return myArtist; 
}

string Dateiliste::GetSong () 
{ 
return mySong; 
}

string Dateiliste::GetKompletterDateipfad ()
{
string data = myVerzeichnis;
data.append("/");
data.append(myDatei);
return data;
}

TAktion Aktionsliste::GetAktion()
{
return myAktion;
}

Aktionsliste::Aktionsliste(TAktion Aktion)
{
Naechster = 0;
myAktion = Aktion;
}


TMenuElement::TMenuElement(string Text, void (*Funktion)(ClientSocket*), ClientSocket* Display)
{
	myText = Text;
	myDisplay = Display;
	myFunktion = Funktion;
	myDateilistenEintrag = 0;
	Vorheriger = 0;
	Naechster = 0;
}

TMenuElement::TMenuElement(string Text, void (*Funktion)(ClientSocket*, Dateiliste*), ClientSocket* Display, Dateiliste* DateilistenEintrag)
{
	myText = Text;
	myDisplay = Display;
	myPlayFunktion = Funktion;
	myDateilistenEintrag = DateilistenEintrag;
	Vorheriger = 0;
	Naechster = 0;
}

string TMenuElement::GetText()
{
	return myText;
}

void TMenuElement::Aktion()
{
if (myFunktion != 0 && myDateilistenEintrag == 0)
	myFunktion(myDisplay);
else
	myPlayFunktion(myDisplay, myDateilistenEintrag);

}

