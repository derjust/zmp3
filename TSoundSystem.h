#include <QThread>
#include <QList>

#include <fmod.hpp>
#include <fmod_errors.h>

#include "TSong.h"

class TSoundSystem : QThread {
   private:
	QList<TSong> songList;
	QListIterator<TSong>* i;

	FMOD::System *system;

	void run();
   public:
	TSoundSystem();
	void appendSong(TSong aSong);
	void clearSongList();

   public slots:

};
