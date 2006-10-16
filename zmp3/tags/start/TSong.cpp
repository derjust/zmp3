#include "TSong.h"

TSong::TSong(QString fileName) {
	this->fileName = fileName;
	ID3_Tag myTag( this->fileName.toLatin1() );
 	this->artist = ID3_GetArtist(&myTag);
	this->title = ID3_GetTitle(&myTag);
	
	if (this->artis.isEmpty()) {
		this->artist = this->fileName;
	}
}

QString TSong::getFileName() {
	return this->fileName;
}

QString TSong::getTitle() {
	return this->title;
}

QString TSong::getArtist() {
	return this->artist;
}
