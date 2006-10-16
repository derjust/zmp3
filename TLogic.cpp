#include "TLogic.h"

TLogic::TLogic() : QObject() {
	QString basePath = "/media/musik/giFT/completed/";
	myLCDController = new TLCDController();
	mySoundSystem = new TSoundSystem();
	myPushButtonSystem = new TPushButtonSystem();

	QStringList musicFiles =QDir(basePath,"*.mp3 *.MP3 *.ogg *.OGG", QDir::Name, QDir::Files | QDir::Readable ).entryList();

	QStringListIterator i(musicFiles);
	while (i.hasNext()) {
		allSongs << TSong( basePath +  i.next() );
	}
}
