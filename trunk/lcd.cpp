/********************************************************
 *		Funktionen der LCD-Funktionen		*
 *							*
 *				by Sebastian Just	*
 * 27.06.2004 letzte Änderung				*
 ********************************************************
*/

#include "lcd.h"

using namespace std;

ClientSocket* LCDconnect(int Display=0)
{
cout << "LCD             ";
ClientSocket* client_socket; 
client_socket = new ClientSocket( "127.0.0.1", (13666+Display) );
string reply;
*client_socket << "hello\r\n";
*client_socket << "client_set name zmp3\r\n";
*client_socket << "screen_add 0\r\n";
*client_socket << "screen_set 0 heartbeat off\r\n";
*client_socket << "widget_add 0 0 string\r\n";
*client_socket << "widget_add 0 1 string\r\n";
*client_socket << "widget_add 0 2 string\r\n";
*client_socket << "widget_add 0 3 string\r\n";

*client_socket << "widget_set 0 0 1 1 \"*****   zmp3   *****\"\r\n";
*client_socket << "widget_set 0 1 1 2 \"*       v. 2       *\"\r\n";
*client_socket << "widget_set 0 2 1 3 \"*by  Sebastian Just*\"\r\n";
*client_socket << "widget_set 0 3 1 4 \"********************\"\r\n";

cout << "[OK]" << endl;
return client_socket;
}

void LCDclear(ClientSocket* client_socket)
{
*client_socket << "widget_set 0 0 1 1 \"                    \"\r\n";
*client_socket << "widget_set 0 1 1 2 \"                    \"\r\n";
*client_socket << "widget_set 0 2 1 3 \"                    \"\r\n";
*client_socket << "widget_set 0 3 1 4 \"                    \"\r\n";
}

void LCDwrite(ClientSocket* client_socket, int Zeile, string Text)
{
switch(Zeile)
{
case 0:
*client_socket << "widget_set 0 0 1 1 \"" << Text <<"\"\r\n";

break;
case 1:
*client_socket << "widget_set 0 1 1 2 \"" << Text <<"\"\r\n";

break;
case 2:
*client_socket << "widget_set 0 2 1 3 \"" << Text <<"\"\r\n";

break;
case 3:
*client_socket << "widget_set 0 3 1 4 \"" << Text <<"\"\r\n";

break;
}
}
