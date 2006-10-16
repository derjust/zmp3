#include "musicplay.h"

using namespace std;

extern pthread_mutex_t  mutexPlayliste;
extern Dateiliste* lPlayliste;

int NaechsterChannel;
int Lieder=0;

void AufLiedWarten()
{
bool Abbruch=true;
while (Abbruch)
{
	pthread_mutex_lock(&mutexPlayliste);
	if (lPlayliste != 0)
	{
		Abbruch=false;
	}
	pthread_mutex_unlock(&mutexPlayliste);
	sleep(1);
}
}

void *Musikwiedergabe( void *ptr)
{
ptr=0;
ClientSocket* Display2 = LCDconnect(1);

LCDwrite(Display2, 0, "Musik-Thread    [OK]");
LCDwrite(Display2, 1, "Sound-System        ");
LCDwrite(Display2, 2, "                    ");
LCDwrite(Display2, 3, "                    ");

FSOUND_Init(44100, 2, 0);

LCDwrite(Display2, 1, "Sound-System    [OK]");

for (;;) 
	musicplay(Display2,NULL,1);
}

void musicplay(ClientSocket* Display2, FSOUND_STREAM* AltesLied = NULL, int AlterChannel = 0)
{
FSOUND_STREAM* Lied;
float Fortschritt;
string Balken;
string Zeit;
short int Channel;
short int n;

AufLiedWarten();

//Lied laden
pthread_mutex_lock(&mutexPlayliste);
Lied = FSOUND_Stream_Open(lPlayliste->GetKompletterDateipfad().c_str() , FSOUND_MPEGACCURATE , 0 , 0 );
pthread_mutex_unlock(&mutexPlayliste);
//Aktuellen Channel finden
if (AlterChannel == 0 )
	Channel = 1;
else
	Channel = 0;
//so, damit die anzeige schön ist
Lieder++;
//Lied abspielen
Channel = FSOUND_Stream_Play( Channel, Lied );
//GGf. läuft das alte Lied ja noch -> Faden und dann löschen
if (AltesLied != NULL)
{
	FadeKanaele(AltesLied, AlterChannel, Channel);
	FSOUND_Stream_Close(AltesLied);
	//der Fade ist ja noch dran -> also erstmal warten. sonst überschreibt uns die folgenden
	//while-schleife die fade-animation
	sleep(19);
}

//Das Lied läuft und gut is
while (FSOUND_IsPlaying ( Channel) )
{
	if ( ((FSOUND_Stream_GetLengthMs(Lied) / 1000) - 
	      (FSOUND_Stream_GetTime(Lied)) / 1000) < 21 )
	{
		break; //nur noch 20 Sekunden über
	}

	Fortschritt = FSOUND_Stream_GetTime(Lied);
	if (Fortschritt < 0 ) 
	{
		continue;
	}
	Fortschritt = Fortschritt / FSOUND_Stream_GetLengthMs(Lied);
	Fortschritt = Fortschritt * 100;
	Balken = "";
	for (n=5; n <= Fortschritt; n=n+5)
	{
		Balken.append("#");
	}
	while (Balken.length() < 20)
	{
		Balken.append(" ");
	}
	pthread_mutex_lock(&mutexPlayliste);
	if (lPlayliste != 0)
	{
		LCDwrite(Display2, 0, lPlayliste->GetArtist());	
		LCDwrite(Display2, 1, lPlayliste->GetSong());
	}
	pthread_mutex_unlock(&mutexPlayliste);	
	LCDwrite(Display2, 2, Balken);
	if (Lieder < 10)
	{
	Zeit = "0";
	}
	Zeit.append(IntToStr(Lieder));
	Zeit.append(" ");
	Zeit.append(SecToMin(FSOUND_Stream_GetTime(Lied)/1000));
	Zeit.append(" / ");
	Zeit.append(SecToMin(FSOUND_Stream_GetLengthMs(Lied)/1000));
	Zeit.append(" ");
	if (Fortschritt < 10)
	{
		Zeit.append(" ");
	}
	Zeit.append( IntToStr(int(Fortschritt)) );
	Zeit.append("%");
	LCDwrite(Display2, 3, Zeit );	
	sleep(1);
	//nächstes lied abfangen per tastendruck
}
//Zeit für den Fade

if (lPlayliste != 0)
	lPlayliste = lPlayliste->Naechster;

musicplay(Display2, Lied, Channel);
}

string IntToStr(int Zahl)
{
string data;
stringstream ss;

ss << Zahl;
data = ss.str();
return data;
}

string SecToMin(int Sekunden)
{
int Minuten;
string sMinuten;
string sSekunden;
string data;
Minuten = Sekunden / 60;
Sekunden = Sekunden - (Minuten*60);
sMinuten = IntToStr(Minuten);
sSekunden = IntToStr(Sekunden);
if (sMinuten.length()==1)
{
	data = sMinuten;
	sMinuten = "0";
	sMinuten.append(data);
}
if (sSekunden.length()==1)
{
	data = sSekunden;
	sSekunden = "0";
	sSekunden.append(data);
}
data = sMinuten;
data.append(":");
data.append(sSekunden);
return data;
}

void FadeKanaele(FSOUND_STREAM* AktuellesLied, int Kanal1, int Kanal2)
{
// Kanal1 ausblenden
// Kanal2 einblenden
// AktuellesLied sollte Langsam aus gehen :)
float vol = 255;
int LiedLaenge = FSOUND_Stream_GetLengthMs( AktuellesLied );
while (FSOUND_IsPlaying ( Kanal1 ) )
{
  vol = 255.0 / 20 * (float)( LiedLaenge / 1000 - LiedLaenge / 1000 );
  FSOUND_SetVolume( Kanal1, (int)vol );
  FSOUND_SetVolume( Kanal2, 255-(int)vol );
  usleep(500000);  // sleep von 0,1 - 0,5 sec wär gut
}
}
