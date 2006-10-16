#include <string>
#include <sstream>

#ifndef lcd_h
  #define lcd_h lcd_h
    #include "lcd.h"
#endif

#ifndef fmod_h 
  #define fmod_h fmod_h
    #include "fmod.h"
#endif

#ifndef listen_h
  #define listen_h listen_h
    #include "listen.h"
#endif


using namespace std;

void *Musikwiedergabe( void *ptr);

void musicplay(ClientSocket* Display2, FSOUND_STREAM* AltesLied, int AlterChannel);

string IntToStr(int Zahl);

string SecToMin(int Sekunden);

void FadeKanaele(FSOUND_STREAM* AktuellesLied, int Kanal1, int Kanal2);

void AufLiedWarten();
