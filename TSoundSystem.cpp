#include "TSoundSystem.h"

TSoundSystem::TSoundSystem() : QThread() {
	i = new QListIterator<TSong>(songList);
	FMOD_RESULT result;
	result = FMOD::System_Create(&system);
	system->setPluginPath("plugins/");
	if (result != FMOD_OK)
	{
		qFatal("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
	}
	result = system->init(2, FMOD_INIT_NORMAL, 0);
	if (result != FMOD_OK)
	{
		qFatal("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
	}

	this->start();
}

void TSoundSystem::appendSong(TSong aSong) {
	songList << aSong;
}

void TSoundSystem::clearSongList() {
	songList.clear();
}

void TSoundSystem::run() {
	QString fileName;
	FMOD::Sound *sound;
	FMOD::Channel *channel1=0;
	FMOD::Channel *channel2=0;
	bool channel1IsPlaying = false;
	bool channel2IsPlaying = false;
	while(true) {
		if (channel1) 
			channel1->isPlaying(&channel1IsPlaying);
		if (channel2)
			channel2->isPlaying(&channel2IsPlaying);
		if (!channel2IsPlaying) {
			if (i->hasNext()) {
				TSong curSong = i->next();
				fileName = curSong.getFileName();
				system->createStream(fileName.toLatin1().constData(), FMOD_DEFAULT, 0, &sound);
				system->playSound(FMOD_CHANNEL_FREE, sound, false, &channel1);	
			}
		}
		usleep(500000);
	}
}
