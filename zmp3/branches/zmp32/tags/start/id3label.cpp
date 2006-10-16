#include "id3label.h"

string ID3Song(string Datei)
{
ID3_Frame *myFrame = NULL;
string Label;
ID3_Tag myTag(Datei.c_str() );
char title[ 512 ];
memset(title, 0x0, 512);

if ( myFrame = myTag.Find ( ID3FID_TITLE ) )
{
	myFrame->Field ( ID3FN_TEXT ).Get ( title, 512 );
	Label = title;
}
if (Label.length() == 0) 
{
	Label = Datei;
}
return Label; 
}

string ID3Artist(string Datei)
{
ID3_Frame *myFrame = NULL;
string Label;
ID3_Tag myTag(Datei.c_str() );
char artist [512];
memset(artist, 0x0, 512);

if (myFrame = myTag.Find ( ID3FID_LEADARTIST ) ) 
{
	myFrame->Field ( ID3FN_TEXT).Get (artist, 512);
	Label = artist;
}
if (Label.length() == 0) 
{
	Label = Datei;
}
return Label; 
}

