#include <string>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

#ifndef listen_h
  #define listen_h listen_h
    #include "listen.h"
#endif

using namespace std;

Dateiliste* DateilisteLaden();
void DateilisteSpeichern(Dateiliste* lDateiliste);
Dateiliste* DateilisteErstellen(string Basispfad, Dateiliste* lStart);
