/********************************************************
 *		Prototypen der LCD-Funktionen		*
 *							*
 *				by Sebastian Just	*
 * 27.06.2004 letzte Änderung				*
 ********************************************************
*/
#include <string>
#include <iostream>

#ifndef ClientSocket_h
  #define ClientSocket_h ClientSocket_h
    #include "ClientSocket.h"
#endif

#ifndef SocketException_h
  #define SocketException_h SocketException_h
    #include "SocketException.h"
#endif

using namespace std;

ClientSocket* LCDconnect(int Display);

void LCDwrite(ClientSocket* client_socket, int Zeile, string Text);

void LCDclear(ClientSocket* client_socket);

