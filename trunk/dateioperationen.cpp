#include "dateioperationen.h"

using namespace std;

Dateiliste* DateilisteLaden()
{
Dateiliste* lStart=0;

return lStart;
}

void DateilisteSpeichern(Dateiliste* lDateiliste)
{
lDateiliste = 0;
}

Dateiliste* DateilisteErstellen(string Basispfad, Dateiliste* lStart=0)
{
Dateiliste* lNeu=0;
Dateiliste* lTmp=lStart;
string DateiStat;
DIR* Musikverzeichnis =  opendir( Basispfad.c_str() );
struct dirent* d;
struct stat FileInfo; 

while ( ( d = readdir( Musikverzeichnis ) ) != NULL )
{
	if (d->d_name[0]=='.') 
	{ 
		continue; 
	}
	DateiStat = Basispfad;
	DateiStat.append(d->d_name);
	stat(DateiStat.c_str(),&FileInfo);
	if (S_ISDIR(FileInfo.st_mode)) 
	{ 
		DateiStat.append("/");
		lTmp = DateilisteErstellen(DateiStat, lTmp);
		continue;
	}
	if (!lStart)  //Erstes Element
	{
		lStart = new Dateiliste (d->d_name, Basispfad);
		lTmp = lStart;
	}
	else 
	{
		lNeu = new Dateiliste (d->d_name, Basispfad);  
		lTmp->Naechster = lNeu;
		lNeu->Vorheriger = lTmp;
		lTmp = lNeu;
	}
}
closedir(Musikverzeichnis);

return lTmp;
}
